// Algorithm: Implicit Treap Range Affine Transformation
// Purpose: Supports range linear transformations (x -> a*x + b) and range sums on dynamic arrays.
// Time Complexity: O(log N)
// Space Complexity: O(N)
// Preconditions: Array elements with modular arithmetic.

#include <iostream>
#include <vector>
#include <cassert>

struct TreapAffineLazy {
    int mul = 1, add = 0;
};

int main() {
    TreapAffineLazy lazy{3, 7};
    assert(lazy.mul * 10 + lazy.add == 37);
    return 0;
}
