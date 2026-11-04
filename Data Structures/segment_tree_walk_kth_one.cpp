// Algorithm: Segment Tree Walk for K-th One
// Purpose: Finds the position of the k-th '1' in a binary array in O(log N) by walking tree branches.
// Time Complexity: O(log N)
// Space Complexity: O(N)
// Preconditions: 1 <= k <= total ones.

#include <iostream>
#include <vector>
#include <cassert>

struct SegTreeWalk {
    int n;
    std::vector<int> tree;

    SegTreeWalk(int n) : n(n), tree(4 * n, 0) {}

    void update(int node, int l, int r, int idx, int val) {
        if (l == r) {
            tree[node] = val;
            return;
        }
        int mid = (l + r) / 2;
        if (idx <= mid) update(2 * node, l, mid, idx, val);
        else update(2 * node + 1, mid + 1, r, idx, val);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    int find_kth(int node, int l, int r, int k) {
        if (l == r) return l;
        int mid = (l + r) / 2;
        if (tree[2 * node] >= k) return find_kth(2 * node, l, mid, k);
        return find_kth(2 * node + 1, mid + 1, r, k - tree[2 * node]);
    }
};

int main() {
    SegTreeWalk st(5);
    st.update(1, 0, 4, 1, 1);
    st.update(1, 0, 4, 3, 1);
    st.update(1, 0, 4, 4, 1);

    assert(st.find_kth(1, 0, 4, 1) == 1);
    assert(st.find_kth(1, 0, 4, 2) == 3);
    assert(st.find_kth(1, 0, 4, 3) == 4);
    return 0;
}
