// Algorithm: Point to Line Segment Minimum Distance
// Purpose: Computes the minimum Euclidean distance between a 2D point and a finite line segment.
// Time Complexity: O(1)
// Space Complexity: O(1)
// Preconditions: Finite segment endpoints a and b.

#include <iostream>
#include <cmath>
#include <algorithm>
#include <cassert>

struct Point {
    double x, y;
};

double dist_to_segment(Point p, Point a, Point b) {
    double l2 = (b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y);
    if (l2 < 1e-9) return std::hypot(p.x - a.x, p.y - a.y);
    double t = std::max(0.0, std::min(1.0, ((p.x - a.x) * (b.x - a.x) + (p.y - a.y) * (b.y - a.y)) / l2));
    Point projection = {a.x + t * (b.x - a.x), a.y + t * (b.y - a.y)};
    return std::hypot(p.x - projection.x, p.y - projection.y);
}

int main() {
    Point p = {1, 1};
    Point a = {0, 0}, b = {2, 0};
    assert(std::abs(dist_to_segment(p, a, b) - 1.0) < 1e-6);
    return 0;
}
