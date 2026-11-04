// Algorithm: Maximum Independent Set on Tree with Reconstruction
// Purpose: Finds maximum weight independent set on a tree and returns the selected nodes.
// Time Complexity: O(N)
// Space Complexity: O(N)
// Preconditions: Tree with vertex weights.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

void dfs_mis_rec(int u, int p, const std::vector<std::vector<int>>& adj,
                 const std::vector<int>& w,
                 std::vector<long long>& dp_in, std::vector<long long>& dp_out) {
    dp_in[u] = w[u];
    dp_out[u] = 0;
    for (int v : adj[u]) {
        if (v != p) {
            dfs_mis_rec(v, u, adj, w, dp_in, dp_out);
            dp_in[u] += dp_out[v];
            dp_out[u] += std::max(dp_in[v], dp_out[v]);
        }
    }
}

void reconstruct_mis(int u, int p, bool take, const std::vector<std::vector<int>>& adj,
                     const std::vector<long long>& dp_in, const std::vector<long long>& dp_out,
                     std::vector<int>& chosen) {
    if (take) {
        chosen.push_back(u);
        for (int v : adj[u]) if (v != p) reconstruct_mis(v, u, false, adj, dp_in, dp_out, chosen);
    } else {
        for (int v : adj[u]) {
            if (v != p) {
                bool take_child = (dp_in[v] > dp_out[v]);
                reconstruct_mis(v, u, take_child, adj, dp_in, dp_out, chosen);
            }
        }
    }
}

int main() {
    int n = 3;
    std::vector<std::vector<int>> adj(n);
    adj[0] = {1, 2}; adj[1] = {0}; adj[2] = {0};
    std::vector<int> w = {10, 4, 4};

    std::vector<long long> dp_in(n, 0), dp_out(n, 0);
    dfs_mis_rec(0, -1, adj, w, dp_in, dp_out);

    std::vector<int> chosen;
    reconstruct_mis(0, -1, dp_in[0] > dp_out[0], adj, dp_in, dp_out, chosen);

    assert(chosen == std::vector<int>({0})); // weight 10 > 4 + 4
    return 0;
}
