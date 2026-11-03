// Algorithm: Point2D and Vector2D
// Supports: Vector addition, subtraction, dot product, cross product, orientation test
// Indexing: 2D Cartesian plane (x, y)
// Complexity: O(1) per operation, exact 64-bit/128-bit integer precision
// Preconditions: Point coordinates fit within 64-bit signed integers

#ifndef GEOMETRY_POINT_H
#define GEOMETRY_POINT_H

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

struct Point {
    long long x, y;
    int id = 0;

    Point() : x(0), y(0), id(0) {}
    Point(long long x, long long y, int id = 0) : x(x), y(y), id(id) {}

    Point operator+(const Point& o) const { return Point(x + o.x, y + o.y); }
    Point operator-(const Point& o) const { return Point(x - o.x, y - o.y); }

    bool operator<(const Point& o) const {
        if (x != o.x) return x < o.x;
        return y < o.y;
    }
    bool operator==(const Point& o) const {
        return x == o.x && y == o.y;
    }
    bool operator!=(const Point& o) const {
        return !(*this == o);
    }

    // Dot product: A . B = A.x * B.x + A.y * B.y
    long long dot(const Point& o) const {
        return x * o.x + y * o.y;
    }

    // 2D Cross product: A x B = A.x * B.y - A.y * B.x
    __int128 cross(const Point& o) const {
        return (__int128)x * o.y - (__int128)y * o.x;
    }

    // Cross product of vectors (B - A) and (C - A)
    // > 0: CCW turn (left)
    // < 0: CW turn (right)
    // == 0: collinear
    static __int128 orientation(const Point& a, const Point& b, const Point& c) {
        return (b - a).cross(c - a);
    }

    // Squared Euclidean distance
    long long dist_sq(const Point& o) const {
        long long dx = x - o.x;
        long long dy = y - o.y;
        return dx * dx + dy * dy;
    }
};

#endif // GEOMETRY_POINT_H
