#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Median of Two Sorted Arrays
// Purpose: Finds the median value of two sorted arrays of lengths M and N in O(log(min(M, N))) time.
// Time Complexity: O(log(min(M, N))) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Both arrays sorted in non-decreasing order.

class MedianTwoSortedArrays {
public:
    static double find_median(const std::vector<int>& a, const std::vector<int>& b) {
        if (a.size() > b.size()) return find_median(b, a);

        int m = a.size(), n = b.size();
        int low = 0, high = m;

        while (low <= high) {
            int partition_a = (low + high) / 2;
            int partition_b = (m + n + 1) / 2 - partition_a;

            int max_left_a = (partition_a == 0) ? -2e9 : a[partition_a - 1];
            int min_right_a = (partition_a == m) ? 2e9 : a[partition_a];

            int max_left_b = (partition_b == 0) ? -2e9 : b[partition_b - 1];
            int min_right_b = (partition_b == n) ? 2e9 : b[partition_b];

            if (max_left_a <= min_right_b && max_left_b <= min_right_a) {
                if ((m + n) % 2 == 0) {
                    return (std::max(max_left_a, max_left_b) + std::min(min_right_a, min_right_b)) / 2.0;
                } else {
                    return std::max(max_left_a, max_left_b);
                }
            } else if (max_left_a > min_right_b) {
                high = partition_a - 1;
            } else {
                low = partition_a + 1;
            }
        }
        return 0.0;
    }
};

int main() {
    std::vector<int> a = {1, 3};
    std::vector<int> b = {2};
    assert(MedianTwoSortedArrays::find_median(a, b) == 2.0);

    std::vector<int> c = {1, 2};
    std::vector<int> d = {3, 4};
    assert(MedianTwoSortedArrays::find_median(c, d) == 2.5);

    std::cout << "median_of_two_sorted_arrays tests passed successfully.\n";
    return 0;
}
