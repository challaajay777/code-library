// Algorithm: Tree Distance via Binary Lifting LCA
// Purpose: Calculates shortest path distance between any two tree nodes in O(log N) time.
// Time Complexity: O(N log N) build, O(log N) query
// Space Complexity: O(N log N)
// Preconditions: Connected tree.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

struct TreeDistanceLCA {
    int n, LOGN;
    std::vector<std::vector<int>> up;
    std::vector<int> depth;

    TreeDistanceLCA(int n, const std::vector<std::vector<int>>& adj, int root = 0) : n(n) {
        LOGN = 18;
        up.assign(n, std::vector<int>(LOGN, root));
        depth.assign(n, 0);
        dfs(root, root, 0, adj);
    }

    void dfs(int u, int p, int d, const std::vector<std::vector<int>>& adj) {
        depth[u] = d;
        up[u][0] = p;
        for (int i = 1; i < LOGN; ++i) up[u][i] = up[up[u][i - 1]][i - 1];
        for (int v : adj[u]) if (v != p) dfs(v, u, d + 1, adj);
    }

    int lca(int u, int v) {
        if (depth[u] < depth[v]) std::swap(u, v);
        for (int i = LOGN - 1; i >= 0; --i) {
            if (depth[u] - (1 << i) >= depth[v]) u = up[u][i];
        }
        if (u == v) return u;
        for (int i = LOGN - 1; i >= 0; --i) {
            if (up[u][i] != up[v][i]) {
                u = up[u][i];
                v = up[v][i];
            }
        }
        return up[u][0];
    }

    int dist(int u, int v) {
        return depth[u] + depth[v] - 2 * depth[lca(u, v)];
    }
};

int main() {
    int n = 4;
    std::vector<std::vector<int>> adj(n);
    adj[0] = {1, 2}; adj[1] = {0, 3}; adj[2] = {0}; adj[3] = {1};
    TreeDistanceLCA td(n, adj, 0);
    assert(td.dist(2, 3) == 3);
    assert(td.dist(1, 3) == 1);
    return 0;
}
