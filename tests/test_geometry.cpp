// Test suite for Geometry algorithms
#include <bits/stdc++.h>
#include <cassert>
#include "Geometry/point2d_and_vector2d.cpp"
#include "Geometry/convex_hull_monotone_chain.cpp"
#include "Geometry/segment_intersection.cpp"
#include "Geometry/polygon_area_and_point_in_polygon.cpp"
#include "Geometry/closest_pair_of_points.cpp"

using namespace std;

void test_point_and_hull() {
    Point a(0, 0), b(4, 0), c(4, 3), d(0, 3);
    vector<Point> pts = {a, b, c, d, Point(2, 1), Point(1, 2)};
    auto hull = convex_hull(pts);
    // Hull of rectangle should be 4 vertices
    assert(hull.size() == 4);
}

void test_segment_intersection() {
    Point a(0, 0), b(4, 4);
    Point c(0, 4), d(4, 0);
    assert(segments_intersect(a, b, c, d)); // Crosses at (2, 2)

    Point e(0, 5), f(4, 5);
    assert(!segments_intersect(a, b, e, f)); // Parallel, disjoint

    Point g(2, 2), h(5, 5);
    assert(segments_intersect(a, b, g, h)); // Overlapping collinear
}

void test_polygon_and_picks() {
    // 3 x 3 square from (0,0) to (3,3)
    vector<Point> square = {Point(0, 0), Point(3, 0), Point(3, 3), Point(0, 3)};
    __int128 area2 = polygon_area_2x(square);
    assert(area2 == 18); // Area = 9 -> 2*Area = 18

    long long b = boundary_lattice_points(square);
    assert(b == 12); // 4 sides of length 3 -> 12 points

    long long i = interior_lattice_points(square);
    // Interior points in (0..3) x (0..3): 2 x 2 = 4 points {(1,1), (1,2), (2,1), (2,2)}
    assert(i == 4);

    // Point in polygon
    assert(point_in_polygon(Point(1, 1), square) == 1); // Strictly inside
    assert(point_in_polygon(Point(0, 1), square) == 0); // On boundary
    assert(point_in_polygon(Point(5, 5), square) == -1); // Outside
}

void test_closest_pair() {
    vector<Point> pts = {
        Point(0, 0, 0),
        Point(10, 10, 1),
        Point(1, 1, 2),
        Point(5, 5, 3),
        Point(20, 20, 4)
    };
    auto res = closest_pair(pts);
    // Closest pair is (0,0) and (1,1) -> dist_sq = 1^2 + 1^2 = 2
    assert(res.min_dist_sq == 2);
}

int main() {
    cout << "[TEST] Running test_geometry suite...\n";
    test_point_and_hull();
    test_segment_intersection();
    test_polygon_and_picks();
    test_closest_pair();
    cout << "[TEST] All 4 test sets in test_geometry passed!\n";
    return 0;
}
