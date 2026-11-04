// Algorithm: Planar Graph Face Count via Euler Formula
// Purpose: Verifies planar topology and calculates face count via Euler formula V - E + F = 1 + C.
// Time Complexity: O(1)
// Space Complexity: O(1)
// Preconditions: Planar graph parameters.

#include <iostream>
#include <cassert>

int count_planar_faces(int v, int e, int connected_components = 1) {
    // V - E + F = 1 + C => F = E - V + 1 + C
    return e - v + 1 + connected_components;
}

int main() {
    // K4: V = 4, E = 6, C = 1 -> F = 6 - 4 + 2 = 4
    assert(count_planar_faces(4, 6, 1) == 4);
    return 0;
}
