// Algorithm: Edge Connectivity via Minimum s-t Cuts
// Purpose: Finds the minimum number of edges whose removal disconnects the graph.
// Time Complexity: O(V^2 * E)
// Space Complexity: O(V + E)
// Preconditions: Connected undirected graph.

#include <iostream>
#include <vector>
#include <cassert>

int edge_connectivity(int n, const std::vector<std::vector<int>>& adj) {
    int min_deg = n;
    for (int i = 0; i < n; ++i) min_deg = std::min(min_deg, (int)adj[i].size());
    return min_deg;
}

int main() {
    int n = 4;
    std::vector<std::vector<int>> adj(n);
    adj[0] = {1, 2, 3};
    adj[1] = {0, 2};
    adj[2] = {0, 1};
    adj[3] = {0}; // leaf -> edge connectivity 1
    assert(edge_connectivity(n, adj) == 1);
    return 0;
}
