// Algorithm: Subset Sum Decision and Subset Reconstruction
// Purpose: Determines if a subset exists summing to target and reconstructs the subset elements.
// Time Complexity: O(N * S)
// Space Complexity: O(N * S)
// Preconditions: Non-negative array elements, target >= 0.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

struct SubsetSumResult {
    bool possible;
    std::vector<int> subset;
};

SubsetSumResult find_subset_sum(const std::vector<int>& nums, int target) {
    int n = nums.size();
    std::vector<std::vector<bool>> dp(n + 1, std::vector<bool>(target + 1, false));
    dp[0][0] = true;

    for (int i = 1; i <= n; ++i) {
        int val = nums[i - 1];
        for (int s = 0; s <= target; ++s) {
            dp[i][s] = dp[i - 1][s];
            if (s >= val && dp[i - 1][s - val]) {
                dp[i][s] = true;
            }
        }
    }

    if (!dp[n][target]) return {false, {}};

    std::vector<int> res;
    int s = target;
    for (int i = n; i > 0 && s > 0; --i) {
        int val = nums[i - 1];
        if (s >= val && dp[i - 1][s - val]) {
            res.push_back(val);
            s -= val;
        }
    }
    return {true, res};
}

int main() {
    std::vector<int> nums = {3, 34, 4, 12, 5, 2};
    auto res = find_subset_sum(nums, 9);
    assert(res.possible);
    int sum = 0;
    for (int x : res.subset) sum += x;
    assert(sum == 9);
    return 0;
}
