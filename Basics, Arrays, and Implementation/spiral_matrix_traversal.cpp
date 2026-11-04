#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Spiral Matrix Traversal and Generation
// Purpose: Traverses an R x C matrix in spiral order or constructs an N x N matrix filled with 1 to N^2 in spiral order.
// Time Complexity: O(R * C) time
// Space Complexity: O(1) auxiliary space beyond result vector
// Preconditions: R, C >= 1.

class SpiralMatrix {
public:
    template <typename T>
    static std::vector<T> traverse(const std::vector<std::vector<T>>& mat) {
        if (mat.empty() || mat[0].empty()) return {};
        int top = 0, bottom = mat.size() - 1;
        int left = 0, right = mat[0].size() - 1;
        std::vector<T> order;

        while (top <= bottom && left <= right) {
            for (int j = left; j <= right; ++j) order.push_back(mat[top][j]);
            top++;
            for (int i = top; i <= bottom; ++i) order.push_back(mat[i][right]);
            right--;
            if (top <= bottom) {
                for (int j = right; j >= left; --j) order.push_back(mat[bottom][j]);
                bottom--;
            }
            if (left <= right) {
                for (int i = bottom; i >= top; --i) order.push_back(mat[i][left]);
                left++;
            }
        }
        return order;
    }

    static std::vector<std::vector<int>> generate(int n) {
        std::vector<std::vector<int>> mat(n, std::vector<int>(n, 0));
        int top = 0, bottom = n - 1, left = 0, right = n - 1;
        int val = 1;

        while (top <= bottom && left <= right) {
            for (int j = left; j <= right; ++j) mat[top][j] = val++;
            top++;
            for (int i = top; i <= bottom; ++i) mat[i][right] = val++;
            right--;
            if (top <= bottom) {
                for (int j = right; j >= left; --j) mat[bottom][j] = val++;
                bottom--;
            }
            if (left <= right) {
                for (int i = bottom; i >= top; --i) mat[i][left] = val++;
                left++;
            }
        }
        return mat;
    }
};

int main() {
    std::vector<std::vector<int>> mat = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    auto spiral = SpiralMatrix::traverse(mat);
    std::vector<int> expected = {1, 2, 3, 6, 9, 8, 7, 4, 5};
    assert(spiral == expected);

    auto gen = SpiralMatrix::generate(3);
    assert(gen == mat);

    std::cout << "spiral_matrix_traversal tests passed successfully.\n";
    return 0;
}
