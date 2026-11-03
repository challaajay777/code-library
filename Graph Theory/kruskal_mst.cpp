// Algorithm: Kruskal's Minimum Spanning Tree
// Supports: Minimum spanning forest, total MST weight, edge list recovery
// Indexing: 0-based vertex indices [0, n - 1]
// Complexity: O(E log E) time, O(V + E) memory
// Preconditions: 0 <= u, v < n

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

struct KruskalMST {
    struct Edge {
        int u, v;
        long long w;
        bool operator<(const Edge& o) const {
            return w < o.w;
        }
    };

    int n;
    vector<Edge> edges;

    explicit KruskalMST(int n) : n(n) {}

    void add_edge(int u, int v, long long w) {
        assert(0 <= u && u < n && 0 <= v && v < n);
        edges.push_back({u, v, w});
    }

    // Returns {total_mst_weight, mst_edges}. If disconnected, returns MST for each component.
    pair<long long, vector<Edge>> solve() {
        sort(edges.begin(), edges.end());
        vector<int> parent(n), sz(n, 1);
        iota(parent.begin(), parent.end(), 0);

        auto find = [&](auto& self, int u) -> int {
            return parent[u] == u ? u : (parent[u] = self(self, parent[u]));
        };

        long long total_weight = 0;
        vector<Edge> mst_edges;
        mst_edges.reserve(n - 1);

        for (const auto& e : edges) {
            int root_u = find(find, e.u);
            int root_v = find(find, e.v);
            if (root_u != root_v) {
                if (sz[root_u] < sz[root_v]) swap(root_u, root_v);
                parent[root_v] = root_u;
                sz[root_u] += sz[root_v];
                total_weight += e.w;
                mst_edges.push_back(e);
                if ((int)mst_edges.size() == n - 1) break;
            }
        }
        return {total_weight, mst_edges};
    }
};
