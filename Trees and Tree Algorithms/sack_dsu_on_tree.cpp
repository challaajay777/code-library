// Algorithm: DSU on Tree (Sack / Small-to-Large Tree Merging)
// Supports: Offline subtree queries (e.g. distinct color count in all subtrees)
// Indexing: 0-based vertex indices [0, n - 1]
// Complexity: O(n log n) total time, O(n) memory
// Preconditions: Connected tree, color vector size n

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

struct DsuOnTree {
    int n;
    vector<vector<int>> adj;
    vector<int> color;
    vector<int> sz, heavy, tin, tout, node_at;
    int timer = 0;

    // State for answering subtree queries (e.g., color frequency, distinct colors count)
    vector<int> freq;
    int distinct_count = 0;
    vector<int> ans;

    DsuOnTree(int n, const vector<int>& c)
        : n(n), adj(n), color(c), sz(n, 0), heavy(n, -1),
          tin(n, 0), tout(n, 0), node_at(n, 0), ans(n, 0) {
        int max_c = *max_element(c.begin(), c.end());
        freq.assign(max_c + 1, 0);
    }

    void add_edge(int u, int v) {
        assert(0 <= u && u < n && 0 <= v && v < n);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

private:
    void dfs_sz(int u, int p) {
        sz[u] = 1;
        tin[u] = timer;
        node_at[timer++] = u;
        int max_sz = 0;

        for (int v : adj[u]) {
            if (v == p) continue;
            dfs_sz(v, u);
            sz[u] += sz[v];
            if (sz[v] > max_sz) {
                max_sz = sz[v];
                heavy[u] = v;
            }
        }
        tout[u] = timer - 1;
    }

    void add_node(int u) {
        int c = color[u];
        if (freq[c] == 0) distinct_count++;
        freq[c]++;
    }

    void remove_node(int u) {
        int c = color[u];
        freq[c]--;
        if (freq[c] == 0) distinct_count--;
    }

    void dfs_sack(int u, int p, bool keep) {
        // Run light children without keeping their data
        for (int v : adj[u]) {
            if (v != p && v != heavy[u]) {
                dfs_sack(v, u, false);
            }
        }

        // Run heavy child and keep its data
        if (heavy[u] != -1) {
            dfs_sack(heavy[u], u, true);
        }

        // Add u and light subtrees
        add_node(u);
        for (int v : adj[u]) {
            if (v != p && v != heavy[u]) {
                for (int t = tin[v]; t <= tout[v]; ++t) {
                    add_node(node_at[t]);
                }
            }
        }

        ans[u] = distinct_count;

        if (!keep) {
            for (int t = tin[u]; t <= tout[u]; ++t) {
                remove_node(node_at[t]);
            }
        }
    }

public:
    // Returns distinct colors count for every subtree
    vector<int> solve(int root = 0) {
        timer = 0;
        distinct_count = 0;
        dfs_sz(root, -1);
        dfs_sack(root, -1, true);
        return ans;
    }
};
