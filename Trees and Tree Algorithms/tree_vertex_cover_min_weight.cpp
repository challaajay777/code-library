// Algorithm: Minimum Weight Vertex Cover on Trees
// Purpose: Calculates minimum total weight of vertices needed to cover all tree edges.
// Time Complexity: O(N)
// Space Complexity: O(N)
// Preconditions: Tree with non-negative vertex weights.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

void dfs_mvc(int u, int p, const std::vector<std::vector<int>>& adj,
             const std::vector<int>& weight,
             std::vector<long long>& dp_in, std::vector<long long>& dp_out) {
    dp_in[u] = weight[u];
    dp_out[u] = 0;

    for (int v : adj[u]) {
        if (v != p) {
            dfs_mvc(v, u, adj, weight, dp_in, dp_out);
            dp_in[u] += std::min(dp_in[v], dp_out[v]);
            dp_out[u] += dp_in[v];
        }
    }
}

int main() {
    int n = 3;
    std::vector<std::vector<int>> adj(n);
    adj[0] = {1, 2}; adj[1] = {0}; adj[2] = {0};
    std::vector<int> weight = {10, 2, 3};

    std::vector<long long> dp_in(n, 0), dp_out(n, 0);
    dfs_mvc(0, -1, adj, weight, dp_in, dp_out);

    // Pick 1 and 2 (cost 5) vs Pick 0 (cost 10) -> min weight is 5
    assert(std::min(dp_in[0], dp_out[0]) == 5);
    return 0;
}
