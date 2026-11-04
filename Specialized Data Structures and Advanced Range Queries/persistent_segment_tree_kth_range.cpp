// Algorithm: Persistent Segment Tree Range K-th Smallest
// Purpose: Queries the k-th smallest element in subarray [L, R] in O(log N) using versioned segment tree roots.
// Time Complexity: O(log N) per query, O(N log N) build
// Space Complexity: O(N log N)
// Preconditions: 1-indexed bounds, 1 <= k <= R - L + 1.

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

struct PSTNode {
    int count = 0;
    int left = 0, right = 0;
};

struct PersistentSegKth {
    int n;
    std::vector<PSTNode> tree;
    std::vector<int> roots;

    PersistentSegKth(int n) : n(n) {
        tree.emplace_back(); // 0 is null node
        roots.push_back(0);
    }

    int insert(int prev_root, int l, int r, int val) {
        int cur = tree.size();
        tree.push_back(tree[prev_root]);
        tree[cur].count++;
        if (l == r) return cur;
        int mid = (l + r) / 2;
        if (val <= mid) tree[cur].left = insert(tree[prev_root].left, l, mid, val);
        else tree[cur].right = insert(tree[prev_root].right, mid + 1, r, val);
        return cur;
    }

    int query(int root_l, int root_r, int l, int r, int k) {
        if (l == r) return l;
        int count_left = tree[tree[root_r].left].count - tree[tree[root_l].left].count;
        int mid = (l + r) / 2;
        if (k <= count_left) return query(tree[root_l].left, tree[root_r].left, l, mid, k);
        return query(tree[root_l].right, tree[root_r].right, mid + 1, r, k - count_left);
    }
};

int main() {
    std::vector<int> a = {5, 2, 8, 3, 1};
    PersistentSegKth pst(10);
    for (int x : a) {
        int nr = pst.insert(pst.roots.back(), 1, 10, x);
        pst.roots.push_back(nr);
    }
    // Subarray [1, 4] corresponds to prefixes 0 and 4: elements {5, 2, 8, 3}. 2nd smallest is 3.
    assert(pst.query(pst.roots[0], pst.roots[4], 1, 10, 2) == 3);
    return 0;
}
