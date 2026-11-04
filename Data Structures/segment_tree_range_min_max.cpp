// Algorithm: Segment Tree for Range Min and Max
// Purpose: Maintains both minimum and maximum of range [L, R] simultaneously in O(log N).
// Time Complexity: O(log N) query/update
// Space Complexity: O(N)
// Preconditions: Array of comparable numbers.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

struct RangeMinMaxTree {
    int n;
    std::vector<int> tree_min, tree_max;

    RangeMinMaxTree(int n) : n(n), tree_min(4 * n, 1e9), tree_max(4 * n, -1e9) {}

    void update(int node, int l, int r, int idx, int val) {
        if (l == r) {
            tree_min[node] = tree_max[node] = val;
            return;
        }
        int mid = (l + r) / 2;
        if (idx <= mid) update(2 * node, l, mid, idx, val);
        else update(2 * node + 1, mid + 1, r, idx, val);
        tree_min[node] = std::min(tree_min[2 * node], tree_min[2 * node + 1]);
        tree_max[node] = std::max(tree_max[2 * node], tree_max[2 * node + 1]);
    }

    std::pair<int, int> query(int node, int l, int r, int ql, int qr) {
        if (ql > r || qr < l) return {1e9, -1e9};
        if (ql <= l && r <= qr) return {tree_min[node], tree_max[node]};
        int mid = (l + r) / 2;
        auto left = query(2 * node, l, mid, ql, qr);
        auto right = query(2 * node + 1, mid + 1, r, ql, qr);
        return {std::min(left.first, right.first), std::max(left.second, right.second)};
    }
};

int main() {
    RangeMinMaxTree tree(5);
    tree.update(1, 0, 4, 0, 10);
    tree.update(1, 0, 4, 1, 2);
    tree.update(1, 0, 4, 2, 7);
    tree.update(1, 0, 4, 3, 20);
    tree.update(1, 0, 4, 4, 5);

    auto [mn, mx] = tree.query(1, 0, 4, 1, 3);
    assert(mn == 2);
    assert(mx == 20);
    return 0;
}
