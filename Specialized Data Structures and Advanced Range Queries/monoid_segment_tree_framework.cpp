// Algorithm: Generic Monoid Segment Tree
// Purpose: Generic C++ template segment tree requiring only associative binary op and identity element.
// Time Complexity: O(log N) query/update
// Space Complexity: O(N)
// Preconditions: Algebraic monoid (S, op, e).

#include <iostream>
#include <vector>
#include <functional>
#include <cassert>

template <typename T>
class MonoidSegTree {
    int n;
    std::vector<T> tree;
    T identity;
    std::function<T(T, T)> op;

public:
    MonoidSegTree(int n, T id, std::function<T(T, T)> operation)
        : n(n), tree(2 * n, id), identity(id), op(operation) {}

    void update(int p, T val) {
        for (tree[p += n] = val; p > 1; p >>= 1) {
            tree[p >> 1] = op(tree[p], tree[p ^ 1]);
        }
    }

    T query(int l, int r) {
        T res_l = identity, res_r = identity;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res_l = op(res_l, tree[l++]);
            if (r & 1) res_r = op(tree[--r], res_r);
        }
        return op(res_l, res_r);
    }
};

int main() {
    MonoidSegTree<int> st(4, 0, [](int a, int b) { return a + b; });
    st.update(0, 10);
    st.update(1, 20);
    assert(st.query(0, 2) == 30);
    return 0;
}
