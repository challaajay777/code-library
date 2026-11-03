// Algorithm: Breadth-First Search (BFS) Shortest Path
// Supports: Shortest path in unweighted graphs, distances, path reconstruction
// Indexing: 0-based vertex indices [0, n - 1]
// Complexity: O(V + E) time, O(V) memory
// Preconditions: 0 <= src, target < n

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

struct BFS {
    int n;
    vector<vector<int>> adj;
    vector<int> dist;
    vector<int> parent;

    explicit BFS(int n) : n(n), adj(n), dist(n, -1), parent(n, -1) {}

    void add_edge(int u, int v, bool directed = false) {
        assert(0 <= u && u < n && 0 <= v && v < n);
        adj[u].push_back(v);
        if (!directed) adj[v].push_back(u);
    }

    void run(int src) {
        assert(0 <= src && src < n);
        fill(dist.begin(), dist.end(), -1);
        fill(parent.begin(), parent.end(), -1);
        queue<int> q;
        dist[src] = 0;
        q.push(src);

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : adj[u]) {
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    parent[v] = u;
                    q.push(v);
                }
            }
        }
    }

    // Returns sequence of vertices from src to target, or empty if unreachable
    vector<int> get_path(int target) const {
        assert(0 <= target && target < n);
        if (dist[target] == -1) return {};
        vector<int> path;
        for (int cur = target; cur != -1; cur = parent[cur]) {
            path.push_back(cur);
        }
        reverse(path.begin(), path.end());
        return path;
    }
};
