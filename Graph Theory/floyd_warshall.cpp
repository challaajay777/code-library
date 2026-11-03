// Algorithm: Floyd-Warshall Algorithm
// Supports: All-pairs shortest paths, path reconstruction, negative cycle detection
// Indexing: 0-based vertex indices [0, n - 1]
// Complexity: O(V^3) time, O(V^2) memory
// Preconditions: Graph vertices 0 <= u, v < n

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

struct FloydWarshall {
    static constexpr long long INF_WEIGHT = 1e18;

    int n;
    vector<vector<long long>> dist;
    vector<vector<int>> next_node;

    explicit FloydWarshall(int n)
        : n(n),
          dist(n, vector<long long>(n, INF_WEIGHT)),
          next_node(n, vector<int>(n, -1)) {
        for (int i = 0; i < n; ++i) {
            dist[i][i] = 0;
            next_node[i][i] = i;
        }
    }

    void add_edge(int u, int v, long long w, bool directed = true) {
        assert(0 <= u && u < n && 0 <= v && v < n);
        if (w < dist[u][v]) {
            dist[u][v] = w;
            next_node[u][v] = v;
        }
        if (!directed && w < dist[v][u]) {
            dist[v][u] = w;
            next_node[v][u] = u;
        }
    }

    // Computes all-pairs shortest paths. Returns false if any negative cycle exists.
    bool compute() {
        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (dist[i][k] < INF_WEIGHT && dist[k][j] < INF_WEIGHT) {
                        if (dist[i][k] + dist[k][j] < dist[i][j]) {
                            dist[i][j] = dist[i][k] + dist[k][j];
                            next_node[i][j] = next_node[i][k];
                        }
                    }
                }
            }
        }

        // Check for negative cycles
        for (int i = 0; i < n; ++i) {
            if (dist[i][i] < 0) return false;
        }
        return true;
    }

    // Reconstructs sequence of vertices from u to v
    vector<int> get_path(int u, int v) const {
        assert(0 <= u && u < n && 0 <= v && v < n);
        if (dist[u][v] == INF_WEIGHT) return {};
        vector<int> path = {u};
        while (u != v) {
            u = next_node[u][v];
            if (u == -1) return {};
            path.push_back(u);
        }
        return path;
    }
};
