// Algorithm: Modular Combinatorics (Factorials and nCr)
// Supports: Precomputed factorials, inverse factorials, nCr, nPr under prime modulo
// Indexing: 0-based integers [0, N]
// Complexity: O(N) precomputation, O(1) per nCr query, O(N) memory
// Preconditions: Modulo MOD is prime; 0 <= r <= n <= N

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

template <int MOD = 1000000007>
struct Combinatorics {
    int max_n;
    vector<int> fact, inv_fact, inv;

    explicit Combinatorics(int n) : max_n(n), fact(n + 1), inv_fact(n + 1), inv(n + 1) {
        fact[0] = inv_fact[0] = 1;
        inv[1] = 1;
        for (int i = 2; i <= n; ++i) {
            inv[i] = (int)(1LL * (MOD - MOD / i) * inv[MOD % i] % MOD);
        }
        for (int i = 1; i <= n; ++i) {
            fact[i] = (int)(1LL * fact[i - 1] * i % MOD);
            inv_fact[i] = (int)(1LL * inv_fact[i - 1] * inv[i] % MOD);
        }
    }

    int nCr(int n, int r) const {
        if (r < 0 || r > n || n > max_n) return 0;
        return (int)(1LL * fact[n] * inv_fact[r] % MOD * inv_fact[n - r] % MOD);
    }

    int nPr(int n, int r) const {
        if (r < 0 || r > n || n > max_n) return 0;
        return (int)(1LL * fact[n] * inv_fact[n - r] % MOD);
    }

    // Stars and bars: number of ways to put n identical items into k distinct bins (bins can be empty)
    int stars_and_bars(int n, int k) const {
        if (n == 0 && k == 0) return 1;
        if (k <= 0) return 0;
        return nCr(n + k - 1, k - 1);
    }
};
