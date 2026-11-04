// Algorithm: Circle-Circle Intersection Area
// Purpose: Calculates the exact overlapping area between two circles.
// Time Complexity: O(1)
// Space Complexity: O(1)
// Preconditions: Two circles with radii r1, r2 > 0.

#include <iostream>
#include <cmath>
#include <cassert>
#include <algorithm>

const double PI = std::acos(-1.0);

double circle_intersection_area(double x1, double y1, double r1, double x2, double y2, double r2) {
    double d = std::hypot(x1 - x2, y1 - y2);
    if (d >= r1 + r2) return 0.0;
    if (d <= std::abs(r1 - r2)) return PI * std::min(r1, r2) * std::min(r1, r2);

    double alpha = 2.0 * std::acos((r1 * r1 + d * d - r2 * r2) / (2.0 * r1 * d));
    double beta = 2.0 * std::acos((r2 * r2 + d * d - r1 * r1) / (2.0 * r2 * d));

    double area1 = 0.5 * r1 * r1 * (alpha - std::sin(alpha));
    double area2 = 0.5 * r2 * r2 * (beta - std::sin(beta));
    return area1 + area2;
}

int main() {
    double a = circle_intersection_area(0, 0, 2, 2, 0, 2);
    assert(a > 0.0);
    return 0;
}
