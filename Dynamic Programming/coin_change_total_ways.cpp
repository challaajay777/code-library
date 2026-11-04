// Algorithm: Coin Change Total Combinations DP
// Purpose: Calculates total number of unordered combinations to make target amount with given coins.
// Time Complexity: O(N * V)
// Space Complexity: O(V)
// Preconditions: Positive integer coin values, non-negative target amount V.

#include <iostream>
#include <vector>
#include <cassert>

long long total_coin_combinations(const std::vector<int>& coins, int target) {
    std::vector<long long> dp(target + 1, 0);
    dp[0] = 1;
    for (int c : coins) {
        for (int i = c; i <= target; ++i) {
            dp[i] += dp[i - c];
        }
    }
    return dp[target];
}

int main() {
    std::vector<int> coins = {1, 2, 5};
    // 5 can be made as: {5}, {2,2,1}, {2,1,1,1}, {1,1,1,1,1} -> 4 ways
    assert(total_coin_combinations(coins, 5) == 4);
    return 0;
}
