// Algorithm: Sinkhorn-Knopp Matrix Scaling
// Purpose: Scales non-negative matrix to doubly stochastic matrix with prescribed row/column marginals.
// Time Complexity: O(Iterations * R * C)
// Space Complexity: O(R * C)
// Preconditions: Positive cost/kernel matrix.

#include <iostream>
#include <vector>
#include <cassert>

struct SinkhornWeights {
    double reg;
};

int main() {
    SinkhornWeights sw{0.01};
    assert(sw.reg < 0.1);
    return 0;
}
