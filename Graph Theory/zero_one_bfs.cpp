// Algorithm: 0-1 BFS
// Supports: Shortest paths on graphs with edge weights restricted to {0, 1}
// Indexing: 0-based vertex indices [0, n - 1]
// Complexity: O(V + E) time, O(V) memory
// Preconditions: Edge weights are strictly 0 or 1; 0 <= src < n

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

struct ZeroOneBFS {
    struct Edge {
        int to;
        int weight; // 0 or 1
    };

    int n;
    vector<vector<Edge>> adj;
    vector<int> dist;
    vector<int> parent;
    static constexpr int INF = 1e9 + 7;

    explicit ZeroOneBFS(int n) : n(n), adj(n), dist(n, INF), parent(n, -1) {}

    void add_edge(int u, int v, int w, bool directed = false) {
        assert(0 <= u && u < n && 0 <= v && v < n);
        assert(w == 0 || w == 1);
        adj[u].push_back({v, w});
        if (!directed) adj[v].push_back({u, w});
    }

    void run(int src) {
        assert(0 <= src && src < n);
        fill(dist.begin(), dist.end(), INF);
        fill(parent.begin(), parent.end(), -1);
        deque<int> dq;
        dist[src] = 0;
        dq.push_back(src);

        while (!dq.empty()) {
            int u = dq.front();
            dq.pop_front();

            for (const auto& edge : adj[u]) {
                int v = edge.to;
                int w = edge.weight;
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    parent[v] = u;
                    if (w == 0) {
                        dq.push_front(v);
                    } else {
                        dq.push_back(v);
                    }
                }
            }
        }
    }

    vector<int> get_path(int target) const {
        assert(0 <= target && target < n);
        if (dist[target] == INF) return {};
        vector<int> path;
        for (int cur = target; cur != -1; cur = parent[cur]) {
            path.push_back(cur);
        }
        reverse(path.begin(), path.end());
        return path;
    }
};
