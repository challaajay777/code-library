// Algorithm: Lowest Common Ancestor via Euler Tour and RMQ
// Purpose: Queries LCA of two nodes in O(1) time after O(N log N) Sparse Table precomputation.
// Time Complexity: O(N log N) precomputation, O(1) per query
// Space Complexity: O(N log N)
// Preconditions: Connected tree of n vertices.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

struct LCAEulerRMQ {
    int n;
    std::vector<int> first, depth, tour;
    std::vector<std::vector<int>> st;
    std::vector<int> lg;

    LCAEulerRMQ(int n, const std::vector<std::vector<int>>& adj, int root = 0) : n(n), first(n), depth(n) {
        dfs(root, -1, 0, adj);
        int m = tour.size();
        lg.assign(m + 1, 0);
        for (int i = 2; i <= m; ++i) lg[i] = lg[i / 2] + 1;

        int k = lg[m] + 1;
        st.assign(k, std::vector<int>(m));
        for (int i = 0; i < m; ++i) st[0][i] = tour[i];

        for (int j = 1; (1 << j) <= m; ++j) {
            for (int i = 0; i + (1 << j) <= m; ++i) {
                int left = st[j - 1][i];
                int right = st[j - 1][i + (1 << (j - 1))];
                st[j][i] = (depth[left] < depth[right]) ? left : right;
            }
        }
    }

    void dfs(int u, int p, int d, const std::vector<std::vector<int>>& adj) {
        depth[u] = d;
        first[u] = tour.size();
        tour.push_back(u);
        for (int v : adj[u]) {
            if (v != p) {
                dfs(v, u, d + 1, adj);
                tour.push_back(u);
            }
        }
    }

    int query(int u, int v) {
        int l = first[u], r = first[v];
        if (l > r) std::swap(l, r);
        int len = r - l + 1;
        int k = lg[len];
        int left = st[k][l];
        int right = st[k][r - (1 << k) + 1];
        return (depth[left] < depth[right]) ? left : right;
    }
};

int main() {
    int n = 5;
    std::vector<std::vector<int>> adj(n);
    adj[0] = {1, 2}; adj[1] = {0, 3, 4}; adj[2] = {0};
    adj[3] = {1}; adj[4] = {1};

    LCAEulerRMQ lca(n, adj, 0);
    assert(lca.query(3, 4) == 1);
    assert(lca.query(3, 2) == 0);
    assert(lca.query(1, 3) == 1);
    return 0;
}
