// Algorithm: Hamiltonian Path Check and Extraction via Bitmask DP
// Purpose: Checks if a directed graph contains a path visiting every vertex exactly once and extracts it.
// Time Complexity: O(2^N * N^2)
// Space Complexity: O(2^N * N)
// Preconditions: N <= 20, directed graph adjacency matrix.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

struct HamResult {
    bool exists;
    std::vector<int> path;
};

HamResult find_hamiltonian_path(int n, const std::vector<std::vector<bool>>& adj) {
    int total = 1 << n;
    std::vector<std::vector<bool>> dp(total, std::vector<bool>(n, false));
    std::vector<std::vector<int>> parent(total, std::vector<int>(n, -1));

    for (int i = 0; i < n; ++i) dp[1 << i][i] = true;

    for (int mask = 1; mask < total; ++mask) {
        for (int u = 0; u < n; ++u) {
            if (!dp[mask][u]) continue;
            for (int v = 0; v < n; ++v) {
                if (!(mask & (1 << v)) && adj[u][v]) {
                    dp[mask | (1 << v)][v] = true;
                    parent[mask | (1 << v)][v] = u;
                }
            }
        }
    }

    int full_mask = total - 1;
    for (int i = 0; i < n; ++i) {
        if (dp[full_mask][i]) {
            std::vector<int> path;
            int cur_mask = full_mask, cur_node = i;
            while (cur_node != -1) {
                path.push_back(cur_node);
                int p = parent[cur_mask][cur_node];
                cur_mask ^= (1 << cur_node);
                cur_node = p;
            }
            std::reverse(path.begin(), path.end());
            return {true, path};
        }
    }
    return {false, {}};
}

int main() {
    int n = 4;
    std::vector<std::vector<bool>> adj(n, std::vector<bool>(n, false));
    adj[0][1] = adj[1][2] = adj[2][3] = true;

    auto res = find_hamiltonian_path(n, adj);
    assert(res.exists);
    assert(res.path == std::vector<int>({0, 1, 2, 3}));
    return 0;
}
