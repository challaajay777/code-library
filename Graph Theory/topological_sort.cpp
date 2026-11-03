// Algorithm: Topological Sort (Kahn's Algorithm)
// Supports: Topological ordering of DAG, cycle detection
// Indexing: 0-based vertex indices [0, n - 1]
// Complexity: O(V + E) time, O(V + E) memory
// Preconditions: 0 <= u, v < n

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

struct TopologicalSort {
    int n;
    vector<vector<int>> adj;
    vector<int> in_degree;

    explicit TopologicalSort(int n) : n(n), adj(n), in_degree(n, 0) {}

    void add_edge(int u, int v) {
        assert(0 <= u && u < n && 0 <= v && v < n);
        adj[u].push_back(v);
        in_degree[v]++;
    }

    // Returns topological ordering, or empty vector if the graph contains a cycle
    vector<int> sort_dag() {
        queue<int> q;
        for (int i = 0; i < n; ++i) {
            if (in_degree[i] == 0) {
                q.push(i);
            }
        }

        vector<int> order;
        order.reserve(n);
        vector<int> deg = in_degree;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            order.push_back(u);

            for (int v : adj[u]) {
                if (--deg[v] == 0) {
                    q.push(v);
                }
            }
        }

        if ((int)order.size() != n) return {}; // Cycle detected
        return order;
    }
};
