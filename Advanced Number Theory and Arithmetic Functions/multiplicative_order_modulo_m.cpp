#include <iostream>
#include <numeric>
#include <cassert>

// Algorithm: Multiplicative Order Modulo M
// Purpose: Finds smallest positive integer k such that a^k = 1 (mod m) in O(sqrt(phi(m))) time.
// Time Complexity: O(sqrt(phi(m))) time
// Space Complexity: O(1) auxiliary space
// Preconditions: gcd(a, m) = 1; m >= 1.

class MultiplicativeOrder {
private:
    static long long power(long long base, long long exp, long long mod) {
        long long res = 1;
        base %= mod;
        while (exp > 0) {
            if (exp & 1) res = (__int128)res * base % mod;
            base = (__int128)base * base % mod;
            exp >>= 1;
        }
        return res;
    }

    static long long phi(long long n) {
        long long res = n;
        for (long long p = 2; p * p <= n; ++p) {
            if (n % p == 0) {
                while (n % p == 0) n /= p;
                res -= res / p;
            }
        }
        if (n > 1) res -= res / n;
        return res;
    }

public:
    static long long get_order(long long a, long long m) {
        if (std::gcd(a, m) != 1) return -1;
        long long totient = phi(m);
        long long min_ord = totient;

        for (long long d = 1; d * d <= totient; ++d) {
            if (totient % d == 0) {
                if (power(a, d, m) == 1) return d;
                if (power(a, totient / d, m) == 1) {
                    min_ord = std::min(min_ord, totient / d);
                }
            }
        }
        return min_ord;
    }
};

int main() {
    assert(MultiplicativeOrder::get_order(2, 7) == 3); // 2^3 = 8 = 1 mod 7
    assert(MultiplicativeOrder::get_order(3, 7) == 6);

    std::cout << "multiplicative_order_modulo_m tests passed successfully.\n";
    return 0;
}
