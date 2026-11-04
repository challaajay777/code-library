// Algorithm: Point in Convex Polygon in O(log N)
// Purpose: Tests whether query point Q lies strictly inside a convex polygon in logarithmic time.
// Time Complexity: O(log N)
// Space Complexity: O(1)
// Preconditions: Convex polygon vertices sorted CCW from poly[0].

#include <iostream>
#include <vector>
#include <cassert>

struct Point {
    long long x, y;
};

long long cross(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool point_in_convex_polygon(const std::vector<Point>& poly, Point p) {
    int n = poly.size();
    if (n < 3) return false;
    if (cross(poly[0], poly[1], p) < 0 || cross(poly[0], poly[n - 1], p) > 0) return false;

    int low = 1, high = n - 2, ans = 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (cross(poly[0], poly[mid], p) >= 0) {
            ans = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return cross(poly[ans], poly[ans + 1], p) >= 0;
}

int main() {
    std::vector<Point> poly = {{0, 0}, {5, 0}, {5, 5}, {0, 5}};
    assert(point_in_convex_polygon(poly, {2, 2}));
    assert(!point_in_convex_polygon(poly, {6, 6}));
    return 0;
}
