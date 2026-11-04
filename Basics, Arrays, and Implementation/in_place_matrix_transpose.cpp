#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: In-Place Matrix Transpose
// Purpose: Transposes an N x N matrix in-place by swapping elements across the main diagonal in O(1) auxiliary memory.
// Time Complexity: O(N^2) time with N*(N-1)/2 swaps
// Space Complexity: O(1) auxiliary space
// Preconditions: Square matrix (N x N).

class InPlaceMatrixTranspose {
public:
    template <typename T>
    static void transpose(std::vector<std::vector<T>>& mat) {
        int n = mat.size();
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                std::swap(mat[i][j], mat[j][i]);
            }
        }
    }
};

int main() {
    std::vector<std::vector<int>> mat = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };
    InPlaceMatrixTranspose::transpose(mat);
    assert(mat[0][1] == 5);
    assert(mat[1][0] == 2);
    assert(mat[2][3] == 15);
    assert(mat[3][2] == 12);

    std::cout << "in_place_matrix_transpose tests passed successfully.\n";
    return 0;
}
