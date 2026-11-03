// Algorithm: Segment Tree (Point Update, Range Query)
// Supports: Point update, associative range query (min, sum, gcd, etc.)
// Indexing: 0-based input array indices
// Complexity: O(n) construction, O(log n) per update and range query, O(n) memory
// Preconditions: Monoid structure (associative combine function, identity element)

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

template <typename T, typename Combine = plus<T>>
struct SegmentTree {
    int n;
    T identity;
    Combine combine;
    vector<T> tree;

    SegmentTree(int n, T identity, Combine combine = Combine())
        : n(n), identity(identity), combine(combine), tree(4 * n, identity) {}

    SegmentTree(const vector<T>& a, T identity, Combine combine = Combine())
        : n((int)a.size()), identity(identity), combine(combine), tree(4 * n, identity) {
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
        tree[node] = combine(tree[2 * node], tree[2 * node + 1]);
    }

    void update(int node, int start, int end, int idx, T val) {
        if (start == end) {
            tree[node] = val;
            return;
        }
        int mid = start + (end - start) / 2;
        if (idx <= mid) {
            update(2 * node, start, mid, idx, val);
        } else {
            update(2 * node + 1, mid + 1, end, idx, val);
        }
        tree[node] = combine(tree[2 * node], tree[2 * node + 1]);
    }

    T query(int node, int start, int end, int l, int r) const {
        if (r < start || end < l) return identity;
        if (l <= start && end <= r) return tree[node];
        int mid = start + (end - start) / 2;
        return combine(query(2 * node, start, mid, l, r),
                       query(2 * node + 1, mid + 1, end, l, r));
    }

public:
    void set(int idx, T val) {
        assert(0 <= idx && idx < n);
        update(1, 0, n - 1, idx, val);
    }

    T query(int l, int r) const {
        if (l > r) return identity;
        assert(0 <= l && r < n);
        return query(1, 0, n - 1, l, r);
    }
};
