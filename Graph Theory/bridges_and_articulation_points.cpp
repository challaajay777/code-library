// Algorithm: Bridges and Articulation Points (Cut Vertices & Edges)
// Supports: Finding all bridges and articulation points in an undirected multigraph
// Indexing: 0-based vertex indices [0, n - 1]
// Complexity: O(V + E) time, O(V + E) memory
// Preconditions: Undirected graph; handles parallel edges and self loops

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

struct BridgesAndArticulationPoints {
    struct Edge {
        int to;
        int id;
    };

    int n;
    int edge_count = 0;
    vector<vector<Edge>> adj;
    vector<int> tin, low;
    vector<bool> is_articulation;
    vector<pair<int, int>> bridges;
    int timer = 0;

    explicit BridgesAndArticulationPoints(int n)
        : n(n), adj(n), tin(n, -1), low(n, -1), is_articulation(n, false) {}

    void add_edge(int u, int v) {
        assert(0 <= u && u < n && 0 <= v && v < n);
        int id = edge_count++;
        adj[u].push_back({v, id});
        adj[v].push_back({u, id});
    }

private:
    void dfs(int u, int parent_edge_id) {
        tin[u] = low[u] = ++timer;
        int children = 0;

        for (const auto& e : adj[u]) {
            int v = e.to;
            int id = e.id;
            if (id == parent_edge_id) continue;

            if (tin[v] != -1) {
                // Back-edge
                low[u] = min(low[u], tin[v]);
            } else {
                // Tree-edge
                children++;
                dfs(v, id);
                low[u] = min(low[u], low[v]);

                if (low[v] > tin[u]) {
                    bridges.push_back({min(u, v), max(u, v)});
                }
                if (low[v] >= tin[u] && parent_edge_id != -1) {
                    is_articulation[u] = true;
                }
            }
        }

        if (parent_edge_id == -1 && children > 1) {
            is_articulation[u] = true;
        }
    }

public:
    void run() {
        fill(tin.begin(), tin.end(), -1);
        fill(low.begin(), low.end(), -1);
        fill(is_articulation.begin(), is_articulation.end(), false);
        bridges.clear();
        timer = 0;

        for (int i = 0; i < n; ++i) {
            if (tin[i] == -1) {
                dfs(i, -1);
            }
        }
    }

    vector<int> get_articulation_points() const {
        vector<int> res;
        for (int i = 0; i < n; ++i) {
            if (is_articulation[i]) res.push_back(i);
        }
        return res;
    }
};
