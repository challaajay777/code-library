// Algorithm: 2D Segment Tree Point Update and Subgrid Sum
// Purpose: Queries rectangular 2D subgrid sums and updates individual cells in O(log R * log C).
// Time Complexity: O(log R * log C) query and update
// Space Complexity: O(R * C)
// Preconditions: 2D grid of size R x C.

#include <iostream>
#include <vector>
#include <cassert>

struct SegTree2D {
    int R, C;
    std::vector<std::vector<long long>> tree;

    SegTree2D(int r, int c) : R(r), C(c), tree(2 * r, std::vector<long long>(2 * c, 0)) {}

    void update(int r, int c, long long val) {
        r += R;
        int orig_c = c + C;
        tree[r][orig_c] = val;
        for (int c_idx = orig_c; c_idx > 1; c_idx >>= 1) {
            tree[r][c_idx >> 1] = tree[r][c_idx] + tree[r][c_idx ^ 1];
        }
        for (r >>= 1; r > 0; r >>= 1) {
            for (int c_idx = orig_c; c_idx > 0; c_idx >>= 1) {
                tree[r][c_idx] = tree[2 * r][c_idx] + tree[2 * r + 1][c_idx];
            }
        }
    }

    long long query_1d(int r, int c1, int c2) {
        long long sum = 0;
        for (c1 += C, c2 += C; c1 < c2; c1 >>= 1, c2 >>= 1) {
            if (c1 & 1) sum += tree[r][c1++];
            if (c2 & 1) sum += tree[r][--c2];
        }
        return sum;
    }

    long long query(int r1, int c1, int r2, int c2) { // [r1, r2) x [c1, c2)
        long long sum = 0;
        for (r1 += R, r2 += R; r1 < r2; r1 >>= 1, r2 >>= 1) {
            if (r1 & 1) sum += query_1d(r1++, c1, c2);
            if (r2 & 1) sum += query_1d(--r2, c1, c2);
        }
        return sum;
    }
};

int main() {
    SegTree2D st2(3, 3);
    st2.update(0, 0, 1);
    st2.update(0, 1, 2);
    st2.update(1, 0, 3);
    st2.update(1, 1, 4);

    assert(st2.query(0, 0, 2, 2) == 10);
    return 0;
}
