// Algorithm: Sparse Table (RMQ)
// Supports: Static Range Minimum / Maximum Query in O(1)
// Indexing: 0-based indices [l, r]
// Complexity: O(n log n) preprocessing, O(1) per range query, O(n log n) memory
// Preconditions: Operation is associative and idempotent (f(x, x) = x, e.g. min, max, gcd)

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

template <typename T, typename Op = less<T>>
struct SparseTable {
    int n, K;
    vector<vector<T>> table;
    vector<int> lg;
    Op cmp;

    explicit SparseTable(const vector<T>& a, Op cmp = Op()) : n((int)a.size()), cmp(cmp) {
        if (n == 0) return;
        lg.assign(n + 1, 0);
        for (int i = 2; i <= n; ++i) lg[i] = lg[i / 2] + 1;
        K = lg[n] + 1;

        table.assign(K, vector<T>(n));
        table[0] = a;

        for (int j = 1; j < K; ++j) {
            for (int i = 0; i + (1 << j) <= n; ++i) {
                const T& left = table[j - 1][i];
                const T& right = table[j - 1][i + (1 << (j - 1))];
                table[j][i] = cmp(left, right) ? left : right;
            }
        }
    }

    // Queries range [l, r] inclusive in O(1)
    T query(int l, int r) const {
        assert(0 <= l && l <= r && r < n);
        int j = lg[r - l + 1];
        const T& left = table[j][l];
        const T& right = table[j][r - (1 << j) + 1];
        return cmp(left, right) ? left : right;
    }
};
