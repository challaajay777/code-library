// Algorithm: Number of Tree Paths with Sum K
// Purpose: Counts downwards simple paths in tree summing to target K using prefix sum hash maps.
// Time Complexity: O(N)
// Space Complexity: O(N)
// Preconditions: Rooted tree with node values.

#include <iostream>
#include <vector>
#include <unordered_map>
#include <cassert>

long long dfs_paths_k(int u, int p, long long cur_sum, long long target,
                      const std::vector<std::vector<int>>& adj,
                      const std::vector<int>& val,
                      std::unordered_map<long long, int>& pref) {
    cur_sum += val[u];
    long long count = pref.count(cur_sum - target) ? pref[cur_sum - target] : 0;

    pref[cur_sum]++;
    for (int v : adj[u]) {
        if (v != p) {
            count += dfs_paths_k(v, u, cur_sum, target, adj, val, pref);
        }
    }
    pref[cur_sum]--;
    return count;
}

int main() {
    int n = 3;
    std::vector<std::vector<int>> adj(n);
    adj[0] = {1, 2}; adj[1] = {0}; adj[2] = {0};
    std::vector<int> val = {10, 5, -5};

    std::unordered_map<long long, int> pref;
    pref[0] = 1;
    long long ways = dfs_paths_k(0, -1, 0, 5, adj, val, pref);
    // Path 0->2: 10 + (-5) = 5
    assert(ways == 1);
    return 0;
}
