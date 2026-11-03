// Algorithm: Euler Tour Tree Flattening
// Supports: Subtree range mapping [tin[u], tout[u]], O(1) ancestor check
// Indexing: 0-based vertex indices [0, n - 1], 0-based tour timestamps
// Complexity: O(n) preprocessing, O(1) subtree query bounds, O(n) memory
// Preconditions: Connected tree, 0 <= u, v < n

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

struct EulerTourTree {
    int n;
    vector<vector<int>> adj;
    vector<int> tin, tout, order;
    int timer = 0;

    explicit EulerTourTree(int n) : n(n), adj(n), tin(n, 0), tout(n, 0) {}

    void add_edge(int u, int v) {
        assert(0 <= u && u < n && 0 <= v && v < n);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void build(int root = 0) {
        timer = 0;
        order.clear();
        order.reserve(n);
        dfs(root, -1);
    }

private:
    void dfs(int u, int p) {
        tin[u] = timer++;
        order.push_back(u);
        for (int v : adj[u]) {
            if (v != p) {
                dfs(v, u);
            }
        }
        tout[u] = timer - 1;
    }

public:
    // Returns [L, R] inclusive interval representing subtree of u in 'order'
    pair<int, int> subtree_interval(int u) const {
        assert(0 <= u && u < n);
        return {tin[u], tout[u]};
    }

    // Returns true if u is an ancestor of v (or u == v)
    bool is_ancestor(int u, int v) const {
        assert(0 <= u && u < n && 0 <= v && v < n);
        return tin[u] <= tin[v] && tout[u] >= tout[v];
    }
};
