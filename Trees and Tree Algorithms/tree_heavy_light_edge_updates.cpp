// Algorithm: HLD Edge Weight Point Update and Path Query
// Purpose: Maps edge weights to the deeper endpoint node and executes path queries via HLD.
// Time Complexity: O(log^2 N) query, O(log N) update
// Space Complexity: O(N)
// Preconditions: Weighted connected tree.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

struct HLDEdges {
    int n, timer;
    std::vector<int> parent, depth, heavy, head, pos;
    std::vector<int> seg;

    HLDEdges(int n, const std::vector<std::vector<std::pair<int, int>>>& adj, int root = 0)
        : n(n), timer(0), parent(n), depth(n), heavy(n, -1), head(n), pos(n), seg(4 * n, 0) {
        dfs_sz(root, -1, 0, adj);
        decompose(root, root, adj);
    }

    int dfs_sz(int u, int p, int d, const std::vector<std::vector<std::pair<int, int>>>& adj) {
        parent[u] = p;
        depth[u] = d;
        int sz = 1, max_c = 0;
        for (auto [v, w] : adj[u]) {
            if (v != p) {
                int c_sz = dfs_sz(v, u, d + 1, adj);
                sz += c_sz;
                if (c_sz > max_c) { max_c = c_sz; heavy[u] = v; }
            }
        }
        return sz;
    }

    void decompose(int u, int h, const std::vector<std::vector<std::pair<int, int>>>& adj) {
        head[u] = h;
        pos[u] = ++timer;
        if (heavy[u] != -1) decompose(heavy[u], h, adj);
        for (auto [v, w] : adj[u]) {
            if (v != parent[u] && v != heavy[u]) decompose(v, v, adj);
        }
    }

    void seg_update(int node, int l, int r, int idx, int val) {
        if (l == r) { seg[node] = val; return; }
        int mid = (l + r) / 2;
        if (idx <= mid) seg_update(2 * node, l, mid, idx, val);
        else seg_update(2 * node + 1, mid + 1, r, idx, val);
        seg[node] = seg[2 * node] + seg[2 * node + 1];
    }

    int seg_query(int node, int l, int r, int ql, int qr) {
        if (ql > r || qr < l) return 0;
        if (ql <= l && r <= qr) return seg[node];
        int mid = (l + r) / 2;
        return seg_query(2 * node, l, mid, ql, qr) + seg_query(2 * node + 1, mid + 1, r, ql, qr);
    }

    void update_edge(int u, int v, int w) {
        if (depth[u] < depth[v]) std::swap(u, v);
        seg_update(1, 1, n, pos[u], w);
    }

    int query_path(int u, int v) {
        int sum = 0;
        while (head[u] != head[v]) {
            if (depth[head[u]] > depth[head[v]]) std::swap(u, v);
            sum += seg_query(1, 1, n, pos[head[v]], pos[v]);
            v = parent[head[v]];
        }
        if (depth[u] > depth[v]) std::swap(u, v);
        if (u != v) {
            sum += seg_query(1, 1, n, pos[u] + 1, pos[v]);
        }
        return sum;
    }
};

int main() {
    int n = 3;
    std::vector<std::vector<std::pair<int, int>>> adj(n);
    adj[0].push_back({1, 5}); adj[1].push_back({0, 5});
    adj[1].push_back({2, 10}); adj[2].push_back({1, 10});

    HLDEdges hld(n, adj, 0);
    hld.update_edge(0, 1, 5);
    hld.update_edge(1, 2, 10);
    assert(hld.query_path(0, 2) == 15);
    return 0;
}
