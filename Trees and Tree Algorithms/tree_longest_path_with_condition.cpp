// Algorithm: Longest Path in Tree with Value Condition
// Purpose: Finds longest simple path where all vertices satisfy a predicate (e.g. gcd > 1 or positive value).
// Time Complexity: O(N)
// Space Complexity: O(N)
// Preconditions: Tree with node attributes.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

int max_cond_path = 0;

int dfs_cond(int u, int p, const std::vector<std::vector<int>>& adj, const std::vector<bool>& valid) {
    if (!valid[u]) return 0;
    int max1 = 0, max2 = 0;
    for (int v : adj[u]) {
        if (v != p) {
            int len = dfs_cond(v, u, adj, valid);
            if (len > max1) { max2 = max1; max1 = len; }
            else if (len > max2) { max2 = len; }
        }
    }
    max_cond_path = std::max(max_cond_path, max1 + max2 + 1);
    return max1 + 1;
}

int main() {
    int n = 4;
    std::vector<std::vector<int>> adj(n);
    adj[0] = {1, 2}; adj[1] = {0, 3}; adj[2] = {0}; adj[3] = {1};
    std::vector<bool> valid = {true, true, false, true};

    max_cond_path = 0;
    dfs_cond(0, -1, adj, valid);
    // Path 2-0-1-3 has 2 invalid, so valid path is 0-1-3 of length 3
    assert(max_cond_path == 3);
    return 0;
}
