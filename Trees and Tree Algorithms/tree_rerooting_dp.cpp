// Algorithm: Tree Rerooting DP (All Distances Sum)
// Supports: Computing sum of distances from each node to all other tree nodes
// Indexing: 0-based vertex indices [0, n - 1]
// Complexity: O(n) total time, O(n) memory
// Preconditions: Connected undirected tree

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

struct TreeRerooting {
    int n;
    vector<vector<int>> adj;
    vector<int> sz;
    vector<long long> down_dist;
    vector<long long> total_dist;

    explicit TreeRerooting(int n)
        : n(n), adj(n), sz(n, 0), down_dist(n, 0), total_dist(n, 0) {}

    void add_edge(int u, int v) {
        assert(0 <= u && u < n && 0 <= v && v < n);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

private:
    void dfs_down(int u, int p) {
        sz[u] = 1;
        down_dist[u] = 0;
        for (int v : adj[u]) {
            if (v == p) continue;
            dfs_down(v, u);
            sz[u] += sz[v];
            down_dist[u] += down_dist[v] + sz[v];
        }
    }

    void dfs_reroot(int u, int p) {
        for (int v : adj[u]) {
            if (v == p) continue;
            // When rerooting from u to v:
            // total_dist[v] = total_dist[u] - sz[v] + (n - sz[v])
            total_dist[v] = total_dist[u] + n - 2 * sz[v];
            dfs_reroot(v, u);
        }
    }

public:
    // Returns vector of size n where res[u] = sum of distances from u to all v
    vector<long long> solve() {
        if (n == 0) return {};
        dfs_down(0, -1);
        total_dist[0] = down_dist[0];
        dfs_reroot(0, -1);
        return total_dist;
    }
};
