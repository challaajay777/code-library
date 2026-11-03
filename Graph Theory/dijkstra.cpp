// Algorithm: Dijkstra's Algorithm
// Supports: Single-source shortest paths on weighted graphs with nonnegative edge weights
// Indexing: 0-based vertex indices [0, n - 1]
// Complexity: O((V + E) log V) time, O(V + E) memory
// Preconditions: All edge weights are >= 0; 0 <= src < n

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

template <typename Weight = long long>
struct Dijkstra {
    struct Edge {
        int to;
        Weight w;
    };

    static constexpr Weight INF_WEIGHT = numeric_limits<Weight>::max() / 2;

    int n;
    vector<vector<Edge>> adj;
    vector<Weight> dist;
    vector<int> parent;

    explicit Dijkstra(int n) : n(n), adj(n), dist(n, INF_WEIGHT), parent(n, -1) {}

    void add_edge(int u, int v, Weight w, bool directed = false) {
        assert(0 <= u && u < n && 0 <= v && v < n);
        assert(w >= 0 && "Dijkstra requires nonnegative weights");
        adj[u].push_back({v, w});
        if (!directed) adj[v].push_back({u, w});
    }

    void run(int src) {
        assert(0 <= src && src < n);
        fill(dist.begin(), dist.end(), INF_WEIGHT);
        fill(parent.begin(), parent.end(), -1);

        using Pair = pair<Weight, int>;
        priority_queue<Pair, vector<Pair>, greater<Pair>> pq;

        dist[src] = 0;
        pq.push({0, src});

        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            if (d > dist[u]) continue;

            for (const auto& edge : adj[u]) {
                int v = edge.to;
                Weight w = edge.w;
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    parent[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }
    }

    vector<int> get_path(int target) const {
        assert(0 <= target && target < n);
        if (dist[target] == INF_WEIGHT) return {};
        vector<int> path;
        for (int cur = target; cur != -1; cur = parent[cur]) {
            path.push_back(cur);
        }
        reverse(path.begin(), path.end());
        return path;
    }
};
