// Algorithm: CDQ Divide and Conquer (3D Partial Order)
// Purpose: Counts for each 3D point (x, y, z) how many points are dominated (xi <= xj, yi <= yj, zi <= zj).
// Time Complexity: O(N log^2 N)
// Space Complexity: O(N)
// Preconditions: 3D points.

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

struct Element3D {
    int a, b, c, id, count, ans;
};

struct FenwickCDQ {
    int n;
    std::vector<int> tree;
    FenwickCDQ(int n) : n(n), tree(n + 1, 0) {}
    void add(int i, int delta) {
        for (; i <= n; i += i & -i) tree[i] += delta;
    }
    int query(int i) {
        int s = 0;
        for (; i > 0; i -= i & -i) s += tree[i];
        return s;
    }
};

void cdq(int l, int r, std::vector<Element3D>& arr, FenwickCDQ& bit) {
    if (l >= r) return;
    int mid = (l + r) / 2;
    cdq(l, mid, arr, bit);
    cdq(mid + 1, r, arr, bit);

    std::vector<Element3D> left(arr.begin() + l, arr.begin() + mid + 1);
    std::vector<Element3D> right(arr.begin() + mid + 1, arr.begin() + r + 1);

    std::sort(left.begin(), left.end(), [](const Element3D& x, const Element3D& y) { return x.b < y.b; });
    std::sort(right.begin(), right.end(), [](const Element3D& x, const Element3D& y) { return x.b < y.b; });

    size_t i = 0;
    for (auto& item : right) {
        while (i < left.size() && left[i].b <= item.b) {
            bit.add(left[i].c, left[i].count);
            i++;
        }
        item.ans += bit.query(item.c);
    }
    for (size_t k = 0; k < i; ++k) {
        bit.add(left[k].c, -left[k].count);
    }
}

int main() {
    std::vector<Element3D> pts = {
        {1, 1, 1, 0, 1, 0},
        {2, 2, 2, 1, 1, 0},
        {3, 3, 3, 2, 1, 0}
    };
    FenwickCDQ bit(10);
    cdq(0, 2, pts, bit);
    assert(pts[2].ans == 2); // dominated by pt 0 and pt 1
    return 0;
}
