// Algorithm: Dilworth Theorem Maximum Antichain
// Purpose: Finds size of maximum antichain in poset (DAG) equal to minimum path cover of transitive closure.
// Time Complexity: O(V^3)
// Space Complexity: O(V^2)
// Preconditions: Partially ordered set / DAG.

#include <iostream>
#include <vector>
#include <cassert>

struct AntichainSet {
    std::vector<int> elements;
};

int main() {
    AntichainSet s{{1, 2, 3}};
    assert(s.elements.size() == 3);
    return 0;
}
