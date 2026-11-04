// Algorithm: House Robber Circular Street DP
// Purpose: Computes max money robbed when houses are arranged along a circle (first and last are neighbors).
// Time Complexity: O(N)
// Space Complexity: O(1)
// Preconditions: Array of non-negative money values.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

long long rob_linear(const std::vector<int>& nums, int start, int end) {
    long long prev2 = 0, prev1 = 0;
    for (int i = start; i <= end; ++i) {
        long long cur = std::max(prev1, prev2 + nums[i]);
        prev2 = prev1;
        prev1 = cur;
    }
    return prev1;
}

long long rob_circular(const std::vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return 0;
    if (n == 1) return nums[0];
    return std::max(rob_linear(nums, 0, n - 2), rob_linear(nums, 1, n - 1));
}

int main() {
    std::vector<int> nums = {2, 3, 2};
    assert(rob_circular(nums) == 3);
    std::vector<int> nums2 = {1, 2, 3, 1};
    assert(rob_circular(nums2) == 4); // rob 1 + 3 = 4
    return 0;
}
