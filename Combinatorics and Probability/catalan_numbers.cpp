// Algorithm: Catalan Numbers
// Supports: Precomputed Catalan numbers C_n modulo prime MOD
// Indexing: 0-based index n [0, N] (C_0 = 1, C_1 = 1, C_2 = 2, C_3 = 5, C_4 = 14)
// Complexity: O(N) precomputation, O(1) query, O(N) memory
// Preconditions: MOD is a prime > 2 * N

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

template <int MOD = 1000000007>
struct CatalanNumbers {
    int max_n;
    vector<int> cat;

    explicit CatalanNumbers(int n) : max_n(n), cat(n + 1) {
        cat[0] = 1;
        vector<int> inv(2 * n + 2, 1);
        for (int i = 2; i <= 2 * n + 1; ++i) {
            inv[i] = (int)(1LL * (MOD - MOD / i) * inv[MOD % i] % MOD);
        }
        for (int i = 0; i < n; ++i) {
            // C_{i+1} = C_i * 2 * (2*i + 1) / (i + 2)
            long long num = (2LL * (2 * i + 1)) % MOD;
            long long den = inv[i + 2];
            cat[i + 1] = (int)(1LL * cat[i] * num % MOD * den % MOD);
        }
    }

    int get(int n) const {
        assert(0 <= n && n <= max_n);
        return cat[n];
    }
};
