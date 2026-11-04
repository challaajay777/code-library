// Algorithm: Tree LCA via Depth Binary Search
// Purpose: Finds lowest common ancestor by binary searching on depth and validating equality of k-th ancestors.
// Time Complexity: O(log^2 N)
// Space Complexity: O(N log N)
// Preconditions: Connected rooted tree.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

struct LCABinarySearch {
    int n, LOGN;
    std::vector<std::vector<int>> up;
    std::vector<int> depth;

    LCABinarySearch(int n, const std::vector<std::vector<int>>& adj, int root = 0) : n(n) {
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

    int get_kth(int u, int k) {
        for (int i = 0; i < LOGN; ++i) {
            if (k & (1 << i)) u = up[u][i];
        }
        return u;
    }

    int lca(int u, int v) {
        if (depth[u] < depth[v]) std::swap(u, v);
        u = get_kth(u, depth[u] - depth[v]);
        if (u == v) return u;

        int low = 0, high = depth[u], ans = 0;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (get_kth(u, mid) == get_kth(v, mid)) {
                ans = mid;
                high = mid - 1; // seek closer common ancestor
            } else {
                low = mid + 1;
            }
        }
        return get_kth(u, ans);
    }
};

int main() {
    int n = 4;
    std::vector<std::vector<int>> adj(n);
    adj[0] = {1, 2}; adj[1] = {0, 3}; adj[2] = {0}; adj[3] = {1};
    LCABinarySearch bs(n, adj, 0);
    assert(bs.lca(2, 3) == 0);
    assert(bs.lca(1, 3) == 1);
    return 0;
}
