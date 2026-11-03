// Algorithm: Euler's Linear Sieve (SPF)
// Supports: Exactly O(N) prime generation, smallest prime factor (SPF), O(log x) factorization
// Indexing: 0-based integer numbers [0, N]
// Complexity: O(N) preprocessing, O(log x) factorization per number
// Preconditions: N >= 2

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

struct LinearSieve {
    int n;
    vector<int> spf; // smallest prime factor
    vector<int> primes;

    explicit LinearSieve(int n) : n(n), spf(n + 1, 0) {
        for (int i = 2; i <= n; ++i) {
            if (spf[i] == 0) {
                spf[i] = i;
                primes.push_back(i);
            }
            for (int p : primes) {
                if (p > spf[i] || 1LL * i * p > n) break;
                spf[i * p] = p;
            }
        }
    }

    // Factorizes x in O(log x) time: returns list of {prime, exponent}
    vector<pair<int, int>> factorize(int x) const {
        assert(1 <= x && x <= n);
        vector<pair<int, int>> factors;
        while (x > 1) {
            int p = spf[x];
            int count = 0;
            while (x % p == 0) {
                count++;
                x /= p;
            }
            factors.push_back({p, count});
        }
        return factors;
    }
};
