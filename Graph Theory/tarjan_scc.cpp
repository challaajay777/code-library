// Algorithm: Tarjan's Strongly Connected Components (SCC)
// Supports: Partitioning directed graph into SCCs, condensation graph indexing
// Indexing: 0-based vertex indices [0, n - 1]
// Complexity: O(V + E) time, O(V + E) memory
// Preconditions: 0 <= u, v < n

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

struct TarjanSCC {
    int n;
    vector<vector<int>> adj;
    vector<int> dfn, low, comp;
    vector<bool> in_stack;
    vector<int> st;
    int timer = 0, comp_count = 0;

    explicit TarjanSCC(int n)
        : n(n), adj(n), dfn(n, -1), low(n, -1), comp(n, -1), in_stack(n, false) {}

    void add_edge(int u, int v) {
        assert(0 <= u && u < n && 0 <= v && v < n);
        adj[u].push_back(v);
    }

private:
    void dfs(int u) {
        dfn[u] = low[u] = ++timer;
        st.push_back(u);
        in_stack[u] = true;

        for (int v : adj[u]) {
            if (dfn[v] == -1) {
                dfs(v);
                low[u] = min(low[u], low[v]);
            } else if (in_stack[v]) {
                low[u] = min(low[u], dfn[v]);
            }
        }

        if (low[u] == dfn[u]) {
            while (true) {
                int node = st.back();
                st.pop_back();
                in_stack[node] = false;
                comp[node] = comp_count;
                if (node == u) break;
            }
            comp_count++;
        }
    }

public:
    // Computes SCCs. comp[u] gives the 0-based component ID of vertex u.
    void run() {
        fill(dfn.begin(), dfn.end(), -1);
        fill(low.begin(), low.end(), -1);
        fill(comp.begin(), comp.end(), -1);
        fill(in_stack.begin(), in_stack.end(), false);
        st.clear();
        timer = 0;
        comp_count = 0;

        for (int i = 0; i < n; ++i) {
            if (dfn[i] == -1) {
                dfs(i);
            }
        }
    }

    // Builds the condensed DAG of components
    vector<vector<int>> build_condensation() const {
        vector<vector<int>> cond_adj(comp_count);
        for (int u = 0; u < n; ++u) {
            for (int v : adj[u]) {
                if (comp[u] != comp[v]) {
                    cond_adj[comp[u]].push_back(comp[v]);
                }
            }
        }
        for (int i = 0; i < comp_count; ++i) {
            sort(cond_adj[i].begin(), cond_adj[i].end());
            cond_adj[i].erase(unique(cond_adj[i].begin(), cond_adj[i].end()), cond_adj[i].end());
        }
        return cond_adj;
    }
};
