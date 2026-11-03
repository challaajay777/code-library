// Algorithm: 2D Fenwick Tree
// Supports: Point addition, 2D rectangular subgrid sum queries
// Indexing: 1-based indexing for coordinates (r, c)
// Complexity: O(log R * log C) per update and query, O(R * C) memory
// Preconditions: 1 <= r <= R and 1 <= c <= C

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

template <typename T>
struct FenwickTree2D {
    int rows, cols;
    vector<vector<T>> tree;

    FenwickTree2D(int r, int c) : rows(r), cols(c), tree(r + 1, vector<T>(c + 1, 0)) {}

    // Add val to cell (r, c)
    void add(int r, int c, T val) {
        assert(1 <= r && r <= rows);
        assert(1 <= c && c <= cols);
        for (int i = r; i <= rows; i += i & -i) {
            for (int j = c; j <= cols; j += j & -j) {
                tree[i][j] += val;
            }
        }
    }

    // Prefix sum of subgrid [1..r] x [1..c]
    T query(int r, int c) const {
        assert(0 <= r && r <= rows);
        assert(0 <= c && c <= cols);
        T sum = 0;
        for (int i = r; i > 0; i -= i & -i) {
            for (int j = c; j > 0; j -= j & -j) {
                sum += tree[i][j];
            }
        }
        return sum;
    }

    // Rectangular subgrid sum in [r1..r2] x [c1..c2] inclusive
    T query(int r1, int c1, int r2, int c2) const {
        if (r1 > r2 || c1 > c2) return 0;
        assert(1 <= r1 && r2 <= rows);
        assert(1 <= c1 && c2 <= cols);
        return query(r2, c2) - query(r1 - 1, c2) - query(r2, c1 - 1) + query(r1 - 1, c1 - 1);
    }
};
