// Algorithm: Fenwick Tree with Range Add and Range Sum
// Supports: Range add, range sum query via dual binary indexed trees
// Indexing: 1-based indexing
// Complexity: O(log n) per range update and query, O(n) memory
// Preconditions: 1 <= l <= r <= n

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

template <typename T>
struct FenwickTreeRangeAdd {
    int n;
    vector<T> bit1, bit2;

    explicit FenwickTreeRangeAdd(int n) : n(n), bit1(n + 1, 0), bit2(n + 1, 0) {}

private:
    void internal_add(vector<T>& b, int idx, T val) {
        for (; idx <= n; idx += idx & -idx) {
            b[idx] += val;
        }
    }

    T internal_query(const vector<T>& b, int idx) const {
        T sum = 0;
        for (; idx > 0; idx -= idx & -idx) {
            sum += b[idx];
        }
        return sum;
    }

    T prefix_sum(int idx) const {
        return internal_query(bit1, idx) * idx - internal_query(bit2, idx);
    }

public:
    // Add val to all elements in [l, r] inclusive
    void add_range(int l, int r, T val) {
        assert(1 <= l && l <= r && r <= n);
        internal_add(bit1, l, val);
        internal_add(bit1, r + 1, -val);
        internal_add(bit2, l, val * (l - 1));
        internal_add(bit2, r + 1, -val * r);
    }

    // Query sum in [l, r] inclusive
    T query_range(int l, int r) const {
        if (l > r) return 0;
        assert(1 <= l && r <= n);
        return prefix_sum(r) - prefix_sum(l - 1);
    }
};
