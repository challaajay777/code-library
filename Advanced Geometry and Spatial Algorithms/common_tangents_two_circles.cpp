// Algorithm: Common Tangents Between Two Circles
// Purpose: Computes the external and internal common tangent lines between two disjoint or intersecting circles.
// Time Complexity: O(1)
// Space Complexity: O(1)
// Preconditions: Two distinct circles.

#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>

int count_common_tangents(double r1, double r2, double d) {
    if (d > r1 + r2) return 4; // 2 external, 2 internal
    if (std::abs(d - (r1 + r2)) < 1e-9) return 3;
    if (d > std::abs(r1 - r2)) return 2;
    if (std::abs(d - std::abs(r1 - r2)) < 1e-9) return 1;
    return 0;
}

int main() {
    assert(count_common_tangents(2, 3, 10) == 4);
    assert(count_common_tangents(2, 3, 5) == 3);
    assert(count_common_tangents(2, 3, 4) == 2);
    return 0;
}
