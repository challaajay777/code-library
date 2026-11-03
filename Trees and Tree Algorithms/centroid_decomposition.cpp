// Algorithm: Centroid Decomposition
// Supports: Tree centroid finding, centroid tree hierarchy construction, centroid depth
// Indexing: 0-based vertex indices [0, n - 1]
// Complexity: O(n log n) construction time, O(n) memory, centroid tree height <= log2(n)
// Preconditions: Connected undirected tree

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

struct CentroidDecomposition {
    int n;
    vector<vector<int>> adj;
    vector<int> sz;
    vector<bool> removed;
    vector<int> c_parent;
    vector<int> c_depth;
    int root = -1;

    explicit CentroidDecomposition(int n)
        : n(n), adj(n), sz(n, 0), removed(n, false), c_parent(n, -1), c_depth(n, 0) {}

    void add_edge(int u, int v) {
        assert(0 <= u && u < n && 0 <= v && v < n);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

private:
    int dfs_sz(int u, int p) {
        sz[u] = 1;
        for (int v : adj[u]) {
            if (v != p && !removed[v]) {
                sz[u] += dfs_sz(v, u);
            }
        }
        return sz[u];
    }

    int get_centroid(int u, int p, int total_sz) {
        for (int v : adj[u]) {
            if (v != p && !removed[v] && sz[v] > total_sz / 2) {
                return get_centroid(v, u, total_sz);
            }
        }
        return u;
    }

    int decompose(int u, int p, int depth) {
        int total = dfs_sz(u, -1);
        int c = get_centroid(u, -1, total);
        removed[c] = true;
        c_parent[c] = p;
        c_depth[c] = depth;

        for (int v : adj[c]) {
            if (!removed[v]) {
                decompose(v, c, depth + 1);
            }
        }
        return c;
    }

public:
    void build() {
        fill(removed.begin(), removed.end(), false);
        fill(c_parent.begin(), c_parent.end(), -1);
        fill(c_depth.begin(), c_depth.end(), 0);
        root = decompose(0, -1, 0);
    }
};
