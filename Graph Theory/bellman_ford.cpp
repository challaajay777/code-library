// Algorithm: Bellman-Ford Algorithm
// Supports: Shortest paths with arbitrary edge weights, negative cycle detection
// Indexing: 0-based vertex indices [0, n - 1]
// Complexity: O(V * E) time, O(V + E) memory
// Preconditions: 0 <= src < n; handles negative edges properly

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

struct BellmanFord {
    struct Edge {
        int u, v;
        long long w;
    };

    static constexpr long long INF_WEIGHT = 1e18;
    static constexpr long long NEG_INF = -1e18;

    int n;
    vector<Edge> edges;
    vector<long long> dist;
    vector<int> parent;

    explicit BellmanFord(int n) : n(n), dist(n, INF_WEIGHT), parent(n, -1) {}

    void add_edge(int u, int v, long long w) {
        assert(0 <= u && u < n && 0 <= v && v < n);
        edges.push_back({u, v, w});
    }

    // Returns true if a negative cycle reachable from src exists
    bool run(int src) {
        assert(0 <= src && src < n);
        fill(dist.begin(), dist.end(), INF_WEIGHT);
        fill(parent.begin(), parent.end(), -1);
        dist[src] = 0;

        for (int iter = 0; iter < n - 1; ++iter) {
            bool any_relaxed = false;
            for (const auto& e : edges) {
                if (dist[e.u] < INF_WEIGHT && dist[e.u] + e.w < dist[e.v]) {
                    dist[e.v] = max(NEG_INF, dist[e.u] + e.w);
                    parent[e.v] = e.u;
                    any_relaxed = true;
                }
            }
            if (!any_relaxed) break;
        }

        // Check for reachable negative cycles
        for (const auto& e : edges) {
            if (dist[e.u] < INF_WEIGHT && dist[e.u] + e.w < dist[e.v]) {
                return true; // Negative cycle detected
            }
        }
        return false;
    }

    // Finds the sequence of vertices forming a negative cycle if one exists
    vector<int> find_negative_cycle() {
        vector<long long> d(n, 0);
        vector<int> p(n, -1);
        int last_relaxed = -1;

        for (int iter = 0; iter < n; ++iter) {
            last_relaxed = -1;
            for (const auto& e : edges) {
                if (d[e.u] + e.w < d[e.v]) {
                    d[e.v] = d[e.u] + e.w;
                    p[e.v] = e.u;
                    last_relaxed = e.v;
                }
            }
        }

        if (last_relaxed == -1) return {};

        int cur = last_relaxed;
        for (int i = 0; i < n; ++i) cur = p[cur];

        vector<int> cycle;
        for (int v = cur; ; v = p[v]) {
            cycle.push_back(v);
            if (v == cur && cycle.size() > 1) break;
        }
        reverse(cycle.begin(), cycle.end());
        return cycle;
    }
};
