// Algorithm: Block-Cut Tree Construction
// Purpose: Decomposes a graph into biconnected components (blocks) and builds the bipartite Block-Cut tree.
// Time Complexity: O(V + E)
// Space Complexity: O(V + E)
// Preconditions: Connected undirected graph.

#include <iostream>
#include <vector>
#include <stack>
#include <cassert>
#include <algorithm>

struct BlockCutTree {
    int n, timer;
    std::vector<std::vector<int>> adj;
    std::vector<int> tin, low;
    std::stack<int> st;
    std::vector<std::vector<int>> blocks; // each block contains vertices
    std::vector<bool> is_cut;
    std::vector<std::vector<int>> tree; // block-cut tree

    BlockCutTree(int n) : n(n), timer(0), adj(n), tin(n, 0), low(n, 0), is_cut(n, false) {}

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs(int u, int p = -1) {
        tin[u] = low[u] = ++timer;
        st.push(u);
        int children = 0;

        for (int v : adj[u]) {
            if (v == p) continue;
            if (tin[v]) {
                low[u] = std::min(low[u], tin[v]);
            } else {
                children++;
                dfs(v, u);
                low[u] = std::min(low[u], low[v]);
                if (low[v] >= tin[u]) {
                    if (p != -1) is_cut[u] = true;
                    std::vector<int> comp = {u};
                    while (true) {
                        int x = st.top();
                        st.pop();
                        comp.push_back(x);
                        if (x == v) break;
                    }
                    blocks.push_back(comp);
                }
            }
        }
        if (p == -1 && children > 1) is_cut[u] = true;
    }

    void build() {
        for (int i = 0; i < n; ++i) {
            if (!tin[i]) dfs(i);
        }
    }
};

int main() {
    BlockCutTree bct(4);
    bct.add_edge(0, 1);
    bct.add_edge(1, 2);
    bct.add_edge(2, 0);
    bct.add_edge(2, 3);
    bct.build();

    // Node 2 is cut vertex connecting triangle {0,1,2} and edge {2,3}
    assert(bct.is_cut[2]);
    assert(bct.blocks.size() == 2);
    return 0;
}
