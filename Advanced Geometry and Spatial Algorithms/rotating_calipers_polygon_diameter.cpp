// Algorithm: Rotating Calipers Convex Polygon Diameter
// Purpose: Finds the maximum Euclidean distance between any pair of vertices of a convex polygon in O(N).
// Time Complexity: O(N)
// Space Complexity: O(N)
// Preconditions: Vertices of strictly convex polygon in counter-clockwise order.

#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>
#include <algorithm>

struct Point {
    long long x, y;
};

long long cross_product(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

long long dist_sq(Point a, Point b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

long long polygon_diameter_sq(const std::vector<Point>& poly) {
    int n = poly.size();
    if (n <= 1) return 0;
    if (n == 2) return dist_sq(poly[0], poly[1]);

    int k = 1;
    while (std::abs(cross_product(poly[n - 1], poly[0], poly[(k + 1) % n])) >
           std::abs(cross_product(poly[n - 1], poly[0], poly[k]))) {
        k++;
    }

    long long max_d = 0;
    for (int i = 0, j = k; i <= k; ++i) {
        while (std::abs(cross_product(poly[i], poly[(i + 1) % n], poly[(j + 1) % n])) >
               std::abs(cross_product(poly[i], poly[(i + 1) % n], poly[j]))) {
            max_d = std::max(max_d, dist_sq(poly[i], poly[j]));
            j = (j + 1) % n;
        }
        max_d = std::max(max_d, dist_sq(poly[i], poly[j]));
    }
    return max_d;
}

int main() {
    std::vector<Point> poly = {{0, 0}, {4, 0}, {4, 3}, {0, 3}};
    // Square diagonal 4^2 + 3^2 = 25
    assert(polygon_diameter_sq(poly) == 25);
    return 0;
}
