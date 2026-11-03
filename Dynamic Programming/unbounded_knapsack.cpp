// Algorithm: Unbounded Knapsack
// Supports: Maximum value with infinite supply of each item, exact weight combination
// Complexity: O(n * W) time, O(W) memory
// Preconditions: Capacity W >= 0, weights > 0

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

long long knapsack_unbounded(int W, const vector<pair<int, long long>>& items) {
    assert(W >= 0);
    vector<long long> dp(W + 1, 0);

    for (int w = 1; w <= W; ++w) {
        for (const auto& [wt, val] : items) {
            assert(wt > 0);
            if (wt <= w) {
                dp[w] = max(dp[w], dp[w - wt] + val);
            }
        }
    }
    return dp[W];
}
