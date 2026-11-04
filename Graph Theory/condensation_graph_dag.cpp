// Algorithm: Condensation Graph Construction via Tarjan
// Purpose: Contracts Strongly Connected Components into supernodes forming a topological DAG.
// Time Complexity: O(V + E)
// Space Complexity: O(V + E)
// Preconditions: Directed graph.

#include <iostream>
#include <vector>
#include <stack>
#include <set>
#include <cassert>
#include <algorithm>

struct CondensationGraph {
    int n, timer, scc_count;
    std::vector<std::vector<int>> adj;
    std::vector<int> tin, low, comp;
    std::stack<int> st;
    std::vector<bool> on_stack;
    std::vector<std::vector<int>> dag_adj;

    CondensationGraph(int n) : n(n), timer(0), scc_count(0), adj(n),
                               tin(n, 0), low(n, 0), comp(n, -1), on_stack(n, false) {}

    void add_edge(int u, int v) { adj[u].push_back(v); }

    void dfs(int u) {
        tin[u] = low[u] = ++timer;
        st.push(u);
        on_stack[u] = true;

        for (int v : adj[u]) {
            if (!tin[v]) {
                dfs(v);
                low[u] = std::min(low[u], low[v]);
            } else if (on_stack[v]) {
                low[u] = std::min(low[u], tin[v]);
            }
        }

        if (low[u] == tin[u]) {
            while (true) {
                int x = st.top();
                st.pop();
                on_stack[x] = false;
                comp[x] = scc_count;
                if (x == u) break;
            }
            scc_count++;
        }
    }

    void build() {
        for (int i = 0; i < n; ++i) if (!tin[i]) dfs(i);

        dag_adj.resize(scc_count);
        std::set<std::pair<int, int>> unique_edges;
        for (int u = 0; u < n; ++u) {
            for (int v : adj[u]) {
                if (comp[u] != comp[v]) {
                    unique_edges.insert({comp[u], comp[v]});
                }
            }
        }
        for (auto [cu, cv] : unique_edges) dag_adj[cu].push_back(cv);
    }
};

int main() {
    CondensationGraph cg(4);
    cg.add_edge(0, 1);
    cg.add_edge(1, 0); // SCC {0, 1}
    cg.add_edge(1, 2);
    cg.add_edge(2, 3);
    cg.build();

    assert(cg.scc_count == 3);
    assert(cg.comp[0] == cg.comp[1]);
    return 0;
}
