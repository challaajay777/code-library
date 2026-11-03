// Algorithm: Segment-Segment Intersection
// Supports: Exact 2D line segment intersection detection (proper and collinear overlap)
// Indexing: 2D integer coordinates
// Complexity: O(1) time, exact arithmetic using __int128 to prevent overflow
// Preconditions: Segment endpoints fit in 64-bit signed integers

#include <bits/stdc++.h>
#include <cassert>
#include "point2d_and_vector2d.cpp"
using namespace std;

inline int sgn(__int128 val) {
    if (val > 0) return 1;
    if (val < 0) return -1;
    return 0;
}

// Checks if 1D interval [a, b] overlaps with [c, d]
inline bool intervals_overlap(long long a, long long b, long long c, long long d) {
    if (a > b) swap(a, b);
    if (c > d) swap(c, d);
    return max(a, c) <= min(b, d);
}

// Returns true if segment AB intersects segment CD
bool segments_intersect(const Point& a, const Point& b, const Point& c, const Point& d) {
    int cp1 = sgn(Point::orientation(a, b, c));
    int cp2 = sgn(Point::orientation(a, b, d));
    int cp3 = sgn(Point::orientation(c, d, a));
    int cp4 = sgn(Point::orientation(c, d, b));

    if (cp1 * cp2 < 0 && cp3 * cp4 < 0) {
        return true; // Proper crossing intersection
    }

    // Collinear or endpoint touching check: bounding box intersection
    if (cp1 == 0 && intervals_overlap(a.x, b.x, c.x, c.x) && intervals_overlap(a.y, b.y, c.y, c.y)) return true;
    if (cp2 == 0 && intervals_overlap(a.x, b.x, d.x, d.x) && intervals_overlap(a.y, b.y, d.y, d.y)) return true;
    if (cp3 == 0 && intervals_overlap(c.x, d.x, a.x, a.x) && intervals_overlap(c.y, d.y, a.y, a.y)) return true;
    if (cp4 == 0 && intervals_overlap(c.x, d.x, b.x, b.x) && intervals_overlap(c.y, d.y, b.y, b.y)) return true;

    return false;
}
