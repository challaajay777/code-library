// Algorithm: Diameter of Directed Acyclic Graph
// Purpose: Calculates the maximum path length between any pair of vertices in a DAG.
// Time Complexity: O(V + E)
// Space Complexity: O(V)
// Preconditions: Graph is a DAG.

#include <iostream>
#include <vector>
#include <queue>
#include <cassert>
#include <algorithm>

int dag_diameter(int n, const std::vector<std::vector<int>>& adj) {
    std::vector<int> in_deg(n, 0);
    for (int u = 0; u < n; ++u) {
        for (int v : adj[u]) in_deg[v]++;
    }

    std::queue<int> q;
    for (int i = 0; i < n; ++i) {
        if (in_deg[i] == 0) q.push(i);
    }

    std::vector<int> dp(n, 0);
    int max_len = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            dp[v] = std::max(dp[v], dp[u] + 1);
            max_len = std::max(max_len, dp[v]);
            if (--in_deg[v] == 0) q.push(v);
        }
    }
    return max_len;
}

int main() {
    int n = 4;
    std::vector<std::vector<int>> adj(n);
    adj[0].push_back(1);
    adj[1].push_back(2);
    adj[2].push_back(3);
    assert(dag_diameter(n, adj) == 3);
    return 0;
}
