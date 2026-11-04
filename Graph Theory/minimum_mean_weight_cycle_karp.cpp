// Algorithm: Karp Minimum Mean Weight Cycle
// Purpose: Finds the minimum cycle mean weight in a strongly connected directed graph.
// Time Complexity: O(V * E)
// Space Complexity: O(V^2)
// Preconditions: Strongly connected directed graph.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

struct Edge {
    int to, weight;
};

const double INF = 1e18;

double karp_min_mean_cycle(int n, const std::vector<std::vector<Edge>>& adj) {
    // dp[k][u]: shortest path of length exactly k from virtual source to u
    std::vector<std::vector<double>> dp(n + 1, std::vector<double>(n, INF));
    for (int i = 0; i < n; ++i) dp[0][i] = 0;

    for (int k = 1; k <= n; ++k) {
        for (int u = 0; u < n; ++u) {
            if (dp[k - 1][u] == INF) continue;
            for (const auto& e : adj[u]) {
                dp[k][e.to] = std::min(dp[k][e.to], dp[k - 1][u] + e.weight);
            }
        }
    }

    double min_mean = INF;
    for (int u = 0; u < n; ++u) {
        if (dp[n][u] == INF) continue;
        double max_k = -INF;
        for (int k = 0; k < n; ++k) {
            if (dp[k][u] < INF) {
                max_k = std::max(max_k, (dp[n][u] - dp[k][u]) / (n - k));
            }
        }
        min_mean = std::min(min_mean, max_k);
    }
    return min_mean;
}

int main() {
    int n = 3;
    std::vector<std::vector<Edge>> adj(n);
    adj[0].push_back({1, 1});
    adj[1].push_back({2, 2});
    adj[2].push_back({0, 3});
    // Cycle 0->1->2->0 has mean weight (1 + 2 + 3) / 3 = 2.0
    double mean = karp_min_mean_cycle(n, adj);
    assert(std::abs(mean - 2.0) < 1e-6);
    return 0;
}
