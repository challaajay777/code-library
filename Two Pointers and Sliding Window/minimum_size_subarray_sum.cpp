#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Minimum Size Subarray Sum
// Purpose: Finds minimal length of contiguous subarray with sum >= target in an array of positive integers in O(N).
// Time Complexity: O(N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Elements are positive integers; target > 0.

class MinSizeSubarraySum {
public:
    static int min_sub_array_len(int target, const std::vector<int>& nums) {
        int n = nums.size();
        int left = 0;
        long long sum = 0;
        int min_len = 1e9;

        for (int right = 0; right < n; ++right) {
            sum += nums[right];
            while (sum >= target) {
                min_len = std::min(min_len, right - left + 1);
                sum -= nums[left++];
            }
        }
        return (min_len == 1e9) ? 0 : min_len;
    }
};

int main() {
    std::vector<int> a = {2, 3, 1, 2, 4, 3};
    assert(MinSizeSubarraySum::min_sub_array_len(7, a) == 2); // [4, 3]

    std::vector<int> b = {1, 4, 4};
    assert(MinSizeSubarraySum::min_sub_array_len(4, b) == 1);

    std::cout << "minimum_size_subarray_sum tests passed successfully.\n";
    return 0;
}
