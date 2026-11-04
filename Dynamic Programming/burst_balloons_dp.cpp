// Algorithm: Burst Balloons Maximum Coins Interval DP
// Purpose: Calculates maximum coins obtained by bursting balloons with boundary multipliers.
// Time Complexity: O(N^3)
// Space Complexity: O(N^2)
// Preconditions: Array of balloon values.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

int max_coins_burst_balloons(const std::vector<int>& nums) {
    std::vector<int> b;
    b.push_back(1);
    for (int x : nums) b.push_back(x);
    b.push_back(1);

    int n = b.size();
    std::vector<std::vector<int>> dp(n, std::vector<int>(n, 0));

    for (int len = 2; len < n; ++len) {
        for (int i = 0; i < n - len; ++i) {
            int j = i + len;
            for (int k = i + 1; k < j; ++k) {
                dp[i][j] = std::max(dp[i][j], dp[i][k] + dp[k][j] + b[i] * b[k] * b[j]);
            }
        }
    }
    return dp[0][n - 1];
}

int main() {
    std::vector<int> nums = {3, 1, 5, 8};
    assert(max_coins_burst_balloons(nums) == 167);
    return 0;
}
