// Algorithm: Minkowski Sum of Two Convex Polygons
// Purpose: Computes the Minkowski sum P + Q of two convex polygons in linear time O(N + M).
// Time Complexity: O(N + M)
// Space Complexity: O(N + M)
// Preconditions: Two convex polygons in counter-clockwise order.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

struct Point {
    long long x, y;
};

long long cross(Point a, Point b) { return a.x * b.y - a.y * b.x; }

std::vector<Point> minkowski_sum(std::vector<Point> P, std::vector<Point> Q) {
    auto reorder = [](std::vector<Point>& poly) {
        size_t pos = 0;
        for (size_t i = 1; i < poly.size(); ++i) {
            if (poly[i].y < poly[pos].y || (poly[i].y == poly[pos].y && poly[i].x < poly[pos].x)) pos = i;
        }
        std::rotate(poly.begin(), poly.begin() + pos, poly.end());
    };
    reorder(P);
    reorder(Q);

    int n = P.size(), m = Q.size();
    P.push_back(P[0]); P.push_back(P[1]);
    Q.push_back(Q[0]); Q.push_back(Q[1]);

    std::vector<Point> result;
    int i = 0, j = 0;
    while (i < n || j < m) {
        result.push_back({P[i].x + Q[j].x, P[i].y + Q[j].y});
        Point edge_P = {P[i + 1].x - P[i].x, P[i + 1].y - P[i].y};
        Point edge_Q = {Q[j + 1].x - Q[j].x, Q[j + 1].y - Q[j].y};
        long long cr = cross(edge_P, edge_Q);
        if (cr >= 0 && i < n) i++;
        if (cr <= 0 && j < m) j++;
    }
    return result;
}

int main() {
    std::vector<Point> P = {{0, 0}, {2, 0}, {0, 2}};
    std::vector<Point> Q = {{0, 0}, {1, 0}, {0, 1}};
    auto sum = minkowski_sum(P, Q);
    assert(!sum.empty());
    return 0;
}
