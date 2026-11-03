// Algorithm: Polygon Area and Point-in-Polygon (Ray Casting)
// Supports: Exact 2x polygon area (shoelace), Pick's theorem, Point-in-polygon test (inside, on boundary, outside)
// Indexing: Counter-clockwise or clockwise polygon vertices
// Complexity: O(n) time, O(1) space
// Preconditions: Simple polygon vertices

#include <bits/stdc++.h>
#include <cassert>
#include "point2d_and_vector2d.cpp"
using namespace std;

// Computes 2 * Area of polygon using shoelace formula
__int128 polygon_area_2x(const vector<Point>& poly) {
    int n = (int)poly.size();
    if (n < 3) return 0;
    __int128 area = 0;
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        area += (__int128)poly[i].x * poly[j].y - (__int128)poly[i].y * poly[j].x;
    }
    return area < 0 ? -area : area;
}

// Counts number of integer lattice points strictly on boundary of polygon (sum of gcd(|dx|, |dy|))
long long boundary_lattice_points(const vector<Point>& poly) {
    int n = (int)poly.size();
    long long count = 0;
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        long long dx = abs(poly[i].x - poly[j].x);
        long long dy = abs(poly[i].y - poly[j].y);
        count += std::gcd(dx, dy);
    }
    return count;
}

// Pick's Theorem: returns number of strictly interior integer lattice points
// Area = interior + boundary / 2 - 1  ==>  interior = (2 * Area - boundary + 2) / 2
long long interior_lattice_points(const vector<Point>& poly) {
    __int128 a2 = polygon_area_2x(poly);
    long long b = boundary_lattice_points(poly);
    return (long long)((a2 - b + 2) / 2);
}

// Point in polygon: returns 1 if strictly inside, 0 if on boundary, -1 if outside
int point_in_polygon(const Point& pt, const vector<Point>& poly) {
    int n = (int)poly.size();
    bool inside = false;

    for (int i = 0; i < n; ++i) {
        Point a = poly[i];
        Point b = poly[(i + 1) % n];

        // Check if pt is on segment AB
        __int128 cp = Point::orientation(a, b, pt);
        if (cp == 0) {
            if (min(a.x, b.x) <= pt.x && pt.x <= max(a.x, b.x) &&
                min(a.y, b.y) <= pt.y && pt.y <= max(a.y, b.y)) {
                return 0; // On boundary
            }
        }

        // Ray casting intersection
        if ((a.y > pt.y) != (b.y > pt.y)) {
            double x_intersect = (double)(b.x - a.x) * (pt.y - a.y) / (double)(b.y - a.y) + a.x;
            if (pt.x < x_intersect) {
                inside = !inside;
            }
        }
    }
    return inside ? 1 : -1;
}
