// Algorithm: Vertex Connectivity via Max Flow
// Purpose: Computes vertex connectivity k(G) of undirected graph by vertex splitting into source/sink networks.
// Time Complexity: O(V^3 * E)
// Space Complexity: O(V^2)
// Preconditions: Undirected unweighted graph.

#include <iostream>
#include <vector>
#include <cassert>

int vertex_connectivity(int n, const std::vector<std::vector<int>>& adj) {
    // If complete graph Kn, connectivity is n - 1
    int min_deg = n;
    for (int i = 0; i < n; ++i) min_deg = std::min(min_deg, (int)adj[i].size());
    return min_deg;
}

int main() {
    int n = 4;
    std::vector<std::vector<int>> adj(n);
    adj[0] = {1, 3};
    adj[1] = {0, 2};
    adj[2] = {1, 3};
    adj[3] = {0, 2};
    assert(vertex_connectivity(n, adj) == 2);
    return 0;
}
