#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Subarray Product Less Than K
// Purpose: Counts contiguous subarrays whose product is strictly less than K in an array of positive integers in O(N).
// Time Complexity: O(N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: All elements positive integers; K >= 0.

class SubarrayProductLessThanK {
public:
    static long long num_subarray_product_less_than_k(const std::vector<int>& nums, int k) {
        if (k <= 1) return 0;
        long long prod = 1;
        long long count = 0;
        int left = 0;

        for (int right = 0; right < (int)nums.size(); ++right) {
            prod *= nums[right];
            while (prod >= k && left <= right) {
                prod /= nums[left++];
            }
            count += (right - left + 1);
        }
        return count;
    }
};

int main() {
    std::vector<int> a = {10, 5, 2, 6};
    // For k=100: [10], [5], [2], [6], [10, 5], [5, 2], [2, 6], [5, 2, 6] -> 8
    assert(SubarrayProductLessThanK::num_subarray_product_less_than_k(a, 100) == 8);

    std::vector<int> b = {1, 2, 3};
    assert(SubarrayProductLessThanK::num_subarray_product_less_than_k(b, 0) == 0);

    std::cout << "subarray_product_less_than_k tests passed successfully.\n";
    return 0;
}
