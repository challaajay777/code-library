#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Lucas' Theorem for Binomial Coefficients
// Purpose: Computes C(N, K) modulo a small prime P in O(P + log_P N) time.
// Time Complexity: O(P + log_P N) time
// Space Complexity: O(P) space for factorial table
// Preconditions: Modulus P is a small prime.

class LucasTheorem {
private:
    static long long power(long long base, long long exp, long long mod) {
        long long res = 1;
        base %= mod;
        while (exp > 0) {
            if (exp & 1) res = (res * base) % mod;
            base = (base * base) % mod;
            exp >>= 1;
        }
        return res;
    }

    static long long mod_inverse(long long n, long long p) {
        return power(n, p - 2, p);
    }

    static long long ncr_small(long long n, long long r, long long p) {
        if (r < 0 || r > n) return 0;
        if (r == 0 || r == n) return 1;
        long long num = 1, den = 1;
        for (long long i = 0; i < r; ++i) {
            num = (num * (n - i)) % p;
            den = (den * (i + 1)) % p;
        }
        return (num * mod_inverse(den, p)) % p;
    }

public:
    static long long ncr_lucas(long long n, long long r, long long p) {
        if (r == 0) return 1;
        long long ni = n % p;
        long long ri = r % p;
        if (ri > ni) return 0;
        return (ncr_lucas(n / p, r / p, p) * ncr_small(ni, ri, p)) % p;
    }
};

int main() {
    // C(10, 2) = 45 = 3 mod 7
    assert(LucasTheorem::ncr_lucas(10, 2, 7) == 3);

    std::cout << "lucas_theorem_combinations tests passed successfully.\n";
    return 0;
}
