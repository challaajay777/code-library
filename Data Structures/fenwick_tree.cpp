// Algorithm: Fenwick Tree (Binary Indexed Tree)
// Supports: Point update (add), prefix sum query, range sum query
// Indexing: 1-based indexing internally
// Complexity: O(log n) per update and query, O(n) memory
// Preconditions: 1 <= idx <= n

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

template <typename T>
struct FenwickTree {
    int n;
    vector<T> tree;

    explicit FenwickTree(int n) : n(n), tree(n + 1, 0) {}

    // Adds val to element at 1-based index idx
    void add(int idx, T val) {
        assert(1 <= idx && idx <= n);
        for (; idx <= n; idx += idx & -idx) {
            tree[idx] += val;
        }
    }

    // Returns prefix sum of elements in [1, idx]
    T query(int idx) const {
        assert(0 <= idx && idx <= n);
        T sum = 0;
        for (; idx > 0; idx -= idx & -idx) {
            sum += tree[idx];
        }
        return sum;
    }

    // Returns sum of elements in [l, r] inclusive
    T query(int l, int r) const {
        if (l > r) return 0;
        assert(1 <= l && r <= n);
        return query(r) - query(l - 1);
    }
};
