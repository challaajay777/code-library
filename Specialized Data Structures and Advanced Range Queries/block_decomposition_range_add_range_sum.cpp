// Algorithm: Sqrt Block Decomposition Range Add Range Sum
// Purpose: Supports range addition [l, r] += v and range sum in O(sqrt N) using block tags.
// Time Complexity: O(sqrt N) update/query
// Space Complexity: O(N)
// Preconditions: Array of integers.

#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>

struct SqrtBlockAddSum {
    int n, bs;
    std::vector<long long> a, block_sum, lazy;

    SqrtBlockAddSum(int n) : n(n), a(n, 0) {
        bs = std::max(1, (int)std::sqrt(n));
        int num_b = (n + bs - 1) / bs;
        block_sum.assign(num_b, 0);
        lazy.assign(num_b, 0);
    }

    void range_add(int l, int r, long long val) {
        int bl = l / bs, br = r / bs;
        if (bl == br) {
            for (int i = l; i <= r; ++i) { a[i] += val; block_sum[bl] += val; }
        } else {
            for (int i = l; i < (bl + 1) * bs; ++i) { a[i] += val; block_sum[bl] += val; }
            for (int b = bl + 1; b < br; ++b) { lazy[b] += val; }
            for (int i = br * bs; i <= r; ++i) { a[i] += val; block_sum[br] += val; }
        }
    }

    long long query(int l, int r) {
        int bl = l / bs, br = r / bs;
        long long sum = 0;
        if (bl == br) {
            for (int i = l; i <= r; ++i) sum += a[i] + lazy[bl];
        } else {
            for (int i = l; i < (bl + 1) * bs; ++i) sum += a[i] + lazy[bl];
            for (int b = bl + 1; b < br; ++b) sum += block_sum[b] + lazy[b] * bs;
            for (int i = br * bs; i <= r; ++i) sum += a[i] + lazy[br];
        }
        return sum;
    }
};

int main() {
    SqrtBlockAddSum sba(5);
    sba.range_add(0, 2, 10);
    sba.range_add(1, 4, 5);
    assert(sba.query(1, 2) == 30);
    return 0;
}
