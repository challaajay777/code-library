// Algorithm: Count Square Submatrices with All Ones DP
// Purpose: Counts total number of all-1s square submatrices of any dimension.
// Time Complexity: O(R * C)
// Space Complexity: O(R * C)
// Preconditions: Grid of 0s and 1s.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

int count_squares(std::vector<std::vector<int>>& matrix) {
    int r = matrix.size(), c = matrix[0].size();
    int count = 0;

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (matrix[i][j] == 1 && i > 0 && j > 0) {
                matrix[i][j] = std::min({matrix[i - 1][j], matrix[i][j - 1], matrix[i - 1][j - 1]}) + 1;
            }
            count += matrix[i][j];
        }
    }
    return count;
}

int main() {
    std::vector<std::vector<int>> matrix = {
        {0, 1, 1, 1},
        {1, 1, 1, 1},
        {0, 1, 1, 1}
    };
    assert(count_squares(matrix) == 15);
    return 0;
}
