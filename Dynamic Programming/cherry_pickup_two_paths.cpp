// Algorithm: Cherry Pickup Dual Synchronous Path DP
// Purpose: Finds maximum cherries collected by two paths moving simultaneously from (0,0) to (n-1, n-1).
// Time Complexity: O(N^3)
// Space Complexity: O(N^2)
// Preconditions: Grid where 0 is empty, 1 is cherry, -1 is thorn (obstacle).

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

int cherry_pickup(const std::vector<std::vector<int>>& grid) {
    int n = grid.size();
    std::vector<std::vector<int>> dp(n, std::vector<int>(n, -1));
    dp[0][0] = grid[0][0];

    int max_steps = 2 * n - 2;
    for (int step = 1; step <= max_steps; ++step) {
        std::vector<std::vector<int>> next_dp(n, std::vector<int>(n, -1));
        for (int r1 = std::max(0, step - (n - 1)); r1 <= std::min(n - 1, step); ++r1) {
            int c1 = step - r1;
            if (grid[r1][c1] == -1) continue;
            for (int r2 = r1; r2 <= std::min(n - 1, step); ++r2) {
                int c2 = step - r2;
                if (grid[r2][c2] == -1) continue;

                int cherries = (r1 == r2) ? grid[r1][c1] : grid[r1][c1] + grid[r2][c2];
                int prev_max = -1;

                if (r1 > 0 && r2 > 0) prev_max = std::max(prev_max, dp[r1 - 1][r2 - 1]);
                if (r1 > 0 && c2 > 0) prev_max = std::max(prev_max, dp[r1 - 1][r2]);
                if (c1 > 0 && r2 > 0) prev_max = std::max(prev_max, dp[r1][r2 - 1]);
                if (c1 > 0 && c2 > 0) prev_max = std::max(prev_max, dp[r1][r2]);

                if (prev_max != -1) {
                    next_dp[r1][r2] = prev_max + cherries;
                }
            }
        }
        dp = next_dp;
    }
    return std::max(0, dp[n - 1][n - 1]);
}

int main() {
    std::vector<std::vector<int>> grid = {
        {0, 1, -1},
        {1, 0, -1},
        {1, 1,  1}
    };
    assert(cherry_pickup(grid) == 5);
    return 0;
}
