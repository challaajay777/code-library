// Algorithm: Maximum Weight Path Between Any Two Nodes
// Purpose: Finds the maximum sum of vertex weights along any simple path in the tree in linear time.
// Time Complexity: O(N)
// Space Complexity: O(N)
// Preconditions: Tree with arbitrary real/integer vertex weights.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

long long max_path_sum_tree = -1e18;

long long dfs_max_path(int u, int p, const std::vector<std::vector<int>>& adj, const std::vector<int>& val) {
    long long max1 = 0, max2 = 0;
    for (int v : adj[u]) {
        if (v != p) {
            long long sub = dfs_max_path(v, u, adj, val);
            if (sub > max1) { max2 = max1; max1 = sub; }
            else if (sub > max2) { max2 = sub; }
        }
    }
    max_path_sum_tree = std::max(max_path_sum_tree, val[u] + max1 + max2);
    return val[u] + max1;
}

int main() {
    int n = 3;
    std::vector<std::vector<int>> adj(n);
    adj[0] = {1, 2}; adj[1] = {0}; adj[2] = {0};
    std::vector<int> val = {10, -2, 5};

    dfs_max_path(0, -1, adj, val);
    assert(max_path_sum_tree == 15); // 5 + 10
    return 0;
}
