// Algorithm: Directed Minimum Spanning Arborescence
// Purpose: Calculates minimum total cost to reach all nodes from root in a directed graph using cycle contraction.
// Time Complexity: O(V * E)
// Space Complexity: O(V + E)
// Preconditions: Directed graph with designated root.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

struct ArborescenceEdge {
    int u, v, w;
};

int directed_mst(int n, int root, std::vector<ArborescenceEdge> edges) {
    const int INF = 1e9;
    int ans = 0;
    while (true) {
        std::vector<int> in_w(n, INF), parent(n, -1);
        for (const auto& e : edges) {
            if (e.u != e.v && e.w < in_w[e.v]) {
                in_w[e.v] = e.w;
                parent[e.v] = e.u;
            }
        }
        in_w[root] = 0;
        for (int i = 0; i < n; ++i) if (in_w[i] == INF) return -1;

        int cycle_count = 0;
        std::vector<int> id(n, -1), vis(n, -1);
        for (int i = 0; i < n; ++i) {
            ans += in_w[i];
            int v = i;
            while (vis[v] != i && id[v] == -1 && v != root) {
                vis[v] = i;
                v = parent[v];
            }
            if (v != root && id[v] == -1) {
                for (int u = parent[v]; u != v; u = parent[u]) id[u] = cycle_count;
                id[v] = cycle_count++;
            }
        }

        if (cycle_count == 0) break;
        for (int i = 0; i < n; ++i) if (id[i] == -1) id[i] = cycle_count++;
        for (auto& e : edges) {
            int v = e.v;
            e.u = id[e.u];
            e.v = id[e.v];
            if (e.u != e.v) e.w -= in_w[v];
        }
        n = cycle_count;
        root = id[root];
    }
    return ans;
}

int main() {
    int n = 3;
    std::vector<ArborescenceEdge> edges = {
        {0, 1, 5},
        {0, 2, 10},
        {1, 2, 3}
    };
    // Root 0: 0->1 (5), 1->2 (3) = 8
    assert(directed_mst(n, 0, edges) == 8);
    return 0;
}
