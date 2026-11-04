#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Generalized Lucas Theorem (Prime Powers p^k)
// Purpose: Calculates Binomial Coefficient C(N, K) modulo prime power p^k using Granville's formula in O(p^k log N).
// Time Complexity: O(p^k + log_p N) time
// Space Complexity: O(p^k) space
// Preconditions: p is prime, k >= 1.

class GeneralizedLucas {
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

    static long long ext_gcd(long long a, long long b, long long& x, long long& y) {
        if (b == 0) { x = 1; y = 0; return a; }
        long long x1, y1;
        long long d = ext_gcd(b, a % b, x1, y1);
        x = y1;
        y = x1 - y1 * (a / b);
        return d;
    }

    static long long mod_inv(long long a, long long m) {
        long long x, y;
        ext_gcd(a, m, x, y);
        return (x % m + m) % m;
    }

    // Computes N! / (p^e) mod p^k
    static long long fact_mod(long long n, long long p, long long pk) {
        if (n == 0) return 1;
        long long res = 1;
        for (long long i = 1; i <= pk; ++i) {
            if (i % p != 0) res = (res * i) % pk;
        }
        res = power(res, n / pk, pk);
        for (long long i = 1; i <= n % pk; ++i) {
            if (i % p != 0) res = (res * i) % pk;
        }
        return (res * fact_mod(n / p, p, pk)) % pk;
    }

public:
    static long long ncr_pk(long long n, long long r, long long p, int k) {
        if (r < 0 || r > n) return 0;
        long long pk = 1;
        for (int i = 0; i < k; ++i) pk *= p;

        // Count factor of p in C(n, r)
        long long e = 0;
        for (long long i = n; i > 0; i /= p) e += i / p;
        for (long long i = r; i > 0; i /= p) e -= i / p;
        for (long long i = n - r; i > 0; i /= p) e -= i / p;

        if (e >= k) return 0;

        long long num = fact_mod(n, p, pk);
        long long den = (fact_mod(r, p, pk) * fact_mod(n - r, p, pk)) % pk;
        long long ans = (num * mod_inv(den, pk)) % pk;
        ans = (ans * power(p, e, pk)) % pk;
        return ans;
    }
};

int main() {
    // C(10, 2) = 45. Modulo 4 (2^2) = 1.
    assert(GeneralizedLucas::ncr_pk(10, 2, 2, 2) == 1);
    // C(10, 2) = 45. Modulo 9 (3^2) = 0.
    assert(GeneralizedLucas::ncr_pk(10, 2, 3, 2) == 0);

    std::cout << "lucas_theorem_generalized tests passed successfully.\n";
    return 0;
}
