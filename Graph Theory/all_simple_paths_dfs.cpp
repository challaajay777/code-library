// Algorithm: All Simple Paths Enumeration DFS
// Purpose: Finds all simple paths between source and destination in a general graph with backtracking.
// Time Complexity: O(V * Paths)
// Space Complexity: O(V)
// Preconditions: Graph with source and target vertices.

#include <iostream>
#include <vector>
#include <cassert>

void dfs_paths(int u, int dst, const std::vector<std::vector<int>>& adj,
               std::vector<bool>& vis, std::vector<int>& cur_path,
               std::vector<std::vector<int>>& all_paths) {
    vis[u] = true;
    cur_path.push_back(u);

    if (u == dst) {
        all_paths.push_back(cur_path);
    } else {
        for (int v : adj[u]) {
            if (!vis[v]) {
                dfs_paths(v, dst, adj, vis, cur_path, all_paths);
            }
        }
    }

    cur_path.pop_back();
    vis[u] = false;
}

std::vector<std::vector<int>> get_all_paths(int n, const std::vector<std::vector<int>>& adj, int src, int dst) {
    std::vector<bool> vis(n, false);
    std::vector<int> cur_path;
    std::vector<std::vector<int>> all_paths;
    dfs_paths(src, dst, adj, vis, cur_path, all_paths);
    return all_paths;
}

int main() {
    int n = 4;
    std::vector<std::vector<int>> adj(n);
    adj[0] = {1, 2, 3};
    adj[1] = {3};
    adj[2] = {0, 1};
    adj[3] = {};

    auto paths = get_all_paths(n, adj, 0, 3);
    // Paths: 0->3, 0->1->3
    assert((int)paths.size() == 2);
    return 0;
}
