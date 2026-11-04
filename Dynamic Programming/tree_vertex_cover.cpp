// Algorithm: Minimum Vertex Cover on Trees DP
// Purpose: Finds the minimum number of vertices such that every edge is incident to at least one chosen vertex.
// Time Complexity: O(N)
// Space Complexity: O(N)
// Preconditions: Connected tree of n vertices.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

void dfs_vc(int u, int p, const std::vector<std::vector<int>>& adj,
            std::vector<int>& dp_incl, std::vector<int>& dp_excl) {
    dp_incl[u] = 1;
    dp_excl[u] = 0;

    for (int v : adj[u]) {
        if (v != p) {
            dfs_vc(v, u, adj, dp_incl, dp_excl);
            dp_incl[u] += std::min(dp_incl[v], dp_excl[v]);
            dp_excl[u] += dp_incl[v];
        }
    }
}

int min_vertex_cover(int n, const std::vector<std::vector<int>>& adj) {
    std::vector<int> dp_incl(n, 0), dp_excl(n, 0);
    dfs_vc(0, -1, adj, dp_incl, dp_excl);
    return std::min(dp_incl[0], dp_excl[0]);
}

int main() {
    // Star tree: center 0 with leaves 1, 2, 3
    int n = 4;
    std::vector<std::vector<int>> adj(n);
    adj[0].push_back(1); adj[1].push_back(0);
    adj[0].push_back(2); adj[2].push_back(0);
    adj[0].push_back(3); adj[3].push_back(0);

    // Minimum vertex cover is simply node 0 (size 1)
    assert(min_vertex_cover(n, adj) == 1);
    return 0;
}
