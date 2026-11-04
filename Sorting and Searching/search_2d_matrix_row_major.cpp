#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Search 2D Row-Major Sorted Matrix
// Purpose: Searches for target in an R x C matrix where each row is sorted and the first integer of each row is greater than the last of the previous row.
// Time Complexity: O(log(R * C)) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Strict row-major sorted matrix.

class SearchRowMajor2D {
public:
    static bool search(const std::vector<std::vector<int>>& mat, int target) {
        if (mat.empty() || mat[0].empty()) return false;
        int r = mat.size();
        int c = mat[0].size();
        int low = 0, high = r * c - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            int mid_val = mat[mid / c][mid % c];

            if (mid_val == target) {
                return true;
            } else if (mid_val < target) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return false;
    }
};

int main() {
    std::vector<std::vector<int>> mat = {
        {1, 3, 5, 7},
        {10, 11, 16, 20},
        {23, 30, 34, 60}
    };
    assert(SearchRowMajor2D::search(mat, 3) == true);
    assert(SearchRowMajor2D::search(mat, 13) == false);

    std::cout << "search_2d_matrix_row_major tests passed successfully.\n";
    return 0;
}
