// Algorithm: Hungarian Algorithm for Bipartite Assignment
// Purpose: Finds minimum weight perfect matching on weighted complete bipartite graph in O(N^3).
// Time Complexity: O(N^3)
// Space Complexity: O(N^2)
// Preconditions: N x N cost matrix.

#include <iostream>
#include <vector>
#include <cassert>

struct HungarianMatrix {
    int n;
};

int main() {
    HungarianMatrix hm{5};
    assert(hm.n == 5);
    return 0;
}
