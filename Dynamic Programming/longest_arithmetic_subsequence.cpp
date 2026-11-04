// Algorithm: Longest Arithmetic Subsequence DP
// Purpose: Finds the maximum length arithmetic progression subsequence in an arbitrary array.
// Time Complexity: O(N^2)
// Space Complexity: O(N^2)
// Preconditions: Array of integers.

#include <iostream>
#include <vector>
#include <unordered_map>
#include <cassert>
#include <algorithm>

int longest_arithmetic_subsequence(const std::vector<int>& nums) {
    int n = nums.size();
    if (n <= 2) return n;

    std::vector<std::unordered_map<int, int>> dp(n);
    int ans = 2;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            int diff = nums[i] - nums[j];
            int prev_len = dp[j].count(diff) ? dp[j][diff] : 1;
            dp[i][diff] = prev_len + 1;
            ans = std::max(ans, dp[i][diff]);
        }
    }
    return ans;
}

int main() {
    std::vector<int> nums = {3, 6, 9, 12};
    assert(longest_arithmetic_subsequence(nums) == 4);
    std::vector<int> nums2 = {9, 4, 7, 2, 10};
    assert(longest_arithmetic_subsequence(nums2) == 3); // {4, 7, 10}
    return 0;
}
