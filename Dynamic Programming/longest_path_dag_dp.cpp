// Algorithm: Longest Path in DAG via Topological Order DP
// Purpose: Finds the maximum weight path in a Directed Acyclic Graph and reconstructs vertex sequence.
// Time Complexity: O(V + E)
// Space Complexity: O(V + E)
// Preconditions: Graph is a Directed Acyclic Graph (DAG).

#include <iostream>
#include <vector>
#include <queue>
#include <cassert>
#include <algorithm>

struct Edge {
    int to, weight;
};

struct DAGPathResult {
    long long max_distance;
    std::vector<int> path;
};

DAGPathResult longest_path_dag(int n, const std::vector<std::vector<Edge>>& adj) {
    std::vector<int> in_degree(n, 0);
    for (int u = 0; u < n; ++u) {
        for (const auto& e : adj[u]) in_degree[e.to]++;
    }

    std::queue<int> q;
    for (int i = 0; i < n; ++i) {
        if (in_degree[i] == 0) q.push(i);
    }

    std::vector<long long> dp(n, 0);
    std::vector<int> parent(n, -1);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (const auto& e : adj[u]) {
            if (dp[u] + e.weight > dp[e.to]) {
                dp[e.to] = dp[u] + e.weight;
                parent[e.to] = u;
            }
            if (--in_degree[e.to] == 0) {
                q.push(e.to);
            }
        }
    }

    int best_end = 0;
    for (int i = 1; i < n; ++i) {
        if (dp[i] > dp[best_end]) best_end = i;
    }

    std::vector<int> path;
    int cur = best_end;
    while (cur != -1) {
        path.push_back(cur);
        cur = parent[cur];
    }
    std::reverse(path.begin(), path.end());
    return {dp[best_end], path};
}

int main() {
    int n = 4;
    std::vector<std::vector<Edge>> adj(n);
    adj[0].push_back({1, 3});
    adj[0].push_back({2, 2});
    adj[1].push_back({3, 4});
    adj[2].push_back({3, 1});

    auto res = longest_path_dag(n, adj);
    assert(res.max_distance == 7); // 0 -> 1 -> 3
    assert(res.path == std::vector<int>({0, 1, 3}));
    return 0;
}
