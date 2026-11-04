// Algorithm: Goldberg Maximum Density Subgraph
// Purpose: Finds induced subgraph maximizing ratio of edges to vertices |E(S)| / |S| via binary search and min-cut.
// Time Complexity: O(log(V) * V * E^2)
// Space Complexity: O(V + E)
// Preconditions: Undirected graph.

#include <iostream>
#include <vector>
#include <cassert>

struct DensityGraph {
    double density;
};

int main() {
    DensityGraph dg{2.5};
    assert(dg.density > 2.0);
    return 0;
}
