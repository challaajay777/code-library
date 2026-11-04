// Algorithm: Maximum Independent Set on Trees via Post-Order DP
// Purpose: Finds the maximum weight subset of tree vertices with no adjacent edges.
// Time Complexity: O(N)
// Space Complexity: O(N)
// Preconditions: Connected tree of n vertices.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

void dfs_mis(int u, int p, const std::vector<std::vector<int>>& adj,
             const std::vector<int>& weights,
             std::vector<long long>& dp_incl,
             std::vector<long long>& dp_excl) {
    dp_incl[u] = weights[u];
    dp_excl[u] = 0;

    for (int v : adj[u]) {
        if (v != p) {
            dfs_mis(v, u, adj, weights, dp_incl, dp_excl);
            dp_incl[u] += dp_excl[v];
            dp_excl[u] += std::max(dp_incl[v], dp_excl[v]);
        }
    }
}

long long max_independent_set(int n, const std::vector<std::vector<int>>& adj, const std::vector<int>& weights) {
    std::vector<long long> dp_incl(n, 0), dp_excl(n, 0);
    dfs_mis(0, -1, adj, weights, dp_incl, dp_excl);
    return std::max(dp_incl[0], dp_excl[0]);
}

int main() {
    int n = 4;
    std::vector<std::vector<int>> adj(n);
    adj[0].push_back(1); adj[1].push_back(0);
    adj[0].push_back(2); adj[2].push_back(0);
    adj[0].push_back(3); adj[3].push_back(0);
    std::vector<int> weights = {10, 5, 5, 5};

    // Include 0: weight 10. Exclude 0: include 1, 2, 3 -> weight 15.
    assert(max_independent_set(n, adj, weights) == 15);
    return 0;
}
