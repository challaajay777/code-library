#include <iostream>
#include <cassert>

// Algorithm: Narayana Numbers
// Purpose: Computes N(n, k) = (1/n) * C(n, k) * C(n, k-1) counting Dyck paths of length 2n with exactly k peaks in O(n).
// Time Complexity: O(N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: 1 <= k <= n.

class NarayanaNumbers {
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

    static long long ncr(long long n, long long r, long long mod) {
        if (r < 0 || r > n) return 0;
        if (r == 0 || r == n) return 1;
        long long num = 1, den = 1;
        for (long long i = 0; i < r; ++i) {
            num = (num * (n - i)) % mod;
            den = (den * (i + 1)) % mod;
        }
        return (num * power(den, mod - 2, mod)) % mod;
    }

public:
    static long long get_narayana(long long n, long long k, long long mod = 1e9 + 7) {
        if (k < 1 || k > n) return 0;
        long long c1 = ncr(n, k, mod);
        long long c2 = ncr(n, k - 1, mod);
        long long inv_n = power(n, mod - 2, mod);
        return (c1 * c2 % mod * inv_n) % mod;
    }
};

int main() {
    // For n=3:
    // N(3, 1) = 1
    // N(3, 2) = 3
    // N(3, 3) = 1
    // Sum = Catalan(3) = 5
    assert(NarayanaNumbers::get_narayana(3, 1) == 1);
    assert(NarayanaNumbers::get_narayana(3, 2) == 3);
    assert(NarayanaNumbers::get_narayana(3, 3) == 1);

    std::cout << "narayana_numbers tests passed successfully.\n";
    return 0;
}
