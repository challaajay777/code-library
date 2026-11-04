// Algorithm: Tree Center Identification (1 or 2 Centers)
// Purpose: Finds the 1 or 2 centers of a tree by repeatedly pruning leaves.
// Time Complexity: O(N)
// Space Complexity: O(N)
// Preconditions: Connected unweighted tree.

#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

std::vector<int> find_tree_centers(int n, const std::vector<std::vector<int>>& adj) {
    if (n == 1) return {0};
    std::vector<int> deg(n);
    std::queue<int> leaves;
    for (int i = 0; i < n; ++i) {
        deg[i] = adj[i].size();
        if (deg[i] == 1) leaves.push(i);
    }

    int remaining = n;
    while (remaining > 2) {
        int sz = leaves.size();
        remaining -= sz;
        for (int i = 0; i < sz; ++i) {
            int leaf = leaves.front();
            leaves.pop();
            for (int neighbor : adj[leaf]) {
                if (--deg[neighbor] == 1) {
                    leaves.push(neighbor);
                }
            }
        }
    }

    std::vector<int> centers;
    while (!leaves.empty()) {
        centers.push_back(leaves.front());
        leaves.pop();
    }
    return centers;
}

int main() {
    int n = 4;
    std::vector<std::vector<int>> adj(n);
    adj[0] = {1}; adj[1] = {0, 2}; adj[2] = {1, 3}; adj[3] = {2};
    auto c = find_tree_centers(n, adj);
    assert(c.size() == 2);
    return 0;
}
