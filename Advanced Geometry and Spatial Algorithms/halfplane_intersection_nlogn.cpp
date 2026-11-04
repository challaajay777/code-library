// Algorithm: Half-Plane Intersection in O(N log N)
// Purpose: Computes the convex polygon formed by the intersection of N half-planes in O(N log N).
// Time Complexity: O(N log N)
// Space Complexity: O(N)
// Preconditions: Collection of directed bounding half-planes.

#include <iostream>
#include <vector>
#include <cmath>
#include <deque>
#include <cassert>
#include <algorithm>

struct Point {
    double x, y;
};

struct Line {
    Point p, v; // p + t * v
    double angle;
    Line() {}
    Line(Point p, Point v) : p(p), v(v), angle(std::atan2(v.y, v.x)) {}
};

double cross_prod(Point a, Point b) { return a.x * b.y - a.y * b.x; }

Point line_intersection(Line a, Line b) {
    Point u = {a.p.x - b.p.x, a.p.y - b.p.y};
    double t = cross_prod(b.v, u) / cross_prod(a.v, b.v);
    return {a.p.x + a.v.x * t, a.p.y + a.v.y * t};
}

bool on_left(Line l, Point p) {
    return cross_prod(l.v, {p.x - l.p.x, p.y - l.p.y}) >= -1e-9;
}

std::vector<Point> halfplane_intersection(std::vector<Line> lines) {
    std::sort(lines.begin(), lines.end(), [](const Line& a, const Line& b) {
        if (std::abs(a.angle - b.angle) > 1e-9) return a.angle < b.angle;
        return on_left(a, b.p);
    });

    std::vector<Line> unique_lines;
    for (size_t i = 0; i < lines.size(); ++i) {
        if (i == 0 || std::abs(lines[i].angle - lines[i - 1].angle) > 1e-9) {
            unique_lines.push_back(lines[i]);
        }
    }

    std::deque<Line> q;
    std::deque<Point> pts;

    for (const auto& l : unique_lines) {
        while (pts.size() >= 1 && !on_left(l, pts.back())) pts.pop_back(), q.pop_back();
        while (pts.size() >= 1 && !on_left(l, pts.front())) pts.pop_front(), q.pop_front();
        if (!q.empty()) pts.push_back(line_intersection(q.back(), l));
        q.push_back(l);
    }
    while (pts.size() >= 1 && !on_left(q.front(), pts.back())) pts.pop_back(), q.pop_back();
    if (q.size() < 3) return {};

    pts.push_back(line_intersection(q.back(), q.front()));
    return std::vector<Point>(pts.begin(), pts.end());
}

int main() {
    std::vector<Line> box = {
        Line({0, 0}, {1, 0}),  // y >= 0
        Line({1, 0}, {0, 1}),  // x <= 1
        Line({1, 1}, {-1, 0}), // y <= 1
        Line({0, 1}, {0, -1})  // x >= 0
    };
    auto poly = halfplane_intersection(box);
    assert(poly.size() == 4);
    return 0;
}
