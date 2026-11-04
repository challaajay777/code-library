// Algorithm: Segment Tree with Combined Lazy Mul and Add
// Purpose: Supports range multiplication [l, r] *= mul, range addition [l, r] += add, and range sums modulo M.
// Time Complexity: O(log N) update/query
// Space Complexity: O(N)
// Preconditions: Non-negative modulo M.

#include <iostream>
#include <vector>
#include <cassert>

struct SegTreeAffine {
    static const int MOD = 1000000007;
    int n;
    std::vector<long long> tree, lazy_mul, lazy_add;

    SegTreeAffine(int n) : n(n), tree(4 * n, 0), lazy_mul(4 * n, 1), lazy_add(4 * n, 0) {}

    void apply(int node, int l, int r, long long mul, long long add) {
        tree[node] = (tree[node] * mul + add * (r - l + 1)) % MOD;
        lazy_mul[node] = (lazy_mul[node] * mul) % MOD;
        lazy_add[node] = (lazy_add[node] * mul + add) % MOD;
    }

    void push_down(int node, int l, int r) {
        int mid = (l + r) / 2;
        apply(2 * node, l, mid, lazy_mul[node], lazy_add[node]);
        apply(2 * node + 1, mid + 1, r, lazy_mul[node], lazy_add[node]);
        lazy_mul[node] = 1;
        lazy_add[node] = 0;
    }

    void update_mul(int node, int l, int r, int ql, int qr, long long val) {
        if (ql <= l && r <= qr) { apply(node, l, r, val, 0); return; }
        push_down(node, l, r);
        int mid = (l + r) / 2;
        if (ql <= mid) update_mul(2 * node, l, mid, ql, qr, val);
        if (qr > mid) update_mul(2 * node + 1, mid + 1, r, ql, qr, val);
        tree[node] = (tree[2 * node] + tree[2 * node + 1]) % MOD;
    }

    void update_add(int node, int l, int r, int ql, int qr, long long val) {
        if (ql <= l && r <= qr) { apply(node, l, r, 1, val); return; }
        push_down(node, l, r);
        int mid = (l + r) / 2;
        if (ql <= mid) update_add(2 * node, l, mid, ql, qr, val);
        if (qr > mid) update_add(2 * node + 1, mid + 1, r, ql, qr, val);
        tree[node] = (tree[2 * node] + tree[2 * node + 1]) % MOD;
    }

    long long query(int node, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return tree[node];
        push_down(node, l, r);
        int mid = (l + r) / 2;
        long long sum = 0;
        if (ql <= mid) sum = (sum + query(2 * node, l, mid, ql, qr)) % MOD;
        if (qr > mid) sum = (sum + query(2 * node + 1, mid + 1, r, ql, qr)) % MOD;
        return sum;
    }
};

int main() {
    SegTreeAffine sta(4);
    sta.update_add(1, 0, 3, 0, 3, 2); // [2, 2, 2, 2]
    sta.update_mul(1, 0, 3, 1, 2, 3); // [2, 6, 6, 2]
    assert(sta.query(1, 0, 3, 0, 3) == 16);
    return 0;
}
