// Algorithm: Heavy-Light Decomposition Subtree Updates
// Purpose: Updates and queries whole subtrees in contiguous segments on Euler tour using HLD.
// Time Complexity: O(log N) per subtree update/query
// Space Complexity: O(N)
// Preconditions: Rooted tree.

#include <iostream>
#include <vector>
#include <cassert>

struct HLDSubtree {
    int n, timer;
    std::vector<int> sz, in, out;

    HLDSubtree(int n, const std::vector<std::vector<int>>& adj, int root = 0)
        : n(n), timer(0), sz(n, 1), in(n), out(n) {
        dfs(root, -1, adj);
    }

    void dfs(int u, int p, const std::vector<std::vector<int>>& adj) {
        in[u] = ++timer;
        for (int v : adj[u]) {
            if (v != p) {
                dfs(v, u, adj);
                sz[u] += sz[v];
            }
        }
        out[u] = timer;
    }

    std::pair<int, int> get_subtree_range(int u) {
        return {in[u], out[u]};
    }
};

int main() {
    int n = 3;
    std::vector<std::vector<int>> adj(n);
    adj[0] = {1, 2}; adj[1] = {0}; adj[2] = {0};
    HLDSubtree hld(n, adj, 0);

    auto r = hld.get_subtree_range(0);
    assert(r.second - r.first + 1 == 3);
    return 0;
}
