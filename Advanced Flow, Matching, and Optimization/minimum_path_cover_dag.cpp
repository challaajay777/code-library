// Algorithm: Minimum Path Cover in DAG via Bipartite Matching
// Purpose: Finds minimum number of vertex-disjoint paths covering all DAG vertices using maximum bipartite matching.
// Time Complexity: O(V * E)
// Space Complexity: O(V + E)
// Preconditions: Directed Acyclic Graph.

#include <iostream>
#include <vector>
#include <cassert>

bool kuhn(int u, const std::vector<std::vector<int>>& adj, std::vector<bool>& vis, std::vector<int>& match) {
    if (vis[u]) return false;
    vis[u] = true;
    for (int v : adj[u]) {
        if (match[v] == -1 || kuhn(match[v], adj, vis, match)) {
            match[v] = u;
            return true;
        }
    }
    return false;
}

int min_path_cover(int n, const std::vector<std::vector<int>>& dag) {
    std::vector<int> match(n, -1);
    int matching = 0;
    for (int i = 0; i < n; ++i) {
        std::vector<bool> vis(n, false);
        if (kuhn(i, dag, vis, match)) matching++;
    }
    return n - matching;
}

int main() {
    int n = 4;
    std::vector<std::vector<int>> dag(n);
    dag[0].push_back(1);
    dag[1].push_back(2);
    // 0 -> 1 -> 2 is one path, 3 is isolated path -> 2 paths
    assert(min_path_cover(n, dag) == 2);
    return 0;
}
