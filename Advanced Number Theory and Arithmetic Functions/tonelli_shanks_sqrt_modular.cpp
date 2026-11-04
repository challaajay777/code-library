#include <iostream>
#include <cassert>

// Algorithm: Hensel's Lemma for Polynomial Roots Modulo Prime Powers
// Purpose: Lifts roots of polynomial f(x) = 0 (mod p) to roots modulo p^k using Hensel's lifting in O(k * deg).
// Time Complexity: O(k) steps
// Space Complexity: O(1) space
// Preconditions: f'(r) != 0 (mod p).

class HenselLifting {
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

public:
    // Lifts root of x^2 = a (mod p) to root modulo p^k
    static long long lift_sqrt(long long a, long long r0, long long p, int k) {
        long long r = r0;
        long long pk = p;

        for (int i = 1; i < k; ++i) {
            long long f_r = (r * r - a) / pk;
            long long f_prime = (2 * r) % p;
            long long inv = power(f_prime, p - 2, p);
            long long t = (-f_r % p + p) % p * inv % p;
            r += t * pk;
            pk *= p;
        }
        return r;
    }
};

int main() {
    // x^2 = 2 mod 7. r0 = 3 (3^2 = 9 = 2 mod 7).
    // Lift to mod 7^2 = 49:
    long long r = HenselLifting::lift_sqrt(2, 3, 7, 2);
    assert((r * r) % 49 == 2);

    std::cout << "tonelli_shanks_sqrt_modular tests passed successfully.\n";
    return 0;
}
