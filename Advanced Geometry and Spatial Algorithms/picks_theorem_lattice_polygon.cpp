// Algorithm: Pick's Theorem for Lattice Polygons
// Purpose: Calculates number of strictly interior lattice points given area and boundary points: I = A - B/2 + 1.
// Time Complexity: O(N log(MaxCoord))
// Space Complexity: O(N)
// Preconditions: Simple polygon with integer vertex coordinates.

#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <cassert>

struct Point {
    long long x, y;
};

long long gcd(long long a, long long b) {
    return b == 0 ? a : gcd(b, a % b);
}

std::pair<long long, long long> picks_theorem(const std::vector<Point>& poly) {
    int n = poly.size();
    long long double_area = 0;
    long long b = 0;

    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        double_area += poly[i].x * poly[j].y - poly[j].x * poly[i].y;
        long long dx = std::abs(poly[j].x - poly[i].x);
        long long dy = std::abs(poly[j].y - poly[i].y);
        b += gcd(dx, dy);
    }
    double_area = std::abs(double_area);
    long long interior = (double_area - b + 2) / 2;
    return {interior, b};
}

int main() {
    std::vector<Point> square = {{0, 0}, {3, 0}, {3, 3}, {0, 3}};
    auto [interior, boundary] = picks_theorem(square);
    assert(boundary == 12);
    assert(interior == 4); // Area 9 = 4 + 12/2 - 1 = 9
    return 0;
}
