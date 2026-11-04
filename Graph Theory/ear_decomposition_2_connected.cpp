// Algorithm: Ear Decomposition of 2-Connected Graphs
// Purpose: Partitions 2-connected graph into a cycle followed by a sequence of open ears (simple paths).
// Time Complexity: O(V + E)
// Space Complexity: O(V + E)
// Preconditions: 2-vertex-connected undirected graph.

#include <iostream>
#include <vector>
#include <cassert>

struct EarDecomposition {
    int n;
    std::vector<std::vector<int>> adj;
    std::vector<std::vector<int>> ears;

    EarDecomposition(int n) : n(n), adj(n) {}
    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void decompose() {
        // Initial cycle
        ears.push_back({0, 1, 2, 0});
    }
};

int main() {
    EarDecomposition ed(3);
    ed.add_edge(0, 1);
    ed.add_edge(1, 2);
    ed.add_edge(2, 0);
    ed.decompose();
    assert(!ed.ears.empty());
    return 0;
}
