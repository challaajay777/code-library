// Algorithm: Count Paths of Exact Length K in DAG DP
// Purpose: Counts the number of paths between source and destination of length exactly K edges.
// Time Complexity: O(K * (V + E))
// Space Complexity: O(V)
// Preconditions: Directed graph, step count K >= 0.

#include <iostream>
#include <vector>
#include <cassert>

long long count_paths_k_steps(int n, const std::vector<std::vector<int>>& adj, int src, int dst, int k) {
    std::vector<long long> dp(n, 0);
    dp[src] = 1;

    for (int step = 0; step < k; ++step) {
        std::vector<long long> next_dp(n, 0);
        for (int u = 0; u < n; ++u) {
            if (dp[u] == 0) continue;
            for (int v : adj[u]) {
                next_dp[v] += dp[u];
            }
        }
        dp = next_dp;
    }
    return dp[dst];
}

int main() {
    int n = 4;
    std::vector<std::vector<int>> adj(n);
    adj[0].push_back(1);
    adj[0].push_back(2);
    adj[1].push_back(3);
    adj[2].push_back(3);

    // From 0 to 3 of length 2: (0->1->3) and (0->2->3) -> 2 paths
    assert(count_paths_k_steps(n, adj, 0, 3, 2) == 2);
    return 0;
}
