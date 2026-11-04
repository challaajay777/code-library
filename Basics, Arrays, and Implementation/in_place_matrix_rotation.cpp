#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: In-Place Matrix Rotation
// Purpose: Rotates an N x N square 2D matrix by 90 degrees clockwise or counter-clockwise in-place using O(1) memory.
// Time Complexity: O(N^2) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Square matrix (N x N).

class InPlaceMatrixRotation {
public:
    template <typename T>
    static void rotate_90_clockwise(std::vector<std::vector<T>>& mat) {
        int n = mat.size();
        // Transpose
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                std::swap(mat[i][j], mat[j][i]);
            }
        }
        // Reverse each row
        for (int i = 0; i < n; ++i) {
            std::reverse(mat[i].begin(), mat[i].end());
        }
    }

    template <typename T>
    static void rotate_90_counter_clockwise(std::vector<std::vector<T>>& mat) {
        int n = mat.size();
        // Transpose
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                std::swap(mat[i][j], mat[j][i]);
            }
        }
        // Reverse each column
        for (int j = 0; j < n; ++j) {
            for (int i = 0; i < n / 2; ++i) {
                std::swap(mat[i][j], mat[n - 1 - i][j]);
            }
        }
    }
};

int main() {
    std::vector<std::vector<int>> mat = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    InPlaceMatrixRotation::rotate_90_clockwise(mat);
    std::vector<std::vector<int>> exp_cw = {
        {7, 4, 1},
        {8, 5, 2},
        {9, 6, 3}
    };
    assert(mat == exp_cw);

    InPlaceMatrixRotation::rotate_90_counter_clockwise(mat);
    std::vector<std::vector<int>> exp_orig = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    assert(mat == exp_orig);

    std::cout << "in_place_matrix_rotation tests passed successfully.\n";
    return 0;
}
