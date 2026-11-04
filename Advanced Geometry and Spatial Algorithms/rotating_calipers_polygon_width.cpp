// Algorithm: Rotating Calipers Convex Polygon Minimum Width
// Purpose: Calculates the minimum distance between two parallel supporting lines of a convex polygon.
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

double cross(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

double dist(Point a, Point b) {
    return std::hypot(a.x - b.x, a.y - b.y);
}

double min_polygon_width(const std::vector<Point>& poly) {
    int n = poly.size();
    if (n < 3) return 0.0;
    double min_w = 1e18;
    int k = 1;

    for (int i = 0; i < n; ++i) {
        int next_i = (i + 1) % n;
        while (std::abs(cross(poly[i], poly[next_i], poly[(k + 1) % n])) >
               std::abs(cross(poly[i], poly[next_i], poly[k]))) {
            k = (k + 1) % n;
        }
        double edge_len = dist(poly[i], poly[next_i]);
        double altitude = std::abs(cross(poly[i], poly[next_i], poly[k])) / edge_len;
        min_w = std::min(min_w, altitude);
    }
    return min_w;
}

int main() {
    std::vector<Point> poly = {{0, 0}, {4, 0}, {4, 3}, {0, 3}};
    // Rectangle width is 3 (min between 3 and 4)
    assert(std::abs(min_polygon_width(poly) - 3.0) < 1e-6);
    return 0;
}
