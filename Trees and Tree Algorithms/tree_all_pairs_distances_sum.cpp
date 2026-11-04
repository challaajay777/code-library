// Algorithm: All-Pairs Distances Sum via Tree Rerooting
// Purpose: Calculates sum of distances from every vertex to all other vertices in O(N) total time.
// Time Complexity: O(N)
// Space Complexity: O(N)
// Preconditions: Connected unweighted tree.

#include <iostream>
#include <vector>
#include <cassert>

struct AllPairsDist {
    int n;
    std::vector<int> sz;
    std::vector<long long> ans;

    AllPairsDist(int n, const std::vector<std::vector<int>>& adj) : n(n), sz(n, 1), ans(n, 0) {
        dfs_down(0, -1, 0, adj);
        dfs_up(0, -1, adj);
    }

    void dfs_down(int u, int p, int d, const std::vector<std::vector<int>>& adj) {
        ans[0] += d;
        for (int v : adj[u]) {
            if (v != p) {
                dfs_down(v, u, d + 1, adj);
                sz[u] += sz[v];
            }
        }
    }

    void dfs_up(int u, int p, const std::vector<std::vector<int>>& adj) {
        for (int v : adj[u]) {
            if (v != p) {
                ans[v] = ans[u] + (n - sz[v]) - sz[v];
                dfs_up(v, u, adj);
            }
        }
    }
};

int main() {
    // Star tree: 0 connected to 1, 2, 3
    int n = 4;
    std::vector<std::vector<int>> adj(n);
    adj[0] = {1, 2, 3}; adj[1] = {0}; adj[2] = {0}; adj[3] = {0};

    AllPairsDist apd(n, adj);
    assert(apd.ans[0] == 3); // 1 + 1 + 1 = 3
    assert(apd.ans[1] == 5); // 1 (to 0) + 2 (to 2) + 2 (to 3) = 5
    return 0;
}
