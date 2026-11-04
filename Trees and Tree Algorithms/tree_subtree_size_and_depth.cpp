// Algorithm: Subtree Sizes, Depths, and Heights DFS
// Purpose: Computes basic tree topological invariants (subtree size, depth, height) in single DFS.
// Time Complexity: O(N)
// Space Complexity: O(N)
// Preconditions: Connected rooted tree.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

struct TreeMetrics {
    std::vector<int> sz, depth, height;

    TreeMetrics(int n, const std::vector<std::vector<int>>& adj, int root = 0)
        : sz(n, 1), depth(n, 0), height(n, 0) {
        dfs(root, -1, 0, adj);
    }

    void dfs(int u, int p, int d, const std::vector<std::vector<int>>& adj) {
        depth[u] = d;
        for (int v : adj[u]) {
            if (v != p) {
                dfs(v, u, d + 1, adj);
                sz[u] += sz[v];
                height[u] = std::max(height[u], height[v] + 1);
            }
        }
    }
};

int main() {
    int n = 4;
    std::vector<std::vector<int>> adj(n);
    adj[0] = {1, 2}; adj[1] = {0, 3}; adj[2] = {0}; adj[3] = {1};

    TreeMetrics tm(n, adj, 0);
    assert(tm.sz[0] == 4);
    assert(tm.sz[1] == 2);
    assert(tm.depth[3] == 2);
    assert(tm.height[0] == 2);
    return 0;
}
