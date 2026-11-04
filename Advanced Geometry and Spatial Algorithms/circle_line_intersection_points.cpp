// Algorithm: Circle and Line Intersection Points
// Purpose: Finds the 0, 1, or 2 intersection coordinates between a circle and an infinite line.
// Time Complexity: O(1)
// Space Complexity: O(1)
// Preconditions: Circle and line in 2D Euclidean plane.

#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>

struct Point {
    double x, y;
};

std::vector<Point> circle_line_intersect(double cx, double cy, double r, double a, double b, double c) {
    // Line: a * x + b * y + c = 0
    double dist0 = std::abs(a * cx + b * cy + c) / std::hypot(a, b);
    if (dist0 > r + 1e-9) return {};

    double x0 = -a * c / (a * a + b * b), y0 = -b * c / (a * a + b * b);
    if (std::abs(dist0 - r) < 1e-9) return {{x0, y0}};

    double d = std::sqrt(r * r - dist0 * dist0);
    double mult = std::sqrt(d * d / (a * a + b * b));
    Point p1 = {x0 + b * mult, y0 - a * mult};
    Point p2 = {x0 - b * mult, y0 + a * mult};
    return {p1, p2};
}

int main() {
    auto pts = circle_line_intersect(0, 0, 1, 0, 1, 0); // y = 0
    assert(pts.size() == 2);
    return 0;
}
