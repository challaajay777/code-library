// Algorithm: Biconnected Components (Hopcroft-Tarjan)
// Purpose: Decomposes undirected graph into maximal 2-vertex-connected subgraphs using DFS stack.
// Time Complexity: O(V + E)
// Space Complexity: O(V + E)
// Preconditions: Undirected graph.

#include <iostream>
#include <vector>
#include <stack>
#include <cassert>
#include <algorithm>

struct BCC {
    int n, timer;
    std::vector<std::vector<int>> adj;
    std::vector<int> tin, low;
    std::stack<std::pair<int, int>> st;
    std::vector<std::vector<std::pair<int, int>>> components;

    BCC(int n) : n(n), timer(0), adj(n), tin(n, 0), low(n, 0) {}

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs(int u, int p = -1) {
        tin[u] = low[u] = ++timer;
        for (int v : adj[u]) {
            if (v == p) continue;
            if (tin[v]) {
                low[u] = std::min(low[u], tin[v]);
                if (tin[v] < tin[u]) st.push({u, v});
            } else {
                st.push({u, v});
                dfs(v, u);
                low[u] = std::min(low[u], low[v]);
                if (low[v] >= tin[u]) {
                    std::vector<std::pair<int, int>> comp;
                    while (true) {
                        auto edge = st.top();
                        st.pop();
                        comp.push_back(edge);
                        if (edge == std::make_pair(u, v)) break;
                    }
                    components.push_back(comp);
                }
            }
        }
    }

    void build() {
        for (int i = 0; i < n; ++i) if (!tin[i]) dfs(i);
    }
};

int main() {
    BCC bcc(4);
    bcc.add_edge(0, 1);
    bcc.add_edge(1, 2);
    bcc.add_edge(2, 0);
    bcc.add_edge(2, 3);
    bcc.build();
    assert(bcc.components.size() == 2);
    return 0;
}
