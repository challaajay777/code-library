// Algorithm: Tree Knapsack with Subtree Size Bounding
// Purpose: Solves knapsack on tree in strictly O(N * W) time using subtree size bounded iteration.
// Time Complexity: O(N * W)
// Space Complexity: O(N * W)
// Preconditions: Rooted tree with item costs and capacities.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

struct KnapsackTree {
    int n, W;
    std::vector<std::vector<int>> adj;
    std::vector<int> cost, val, sz;
    std::vector<std::vector<int>> dp;

    KnapsackTree(int n, int W) : n(n), W(W), adj(n), cost(n), val(n), sz(n, 0), dp(n, std::vector<int>(W + 1, 0)) {}

    void dfs(int u, int p) {
        sz[u] = cost[u];
        if (cost[u] <= W) dp[u][cost[u]] = val[u];

        for (int v : adj[u]) {
            if (v != p) {
                dfs(v, u);
                std::vector<int> nxt = dp[u];
                for (int w1 = 0; w1 <= std::min(W, sz[u]); ++w1) {
                    if (dp[u][w1] == 0 && w1 != cost[u]) continue;
                    for (int w2 = 0; w1 + w2 <= W && w2 <= sz[v]; ++w2) {
                        nxt[w1 + w2] = std::max(nxt[w1 + w2], dp[u][w1] + dp[v][w2]);
                    }
                }
                dp[u] = nxt;
                sz[u] += sz[v];
            }
        }
    }
};

int main() {
    KnapsackTree kt(2, 5);
    kt.adj[0].push_back(1);
    kt.cost = {2, 3};
    kt.val = {10, 20};
    kt.dfs(0, -1);
    assert(kt.dp[0][5] == 30);
    return 0;
}
