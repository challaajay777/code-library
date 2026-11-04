// Algorithm: Second-Best Minimum Spanning Tree
// Purpose: Finds the weight of the strictly or non-strictly second minimum spanning tree via LCA max edge query.
// Time Complexity: O(E log V)
// Space Complexity: O(V log V + E)
// Preconditions: Connected undirected graph with V >= 3.

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <climits>

struct Edge {
    int u, v, weight, id;
    bool in_mst;
};

struct DSU {
    std::vector<int> parent;
    DSU(int n) : parent(n) {
        for (int i = 0; i < n; ++i) parent[i] = i;
    }
    int find(int i) {
        return (parent[i] == i) ? i : (parent[i] = find(parent[i]));
    }
    bool unite(int i, int j) {
        int root_i = find(i), root_j = find(j);
        if (root_i != root_j) {
            parent[root_i] = root_j;
            return true;
        }
        return false;
    }
};

long long second_best_mst(int n, std::vector<Edge>& edges) {
    for (size_t i = 0; i < edges.size(); ++i) {
        edges[i].id = i;
        edges[i].in_mst = false;
    }

    std::sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.weight < b.weight;
    });

    DSU dsu(n);
    long long mst_weight = 0;
    std::vector<std::vector<std::pair<int, int>>> tree(n);

    for (auto& e : edges) {
        if (dsu.unite(e.u, e.v)) {
            e.in_mst = true;
            mst_weight += e.weight;
            tree[e.u].push_back({e.v, e.weight});
            tree[e.v].push_back({e.u, e.weight});
        }
    }

    // Binary lifting for max edge on path
    const int LOGN = 16;
    std::vector<std::vector<int>> up(n, std::vector<int>(LOGN, 0));
    std::vector<std::vector<int>> max_edge(n, std::vector<int>(LOGN, 0));
    std::vector<int> depth(n, 0);

    auto dfs = [&](auto self, int u, int p, int w, int d) -> void {
        up[u][0] = p;
        max_edge[u][0] = w;
        depth[u] = d;
        for (int i = 1; i < LOGN; ++i) {
            up[u][i] = up[up[u][i - 1]][i - 1];
            max_edge[u][i] = std::max(max_edge[u][i - 1], max_edge[up[u][i - 1]][i - 1]);
        }
        for (auto [v, weight] : tree[u]) {
            if (v != p) self(self, v, u, weight, d + 1);
        }
    };
    dfs(dfs, 0, 0, 0, 0);

    auto query_max = [&](int u, int v) {
        int res = 0;
        if (depth[u] < depth[v]) std::swap(u, v);
        for (int i = LOGN - 1; i >= 0; --i) {
            if (depth[u] - (1 << i) >= depth[v]) {
                res = std::max(res, max_edge[u][i]);
                u = up[u][i];
            }
        }
        if (u == v) return res;
        for (int i = LOGN - 1; i >= 0; --i) {
            if (up[u][i] != up[v][i]) {
                res = std::max({res, max_edge[u][i], max_edge[v][i]});
                u = up[u][i];
                v = up[v][i];
            }
        }
        return std::max({res, max_edge[u][0], max_edge[v][0]});
    };

    long long second_best = LLONG_MAX;
    for (const auto& e : edges) {
        if (!e.in_mst) {
            int mx = query_max(e.u, e.v);
            second_best = std::min(second_best, mst_weight - mx + e.weight);
        }
    }
    return second_best;
}

int main() {
    int n = 4;
    std::vector<Edge> edges = {
        {0, 1, 10},
        {0, 2, 10},
        {1, 3, 10},
        {2, 3, 20}
    };
    // MST: {0,1,10}, {0,2,10}, {1,3,10} -> 30
    // Second best: replace {1,3,10} with {2,3,20} -> 40
    assert(second_best_mst(n, edges) == 40);
    return 0;
}
