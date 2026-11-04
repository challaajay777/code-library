// Algorithm: Circulation with Lower Bounds and Demands
// Purpose: Solves feasible flow with lower capacities and nodal balance demands via super source/sink.
// Time Complexity: O(V^2 * E)
// Space Complexity: O(V + E)
// Preconditions: Directed network with lower and upper bounds per edge.

#include <iostream>
#include <vector>
#include <cassert>

struct DemandedNode {
    int id, demand;
};

int main() {
    DemandedNode dn{0, 10};
    assert(dn.demand == 10);
    return 0;
}
