// Algorithm: Convex Polygon Cut by Directed Line
// Purpose: Cuts a convex polygon with a line and returns the resulting sub-polygon on the left side.
// Time Complexity: O(N)
// Space Complexity: O(N)
// Preconditions: Convex polygon in CCW order.

#include <iostream>
#include <vector>
#include <cassert>

struct Point {
    double x, y;
};

double cross_p(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

Point intersect_segments(Point a, Point b, Point c, Point d) {
    double s1 = cross_p(c, d, a);
    double s2 = cross_p(c, d, b);
    return {(a.x * s2 - b.x * s1) / (s2 - s1), (a.y * s2 - b.y * s1) / (s2 - s1)};
}

std::vector<Point> cut_polygon(const std::vector<Point>& poly, Point p1, Point p2) {
    std::vector<Point> res;
    int n = poly.size();
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        double c1 = cross_p(p1, p2, poly[i]);
        double c2 = cross_p(p1, p2, poly[j]);
        if (c1 >= -1e-9) res.push_back(poly[i]);
        if ((c1 > 1e-9 && c2 < -1e-9) || (c1 < -1e-9 && c2 > 1e-9)) {
            res.push_back(intersect_segments(poly[i], poly[j], p1, p2));
        }
    }
    return res;
}

int main() {
    std::vector<Point> square = {{0, 0}, {2, 0}, {2, 2}, {0, 2}};
    auto cut = cut_polygon(square, {0, 1}, {2, 1}); // horizontal cut at y = 1
    assert(cut.size() >= 3);
    return 0;
}
