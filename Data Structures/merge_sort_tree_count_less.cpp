// Algorithm: Merge Sort Tree Count Elements Less Than K
// Purpose: Counts elements strictly less than k in range [L, R] in O(log^2 N) using sorted vectors in tree.
// Time Complexity: O(log^2 N) query, O(N log N) build
// Space Complexity: O(N log N)
// Preconditions: Array of comparable elements.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

struct MergeSortTree {
    int n;
    std::vector<std::vector<int>> tree;

    MergeSortTree(int n) : n(n), tree(4 * n) {}

    void build(int node, int l, int r, const std::vector<int>& a) {
        if (l == r) {
            tree[node] = {a[l]};
            return;
        }
        int mid = (l + r) / 2;
        build(2 * node, l, mid, a);
        build(2 * node + 1, mid + 1, r, a);
        std::merge(tree[2 * node].begin(), tree[2 * node].end(),
                   tree[2 * node + 1].begin(), tree[2 * node + 1].end(),
                   std::back_inserter(tree[node]));
    }

    int count_less(int node, int l, int r, int ql, int qr, int k) {
        if (ql > r || qr < l) return 0;
        if (ql <= l && r <= qr) {
            return std::lower_bound(tree[node].begin(), tree[node].end(), k) - tree[node].begin();
        }
        int mid = (l + r) / 2;
        return count_less(2 * node, l, mid, ql, qr, k) + count_less(2 * node + 1, mid + 1, r, ql, qr, k);
    }
};

int main() {
    std::vector<int> a = {3, 1, 4, 1, 5, 9, 2};
    MergeSortTree mst(a.size());
    mst.build(1, 0, a.size() - 1, a);

    // Range [0, 4] is {3, 1, 4, 1, 5}. Elements < 4 are: 3, 1, 1 (count 3)
    assert(mst.count_less(1, 0, a.size() - 1, 0, 4, 4) == 3);
    return 0;
}
