// Algorithm: Iterative Segment Tree Point Update Range Sum
// Purpose: Fast non-recursive bottom-up segment tree for single point updates and range sum queries.
// Time Complexity: O(log N) update and query, O(N) build
// Space Complexity: O(N)
// Preconditions: Array of numbers.

#include <iostream>
#include <vector>
#include <cassert>

struct IterativeSegTree {
    int n;
    std::vector<long long> tree;

    IterativeSegTree(int n) : n(n), tree(2 * n, 0) {}

    void build(const std::vector<int>& a) {
        for (int i = 0; i < n; ++i) tree[n + i] = a[i];
        for (int i = n - 1; i > 0; --i) tree[i] = tree[i << 1] + tree[i << 1 | 1];
    }

    void update(int p, long long val) {
        for (tree[p += n] = val; p > 1; p >>= 1) {
            tree[p >> 1] = tree[p] + tree[p ^ 1];
        }
    }

    long long query(int l, int r) { // [l, r) half-open
        long long res = 0;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res += tree[l++];
            if (r & 1) res += tree[--r];
        }
        return res;
    }
};

int main() {
    std::vector<int> a = {1, 2, 3, 4, 5};
    IterativeSegTree st(a.size());
    st.build(a);

    assert(st.query(1, 4) == 2 + 3 + 4);
    st.update(2, 10); // replace 3 with 10
    assert(st.query(1, 4) == 2 + 10 + 4);
    return 0;
}
