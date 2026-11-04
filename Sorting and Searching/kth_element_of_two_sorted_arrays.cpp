#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: K-th Element of Two Sorted Arrays
// Purpose: Finds the k-th smallest element (1-indexed) in the merged representation of two sorted arrays in logarithmic time.
// Time Complexity: O(log(min(M, N))) time
// Space Complexity: O(1) auxiliary space
// Preconditions: 1 <= k <= M + N; both arrays sorted.

class KthElementTwoSortedArrays {
public:
    static int find_kth(const std::vector<int>& a, const std::vector<int>& b, int k) {
        if (a.size() > b.size()) return find_kth(b, a, k);

        int m = a.size(), n = b.size();
        int low = std::max(0, k - n);
        int high = std::min(m, k);

        while (low <= high) {
            int cut_a = (low + high) / 2;
            int cut_b = k - cut_a;

            int left_a = (cut_a == 0) ? -2e9 : a[cut_a - 1];
            int right_a = (cut_a == m) ? 2e9 : a[cut_a];

            int left_b = (cut_b == 0) ? -2e9 : b[cut_b - 1];
            int right_b = (cut_b == n) ? 2e9 : b[cut_b];

            if (left_a <= right_b && left_b <= right_a) {
                return std::max(left_a, left_b);
            } else if (left_a > right_b) {
                high = cut_a - 1;
            } else {
                low = cut_a + 1;
            }
        }
        return -1;
    }
};

int main() {
    std::vector<int> a = {2, 3, 6, 7, 9};
    std::vector<int> b = {1, 4, 8, 10};
    // Merged: 1, 2, 3, 4, 6, 7, 8, 9, 10
    assert(KthElementTwoSortedArrays::find_kth(a, b, 5) == 6);
    assert(KthElementTwoSortedArrays::find_kth(a, b, 1) == 1);
    assert(KthElementTwoSortedArrays::find_kth(a, b, 9) == 10);

    std::cout << "kth_element_of_two_sorted_arrays tests passed successfully.\n";
    return 0;
}
