// Algorithm: Tarjan's Offline LCA Algorithm via DSU
// Purpose: Processes Q LCA queries offline during a single DFS traversal in O(N + Q) time.
// Time Complexity: O((N + Q) * alpha(N))
// Space Complexity: O(N + Q)
// Preconditions: Connected tree and pre-known queries.

#include <iostream>
#include <vector>
#include <cassert>

struct DSU {
    std::vector<int> parent;
    DSU(int n) : parent(n) {
        for (int i = 0; i < n; ++i) parent[i] = i;
    }
    int find(int i) { return (parent[i] == i) ? i : (parent[i] = find(parent[i])); }
    void unite(int u, int v) { parent[find(u)] = find(v); }
};

void dfs_tarjan(int u, int p, const std::vector<std::vector<int>>& adj,
                const std::vector<std::vector<std::pair<int, int>>>& queries,
                DSU& dsu, std::vector<int>& ancestor, std::vector<bool>& visited,
                std::vector<int>& ans) {
    ancestor[u] = u;
    for (int v : adj[u]) {
        if (v != p) {
            dfs_tarjan(v, u, adj, queries, dsu, ancestor, visited, ans);
            dsu.unite(v, u);
            ancestor[dsu.find(u)] = u;
        }
    }
    visited[u] = true;
    for (auto [v, q_idx] : queries[u]) {
        if (visited[v]) {
            ans[q_idx] = ancestor[dsu.find(v)];
        }
    }
}

int main() {
    int n = 4;
    std::vector<std::vector<int>> adj(n);
    adj[0] = {1, 2}; adj[1] = {0, 3}; adj[2] = {0}; adj[3] = {1};

    std::vector<std::vector<std::pair<int, int>>> queries(n);
    queries[2].push_back({3, 0});
    queries[3].push_back({2, 0});

    DSU dsu(n);
    std::vector<int> ancestor(n), ans(1);
    std::vector<bool> visited(n, false);

    dfs_tarjan(0, -1, adj, queries, dsu, ancestor, visited, ans);
    assert(ans[0] == 0); // LCA of 2 and 3 is 0
    return 0;
}
