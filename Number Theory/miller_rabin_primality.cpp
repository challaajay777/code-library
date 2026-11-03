// Algorithm: Miller-Rabin Primality Test
// Supports: Deterministic primality testing for all 64-bit integers
// Indexing: 64-bit unsigned integers [0, 2^64 - 1]
// Complexity: O(k log n) where k is 12 deterministic test bases, < 1 microsecond per query
// Preconditions: Uses __int128 for overflow-safe modular multiplication

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

struct MillerRabin {
    static unsigned long long power_mod(unsigned long long base, unsigned long long exp, unsigned long long mod) {
        unsigned long long res = 1;
        base %= mod;
        while (exp > 0) {
            if (exp & 1) res = (unsigned long long)((__int128)res * base % mod);
            base = (unsigned long long)((__int128)base * base % mod);
            exp >>= 1;
        }
        return res;
    }

    // Deterministic for all numbers < 2^64 using 12 established prime bases
    static bool is_prime(unsigned long long n) {
        if (n < 2) return false;
        if (n == 2 || n == 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;

        unsigned long long d = n - 1;
        int s = 0;
        while ((d & 1) == 0) {
            d >>= 1;
            s++;
        }

        static const unsigned long long bases[] = {
            2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37
        };

        for (unsigned long long a : bases) {
            if (n <= a) break;
            unsigned long long x = power_mod(a, d, n);
            if (x == 1 || x == n - 1) continue;

            bool composite = true;
            for (int r = 1; r < s; ++r) {
                x = (unsigned long long)((__int128)x * x % n);
                if (x == n - 1) {
                    composite = false;
                    break;
                }
            }
            if (composite) return false;
        }
        return true;
    }
};
