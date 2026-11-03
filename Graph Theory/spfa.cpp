// Algorithm: Shortest Path Faster Algorithm (SPFA)
// Supports: Single-source shortest paths with negative edges, cycle detection, SLF optimization
// Indexing: 0-based vertex indices [0, n - 1]
// Complexity: O(E) average time, O(V * E) worst-case, O(V + E) memory
// Preconditions: 0 <= src < n; handles negative edges properly

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

struct SPFA {
    struct Edge {
        int to;
        long long w;
    };

    static constexpr long long INF_WEIGHT = 1e18;

    int n;
    vector<vector<Edge>> adj;
    vector<long long> dist;
    vector<int> relax_count;
    vector<bool> in_queue;

    explicit SPFA(int n) : n(n), adj(n), dist(n, INF_WEIGHT), relax_count(n, 0), in_queue(n, false) {}

    void add_edge(int u, int v, long long w, bool directed = true) {
        assert(0 <= u && u < n && 0 <= v && v < n);
        adj[u].push_back({v, w});
        if (!directed) adj[v].push_back({u, w});
    }

    // Returns true if shortest paths computed successfully, false if negative cycle detected
    bool run(int src) {
        assert(0 <= src && src < n);
        fill(dist.begin(), dist.end(), INF_WEIGHT);
        fill(relax_count.begin(), relax_count.end(), 0);
        fill(in_queue.begin(), in_queue.end(), false);

        deque<int> dq;
        dist[src] = 0;
        dq.push_back(src);
        in_queue[src] = true;

        while (!dq.empty()) {
            int u = dq.front();
            dq.pop_front();
            in_queue[u] = false;

            for (const auto& edge : adj[u]) {
                int v = edge.to;
                long long w = edge.w;
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    if (!in_queue[v]) {
                        dq.push_back(v);
                        in_queue[v] = true;
                        relax_count[v]++;
                        if (relax_count[v] >= n) {
                            return false; // Negative cycle detected
                        }
                        // Small Label to Front (SLF) optimization
                        if (!dq.empty() && dist[dq.back()] < dist[dq.front()]) {
                            int back_node = dq.back();
                            dq.pop_back();
                            dq.push_front(back_node);
                        }
                    }
                }
            }
        }
        return true;
    }
};
