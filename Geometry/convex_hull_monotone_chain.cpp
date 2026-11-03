// Algorithm: Convex Hull (Andrew's Monotone Chain)
// Supports: Convex hull of 2D points in counter-clockwise order, strict or non-strict hull
// Indexing: 2D integer coordinates
// Complexity: O(n log n) sorting, O(n) scan, O(n) memory
// Preconditions: Point coordinates fit within 64-bit signed integers

#include <bits/stdc++.h>
#include <cassert>
#include "point2d_and_vector2d.cpp"
using namespace std;

// Andrew's Monotone Chain algorithm
// Returns convex hull vertices in counter-clockwise order
vector<Point> convex_hull(vector<Point> pts, bool include_collinear = false) {
    int n = (int)pts.size();
    if (n <= 1) return pts;

    sort(pts.begin(), pts.end());
    pts.erase(unique(pts.begin(), pts.end()), pts.end());
    n = (int)pts.size();
    if (n <= 2) return pts;

    vector<Point> hull;
    hull.reserve(2 * n);

    // Lower hull
    for (int i = 0; i < n; ++i) {
        while (hull.size() >= 2) {
            __int128 cp = Point::orientation(hull[hull.size() - 2], hull.back(), pts[i]);
            if (include_collinear ? (cp < 0) : (cp <= 0)) {
                hull.pop_back();
            } else {
                break;
            }
        }
        hull.push_back(pts[i]);
    }

    // Upper hull
    size_t lower_hull_size = hull.size();
    for (int i = n - 2; i >= 0; --i) {
        while (hull.size() > lower_hull_size) {
            __int128 cp = Point::orientation(hull[hull.size() - 2], hull.back(), pts[i]);
            if (include_collinear ? (cp < 0) : (cp <= 0)) {
                hull.pop_back();
            } else {
                break;
            }
        }
        hull.push_back(pts[i]);
    }

    hull.pop_back(); // Remove duplicate starting point
    return hull;
}
