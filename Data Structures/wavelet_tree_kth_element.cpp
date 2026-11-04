// Algorithm: Wavelet Tree Range K-th Element
// Purpose: Queries the k-th smallest element in subarray [L, R] in O(log(MaxVal)) time without sorting.
// Time Complexity: O(log(MaxVal)) per query, O(N log(MaxVal)) build
// Space Complexity: O(N log(MaxVal))
// Preconditions: 1-indexed range [L, R], 1 <= k <= R - L + 1.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

struct WaveletTree {
    int lo, hi;
    WaveletTree *left = nullptr, *right = nullptr;
    std::vector<int> b; // b[i] = count of elements mapped to left child in [0..i-1]

    WaveletTree(std::vector<int>::iterator from, std::vector<int>::iterator to, int x, int y) {
        lo = x; hi = y;
        if (lo == hi || from >= to) return;
        int mid = lo + (hi - lo) / 2;
        b.reserve(to - from + 1);
        b.push_back(0);
        for (auto it = from; it != to; ++it) {
            b.push_back(b.back() + (*it <= mid));
        }
        auto pivot = std::stable_partition(from, to, [mid](int v) { return v <= mid; });
        left = new WaveletTree(from, pivot, lo, mid);
        right = new WaveletTree(pivot, to, mid + 1, hi);
    }

    int kth(int l, int r, int k) {
        if (l > r) return 0;
        if (lo == hi) return lo;
        int in_left = b[r] - b[l - 1];
        if (k <= in_left) return left->kth(b[l - 1] + 1, b[r], k);
        return right->kth(l - b[l - 1], r - b[r], k - in_left);
    }
};

int main() {
    std::vector<int> a = {3, 1, 4, 1, 5, 9, 2};
    std::vector<int> copy_a = a;
    WaveletTree wt(copy_a.begin(), copy_a.end(), 1, 10);

    // In 1-indexed range [1, 5] {3, 1, 4, 1, 5}: 2nd smallest is 1
    assert(wt.kth(1, 5, 2) == 1);
    assert(wt.kth(1, 5, 4) == 4);
    return 0;
}
