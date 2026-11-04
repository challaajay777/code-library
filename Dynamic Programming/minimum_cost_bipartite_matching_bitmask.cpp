// Algorithm: Min-Cost Bipartite Matching via Bitmask DP
// Purpose: Computes exact minimum cost perfect matching for bipartite graph with N elements per side.
// Time Complexity: O(2^N * N)
// Space Complexity: O(2^N)
// Preconditions: N <= 20, N x N edge weight matrix.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

const int INF = 1e9;

int min_cost_bipartite_matching(int n, const std::vector<std::vector<int>>& cost) {
    int total_states = 1 << n;
    std::vector<int> dp(total_states, INF);
    dp[0] = 0;

    for (int mask = 0; mask < total_states; ++mask) {
        if (dp[mask] == INF) continue;
        int i = __builtin_popcount(mask); // next worker to assign
        if (i >= n) break;
        for (int j = 0; j < n; ++j) {
            if (!(mask & (1 << j))) {
                int next_mask = mask | (1 << j);
                dp[next_mask] = std::min(dp[next_mask], dp[mask] + cost[i][j]);
            }
        }
    }
    return dp[total_states - 1];
}

int main() {
    int n = 3;
    std::vector<std::vector<int>> cost = {
        {9, 2, 7},
        {6, 4, 3},
        {5, 8, 1}
    };
    // Match worker 0 -> job 1 (2), worker 1 -> job 0 (6), worker 2 -> job 2 (1) = 9 total
    assert(min_cost_bipartite_matching(n, cost) == 9);
    return 0;
}
