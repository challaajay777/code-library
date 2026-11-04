// Algorithm: Farthest Node Distance for All Vertices via Rerooting
// Purpose: Calculates the maximum distance to any node in the tree for every vertex in O(N).
// Time Complexity: O(N)
// Space Complexity: O(N)
// Preconditions: Connected unweighted tree.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

struct FarthestReroot {
    int n;
    std::vector<int> down1, down2, best_child, ans;

    FarthestReroot(int n, const std::vector<std::vector<int>>& adj)
        : n(n), down1(n, 0), down2(n, 0), best_child(n, -1), ans(n, 0) {
        dfs_down(0, -1, adj);
        dfs_up(0, -1, 0, adj);
    }

    void dfs_down(int u, int p, const std::vector<std::vector<int>>& adj) {
        for (int v : adj[u]) {
            if (v != p) {
                dfs_down(v, u, adj);
                int d = down1[v] + 1;
                if (d > down1[u]) {
                    down2[u] = down1[u];
                    down1[u] = d;
                    best_child[u] = v;
                } else if (d > down2[u]) {
                    down2[u] = d;
                }
            }
        }
    }

    void dfs_up(int u, int p, int up_d, const std::vector<std::vector<int>>& adj) {
        ans[u] = std::max(down1[u], up_d);
        for (int v : adj[u]) {
            if (v != p) {
                int next_up = (v == best_child[u] ? down2[u] : down1[u]) + 1;
                dfs_up(v, u, std::max(up_d + 1, next_up), adj);
            }
        }
    }
};

int main() {
    int n = 3;
    std::vector<std::vector<int>> adj(n);
    adj[0] = {1, 2}; adj[1] = {0}; adj[2] = {0};
    FarthestReroot fr(n, adj);
    assert(fr.ans[0] == 1);
    assert(fr.ans[1] == 2);
    assert(fr.ans[2] == 2);
    return 0;
}
