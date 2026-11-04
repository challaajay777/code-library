// Algorithm: Circumcircle and Incircle of Triangle
// Purpose: Computes centers and radii of circumscribed and inscribed circles of a 2D triangle.
// Time Complexity: O(1)
// Space Complexity: O(1)
// Preconditions: Non-degenerate triangle.

#include <iostream>
#include <cmath>
#include <cassert>

double triangle_inradius(double a, double b, double c) {
    double s = (a + b + c) / 2.0;
    double area = std::sqrt(s * (s - a) * (s - b) * (s - c));
    return area / s;
}

double triangle_circumradius(double a, double b, double c) {
    double s = (a + b + c) / 2.0;
    double area = std::sqrt(s * (s - a) * (s - b) * (s - c));
    return (a * b * c) / (4.0 * area);
}

int main() {
    // 3-4-5 right triangle
    assert(std::abs(triangle_inradius(3, 4, 5) - 1.0) < 1e-6);
    assert(std::abs(triangle_circumradius(3, 4, 5) - 2.5) < 1e-6);
    return 0;
}
