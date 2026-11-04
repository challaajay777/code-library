// Algorithm: Metric TSP Shortest Hamiltonian Cycle DP
// Purpose: Calculates minimum Hamiltonian cycle cost starting and returning to node 0.
// Time Complexity: O(N^2 * 2^N)
// Space Complexity: O(N * 2^N)
// Preconditions: Adjacency cost matrix of N vertices (N <= 18).

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

const int INF = 1e9;

int shortest_hamiltonian_cycle(int n, const std::vector<std::vector<int>>& dist) {
    int total = 1 << n;
    std::vector<std::vector<int>> dp(total, std::vector<int>(n, INF));
    dp[1][0] = 0;

    for (int mask = 1; mask < total; ++mask) {
        for (int u = 0; u < n; ++u) {
            if (!(mask & (1 << u)) || dp[mask][u] == INF) continue;
            for (int v = 0; v < n; ++v) {
                if (!(mask & (1 << v))) {
                    dp[mask | (1 << v)][v] = std::min(dp[mask | (1 << v)][v], dp[mask][u] + dist[u][v]);
                }
            }
        }
    }

    int ans = INF;
    int full = total - 1;
    for (int u = 1; u < n; ++u) {
        ans = std::min(ans, dp[full][u] + dist[u][0]);
    }
    return ans;
}

int main() {
    int n = 4;
    std::vector<std::vector<int>> dist = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };
    assert(shortest_hamiltonian_cycle(n, dist) == 80);
    return 0;
}
