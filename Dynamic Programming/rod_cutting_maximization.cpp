// Algorithm: Rod Cutting Profit Maximization DP
// Purpose: Finds the maximum revenue obtainable by cutting up a rod of length n and selling the pieces.
// Time Complexity: O(N^2)
// Space Complexity: O(N)
// Preconditions: Prices array for lengths 1..n.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

int max_rod_cutting_profit(const std::vector<int>& prices) {
    int n = prices.size();
    std::vector<int> dp(n + 1, 0);

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= i; ++j) {
            dp[i] = std::max(dp[i], dp[i - j] + prices[j - 1]);
        }
    }
    return dp[n];
}

int main() {
    std::vector<int> prices = {1, 5, 8, 9, 10, 17, 17, 20};
    assert(max_rod_cutting_profit(prices) == 22);
    return 0;
}
