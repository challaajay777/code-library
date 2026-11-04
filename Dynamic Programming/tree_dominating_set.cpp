// Algorithm: Minimum Dominating Set on Trees DP
// Purpose: Finds the minimum subset of tree vertices such that every vertex is chosen or adjacent to a chosen vertex.
// Time Complexity: O(N)
// Space Complexity: O(N)
// Preconditions: Connected tree of n vertices.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

const int INF = 1e8;

void dfs_ds(int u, int p, const std::vector<std::vector<int>>& adj,
            std::vector<int>& dp0, std::vector<int>& dp1, std::vector<int>& dp2) {
    // dp0: u is chosen in the dominating set
    // dp1: u is not chosen, but covered by at least one child
    // dp2: u is not chosen, not covered by any child (relies on parent to cover it)
    dp0[u] = 1;
    dp1[u] = 0;
    dp2[u] = 0;

    int sum_min = 0;
    int min_diff = INF;
    bool has_child = false;

    for (int v : adj[u]) {
        if (v != p) {
            has_child = true;
            dfs_ds(v, u, adj, dp0, dp1, dp2);
            dp0[u] += std::min({dp0[v], dp1[v], dp2[v]});
            dp2[u] += dp1[v];

            int best_v = std::min(dp0[v], dp1[v]);
            sum_min += best_v;
            min_diff = std::min(min_diff, dp0[v] - best_v);
        }
    }

    if (!has_child) {
        dp1[u] = INF;
    } else {
        dp1[u] = sum_min + std::max(0, min_diff);
    }
}

int min_dominating_set(int n, const std::vector<std::vector<int>>& adj) {
    std::vector<int> dp0(n, 0), dp1(n, 0), dp2(n, 0);
    dfs_ds(0, -1, adj, dp0, dp1, dp2);
    return std::min(dp0[0], dp1[0]);
}

int main() {
    int n = 4;
    std::vector<std::vector<int>> adj(n);
    adj[0].push_back(1); adj[1].push_back(0);
    adj[0].push_back(2); adj[2].push_back(0);
    adj[0].push_back(3); adj[3].push_back(0);

    // Center dominates all 3 leaves
    assert(min_dominating_set(n, adj) == 1);
    return 0;
}
