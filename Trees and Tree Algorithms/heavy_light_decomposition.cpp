// Algorithm: Heavy-Light Decomposition (HLD)
// Supports: Tree path queries/updates in O(log^2 n), subtree queries/updates in O(log n)
// Indexing: 0-based vertex indices [0, n - 1], mapped to 0-based pos array
// Complexity: O(n) preprocessing, O(log^2 n) per path operation, O(n) memory
// Preconditions: Tree is connected; 0 <= u, v < n

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

struct HLD {
    int n;
    vector<vector<int>> adj;
    vector<int> parent, depth, heavy, head, pos, sz;
    int cur_pos = 0;

    explicit HLD(int n)
        : n(n), adj(n), parent(n, -1), depth(n, 0),
          heavy(n, -1), head(n, 0), pos(n, 0), sz(n, 0) {}

    void add_edge(int u, int v) {
        assert(0 <= u && u < n && 0 <= v && v < n);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void build(int root = 0) {
        cur_pos = 0;
        dfs_sz(root, -1, 0);
        dfs_hld(root, root);
    }

private:
    void dfs_sz(int u, int p, int d) {
        parent[u] = p;
        depth[u] = d;
        sz[u] = 1;
        int max_c_sz = 0;
        for (int v : adj[u]) {
            if (v == p) continue;
            dfs_sz(v, u, d + 1);
            sz[u] += sz[v];
            if (sz[v] > max_c_sz) {
                max_c_sz = sz[v];
                heavy[u] = v;
            }
        }
    }

    void dfs_hld(int u, int h) {
        head[u] = h;
        pos[u] = cur_pos++;
        if (heavy[u] != -1) {
            dfs_hld(heavy[u], h);
        }
        for (int v : adj[u]) {
            if (v != parent[u] && v != heavy[u]) {
                dfs_hld(v, v);
            }
        }
    }

public:
    // Decomposes path u-v into intervals [l, r] on the flattened tree
    template <typename Callback>
    void process_path(int u, int v, Callback cb) const {
        for (; head[u] != head[v]; v = parent[head[v]]) {
            if (depth[head[u]] > depth[head[v]]) swap(u, v);
            cb(pos[head[v]], pos[v]);
        }
        if (depth[u] > depth[v]) swap(u, v);
        cb(pos[u], pos[v]);
    }

    // Subtree of u forms contiguous range [pos[u], pos[u] + sz[u] - 1]
    pair<int, int> subtree_range(int u) const {
        assert(0 <= u && u < n);
        return {pos[u], pos[u] + sz[u] - 1};
    }

    int lca(int u, int v) const {
        for (; head[u] != head[v]; v = parent[head[v]]) {
            if (depth[head[u]] > depth[head[v]]) swap(u, v);
        }
        return depth[u] < depth[v] ? u : v;
    }
};
