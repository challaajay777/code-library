#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Diagonal Matrix Traversal
// Purpose: Traverses an R x C matrix diagonally (anti-diagonals where i + j is constant) in zigzag or uniform order.
// Time Complexity: O(R * C) time
// Space Complexity: O(1) auxiliary space beyond result vector
// Preconditions: Non-empty 2D matrix.

class DiagonalMatrixTraversal {
public:
    template <typename T>
    static std::vector<T> traverse_zigzag(const std::vector<std::vector<T>>& mat) {
        if (mat.empty() || mat[0].empty()) return {};
        int r = mat.size(), c = mat[0].size();
        std::vector<T> result;
        result.reserve(r * c);

        for (int diag = 0; diag < r + c - 1; ++diag) {
            if (diag % 2 == 0) {
                // Traverse upwards
                int row = std::min(diag, r - 1);
                int col = diag - row;
                while (row >= 0 && col < c) {
                    result.push_back(mat[row][col]);
                    row--;
                    col++;
                }
            } else {
                // Traverse downwards
                int col = std::min(diag, c - 1);
                int row = diag - col;
                while (col >= 0 && row < r) {
                    result.push_back(mat[row][col]);
                    row++;
                    col--;
                }
            }
        }
        return result;
    }
};

int main() {
    std::vector<std::vector<int>> mat = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    auto diag = DiagonalMatrixTraversal::traverse_zigzag(mat);
    std::vector<int> expected = {1, 2, 4, 7, 5, 3, 6, 8, 9};
    assert(diag == expected);

    std::cout << "diagonal_matrix_traversal tests passed successfully.\n";
    return 0;
}
