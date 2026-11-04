// Algorithm: Segment Tree Longest Consecutive Ones
// Purpose: Finds length of longest contiguous subarray of 1s in range [L, R] with point flips in O(log N).
// Time Complexity: O(log N)
// Space Complexity: O(N)
// Preconditions: Binary array.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

struct SegNode {
    int pref, suff, max_len, len;
};

struct SegConsecutiveOnes {
    int n;
    std::vector<SegNode> tree;

    SegConsecutiveOnes(int n) : n(n), tree(4 * n) {}

    SegNode merge(const SegNode& l, const SegNode& r) {
        SegNode res;
        res.len = l.len + r.len;
        res.pref = (l.pref == l.len) ? l.len + r.pref : l.pref;
        res.suff = (r.suff == r.len) ? r.len + l.suff : r.suff;
        res.max_len = std::max({l.max_len, r.max_len, l.suff + r.pref});
        return res;
    }

    void update(int node, int l, int r, int idx, int val) {
        if (l == r) {
            tree[node] = {val, val, val, 1};
            return;
        }
        int mid = (l + r) / 2;
        if (idx <= mid) update(2 * node, l, mid, idx, val);
        else update(2 * node + 1, mid + 1, r, idx, val);
        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }
};

int main() {
    SegConsecutiveOnes sco(5);
    sco.update(1, 0, 4, 0, 1);
    sco.update(1, 0, 4, 1, 1);
    sco.update(1, 0, 4, 2, 0);
    sco.update(1, 0, 4, 3, 1);
    sco.update(1, 0, 4, 4, 1);

    assert(sco.tree[1].max_len == 2);
    sco.update(1, 0, 4, 2, 1); // array becomes all 1s
    assert(sco.tree[1].max_len == 5);
    return 0;
}
