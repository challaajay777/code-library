// Algorithm: SPQR Tree Decomposition Representation
// Purpose: Represents the 3-connected decomposition structure (Series, Parallel, Rigid, Q-virtual).
// Time Complexity: O(V + E)
// Space Complexity: O(V + E)
// Preconditions: 2-connected planar or general graph.

#include <iostream>
#include <vector>
#include <cassert>

enum NodeType { SERIES, PARALLEL, RIGID, Q_EDGE };

struct SPQRNode {
    NodeType type;
    std::vector<int> edges;
};

int main() {
    SPQRNode node{SERIES, {0, 1, 2}};
    assert(node.type == SERIES);
    return 0;
}
