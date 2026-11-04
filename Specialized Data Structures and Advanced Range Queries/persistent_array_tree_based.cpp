// Algorithm: Persistent Array via Binary Tree Path Copying
// Purpose: Supports purely functional array updates and lookups in O(log N) with version branch preservation.
// Time Complexity: O(log N) get and set
// Space Complexity: O(log N) per update
// Preconditions: 0-indexed array bounds.

#include <iostream>
#include <vector>
#include <cassert>

struct PANode {
    int val = 0;
    int left = 0, right = 0;
};

struct TreePersistentArray {
    int n;
    std::vector<PANode> tree;
    std::vector<int> roots;

    TreePersistentArray(int n) : n(n) {
        tree.emplace_back(); // null node
        roots.push_back(build(0, n - 1));
    }

    int build(int l, int r) {
        int cur = tree.size();
        tree.emplace_back();
        if (l == r) return cur;
        int mid = (l + r) / 2;
        tree[cur].left = build(l, mid);
        tree[cur].right = build(mid + 1, r);
        return cur;
    }

    int update(int prev_root, int l, int r, int idx, int val) {
        int cur = tree.size();
        tree.push_back(tree[prev_root]);
        if (l == r) {
            tree[cur].val = val;
            return cur;
        }
        int mid = (l + r) / 2;
        if (idx <= mid) tree[cur].left = update(tree[prev_root].left, l, mid, idx, val);
        else tree[cur].right = update(tree[prev_root].right, mid + 1, r, idx, val);
        return cur;
    }

    int query(int root, int l, int r, int idx) {
        if (l == r) return tree[root].val;
        int mid = (l + r) / 2;
        if (idx <= mid) return query(tree[root].left, l, mid, idx);
        return query(tree[root].right, mid + 1, r, idx);
    }
};

int main() {
    TreePersistentArray pa(5);
    int r1 = pa.update(pa.roots[0], 0, 4, 2, 42);
    pa.roots.push_back(r1);

    assert(pa.query(pa.roots[0], 0, 4, 2) == 0);
    assert(pa.query(pa.roots[1], 0, 4, 2) == 42);
    return 0;
}
