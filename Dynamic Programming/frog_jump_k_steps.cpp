// Algorithm: Frog Jump with K Steps DP
// Purpose: Finds minimum cost to reach stone N where each jump can be between 1 and K stones.
// Time Complexity: O(N * K)
// Space Complexity: O(N)
// Preconditions: Array of stone heights, jump limit k >= 1.

#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>
#include <algorithm>

int frog_jump_k(const std::vector<int>& heights, int k) {
    int n = heights.size();
    const int INF = 1e9;
    std::vector<int> dp(n, INF);
    dp[0] = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 1; j <= k && i + j < n; ++j) {
            dp[i + j] = std::min(dp[i + j], dp[i] + std::abs(heights[i] - heights[i + j]));
        }
    }
    return dp[n - 1];
}

int main() {
    std::vector<int> heights = {10, 30, 40, 50, 20};
    assert(frog_jump_k(heights, 3) == 30); // 10 -> 40 -> 20 = |10-40| + |40-20| = 30 + 20? No: 10 -> 30 -> 20 = 20 + 10 = 30
    return 0;
}
