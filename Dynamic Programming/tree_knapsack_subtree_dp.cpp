// Algorithm: Tree Knapsack Subtree-Bounded DP
// Purpose: Solves knapsack optimization on a tree where choosing a node requires choosing its parent.
// Time Complexity: O(N * W)
// Space Complexity: O(N * W)
// Preconditions: Rooted tree, item weights >= 0.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

struct TreeKnapsack {
    int n, W;
    std::vector<std::vector<int>> adj;
    std::vector<int> weight, value, sz;
    std::vector<std::vector<long long>> dp;

    TreeKnapsack(int n, int W) : n(n), W(W), adj(n), weight(n), value(n), sz(n, 0), dp(n, std::vector<long long>(W + 1, 0)) {}

    void dfs(int u, int p) {
        sz[u] = weight[u];
        if (weight[u] <= W) dp[u][weight[u]] = value[u];

        for (int v : adj[u]) {
            if (v != p) {
                dfs(v, u);
                std::vector<long long> next_dp = dp[u];
                for (int w1 = 0; w1 <= std::min(W, sz[u]); ++w1) {
                    if (dp[u][w1] == 0 && w1 != weight[u]) continue;
                    for (int w2 = 0; w1 + w2 <= W && w2 <= sz[v]; ++w2) {
                        next_dp[w1 + w2] = std::max(next_dp[w1 + w2], dp[u][w1] + dp[v][w2]);
                    }
                }
                dp[u] = next_dp;
                sz[u] += sz[v];
            }
        }
    }

    long long solve(int root = 0) {
        dfs(root, -1);
        long long ans = 0;
        for (int w = 0; w <= W; ++w) ans = std::max(ans, dp[root][w]);
        return ans;
    }
};

int main() {
    TreeKnapsack tk(3, 4);
    tk.adj[0].push_back(1);
    tk.adj[0].push_back(2);
    tk.weight = {2, 1, 1};
    tk.value = {5, 4, 3};

    // Capacity 4: root weight 2 (value 5) + child 1 weight 1 (value 4) + child 2 weight 1 (val 3) = total weight 4, val 12
    assert(tk.solve(0) == 12);
    return 0;
}
