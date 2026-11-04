// Algorithm: DSU on Tree (Sack / Small-to-Large)
// Purpose: Answers subtree distinct value and frequency queries across all nodes in O(N log N).
// Time Complexity: O(N log N)
// Space Complexity: O(N)
// Preconditions: Rooted tree.

#include <iostream>
#include <vector>
#include <cassert>

struct SackTree {
    int n;
    std::vector<std::vector<int>> adj;
    std::vector<int> color, sz, heavy, cnt, ans;

    SackTree(int n, const std::vector<std::vector<int>>& adj, const std::vector<int>& color)
        : n(n), adj(adj), color(color), sz(n, 1), heavy(n, -1), cnt(100005, 0), ans(n, 0) {
        dfs_sz(0, -1);
        dfs_sack(0, -1, false);
    }

    void dfs_sz(int u, int p) {
        int max_c = 0;
        for (int v : adj[u]) {
            if (v != p) {
                dfs_sz(v, u);
                sz[u] += sz[v];
                if (sz[v] > max_c) { max_c = sz[v]; heavy[u] = v; }
            }
        }
    }

    void add(int u, int p, int delta) {
        cnt[color[u]] += delta;
        for (int v : adj[u]) if (v != p) add(v, u, delta);
    }

    void dfs_sack(int u, int p, bool keep) {
        for (int v : adj[u]) {
            if (v != p && v != heavy[u]) dfs_sack(v, u, false);
        }
        if (heavy[u] != -1) dfs_sack(heavy[u], u, true);

        for (int v : adj[u]) {
            if (v != p && v != heavy[u]) add(v, u, 1);
        }
        cnt[color[u]]++;
        ans[u] = cnt[color[u]]; // frequency of u's color in its subtree

        if (!keep) add(u, p, -1);
    }
};

int main() {
    int n = 3;
    std::vector<std::vector<int>> adj(n);
    adj[0] = {1, 2}; adj[1] = {0}; adj[2] = {0};
    std::vector<int> color = {1, 1, 2};

    SackTree sack(n, adj, color);
    assert(sack.ans[0] == 2); // 2 nodes of color 1 in subtree 0
    return 0;
}
