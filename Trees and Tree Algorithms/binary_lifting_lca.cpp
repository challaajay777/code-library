// Algorithm: Binary Lifting Lowest Common Ancestor (LCA)
// Supports: LCA queries, k-th ancestor, tree distance queries
// Indexing: 0-based vertex indices [0, n - 1]
// Complexity: O(n log n) preprocessing, O(log n) per query, O(n log n) memory
// Preconditions: Connected tree, 0 <= u, v < n, root specified

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

struct BinaryLiftingLCA {
    int n, LOG;
    vector<vector<int>> adj;
    vector<int> depth;
    vector<vector<int>> up;

    explicit BinaryLiftingLCA(int n, int root = 0) : n(n), adj(n), depth(n, 0) {
        LOG = 1;
        while ((1 << LOG) <= n) LOG++;
        up.assign(LOG, vector<int>(n, -1));
    }

    void add_edge(int u, int v) {
        assert(0 <= u && u < n && 0 <= v && v < n);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void build(int root = 0) {
        depth[root] = 0;
        up[0][root] = root;
        dfs(root, root);
        for (int j = 1; j < LOG; ++j) {
            for (int i = 0; i < n; ++i) {
                up[j][i] = up[j - 1][up[j - 1][i]];
            }
        }
    }

private:
    void dfs(int u, int p) {
        for (int v : adj[u]) {
            if (v == p) continue;
            depth[v] = depth[u] + 1;
            up[0][v] = u;
            dfs(v, u);
        }
    }

public:
    // Returns k-th ancestor of u, or -1 if depth[u] < k
    int get_kth_ancestor(int u, int k) const {
        assert(0 <= u && u < n && k >= 0);
        if (depth[u] < k) return -1;
        for (int j = 0; j < LOG; ++j) {
            if (k & (1 << j)) {
                u = up[j][u];
            }
        }
        return u;
    }

    // Returns Lowest Common Ancestor of u and v
    int lca(int u, int v) const {
        assert(0 <= u && u < n && 0 <= v && v < n);
        if (depth[u] < depth[v]) swap(u, v);
        // Lift u to same depth as v
        u = get_kth_ancestor(u, depth[u] - depth[v]);
        if (u == v) return u;

        for (int j = LOG - 1; j >= 0; --j) {
            if (up[j][u] != up[j][v]) {
                u = up[j][u];
                v = up[j][v];
            }
        }
        return up[0][u];
    }

    // Returns distance (number of edges) between u and v
    int distance(int u, int v) const {
        return depth[u] + depth[v] - 2 * depth[lca(u, v)];
    }
};
