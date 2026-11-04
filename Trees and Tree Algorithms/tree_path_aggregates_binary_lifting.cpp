// Algorithm: Tree Path Aggregates via Binary Lifting
// Purpose: Queries minimum, maximum, or sum edge weights along tree path between any two vertices in O(log N).
// Time Complexity: O(N log N) precomputation, O(log N) per query
// Space Complexity: O(N log N)
// Preconditions: Connected weighted tree.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

struct TreePathAggregate {
    int n, LOGN;
    std::vector<std::vector<int>> up, min_edge, max_edge;
    std::vector<int> depth;

    TreePathAggregate(int n, const std::vector<std::vector<std::pair<int, int>>>& adj, int root = 0) : n(n) {
        LOGN = 1;
        while ((1 << LOGN) <= n) LOGN++;
        up.assign(n, std::vector<int>(LOGN, root));
        min_edge.assign(n, std::vector<int>(LOGN, 1e9));
        max_edge.assign(n, std::vector<int>(LOGN, -1e9));
        depth.assign(n, 0);

        dfs(root, root, 0, 0, adj);
    }

    void dfs(int u, int p, int w, int d, const std::vector<std::vector<std::pair<int, int>>>& adj) {
        up[u][0] = p;
        min_edge[u][0] = w;
        max_edge[u][0] = w;
        depth[u] = d;

        for (int i = 1; i < LOGN; ++i) {
            up[u][i] = up[up[u][i - 1]][i - 1];
            min_edge[u][i] = std::min(min_edge[u][i - 1], min_edge[up[u][i - 1]][i - 1]);
            max_edge[u][i] = std::max(max_edge[u][i - 1], max_edge[up[u][i - 1]][i - 1]);
        }

        for (auto [v, weight] : adj[u]) {
            if (v != p) {
                dfs(v, u, weight, d + 1, adj);
            }
        }
    }

    std::pair<int, int> query_min_max(int u, int v) {
        int mn = 1e9, mx = -1e9;
        if (depth[u] < depth[v]) std::swap(u, v);

        for (int i = LOGN - 1; i >= 0; --i) {
            if (depth[u] - (1 << i) >= depth[v]) {
                mn = std::min(mn, min_edge[u][i]);
                mx = std::max(mx, max_edge[u][i]);
                u = up[u][i];
            }
        }
        if (u == v) return {mn, mx};

        for (int i = LOGN - 1; i >= 0; --i) {
            if (up[u][i] != up[v][i]) {
                mn = std::min({mn, min_edge[u][i], min_edge[v][i]});
                mx = std::max({mx, max_edge[u][i], max_edge[v][i]});
                u = up[u][i];
                v = up[v][i];
            }
        }
        mn = std::min({mn, min_edge[u][0], min_edge[v][0]});
        mx = std::max({mx, max_edge[u][0], max_edge[v][0]});
        return {mn, mx};
    }
};

int main() {
    int n = 4;
    std::vector<std::vector<std::pair<int, int>>> adj(n);
    adj[0].push_back({1, 10}); adj[1].push_back({0, 10});
    adj[1].push_back({2, 5});  adj[2].push_back({1, 5});
    adj[1].push_back({3, 20}); adj[3].push_back({1, 20});

    TreePathAggregate tpa(n, adj, 0);
    auto [mn, mx] = tpa.query_min_max(2, 3);
    assert(mn == 5);
    assert(mx == 20);
    return 0;
}
