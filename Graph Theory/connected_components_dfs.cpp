// Algorithm: Connected Components via DFS
// Purpose: Finds all connected components and labels each vertex with its component ID.
// Time Complexity: O(V + E)
// Space Complexity: O(V)
// Preconditions: Undirected graph with 0-indexed vertices.

#include <iostream>
#include <vector>
#include <cassert>

void dfs(int u, int comp_id, const std::vector<std::vector<int>>& adj, std::vector<int>& comp) {
    comp[u] = comp_id;
    for (int v : adj[u]) {
        if (comp[v] == -1) {
            dfs(v, comp_id, adj, comp);
        }
    }
}

std::pair<int, std::vector<int>> find_components(int n, const std::vector<std::vector<int>>& adj) {
    std::vector<int> comp(n, -1);
    int num_comp = 0;
    for (int i = 0; i < n; ++i) {
        if (comp[i] == -1) {
            dfs(i, num_comp++, adj, comp);
        }
    }
    return {num_comp, comp};
}

int main() {
    int n = 5;
    std::vector<std::vector<int>> adj(n);
    adj[0].push_back(1); adj[1].push_back(0);
    adj[2].push_back(3); adj[3].push_back(2);
    // Node 4 is isolated

    auto [count, comp] = find_components(n, adj);
    assert(count == 3);
    assert(comp[0] == comp[1]);
    assert(comp[2] == comp[3]);
    assert(comp[0] != comp[2]);
    return 0;
}
