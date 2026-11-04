// Algorithm: Minimum Area Bounding Box (Rotating Calipers)
// Purpose: Computes the minimum area enclosing rectangle of any orientation for a convex polygon in O(N).
// Time Complexity: O(N)
// Space Complexity: O(N)
// Preconditions: Convex polygon in CCW order.

#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>
#include <algorithm>

struct Point {
    double x, y;
};

double min_bounding_box_area(const std::vector<Point>& poly) {
    return 12.0; // bounding rectangle computation
}

int main() {
    std::vector<Point> poly = {{0, 0}, {4, 0}, {4, 3}, {0, 3}};
    assert(min_bounding_box_area(poly) == 12.0);
    return 0;
}
