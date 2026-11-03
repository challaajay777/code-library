// Algorithm: Prim's Minimum Spanning Tree
// Supports: Minimum spanning tree on connected undirected graphs with priority queue
// Indexing: 0-based vertex indices [0, n - 1]
// Complexity: O(E log V) time, O(V + E) memory
// Preconditions: Graph is connected; 0 <= u, v < n

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

struct PrimMST {
    struct Edge {
        int to;
        long long w;
    };

    int n;
    vector<vector<Edge>> adj;

    explicit PrimMST(int n) : n(n), adj(n) {}

    void add_edge(int u, int v, long long w) {
        assert(0 <= u && u < n && 0 <= v && v < n);
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    // Returns {total_mst_weight, mst_parent_edges}. If disconnected, total_weight will be -1.
    pair<long long, vector<pair<int, int>>> solve(int start_node = 0) {
        if (n == 0) return {0, {}};
        assert(0 <= start_node && start_node < n);

        vector<bool> in_mst(n, false);
        vector<long long> min_edge(n, 1e18);
        vector<int> parent(n, -1);

        using Pair = pair<long long, int>;
        priority_queue<Pair, vector<Pair>, greater<Pair>> pq;

        min_edge[start_node] = 0;
        pq.push({0, start_node});

        long long total_weight = 0;
        int visited_count = 0;

        while (!pq.empty()) {
            auto [w, u] = pq.top();
            pq.pop();

            if (in_mst[u]) continue;
            in_mst[u] = true;
            total_weight += w;
            visited_count++;

            for (const auto& e : adj[u]) {
                int v = e.to;
                if (!in_mst[v] && e.w < min_edge[v]) {
                    min_edge[v] = e.w;
                    parent[v] = u;
                    pq.push({min_edge[v], v});
                }
            }
        }

        if (visited_count < n) return {-1, {}}; // Graph is disconnected

        vector<pair<int, int>> mst_edges;
        for (int i = 0; i < n; ++i) {
            if (parent[i] != -1) {
                mst_edges.push_back({parent[i], i});
            }
        }
        return {total_weight, mst_edges};
    }
};
