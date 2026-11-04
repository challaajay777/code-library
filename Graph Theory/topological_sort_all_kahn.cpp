// Algorithm: Lexicographically Smallest Topological Sort (Kahn)
// Purpose: Finds the unique lexicographically smallest valid topological sort using priority queue.
// Time Complexity: O(V log V + E)
// Space Complexity: O(V + E)
// Preconditions: Directed Acyclic Graph.

#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

std::vector<int> lexico_topological_sort(int n, const std::vector<std::vector<int>>& adj) {
    std::vector<int> in_deg(n, 0);
    for (int u = 0; u < n; ++u) {
        for (int v : adj[u]) in_deg[v]++;
    }

    std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
    for (int i = 0; i < n; ++i) {
        if (in_deg[i] == 0) pq.push(i);
    }

    std::vector<int> order;
    while (!pq.empty()) {
        int u = pq.top();
        pq.pop();
        order.push_back(u);
        for (int v : adj[u]) {
            if (--in_deg[v] == 0) pq.push(v);
        }
    }
    if ((int)order.size() != n) return {};
    return order;
}

int main() {
    int n = 3;
    std::vector<std::vector<int>> adj(n);
    adj[2].push_back(0);
    // 1 and 2 have in_deg 0. Smallest is 1, then 2, then 0
    auto order = lexico_topological_sort(n, adj);
    assert(order == std::vector<int>({1, 2, 0}));
    return 0;
}
