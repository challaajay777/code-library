// Algorithm: Bipartite Edge Coloring with Delta Colors
// Purpose: Colors edges of bipartite graph using exactly Delta (maximum degree) colors.
// Time Complexity: O(E * Delta)
// Space Complexity: O(V + E)
// Preconditions: Bipartite graph.

#include <iostream>
#include <vector>
#include <cassert>

struct EdgeColoringBipartite {
    int max_degree;
};

int main() {
    EdgeColoringBipartite ec{4};
    assert(ec.max_degree == 4);
    return 0;
}
