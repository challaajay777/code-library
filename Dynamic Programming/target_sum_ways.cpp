// Algorithm: Target Sum Ways via Subset Sum Reduction
// Purpose: Calculates number of ways to assign '+' and '-' to elements such that total sum equals target.
// Time Complexity: O(N * Sum)
// Space Complexity: O(Sum)
// Preconditions: Array of non-negative integers, target value.

#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>
#include <cassert>

long long count_target_sum_ways(const std::vector<int>& nums, int target) {
    long long total_sum = std::accumulate(nums.begin(), nums.end(), 0LL);
    if (std::abs(target) > total_sum) return 0;
    if ((total_sum + target) % 2 != 0) return 0;

    long long s1 = (total_sum + target) / 2;
    std::vector<long long> dp(s1 + 1, 0);
    dp[0] = 1;

    for (int num : nums) {
        for (long long s = s1; s >= num; --s) {
            dp[s] += dp[s - num];
        }
    }
    return dp[s1];
}

int main() {
    std::vector<int> nums = {1, 1, 1, 1, 1};
    assert(count_target_sum_ways(nums, 3) == 5);
    return 0;
}
