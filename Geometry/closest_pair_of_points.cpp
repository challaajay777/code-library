// Algorithm: Closest Pair of Points (Divide and Conquer)
// Supports: Finding minimum Euclidean distance squared between any pair of 2D points
// Indexing: 2D integer coordinates
// Complexity: O(n log n) time, O(n) memory
// Preconditions: Point set has size >= 2

#include <bits/stdc++.h>
#include <cassert>
#include "point2d_and_vector2d.cpp"
using namespace std;

struct ClosestPairResult {
    long long min_dist_sq;
    Point p1, p2;
};

ClosestPairResult closest_pair(vector<Point> pts) {
    int n = (int)pts.size();
    assert(n >= 2);

    for (int i = 0; i < n; ++i) pts[i].id = i;
    sort(pts.begin(), pts.end(), [](const Point& a, const Point& b) {
        if (a.x != b.x) return a.x < b.x;
        return a.y < b.y;
    });

    auto rec = [&](auto& self, int l, int r) -> ClosestPairResult {
        if (r - l <= 3) {
            long long d_sq = numeric_limits<long long>::max();
            Point best_p1, best_p2;
            for (int i = l; i <= r; ++i) {
                for (int j = i + 1; j <= r; ++j) {
                    long long cur = pts[i].dist_sq(pts[j]);
                    if (cur < d_sq) {
                        d_sq = cur;
                        best_p1 = pts[i];
                        best_p2 = pts[j];
                    }
                }
            }
            sort(pts.begin() + l, pts.begin() + r + 1, [](const Point& a, const Point& b) {
                return a.y < b.y;
            });
            return {d_sq, best_p1, best_p2};
        }

        int mid = l + (r - l) / 2;
        long long mid_x = pts[mid].x;

        auto left_res = self(self, l, mid);
        auto right_res = self(self, mid + 1, r);

        ClosestPairResult best = (left_res.min_dist_sq < right_res.min_dist_sq) ? left_res : right_res;
        long long d_sq = best.min_dist_sq;

        // Merge step for y-sorting
        inplace_merge(pts.begin() + l, pts.begin() + mid + 1, pts.begin() + r + 1,
                      [](const Point& a, const Point& b) { return a.y < b.y; });

        // Strip check
        vector<Point> strip;
        for (int i = l; i <= r; ++i) {
            long long dx = pts[i].x - mid_x;
            if (dx * dx < d_sq) {
                strip.push_back(pts[i]);
            }
        }

        for (size_t i = 0; i < strip.size(); ++i) {
            for (size_t j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) * (strip[j].y - strip[i].y) < d_sq; ++j) {
                long long cur = strip[i].dist_sq(strip[j]);
                if (cur < d_sq) {
                    d_sq = cur;
                    best = {d_sq, strip[i], strip[j]};
                }
            }
        }
        return best;
    };

    return rec(rec, 0, n - 1);
}
