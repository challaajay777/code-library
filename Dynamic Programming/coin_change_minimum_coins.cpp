// Algorithm: Coin Change Minimum Coins with Combination Reconstruction
// Purpose: Finds the minimum number of coins needed to make amount V and reconstructs the used coin denominations.
// Time Complexity: O(N * V)
// Space Complexity: O(V)
// Preconditions: Positive integer coin values, non-negative target amount V.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

struct CoinResult {
    int min_coins;
    std::vector<int> coins_used;
};

CoinResult min_coin_change(const std::vector<int>& coins, int target) {
    const int INF = 1e9;
    std::vector<int> dp(target + 1, INF);
    std::vector<int> parent(target + 1, -1);
    dp[0] = 0;

    for (int i = 1; i <= target; ++i) {
        for (int c : coins) {
            if (i >= c && dp[i - c] + 1 < dp[i]) {
                dp[i] = dp[i - c] + 1;
                parent[i] = c;
            }
        }
    }

    if (dp[target] >= INF) return {-1, {}};
    std::vector<int> used;
    int cur = target;
    while (cur > 0) {
        used.push_back(parent[cur]);
        cur -= parent[cur];
    }
    return {dp[target], used};
}

int main() {
    std::vector<int> coins = {1, 2, 5};
    auto res = min_coin_change(coins, 11);
    assert(res.min_coins == 3); // 5 + 5 + 1
    int sum = 0;
    for (int c : res.coins_used) sum += c;
    assert(sum == 11);
    return 0;
}
