// Algorithm: Edmonds / Chu-Liu Minimum Spanning Arborescence
// Purpose: Finds a minimum weight directed root-directed spanning tree in O(V * E) time.
// Time Complexity: O(V * E)
// Space Complexity: O(V + E)
// Preconditions: Directed graph with designated root vertex.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

struct Edge {
    int u, v, weight;
};

const int INF = 1e9;

int edmonds_msa(int n, int root, std::vector<Edge> edges) {
    int res = 0;
    while (true) {
        std::vector<int> min_in(n, INF);
        std::vector<int> pre(n, -1);
        for (const auto& e : edges) {
            if (e.u != e.v && e.weight < min_in[e.v]) {
                min_in[e.v] = e.weight;
                pre[e.v] = e.u;
            }
        }
        min_in[root] = 0;
        for (int i = 0; i < n; ++i) if (min_in[i] == INF) return -1;

        int cycle_count = 0;
        std::vector<int> id(n, -1), vis(n, -1);
        for (int i = 0; i < n; ++i) {
            res += min_in[i];
            int v = i;
            while (vis[v] != i && id[v] == -1 && v != root) {
                vis[v] = i;
                v = pre[v];
            }
            if (v != root && id[v] == -1) {
                for (int u = pre[v]; u != v; u = pre[u]) id[u] = cycle_count;
                id[v] = cycle_count++;
            }
        }

        if (cycle_count == 0) break;
        for (int i = 0; i < n; ++i) if (id[i] == -1) id[i] = cycle_count++;

        for (auto& e : edges) {
            int v = e.v;
            e.u = id[e.u];
            e.v = id[e.v];
            if (e.u != e.v) e.weight -= min_in[v];
        }
        n = cycle_count;
        root = id[root];
    }
    return res;
}

int main() {
    int n = 4;
    std::vector<Edge> edges = {
        {0, 1, 10},
        {0, 2, 10},
        {0, 3, 10},
        {1, 2, 1},
        {2, 3, 1}
    };
    // Root = 0: edges 0->1 (10), 1->2 (1), 2->3 (1) = 12
    assert(edmonds_msa(n, 0, edges) == 12);
    return 0;
}
