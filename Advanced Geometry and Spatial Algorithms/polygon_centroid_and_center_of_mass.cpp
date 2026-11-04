// Algorithm: Polygon Geometric Centroid Calculation
// Purpose: Computes center of mass / centroid of non-self-intersecting 2D polygon.
// Time Complexity: O(N)
// Space Complexity: O(1)
// Preconditions: Simple polygon.

#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>

struct Point {
    double x, y;
};

Point polygon_centroid(const std::vector<Point>& poly) {
    int n = poly.size();
    double cx = 0, cy = 0, signed_area = 0;
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        double a = poly[i].x * poly[j].y - poly[j].x * poly[i].y;
        signed_area += a;
        cx += (poly[i].x + poly[j].x) * a;
        cy += (poly[i].y + poly[j].y) * a;
    }
    signed_area *= 0.5;
    cx /= (6.0 * signed_area);
    cy /= (6.0 * signed_area);
    return {cx, cy};
}

int main() {
    std::vector<Point> square = {{0, 0}, {2, 0}, {2, 2}, {0, 2}};
    Point c = polygon_centroid(square);
    assert(std::abs(c.x - 1.0) < 1e-6 && std::abs(c.y - 1.0) < 1e-6);
    return 0;
}
