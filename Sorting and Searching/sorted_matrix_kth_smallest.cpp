#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: K-th Smallest Element in Row-and-Column Sorted Matrix
// Purpose: Finds the k-th smallest element in an N x N matrix sorted along both rows and columns using binary search on answer.
// Time Complexity: O(N log(max_val - min_val)) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Matrix sorted along both dimensions; 1 <= k <= N*N.

class SortedMatrixKthSmallest {
private:
    static int count_less_or_equal(const std::vector<std::vector<int>>& mat, int mid) {
        int n = mat.size();
        int count = 0;
        int row = n - 1;
        int col = 0;

        while (row >= 0 && col < n) {
            if (mat[row][col] <= mid) {
                count += (row + 1);
                col++;
            } else {
                row--;
            }
        }
        return count;
    }

public:
    static int kth_smallest(const std::vector<std::vector<int>>& mat, int k) {
        int n = mat.size();
        int low = mat[0][0];
        int high = mat[n - 1][n - 1];
        int ans = low;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (count_less_or_equal(mat, mid) >= k) {
                ans = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        return ans;
    }
};

int main() {
    std::vector<std::vector<int>> mat = {
        {1, 5, 9},
        {10, 11, 13},
        {12, 13, 15}
    };
    // 8th smallest element is 13
    assert(SortedMatrixKthSmallest::kth_smallest(mat, 8) == 13);
    assert(SortedMatrixKthSmallest::kth_smallest(mat, 1) == 1);

    std::cout << "sorted_matrix_kth_smallest tests passed successfully.\n";
    return 0;
}
