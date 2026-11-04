// Algorithm: Partition Array into K Subsets of Equal Sum DP
// Purpose: Determines whether an array can be partitioned into K subsets each having equal sum via bitmask DP.
// Time Complexity: O(K * 2^N)
// Space Complexity: O(2^N)
// Preconditions: 1 <= K <= N <= 16.

#include <iostream>
#include <vector>
#include <numeric>
#include <cassert>

bool can_partition_k_subsets(const std::vector<int>& nums, int k) {
    int total = std::accumulate(nums.begin(), nums.end(), 0);
    if (total % k != 0) return false;
    int target = total / k;
    int n = nums.size();

    int total_states = 1 << n;
    std::vector<int> dp(total_states, -1);
    dp[0] = 0;

    for (int mask = 0; mask < total_states; ++mask) {
        if (dp[mask] == -1) continue;
        for (int i = 0; i < n; ++i) {
            if (!(mask & (1 << i)) && dp[mask] + nums[i] <= target) {
                dp[mask | (1 << i)] = (dp[mask] + nums[i]) % target;
            }
        }
    }
    return dp[total_states - 1] == 0;
}

int main() {
    std::vector<int> nums = {4, 3, 2, 3, 5, 2, 1};
    assert(can_partition_k_subsets(nums, 4));
    assert(!can_partition_k_subsets({1, 2, 3, 4}, 3));
    return 0;
}
