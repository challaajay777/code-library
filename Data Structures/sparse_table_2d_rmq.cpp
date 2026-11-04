// Algorithm: 2D Sparse Table for Rectangular RMQ
// Purpose: Queries minimum element in subgrid [r1..r2, c1..c2] in strict O(1) time.
// Time Complexity: O(R * C * log R * log C) build, O(1) query
// Space Complexity: O(R * C * log R * log C)
// Preconditions: 2D matrix of comparable values.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

struct SparseTable2D {
    int R, C;
    std::vector<int> lg;
    std::vector<std::vector<std::vector<std::vector<int>>>> st;

    SparseTable2D(const std::vector<std::vector<int>>& mat) {
        R = mat.size();
        C = mat[0].size();
        int max_dim = std::max(R, C);
        lg.assign(max_dim + 1, 0);
        for (int i = 2; i <= max_dim; ++i) lg[i] = lg[i / 2] + 1;

        int kr = lg[R] + 1, kc = lg[C] + 1;
        st.assign(kr, std::vector<std::vector<std::vector<int>>>(kc,
            std::vector<std::vector<int>>(R, std::vector<int>(C))));

        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) st[0][0][i][j] = mat[i][j];
        }

        for (int jr = 0; jr < kr; ++jr) {
            for (int jc = 0; jc < kc; ++jc) {
                if (jr == 0 && jc == 0) continue;
                for (int i = 0; i + (1 << jr) <= R; ++i) {
                    for (int j = 0; j + (1 << jc) <= C; ++j) {
                        if (jc > 0) {
                            st[jr][jc][i][j] = std::min(st[jr][jc - 1][i][j],
                                                        st[jr][jc - 1][i][j + (1 << (jc - 1))]);
                        } else {
                            st[jr][jc][i][j] = std::min(st[jr - 1][jc][i][j],
                                                        st[jr - 1][jc][i + (1 << (jr - 1))][j]);
                        }
                    }
                }
            }
        }
    }

    int query(int r1, int c1, int r2, int c2) {
        int kr = lg[r2 - r1 + 1], kc = lg[c2 - c1 + 1];
        int m1 = st[kr][kc][r1][c1];
        int m2 = st[kr][kc][r2 - (1 << kr) + 1][c1];
        int m3 = st[kr][kc][r1][c2 - (1 << kc) + 1];
        int m4 = st[kr][kc][r2 - (1 << kr) + 1][c2 - (1 << kc) + 1];
        return std::min({m1, m2, m3, m4});
    }
};

int main() {
    std::vector<std::vector<int>> mat = {
        {10, 20, 30},
        {5,  15, 25},
        {40, 50, 60}
    };
    SparseTable2D st2(mat);
    assert(st2.query(0, 0, 1, 1) == 5);
    return 0;
}
