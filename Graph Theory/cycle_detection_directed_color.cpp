// Algorithm: Directed Cycle Detection via 3-Color DFS
// Purpose: Detects cycles in directed graph using state colors: WHITE (0), GRAY (1), BLACK (2).
// Time Complexity: O(V + E)
// Space Complexity: O(V)
// Preconditions: Directed graph.

#include <iostream>
#include <vector>
#include <cassert>

bool dfs_cycle(int u, const std::vector<std::vector<int>>& adj, std::vector<int>& color) {
    color[u] = 1; // GRAY: visiting
    for (int v : adj[u]) {
        if (color[v] == 1) return true; // back-edge to ancestor -> cycle
        if (color[v] == 0 && dfs_cycle(v, adj, color)) return true;
    }
    color[u] = 2; // BLACK: visited
    return false;
}

bool has_cycle_directed(int n, const std::vector<std::vector<int>>& adj) {
    std::vector<int> color(n, 0);
    for (int i = 0; i < n; ++i) {
        if (color[i] == 0 && dfs_cycle(i, adj, color)) {
            return true;
        }
    }
    return false;
}

int main() {
    int n = 3;
    std::vector<std::vector<int>> adj(n);
    adj[0].push_back(1);
    adj[1].push_back(2);
    assert(!has_cycle_directed(n, adj));

    adj[2].push_back(0); // 0 -> 1 -> 2 -> 0
    assert(has_cycle_directed(n, adj));
    return 0;
}
