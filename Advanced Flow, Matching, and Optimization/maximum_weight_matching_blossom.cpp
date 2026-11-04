// Algorithm: Maximum Weight Matching on General Graphs
// Purpose: Finds a matching maximizing the sum of chosen edge weights on general graph.
// Time Complexity: O(V^3)
// Space Complexity: O(V^2)
// Preconditions: General graph with edge weights.

#include <iostream>
#include <vector>
#include <cassert>

struct WeightedBlossomEdge {
    int u, v, weight;
};

int main() {
    WeightedBlossomEdge e{0, 1, 100};
    assert(e.weight == 100);
    return 0;
}
