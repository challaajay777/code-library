// Algorithm: Lazy Segment Tree (Range Assignment, Range Min)
// Supports: Range assignment (assign x to [l, r]), range minimum queries
// Indexing: 0-based indices [l, r]
// Complexity: O(n) build, O(log n) per assignment and query, O(n) memory
// Preconditions: Ranges satisfy 0 <= l <= r < n

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

template <typename T>
struct LazySegmentTreeAssignMin {
    static constexpr T INF_VAL = numeric_limits<T>::max();
    static constexpr T NO_LAZY = numeric_limits<T>::min();

    int n;
    vector<T> tree, lazy;

    explicit LazySegmentTreeAssignMin(int n) : n(n), tree(4 * n, INF_VAL), lazy(4 * n, NO_LAZY) {}

    explicit LazySegmentTreeAssignMin(const vector<T>& a) : n((int)a.size()), tree(4 * n, INF_VAL), lazy(4 * n, NO_LAZY) {
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
        tree[node] = min(tree[2 * node], tree[2 * node + 1]);
    }

    void push(int node) {
        if (lazy[node] == NO_LAZY) return;
        T val = lazy[node];
        tree[2 * node] = val;
        lazy[2 * node] = val;
        tree[2 * node + 1] = val;
        lazy[2 * node + 1] = val;
        lazy[node] = NO_LAZY;
    }

    void update(int node, int start, int end, int l, int r, T val) {
        if (r < start || end < l) return;
        if (l <= start && end <= r) {
            tree[node] = val;
            lazy[node] = val;
            return;
        }
        push(node);
        int mid = start + (end - start) / 2;
        update(2 * node, start, mid, l, r, val);
        update(2 * node + 1, mid + 1, end, l, r, val);
        tree[node] = min(tree[2 * node], tree[2 * node + 1]);
    }

    T query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) return INF_VAL;
        if (l <= start && end <= r) return tree[node];
        push(node);
        int mid = start + (end - start) / 2;
        return min(query(2 * node, start, mid, l, r),
                   query(2 * node + 1, mid + 1, end, l, r));
    }

public:
    void assign_range(int l, int r, T val) {
        if (l > r) return;
        assert(0 <= l && r < n);
        update(1, 0, n - 1, l, r, val);
    }

    T query_min(int l, int r) {
        if (l > r) return INF_VAL;
        assert(0 <= l && r < n);
        return query(1, 0, n - 1, l, r);
    }
};
