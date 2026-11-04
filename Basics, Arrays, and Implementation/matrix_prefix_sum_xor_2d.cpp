#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: 2D Matrix Prefix XOR
// Purpose: Calculates 2D subgrid XOR sums in O(1) time after O(R * C) preprocessing.
// Time Complexity: O(R * C) preprocessing, O(1) per range query
// Space Complexity: O(R * C) auxiliary space
// Preconditions: 0 <= r1 <= r2 < R, 0 <= c1 <= c2 < C.

class PrefixXor2D {
private:
    int R, C;
    std::vector<std::vector<long long>> px;

public:
    PrefixXor2D(const std::vector<std::vector<long long>>& mat) {
        R = mat.size();
        C = (R > 0 ? mat[0].size() : 0);
        px.assign(R + 1, std::vector<long long>(C + 1, 0));

        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                px[i + 1][j + 1] = mat[i][j] ^ px[i][j + 1] ^ px[i + 1][j] ^ px[i][j];
            }
        }
    }

    long long query(int r1, int c1, int r2, int c2) const {
        assert(r1 >= 0 && r1 <= r2 && r2 < R);
        assert(c1 >= 0 && c1 <= c2 && c2 < C);
        return px[r2 + 1][c2 + 1] ^ px[r1][c2 + 1] ^ px[r2 + 1][c1] ^ px[r1][c1];
    }
};

int main() {
    std::vector<std::vector<long long>> mat = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    PrefixXor2D px2(mat);

    assert(px2.query(0, 0, 0, 0) == 1);
    assert(px2.query(0, 0, 1, 1) == (1 ^ 2 ^ 4 ^ 5));
    assert(px2.query(1, 1, 2, 2) == (5 ^ 6 ^ 8 ^ 9));

    std::cout << "matrix_prefix_sum_xor_2d tests passed successfully.\n";
    return 0;
}
