// Algorithm: Shortest Cycle Containing Given Edge
// Purpose: Finds the minimum length cycle in an undirected graph that contains edge (u, v).
// Time Complexity: O(V + E)
// Space Complexity: O(V)
// Preconditions: Undirected graph containing edge (u, v).

#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

int shortest_cycle_with_edge(int n, const std::vector<std::vector<int>>& adj, int u, int v) {
    // Find shortest path between u and v without using direct edge (u, v)
    std::vector<int> dist(n, -1);
    std::queue<int> q;
    dist[u] = 0;
    q.push(u);

    while (!q.empty()) {
        int cur = q.front();
        q.pop();

        for (int neighbor : adj[cur]) {
            if (cur == u && neighbor == v) continue; // skip edge (u, v)
            if (dist[neighbor] == -1) {
                dist[neighbor] = dist[cur] + 1;
                q.push(neighbor);
            }
        }
    }

    if (dist[v] == -1) return -1;
    return dist[v] + 1;
}

int main() {
    int n = 4;
    std::vector<std::vector<int>> adj(n);
    adj[0] = {1, 3};
    adj[1] = {0, 2};
    adj[2] = {1, 3};
    adj[3] = {0, 2};

    assert(shortest_cycle_with_edge(n, adj, 0, 1) == 4);
    return 0;
}
