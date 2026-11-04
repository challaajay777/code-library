// Algorithm: Stone Game Interval DP (Minimax Game Theory)
// Purpose: Computes maximum score difference between first and second player taking from ends of array.
// Time Complexity: O(N^2)
// Space Complexity: O(N^2)
// Preconditions: Array of positive integers representing stone piles.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

long long stone_game_difference(const std::vector<int>& piles) {
    int n = piles.size();
    std::vector<std::vector<long long>> dp(n, std::vector<long long>(n, 0));
    for (int i = 0; i < n; ++i) dp[i][i] = piles[i];

    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i <= n - len; ++i) {
            int j = i + len - 1;
            dp[i][j] = std::max(piles[i] - dp[i + 1][j], piles[j] - dp[i][j - 1]);
        }
    }
    return dp[0][n - 1];
}

int main() {
    std::vector<int> piles = {5, 3, 4, 5};
    assert(stone_game_difference(piles) > 0);
    return 0;
}
