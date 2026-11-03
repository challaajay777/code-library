// Algorithm: 2D Prefix Sums
// Supports: Static 2D rectangular subgrid sum queries in O(1)
// Indexing: 0-based input grid (r, c), 1-based internal prefix table
// Complexity: O(R * C) preprocessing, O(1) per query, O(R * C) space
// Preconditions: 0 <= r1 <= r2 < R and 0 <= c1 <= c2 < C

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

template <typename T>
struct PrefixSums2D {
    int rows, cols;
    vector<vector<T>> pref;

    PrefixSums2D() : rows(0), cols(0) {}
    explicit PrefixSums2D(const vector<vector<T>>& grid) {
        rows = (int)grid.size();
        cols = rows ? (int)grid[0].size() : 0;
        pref.assign(rows + 1, vector<T>(cols + 1, 0));
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                pref[r + 1][c + 1] = grid[r][c] + pref[r][c + 1] + pref[r + 1][c] - pref[r][c];
            }
        }
    }

    // Returns sum in rectangle [r1..r2] x [c1..c2] inclusive
    T query(int r1, int c1, int r2, int c2) const {
        assert(0 <= r1 && r1 <= r2 && r2 < rows);
        assert(0 <= c1 && c1 <= c2 && c2 < cols);
        return pref[r2 + 1][c2 + 1] - pref[r1][c2 + 1] - pref[r2 + 1][c1] + pref[r1][c1];
    }
};
