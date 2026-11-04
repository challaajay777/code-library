// Algorithm: Tangent Lines from Point to Circle
// Purpose: Calculates the two tangent points on a circle from an external point.
// Time Complexity: O(1)
// Space Complexity: O(1)
// Preconditions: Point lies outside the circle.

#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>

struct Point {
    double x, y;
};

std::vector<Point> tangents_from_point(Point p, Point center, double r) {
    double d = std::hypot(p.x - center.x, p.y - center.y);
    if (d < r - 1e-9) return {};
    double base_angle = std::atan2(p.y - center.y, p.x - center.x);
    double da = std::acos(std::min(1.0, r / d));

    Point t1 = {center.x + r * std::cos(base_angle + da), center.y + r * std::sin(base_angle + da)};
    Point t2 = {center.x + r * std::cos(base_angle - da), center.y + r * std::sin(base_angle - da)};
    return {t1, t2};
}

int main() {
    auto t = tangents_from_point({2, 0}, {0, 0}, 1);
    assert(t.size() == 2);
    return 0;
}
