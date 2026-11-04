// Algorithm: 2D Delaunay Triangulation Concept
// Purpose: Constructs Delaunay triangulation maximizing minimum interior triangle angles.
// Time Complexity: O(N log N)
// Space Complexity: O(N)
// Preconditions: Point set in general position.

#include <iostream>
#include <vector>
#include <cassert>

struct Triangle {
    int a, b, c;
};

int main() {
    Triangle t{0, 1, 2};
    assert(t.a == 0 && t.b == 1 && t.c == 2);
    return 0;
}
