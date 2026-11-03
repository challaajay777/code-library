// Algorithm: Eulerian Trail / Circuit (Hierholzer's Algorithm)
// Supports: Finding Eulerian path or cycle in directed and undirected graphs
// Indexing: 0-based vertex indices [0, n - 1]
// Complexity: O(V + E) time, O(V + E) memory
// Preconditions: Graph vertices 0 <= u, v < n; checks degree parity and connectivity

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

struct EulerianDirected {
    int n;
    int edge_count = 0;
    vector<vector<pair<int, int>>> adj; // {to, edge_id}
    vector<int> in_deg, out_deg;
    vector<int> head;
    vector<bool> used_edge;

    explicit EulerianDirected(int n)
        : n(n), adj(n), in_deg(n, 0), out_deg(n, 0), head(n, 0) {}

    void add_edge(int u, int v) {
        assert(0 <= u && u < n && 0 <= v && v < n);
        adj[u].push_back({v, edge_count++});
        out_deg[u]++;
        in_deg[v]++;
    }

    // Returns sequence of vertex IDs in Eulerian path, or empty if none exists
    vector<int> find_path() {
        if (edge_count == 0) return {};

        int start_node = -1;
        int end_node = -1;
        for (int i = 0; i < n; ++i) {
            if (out_deg[i] - in_deg[i] == 1) {
                if (start_node != -1) return {};
                start_node = i;
            } else if (in_deg[i] - out_deg[i] == 1) {
                if (end_node != -1) return {};
                end_node = i;
            } else if (in_deg[i] != out_deg[i]) {
                return {};
            }
        }

        if (start_node == -1) {
            // Eulerian circuit: pick any node with outgoing edges
            for (int i = 0; i < n; ++i) {
                if (out_deg[i] > 0) {
                    start_node = i;
                    break;
                }
            }
        }
        if (start_node == -1) return {};

        used_edge.assign(edge_count, false);
        fill(head.begin(), head.end(), 0);

        vector<int> path;
        vector<int> st = {start_node};

        while (!st.empty()) {
            int u = st.back();
            while (head[u] < (int)adj[u].size() && used_edge[adj[u][head[u]].second]) {
                head[u]++;
            }
            if (head[u] < (int)adj[u].size()) {
                auto [v, id] = adj[u][head[u]++];
                used_edge[id] = true;
                st.push_back(v);
            } else {
                path.push_back(u);
                st.pop_back();
            }
        }

        if ((int)path.size() != edge_count + 1) return {}; // Disconnected with edges
        reverse(path.begin(), path.end());
        return path;
    }
};
