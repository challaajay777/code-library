// Algorithm: Distinct Values in Subtrees via Small-to-Large Merging
// Purpose: Finds number of distinct node values in every subtree in O(N log^2 N) using small-to-large map merge.
// Time Complexity: O(N log^2 N)
// Space Complexity: O(N log N)
// Preconditions: Rooted tree with node values.

#include <iostream>
#include <vector>
#include <set>
#include <cassert>

void dfs_small_to_large(int u, int p, const std::vector<std::vector<int>>& adj,
                        const std::vector<int>& val,
                        std::vector<int>& ans,
                        std::set<int>& values) {
    values.insert(val[u]);
    for (int v : adj[u]) {
        if (v != p) {
            std::set<int> child_values;
            dfs_small_to_large(v, u, adj, val, ans, child_values);
            if (child_values.size() > values.size()) {
                std::swap(values, child_values);
            }
            values.insert(child_values.begin(), child_values.end());
        }
    }
    ans[u] = values.size();
}

int main() {
    int n = 3;
    std::vector<std::vector<int>> adj(n);
    adj[0] = {1, 2}; adj[1] = {0}; adj[2] = {0};
    std::vector<int> val = {1, 2, 2};

    std::vector<int> ans(n, 0);
    std::set<int> root_set;
    dfs_small_to_large(0, -1, adj, val, ans, root_set);

    assert(ans[0] == 2); // {1, 2}
    assert(ans[1] == 1); // {2}
    assert(ans[2] == 1); // {2}
    return 0;
}
