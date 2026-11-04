// Algorithm: Dungeon Game Reverse DP
// Purpose: Determines the knight's minimum initial health required to reach bottom-right corner alive.
// Time Complexity: O(R * C)
// Space Complexity: O(C)
// Preconditions: 2D grid of health bonuses/losses.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

int calculate_minimum_hp(const std::vector<std::vector<int>>& dungeon) {
    int r = dungeon.size(), c = dungeon[0].size();
    const int INF = 1e9;
    std::vector<int> dp(c + 1, INF);
    dp[c - 1] = 1;

    for (int i = r - 1; i >= 0; --i) {
        for (int j = c - 1; j >= 0; --j) {
            int min_hp_exit = std::min(dp[j], dp[j + 1]);
            dp[j] = std::max(1, min_hp_exit - dungeon[i][j]);
        }
        dp[c] = INF;
    }
    return dp[0];
}

int main() {
    std::vector<std::vector<int>> dungeon = {
        {-2, -3,  3},
        {-5, -10, 1},
        {10,  30, -5}
    };
    assert(calculate_minimum_hp(dungeon) == 7);
    return 0;
}
