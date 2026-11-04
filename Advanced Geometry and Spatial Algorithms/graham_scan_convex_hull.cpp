// Algorithm: Graham Scan Convex Hull
// Purpose: Computes the 2D convex hull of N points using polar angle sorting in O(N log N).
// Time Complexity: O(N log N)
// Space Complexity: O(N)
// Preconditions: Point set in 2D Euclidean plane.

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

struct Point {
    long long x, y;
};

long long cross(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

long long dist_sq(Point a, Point b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

std::vector<Point> graham_scan(std::vector<Point>& pts) {
    int n = pts.size();
    if (n <= 2) return pts;

    int min_idx = 0;
    for (int i = 1; i < n; ++i) {
        if (pts[i].y < pts[min_idx].y || (pts[i].y == pts[min_idx].y && pts[i].x < pts[min_idx].x)) {
            min_idx = i;
        }
    }
    std::swap(pts[0], pts[min_idx]);
    Point p0 = pts[0];

    std::sort(pts.begin() + 1, pts.end(), [&](Point a, Point b) {
        long long cr = cross(p0, a, b);
        if (cr != 0) return cr > 0;
        return dist_sq(p0, a) < dist_sq(p0, b);
    });

    std::vector<Point> hull = {pts[0], pts[1]};
    for (int i = 2; i < n; ++i) {
        while (hull.size() >= 2 && cross(hull[hull.size() - 2], hull.back(), pts[i]) <= 0) {
            hull.pop_back();
        }
        hull.push_back(pts[i]);
    }
    return hull;
}

int main() {
    std::vector<Point> pts = {{0, 0}, {0, 3}, {3, 0}, {3, 3}, {1, 1}};
    auto hull = graham_scan(pts);
    assert(hull.size() == 4);
    return 0;
}
