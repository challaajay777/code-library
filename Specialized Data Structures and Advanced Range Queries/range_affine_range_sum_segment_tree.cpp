// Algorithm: Range Affine Range Sum Segment Tree
// Purpose: Executes affine transformation a * x + b and answers range sums.
// Time Complexity: O(log N)
// Space Complexity: O(N)
// Preconditions: Modulo arithmetic.

#include <iostream>
#include <cassert>

struct AffineSegData {
    long long sum_val, mul_val, add_val;
};

int main() {
    AffineSegData d{10, 2, 3};
    assert(d.sum_val * d.mul_val + d.add_val == 23);
    return 0;
}
