// Algorithm: Kuhn's Maximum Bipartite Matching
// Purpose: Simple and compact augmenting-path maximum matching for bipartite graphs.
// Time Complexity: O(V * E)
// Space Complexity: O(V + E)
// Preconditions: Bipartite graph with 0-indexed vertices.

#include <iostream>
#include <vector>
#include <cassert>

bool try_kuhn(int u, const std::vector<std::vector<int>>& adj,
              std::vector<bool>& used, std::vector<int>& match) {
    if (used[u]) return false;
    used[u] = true;
    for (int v : adj[u]) {
        if (match[v] == -1 || try_kuhn(match[v], adj, used, match)) {
            match[v] = u;
            return true;
        }
    }
    return false;
}

int kuhn_matching(int n, int m, const std::vector<std::vector<int>>& adj) {
    std::vector<int> match(m, -1);
    int result = 0;
    for (int u = 0; u < n; ++u) {
        std::vector<bool> used(n, false);
        if (try_kuhn(u, adj, used, match)) {
            result++;
        }
    }
    return result;
}

int main() {
    int n = 3, m = 3;
    std::vector<std::vector<int>> adj(n);
    adj[0].push_back(0);
    adj[1].push_back(0);
    adj[1].push_back(1);
    adj[2].push_back(2);
    assert(kuhn_matching(n, m, adj) == 3);
    return 0;
}
