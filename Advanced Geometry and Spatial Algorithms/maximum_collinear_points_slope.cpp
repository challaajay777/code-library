// Algorithm: Maximum Collinear Points via Slope Hashing
// Purpose: Finds the maximum number of points lying on a single straight line in O(N^2) time.
// Time Complexity: O(N^2)
// Space Complexity: O(N)
// Preconditions: 2D point set.

#include <iostream>
#include <vector>
#include <map>
#include <numeric>
#include <algorithm>
#include <cassert>

struct Point {
    int x, y;
};

long long gcd(long long a, long long b) { return b == 0 ? a : gcd(b, a % b); }

int max_collinear_points(const std::vector<Point>& pts) {
    int n = pts.size();
    if (n <= 2) return n;
    int max_pts = 0;

    for (int i = 0; i < n; ++i) {
        std::map<std::pair<int, int>, int> slopes;
        int duplicates = 1;
        for (int j = i + 1; j < n; ++j) {
            if (pts[i].x == pts[j].x && pts[i].y == pts[j].y) {
                duplicates++;
            } else {
                int dx = pts[j].x - pts[i].x;
                int dy = pts[j].y - pts[i].y;
                int g = gcd(std::abs(dx), std::abs(dy));
                dx /= g; dy /= g;
                if (dx < 0 || (dx == 0 && dy < 0)) { dx = -dx; dy = -dy; }
                slopes[{dx, dy}]++;
            }
        }
        max_pts = std::max(max_pts, duplicates);
        for (const auto& [slope, count] : slopes) {
            max_pts = std::max(max_pts, count + duplicates);
        }
    }
    return max_pts;
}

int main() {
    std::vector<Point> pts = {{1, 1}, {2, 2}, {3, 3}, {1, 2}};
    assert(max_collinear_points(pts) == 3);
    return 0;
}
