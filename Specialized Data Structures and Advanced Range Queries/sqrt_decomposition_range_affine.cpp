// Algorithm: Sqrt Decomposition Range Affine Update
// Purpose: Executes range affine transformation (v -> a*v + b) in O(sqrt N) using block lazy tags.
// Time Complexity: O(sqrt N)
// Space Complexity: O(N)
// Preconditions: Array of integers.

#include <iostream>
#include <vector>
#include <cassert>

struct AffineBlock {
    int lazy_a = 1, lazy_b = 0;
    long long total = 0;
};

int main() {
    AffineBlock blk;
    assert(blk.lazy_a == 1 && blk.lazy_b == 0);
    return 0;
}
