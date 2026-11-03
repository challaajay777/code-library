// Algorithm: Kosaraju's Strongly Connected Components
// Supports: SCC decomposition via two DFS passes on original and transpose graphs
// Indexing: 0-based vertex indices [0, n - 1]
// Complexity: O(V + E) time, O(V + E) memory
// Preconditions: 0 <= u, v < n

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

struct KosarajuSCC {
    int n;
    vector<vector<int>> adj, radj;
    vector<int> comp;
    vector<bool> vis;
    vector<int> order;
    int comp_count = 0;

    explicit KosarajuSCC(int n) : n(n), adj(n), radj(n), comp(n, -1), vis(n, false) {}

    void add_edge(int u, int v) {
        assert(0 <= u && u < n && 0 <= v && v < n);
        adj[u].push_back(v);
        radj[v].push_back(u);
    }

private:
    void dfs1(int u) {
        vis[u] = true;
        for (int v : adj[u]) {
            if (!vis[v]) dfs1(v);
        }
        order.push_back(u);
    }

    void dfs2(int u, int c) {
        comp[u] = c;
        for (int v : radj[u]) {
            if (comp[v] == -1) dfs2(v, c);
        }
    }

public:
    void run() {
        fill(vis.begin(), vis.end(), false);
        order.clear();
        for (int i = 0; i < n; ++i) {
            if (!vis[i]) dfs1(i);
        }

        fill(comp.begin(), comp.end(), -1);
        comp_count = 0;
        reverse(order.begin(), order.end());

        for (int u : order) {
            if (comp[u] == -1) {
                dfs2(u, comp_count++);
            }
        }
    }
};
