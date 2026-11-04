// Algorithm: Partition Equal Subset Sum DP
// Purpose: Determines whether an array can be partitioned into two subsets with equal sum.
// Time Complexity: O(N * Sum)
// Space Complexity: O(Sum)
// Preconditions: Positive integer values.

#include <iostream>
#include <vector>
#include <numeric>
#include <cassert>

bool can_partition(const std::vector<int>& nums) {
    int sum = std::accumulate(nums.begin(), nums.end(), 0);
    if (sum % 2 != 0) return false;
    int target = sum / 2;

    std::vector<bool> dp(target + 1, false);
    dp[0] = true;

    for (int num : nums) {
        for (int s = target; s >= num; --s) {
            dp[s] = dp[s] || dp[s - num];
        }
    }
    return dp[target];
}

int main() {
    assert(can_partition({1, 5, 11, 5}));
    assert(!can_partition({1, 2, 3, 5}));
    return 0;
}
