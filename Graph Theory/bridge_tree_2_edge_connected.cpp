// Algorithm: 2-Edge Connected Components and Bridge Tree
// Purpose: Contracts 2-edge-connected components into vertices of an acyclic bridge tree.
// Time Complexity: O(V + E)
// Space Complexity: O(V + E)
// Preconditions: Connected undirected graph.

#include <iostream>
#include <vector>
#include <stack>
#include <cassert>
#include <algorithm>

struct BridgeTree {
    struct Edge {
        int to, id;
    };
    int n, timer, num_comp;
    std::vector<std::vector<Edge>> adj;
    std::vector<int> tin, low, comp;
    std::vector<bool> is_bridge;
    std::stack<int> st;

    BridgeTree(int n, int m) : n(n), timer(0), num_comp(0), adj(n),
                               tin(n, 0), low(n, 0), comp(n, -1), is_bridge(m, false) {}

    void add_edge(int u, int v, int id) {
        adj[u].push_back({v, id});
        adj[v].push_back({u, id});
    }

    void dfs_bridges(int u, int p_edge) {
        tin[u] = low[u] = ++timer;
        for (const auto& e : adj[u]) {
            if (e.id == p_edge) continue;
            if (tin[e.to]) {
                low[u] = std::min(low[u], tin[e.to]);
            } else {
                dfs_bridges(e.to, e.id);
                low[u] = std::min(low[u], low[e.to]);
                if (low[e.to] > tin[u]) {
                    is_bridge[e.id] = true;
                }
            }
        }
    }

    void dfs_comp(int u, int c) {
        comp[u] = c;
        for (const auto& e : adj[u]) {
            if (!is_bridge[e.id] && comp[e.to] == -1) {
                dfs_comp(e.to, c);
            }
        }
    }

    void build() {
        dfs_bridges(0, -1);
        for (int i = 0; i < n; ++i) {
            if (comp[i] == -1) {
                dfs_comp(i, num_comp++);
            }
        }
    }
};

int main() {
    BridgeTree bt(4, 4);
    bt.add_edge(0, 1, 0);
    bt.add_edge(1, 2, 1);
    bt.add_edge(2, 0, 2);
    bt.add_edge(2, 3, 3); // bridge
    bt.build();

    assert(bt.is_bridge[3]);
    assert(bt.num_comp == 2);
    assert(bt.comp[0] == bt.comp[1] && bt.comp[1] == bt.comp[2]);
    assert(bt.comp[3] != bt.comp[2]);
    return 0;
}
