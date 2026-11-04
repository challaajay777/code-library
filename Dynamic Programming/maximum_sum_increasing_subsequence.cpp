// Algorithm: Maximum Sum Increasing Subsequence (MSIS) DP
// Purpose: Finds a strictly increasing subsequence that has the maximum sum of its elements.
// Time Complexity: O(N^2)
// Space Complexity: O(N)
// Preconditions: Array of positive integers.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

long long max_sum_increasing_subsequence(const std::vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return 0;
    std::vector<long long> dp(n);
    for (int i = 0; i < n; ++i) dp[i] = nums[i];

    long long max_sum = dp[0];
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (nums[j] < nums[i]) {
                dp[i] = std::max(dp[i], dp[j] + nums[i]);
            }
        }
        max_sum = std::max(max_sum, dp[i]);
    }
    return max_sum;
}

int main() {
    std::vector<int> nums = {1, 101, 2, 3, 100, 4, 5};
    // Increasing subsequence {1, 2, 3, 100} sums to 106
    assert(max_sum_increasing_subsequence(nums) == 106);
    return 0;
}
