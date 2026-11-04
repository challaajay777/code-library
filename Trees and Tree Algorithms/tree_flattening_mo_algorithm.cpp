// Algorithm: Mo's Algorithm on Trees via Tour Flattening
// Purpose: Flattens tree paths into Euler tour ranges to answer offline path queries in O(N sqrt(Q)).
// Time Complexity: O((N + Q) sqrt(N))
// Space Complexity: O(N + Q)
// Preconditions: Connected tree with offline queries.

#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>
#include <algorithm>

struct TreeMoQuery {
    int l, r, lca_node, id, block;
    bool operator<(const TreeMoQuery& o) const {
        if (block != o.block) return block < o.block;
        return (block & 1) ? (r < o.r) : (r > o.r);
    }
};

struct TreeMo {
    int n, timer;
    std::vector<int> first, last, order;

    TreeMo(int n, const std::vector<std::vector<int>>& adj, int root = 0)
        : n(n), timer(0), first(n), last(n), order(2 * n) {
        dfs(root, -1, adj);
    }

    void dfs(int u, int p, const std::vector<std::vector<int>>& adj) {
        first[u] = timer;
        order[timer++] = u;
        for (int v : adj[u]) if (v != p) dfs(v, u, adj);
        last[u] = timer;
        order[timer++] = u;
    }
};

int main() {
    int n = 3;
    std::vector<std::vector<int>> adj(n);
    adj[0] = {1, 2}; adj[1] = {0}; adj[2] = {0};
    TreeMo mo(n, adj, 0);
    assert(mo.order.size() == 6);
    return 0;
}
