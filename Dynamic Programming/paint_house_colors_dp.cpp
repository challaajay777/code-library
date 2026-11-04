// Algorithm: Paint House with K Colors DP
// Purpose: Finds the minimum cost to paint N houses with K colors such that no two adjacent houses have same color.
// Time Complexity: O(N * K)
// Space Complexity: O(K)
// Preconditions: N x K matrix of non-negative costs.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <climits>

int min_cost_paint_houses(const std::vector<std::vector<int>>& costs) {
    if (costs.empty()) return 0;
    int n = costs.size(), k = costs[0].size();
    if (k == 0) return 0;
    if (k == 1) return (n == 1) ? costs[0][0] : -1;

    std::vector<int> prev_cost = costs[0];

    for (int i = 1; i < n; ++i) {
        int min1 = INT_MAX, min2 = INT_MAX, min_idx = -1;
        for (int c = 0; c < k; ++c) {
            if (prev_cost[c] < min1) {
                min2 = min1;
                min1 = prev_cost[c];
                min_idx = c;
            } else if (prev_cost[c] < min2) {
                min2 = prev_cost[c];
            }
        }

        std::vector<int> cur_cost(k);
        for (int c = 0; c < k; ++c) {
            cur_cost[c] = costs[i][c] + (c == min_idx ? min2 : min1);
        }
        prev_cost = cur_cost;
    }

    int ans = INT_MAX;
    for (int c : prev_cost) ans = std::min(ans, c);
    return ans;
}

int main() {
    std::vector<std::vector<int>> costs = {
        {1, 5, 3},
        {2, 9, 4}
    };
    // House 0 color 0 (cost 1), House 1 color 2 (cost 4) -> 5
    assert(min_cost_paint_houses(costs) == 5);
    return 0;
}
