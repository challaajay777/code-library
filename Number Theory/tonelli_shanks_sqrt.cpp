#include <iostream>
#include <cassert>

// Algorithm: Tonelli-Shanks Algorithm (Modular Square Root)
// Purpose: Solves congruence x^2 = n (mod p) for odd prime p in expected O(log^2 p) time.
// Time Complexity: O(log^2 p) expected time
// Space Complexity: O(1) auxiliary space
// Preconditions: p is an odd prime; n is a quadratic residue modulo p.

class TonelliShanks {
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

public:
    static long long sqrt_mod(long long n, long long p) {
        n %= p;
        if (n == 0) return 0;
        if (p == 2) return n;
        if (power(n, (p - 1) / 2, p) != 1) return -1; // Not a quadratic residue

        // Express p - 1 = Q * 2^S with Q odd
        long long Q = p - 1;
        long long S = 0;
        while (Q % 2 == 0) {
            Q /= 2;
            S++;
        }

        // Find non-residue z
        long long z = 2;
        while (power(z, (p - 1) / 2, p) == 1) z++;

        long long M = S;
        long long c = power(z, Q, p);
        long long t = power(n, Q, p);
        long long R = power(n, (Q + 1) / 2, p);

        while (t != 1) {
            long long cur = t;
            long long i = 0;
            for (i = 1; i < M; ++i) {
                cur = (__int128)cur * cur % p;
                if (cur == 1) break;
            }

            long long b = power(c, 1LL << (M - i - 1), p);
            M = i;
            c = (__int128)b * b % p;
            t = (__int128)t * c % p;
            R = (__int128)R * b % p;
        }
        return R;
    }
};

int main() {
    long long r = TonelliShanks::sqrt_mod(10, 13);
    assert(r != -1);
    assert((r * r) % 13 == 10);

    long long r2 = TonelliShanks::sqrt_mod(5, 41);
    assert(r2 != -1);
    assert((r2 * r2) % 41 == 5);

    std::cout << "tonelli_shanks_sqrt tests passed successfully.\n";
    return 0;
}
