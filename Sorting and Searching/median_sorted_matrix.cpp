#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Median in a Row-Wise Sorted Matrix
// Purpose: Finds median element of an R x C matrix where each row is sorted in O(32 * R * log C) time without allocating extra memory.
// Time Complexity: O(32 * R * log C) time
// Space Complexity: O(1) auxiliary space
// Preconditions: R * C is odd.

class RowWiseSortedMatrixMedian {
public:
    static int find_median(const std::vector<std::vector<int>>& mat) {
        int r = mat.size();
        int c = mat[0].size();
        int low = 1e9, high = -1e9;

        for (int i = 0; i < r; ++i) {
            low = std::min(low, mat[i][0]);
            high = std::max(high, mat[i][c - 1]);
        }

        int desired = (r * c + 1) / 2;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            int count = 0;

            for (int i = 0; i < r; ++i) {
                count += std::upper_bound(mat[i].begin(), mat[i].end(), mid) - mat[i].begin();
            }

            if (count < desired) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return low;
    }
};

int main() {
    std::vector<std::vector<int>> mat = {
        {1, 3, 5},
        {2, 6, 9},
        {3, 6, 9}
    };
    // Elements: 1, 2, 3, 3, 5, 6, 6, 9, 9 -> median is 5
    assert(RowWiseSortedMatrixMedian::find_median(mat) == 5);

    std::cout << "median_sorted_matrix tests passed successfully.\n";
    return 0;
}
