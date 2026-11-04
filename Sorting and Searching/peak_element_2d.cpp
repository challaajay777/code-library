#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: 2D Matrix Peak Finder
// Purpose: Finds a peak element in an N x M matrix (strictly greater than up, down, left, right neighbors) in O(N log M) time.
// Time Complexity: O(N log M) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Matrix dimensions >= 1.

class PeakElement2D {
public:
    static std::pair<int, int> find_peak(const std::vector<std::vector<int>>& mat) {
        int r = mat.size();
        int c = mat[0].size();
        int low_col = 0, high_col = c - 1;

        while (low_col <= high_col) {
            int mid_col = low_col + (high_col - low_col) / 2;

            // Find row index with maximum element in mid_col
            int max_row = 0;
            for (int i = 1; i < r; ++i) {
                if (mat[i][mid_col] > mat[max_row][mid_col]) {
                    max_row = i;
                }
            }

            int left_val = (mid_col > 0 ? mat[max_row][mid_col - 1] : -1e9);
            int right_val = (mid_col < c - 1 ? mat[max_row][mid_col + 1] : -1e9);
            int cur_val = mat[max_row][mid_col];

            if (cur_val > left_val && cur_val > right_val) {
                return {max_row, mid_col};
            } else if (right_val > cur_val) {
                low_col = mid_col + 1;
            } else {
                high_col = mid_col - 1;
            }
        }
        return {0, 0};
    }
};

int main() {
    std::vector<std::vector<int>> mat = {
        {1, 4, 3},
        {6, 7, 2},
        {5, 3, 1}
    };
    auto [row, col] = PeakElement2D::find_peak(mat);
    assert(row == 1 && col == 1); // 7 is greater than 4, 3, 6, 2

    std::cout << "peak_element_2d tests passed successfully.\n";
    return 0;
}
