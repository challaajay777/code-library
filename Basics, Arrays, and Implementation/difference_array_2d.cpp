// Algorithm: 2D Difference Array
// Supports: O(1) subgrid additions, O(R * C) full grid restoration
// Indexing: 0-based grid indices
// Complexity: O(1) per subgrid addition, O(R * C) restoration, O(R * C) space
// Preconditions: 0 <= r1 <= r2 < R and 0 <= c1 <= c2 < C

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

template <typename T>
struct DifferenceArray2D {
    int rows, cols;
    vector<vector<T>> diff;

    DifferenceArray2D(int r, int c) : rows(r), cols(c), diff(r + 2, vector<T>(c + 2, 0)) {}

    // Add val to rectangular subgrid [r1..r2] x [c1..c2] inclusive
    void add_rect(int r1, int c1, int r2, int c2, T val) {
        assert(0 <= r1 && r1 <= r2 && r2 < rows);
        assert(0 <= c1 && c1 <= c2 && c2 < cols);
        diff[r1][c1] += val;
        diff[r1][c2 + 1] -= val;
        diff[r2 + 1][c1] -= val;
        diff[r2 + 1][c2 + 1] += val;
    }

    // Reconstruct the 2D grid after applying all additions
    vector<vector<T>> build() const {
        vector<vector<T>> res(rows, vector<T>(cols, 0));
        vector<vector<T>> cur = diff;
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                T up = (r > 0) ? cur[r - 1][c] : 0;
                T left = (c > 0) ? cur[r][c - 1] : 0;
                T diag = (r > 0 && c > 0) ? cur[r - 1][c - 1] : 0;
                cur[r][c] += up + left - diag;
                res[r][c] = cur[r][c];
            }
        }
        return res;
    }
};
