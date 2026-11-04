// Algorithm: Minimum Path Sum in Grid DP
// Purpose: Finds path from top-left to bottom-right of matrix minimizing sum of cell values.
// Time Complexity: O(R * C)
// Space Complexity: O(C)
// Preconditions: Grid of non-negative integers.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

int min_path_sum(const std::vector<std::vector<int>>& grid) {
    int r = grid.size(), c = grid[0].size();
    std::vector<int> dp(c, 0);
    dp[0] = grid[0][0];

    for (int j = 1; j < c; ++j) dp[j] = dp[j - 1] + grid[0][j];

    for (int i = 1; i < r; ++i) {
        dp[0] += grid[i][0];
        for (int j = 1; j < c; ++j) {
            dp[j] = std::min(dp[j], dp[j - 1]) + grid[i][j];
        }
    }
    return dp[c - 1];
}

int main() {
    std::vector<std::vector<int>> grid = {
        {1, 3, 1},
        {1, 5, 1},
        {4, 2, 1}
    };
    assert(min_path_sum(grid) == 7); // 1 -> 3 -> 1 -> 1 -> 1
    return 0;
}
