// Algorithm: Tree Diameter and Center
// Supports: Tree diameter length, diameter path, tree center(s)
// Indexing: 0-based vertex indices [0, n - 1]
// Complexity: O(n) time, O(n) memory
// Preconditions: Connected tree, n >= 1

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

struct TreeDiameterCenter {
    int n;
    vector<vector<int>> adj;

    explicit TreeDiameterCenter(int n) : n(n), adj(n) {}

    void add_edge(int u, int v) {
        assert(0 <= u && u < n && 0 <= v && v < n);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

private:
    pair<int, int> bfs_farthest(int start) const {
        vector<int> dist(n, -1);
        queue<int> q;
        dist[start] = 0;
        q.push(start);
        int farthest = start;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (dist[u] > dist[farthest]) {
                farthest = u;
            }
            for (int v : adj[u]) {
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
        }
        return {farthest, dist[farthest]};
    }

public:
    // Returns {u, v, diameter_length}
    tuple<int, int, int> get_diameter_endpoints() const {
        if (n <= 1) return {0, 0, 0};
        int u = bfs_farthest(0).first;
        auto [v, len] = bfs_farthest(u);
        return {u, v, len};
    }

    // Returns all vertices along the simple diameter path from u to v
    vector<int> get_diameter_path() const {
        if (n == 0) return {};
        if (n == 1) return {0};
        auto [u, v, len] = get_diameter_endpoints();

        vector<int> parent(n, -1);
        vector<int> dist(n, -1);
        queue<int> q;
        dist[u] = 0;
        q.push(u);

        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            for (int nxt : adj[cur]) {
                if (dist[nxt] == -1) {
                    dist[nxt] = dist[cur] + 1;
                    parent[nxt] = cur;
                    q.push(nxt);
                }
            }
        }

        vector<int> path;
        for (int cur = v; cur != -1; cur = parent[cur]) {
            path.push_back(cur);
        }
        reverse(path.begin(), path.end());
        return path;
    }

    // Returns tree center(s): 1 node if odd diameter path, 2 nodes if even
    vector<int> get_centers() const {
        auto path = get_diameter_path();
        if (path.empty()) return {};
        int m = (int)path.size();
        if (m % 2 == 1) {
            return {path[m / 2]};
        } else {
            return {path[m / 2 - 1], path[m / 2]};
        }
    }
};
