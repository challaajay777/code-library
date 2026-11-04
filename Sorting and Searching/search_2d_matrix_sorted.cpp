#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Search in 2D Sorted Matrix (Staircase Search)
// Purpose: Searches for target in an R x C matrix where each row and column is sorted in ascending order in O(R + C).
// Time Complexity: O(R + C) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Rows and columns independently sorted in non-decreasing order.

class StaircaseSearch2D {
public:
    static bool search(const std::vector<std::vector<int>>& mat, int target) {
        if (mat.empty() || mat[0].empty()) return false;
        int r = mat.size();
        int c = mat[0].size();

        // Start from top-right corner
        int row = 0;
        int col = c - 1;

        while (row < r && col >= 0) {
            if (mat[row][col] == target) {
                return true;
            } else if (mat[row][col] > target) {
                col--;
            } else {
                row++;
            }
        }
        return false;
    }
};

int main() {
    std::vector<std::vector<int>> mat = {
        {1, 4, 7, 11, 15},
        {2, 5, 8, 12, 19},
        {3, 6, 9, 16, 22},
        {10, 13, 14, 17, 24},
        {18, 21, 23, 26, 30}
    };
    assert(StaircaseSearch2D::search(mat, 5) == true);
    assert(StaircaseSearch2D::search(mat, 20) == false);

    std::cout << "search_2d_matrix_sorted tests passed successfully.\n";
    return 0;
}
