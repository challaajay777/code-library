// Algorithm: Welzl Minimum Enclosing Circle (Randomized O(N))
// Purpose: Finds the center and radius of the minimum enclosing circle enclosing N 2D points in expected O(N).
// Time Complexity: O(N) expected
// Space Complexity: O(N)
// Preconditions: Point set in 2D Euclidean plane.

#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <cassert>
#include <algorithm>

struct Point {
    double x, y;
};

struct Circle {
    Point c;
    double r;
};

double dist(Point a, Point b) {
    return std::hypot(a.x - b.x, a.y - b.y);
}

bool is_inside(Circle c, Point p) {
    return dist(c.c, p) <= c.r + 1e-9;
}

Circle circle_2(Point a, Point b) {
    Point c = {(a.x + b.x) / 2.0, (a.y + b.y) / 2.0};
    return {c, dist(a, b) / 2.0};
}

Circle circle_3(Point a, Point b, Point c) {
    double d = 2 * (a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y));
    if (std::abs(d) < 1e-9) return circle_2(a, b);
    double ux = ((a.x * a.x + a.y * a.y) * (b.y - c.y) + (b.x * b.x + b.y * b.y) * (c.y - a.y) + (c.x * c.x + c.y * c.y) * (a.y - b.y)) / d;
    double uy = ((a.x * a.x + a.y * a.y) * (c.x - b.x) + (b.x * b.x + b.y * b.y) * (a.x - c.x) + (c.x * c.x + c.y * c.y) * (b.x - a.x)) / d;
    Point center = {ux, uy};
    return {center, dist(center, a)};
}

Circle welzl_helper(std::vector<Point>& pts, std::vector<Point> R, int n) {
    if (n == 0 || R.size() == 3) {
        if (R.empty()) return {{0, 0}, 0};
        if (R.size() == 1) return {R[0], 0};
        if (R.size() == 2) return circle_2(R[0], R[1]);
        return circle_3(R[0], R[1], R[2]);
    }
    Point p = pts[n - 1];
    Circle c = welzl_helper(pts, R, n - 1);
    if (is_inside(c, p)) return c;
    R.push_back(p);
    return welzl_helper(pts, R, n - 1);
}

Circle welzl(std::vector<Point> pts) {
    std::mt19937 rng(42);
    std::shuffle(pts.begin(), pts.end(), rng);
    return welzl_helper(pts, {}, pts.size());
}

int main() {
    std::vector<Point> pts = {{0, 0}, {0, 2}, {2, 0}, {2, 2}};
    Circle c = welzl(pts);
    assert(std::abs(c.c.x - 1.0) < 1e-6);
    assert(std::abs(c.c.y - 1.0) < 1e-6);
    assert(std::abs(c.r - std::sqrt(2.0)) < 1e-6);
    return 0;
}
