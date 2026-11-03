// Algorithm: Lazy Segment Tree (Range Add, Range Sum)
// Supports: Range addition updates, range sum queries with lazy propagation
// Indexing: 0-based indices [l, r]
// Complexity: O(n) build, O(log n) per range update and query, O(n) memory
// Preconditions: Ranges satisfy 0 <= l <= r < n

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

template <typename T>
struct LazySegmentTree {
    int n;
    vector<T> tree, lazy;

    explicit LazySegmentTree(int n) : n(n), tree(4 * n, 0), lazy(4 * n, 0) {}

    explicit LazySegmentTree(const vector<T>& a) : n((int)a.size()), tree(4 * n, 0), lazy(4 * n, 0) {
        if (n > 0) build(1, 0, n - 1, a);
    }

private:
    void build(int node, int start, int end, const vector<T>& a) {
        if (start == end) {
            tree[node] = a[start];
            return;
        }
        int mid = start + (end - start) / 2;
        build(2 * node, start, mid, a);
        build(2 * node + 1, mid + 1, end, a);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    void push(int node, int start, int end) {
        if (lazy[node] == 0) return;
        int mid = start + (end - start) / 2;
        // Apply to left child
        tree[2 * node] += lazy[node] * (mid - start + 1);
        lazy[2 * node] += lazy[node];
        // Apply to right child
        tree[2 * node + 1] += lazy[node] * (end - mid);
        lazy[2 * node + 1] += lazy[node];
        lazy[node] = 0;
    }

    void update(int node, int start, int end, int l, int r, T val) {
        if (r < start || end < l) return;
        if (l <= start && end <= r) {
            tree[node] += val * (end - start + 1);
            lazy[node] += val;
            return;
        }
        push(node, start, end);
        int mid = start + (end - start) / 2;
        update(2 * node, start, mid, l, r, val);
        update(2 * node + 1, mid + 1, end, l, r, val);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    T query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) return 0;
        if (l <= start && end <= r) return tree[node];
        push(node, start, end);
        int mid = start + (end - start) / 2;
        return query(2 * node, start, mid, l, r) +
               query(2 * node + 1, mid + 1, end, l, r);
    }

public:
    void add_range(int l, int r, T val) {
        if (l > r) return;
        assert(0 <= l && r < n);
        update(1, 0, n - 1, l, r, val);
    }

    T query_range(int l, int r) {
        if (l > r) return 0;
        assert(0 <= l && r < n);
        return query(1, 0, n - 1, l, r);
    }
};
