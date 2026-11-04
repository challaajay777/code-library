// Algorithm: Traveling Salesperson Problem via Held-Karp Bitmask DP
// Purpose: Solves the exact metric/general TSP minimum tour cost with vertex sequence reconstruction.
// Time Complexity: O(2^N * N^2)
// Space Complexity: O(2^N * N)
// Preconditions: N <= 20, complete directed or undirected cost matrix.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

const int INF = 1e9;

struct TSPResult {
    int min_cost;
    std::vector<int> tour;
};

TSPResult solve_tsp(int n, const std::vector<std::vector<int>>& cost) {
    int total_states = 1 << n;
    std::vector<std::vector<int>> dp(total_states, std::vector<int>(n, INF));
    std::vector<std::vector<int>> parent(total_states, std::vector<int>(n, -1));

    dp[1][0] = 0; // Start at vertex 0

    for (int mask = 1; mask < total_states; ++mask) {
        for (int u = 0; u < n; ++u) {
            if (!(mask & (1 << u)) || dp[mask][u] == INF) continue;
            for (int v = 0; v < n; ++v) {
                if (!(mask & (1 << v))) {
                    int next_mask = mask | (1 << v);
                    int new_cost = dp[mask][u] + cost[u][v];
                    if (new_cost < dp[next_mask][v]) {
                        dp[next_mask][v] = new_cost;
                        parent[next_mask][v] = u;
                    }
                }
            }
        }
    }

    int best_last = -1;
    int min_total = INF;
    int all_mask = total_states - 1;

    for (int u = 1; u < n; ++u) {
        if (dp[all_mask][u] != INF && dp[all_mask][u] + cost[u][0] < min_total) {
            min_total = dp[all_mask][u] + cost[u][0];
            best_last = u;
        }
    }

    std::vector<int> tour;
    int cur_mask = all_mask;
    int cur_node = best_last;
    while (cur_node != -1) {
        tour.push_back(cur_node);
        int p = parent[cur_mask][cur_node];
        cur_mask ^= (1 << cur_node);
        cur_node = p;
    }
    std::reverse(tour.begin(), tour.end());
    tour.push_back(0); // return to start
    return {min_total, tour};
}

int main() {
    int n = 4;
    std::vector<std::vector<int>> cost = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };
    auto res = solve_tsp(n, cost);
    // Optimal tour: 0 -> 1 -> 3 -> 2 -> 0 with cost 10 + 25 + 30 + 15 = 80
    assert(res.min_cost == 80);
    assert((int)res.tour.size() == 5);
    return 0;
}
