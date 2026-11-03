// Algorithm: Derangements (Subfactorials)
// Supports: Number of fixed-point free permutations !n modulo prime MOD
// Indexing: 0-based integer n [0, N] (D_0 = 1, D_1 = 0, D_2 = 1, D_3 = 2, D_4 = 9)
// Complexity: O(N) precomputation, O(1) query, O(N) memory
// Preconditions: Modulo MOD is prime

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

template <int MOD = 1000000007>
struct Derangements {
    int max_n;
    vector<int> d;

    explicit Derangements(int n) : max_n(n), d(n + 1) {
        if (n >= 0) d[0] = 1;
        if (n >= 1) d[1] = 0;
        for (int i = 2; i <= n; ++i) {
            d[i] = (int)(1LL * (i - 1) * (d[i - 1] + d[i - 2]) % MOD);
        }
    }

    int get(int n) const {
        assert(0 <= n && n <= max_n);
        return d[n];
    }
};
