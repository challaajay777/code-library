// Algorithm: 0-1 and Bounded Knapsack
// Supports: Maximum value under capacity W with binary powers decomposition for bounded items
// Complexity: O(n * W) for 0-1 knapsack, O(W * sum(log count_i)) for bounded knapsack
// Preconditions: Weights and capacity W >= 0

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

struct Item {
    long long weight;
    long long value;
    long long count; // 1 for 0-1 knapsack, or finite count for bounded
};

// 0-1 Knapsack using 1D DP space optimization
long long knapsack_01(int W, const vector<pair<int, long long>>& items) {
    assert(W >= 0);
    vector<long long> dp(W + 1, 0);

    for (const auto& [wt, val] : items) {
        assert(wt >= 0);
        for (int w = W; w >= wt; --w) {
            dp[w] = max(dp[w], dp[w - wt] + val);
        }
    }
    return *max_element(dp.begin(), dp.end());
}

// Bounded Knapsack using powers of 2 bundling into 0-1 items
long long knapsack_bounded(int W, const vector<Item>& items) {
    assert(W >= 0);
    vector<pair<int, long long>> unpacked;

    for (const auto& item : items) {
        long long c = item.count;
        long long k = 1;
        while (c > 0) {
            long long take = min(k, c);
            if (item.weight * take <= W) {
                unpacked.push_back({(int)(item.weight * take), item.value * take});
            }
            c -= take;
            k <<= 1;
        }
    }
    return knapsack_01(W, unpacked);
}
