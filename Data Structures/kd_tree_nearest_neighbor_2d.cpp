// Algorithm: 2D K-d Tree Nearest Neighbor Search
// Purpose: Finds the closest point to a query coordinate in 2D space using alternating dimension partitioning.
// Time Complexity: O(N log N) build, O(log N) average query
// Space Complexity: O(N)
// Preconditions: Point set in 2D plane.

#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>
#include <algorithm>

struct Point {
    int x, y;
};

long long dist_sq(Point a, Point b) {
    return 1LL * (a.x - b.x) * (a.x - b.x) + 1LL * (a.y - b.y) * (a.y - b.y);
}

struct KDNode {
    Point pt;
    KDNode *left = nullptr, *right = nullptr;
    KDNode(Point p) : pt(p) {}
};

KDNode* build_kdtree(std::vector<Point>& pts, int l, int r, int depth) {
    if (l > r) return nullptr;
    int mid = (l + r) / 2;
    int cd = depth % 2;
    std::nth_element(pts.begin() + l, pts.begin() + mid, pts.begin() + r + 1,
                     [cd](Point a, Point b) { return cd == 0 ? a.x < b.x : a.y < b.y; });
    KDNode* node = new KDNode(pts[mid]);
    node->left = build_kdtree(pts, l, mid - 1, depth + 1);
    node->right = build_kdtree(pts, mid + 1, r, depth + 1);
    return node;
}

void nearest_neighbor(KDNode* root, Point q, int depth, Point& best_pt, long long& best_dist) {
    if (!root) return;
    long long d = dist_sq(root->pt, q);
    if (d < best_dist) {
        best_dist = d;
        best_pt = root->pt;
    }
    int cd = depth % 2;
    int diff = (cd == 0) ? (q.x - root->pt.x) : (q.y - root->pt.y);

    KDNode* first = (diff < 0) ? root->left : root->right;
    KDNode* second = (diff < 0) ? root->right : root->left;

    nearest_neighbor(first, q, depth + 1, best_pt, best_dist);
    if (1LL * diff * diff < best_dist) {
        nearest_neighbor(second, q, depth + 1, best_pt, best_dist);
    }
}

int main() {
    std::vector<Point> pts = {{2, 3}, {5, 4}, {9, 6}, {4, 7}, {8, 1}, {7, 2}};
    KDNode* root = build_kdtree(pts, 0, pts.size() - 1, 0);

    Point q = {9, 2};
    Point best;
    long long d = 1e18;
    nearest_neighbor(root, q, 0, best, d);

    // Nearest point to (9, 2) is (8, 1) or (7, 2) -> dist^2 = (1^2 + 1^2) = 2
    assert(best.x == 8 && best.y == 1);
    assert(d == 2);
    return 0;
}
