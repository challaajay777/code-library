// Algorithm: Pollard's Rho Algorithm (Brent's Cycle Detection)
// Supports: Fast prime factorization for 64-bit integers in O(n^(1/4))
// Indexing: Positive integers up to 2^62
// Complexity: O(n^(1/4)) expected time per factor, O(1) memory
// Preconditions: Integrated with deterministic Miller-Rabin test

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

struct PollardsRho {
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

    static unsigned long long gcd(unsigned long long a, unsigned long long b) {
        while (b) {
            a %= b;
            swap(a, b);
        }
        return a;
    }

    // Brent's cycle detection variant of Pollard's Rho
    static unsigned long long find_factor(unsigned long long n) {
        if (n % 2 == 0) return 2;
        if (is_prime(n)) return n;

        static mt19937_64 rng(1337);
        unsigned long long c = uniform_int_distribution<unsigned long long>(1, n - 1)(rng);
        unsigned long long y = uniform_int_distribution<unsigned long long>(1, n - 1)(rng);
        unsigned long long m = 128;
        unsigned long long g = 1, r = 1, q = 1, ys = 0, x = 0;

        auto f = [&](unsigned long long val) -> unsigned long long {
            return (unsigned long long)(((__int128)val * val + c) % n);
        };

        while (g == 1) {
            x = y;
            for (unsigned long long i = 0; i < r; ++i) y = f(y);
            unsigned long long k = 0;
            while (k < r && g == 1) {
                ys = y;
                for (unsigned long long i = 0; i < min(m, r - k); ++i) {
                    y = f(y);
                    unsigned long long diff = (x > y) ? (x - y) : (y - x);
                    q = (unsigned long long)((__int128)q * diff % n);
                }
                g = gcd(q, n);
                k += m;
            }
            r <<= 1;
        }

        if (g == n) {
            do {
                ys = f(ys);
                unsigned long long diff = (x > ys) ? (x - ys) : (ys - x);
                g = gcd(diff, n);
            } while (g == 1);
        }
        return (g == n) ? find_factor(n) : g;
    }

    // Returns sorted list of all prime factors of n
    static vector<unsigned long long> factorize(unsigned long long n) {
        if (n <= 1) return {};
        vector<unsigned long long> factors;
        auto dfs = [&](auto& self, unsigned long long cur) -> void {
            if (cur == 1) return;
            if (is_prime(cur)) {
                factors.push_back(cur);
                return;
            }
            unsigned long long factor = find_factor(cur);
            self(self, factor);
            self(self, cur / factor);
        };
        dfs(dfs, n);
        sort(factors.begin(), factors.end());
        return factors;
    }
};
