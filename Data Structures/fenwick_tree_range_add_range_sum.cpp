// Algorithm: Fenwick Tree Range Update and Range Query
// Purpose: Supports range additions [l, r] += v and range sum queries in O(log N) using two BITs.
// Time Complexity: O(log N) update and query
// Space Complexity: O(N)
// Preconditions: 1-indexed bounds.

#include <iostream>
#include <vector>
#include <cassert>

struct FenwickRange {
    int n;
    std::vector<long long> bit1, bit2;

    FenwickRange(int n) : n(n), bit1(n + 1, 0), bit2(n + 1, 0) {}

    void add_internal(std::vector<long long>& b, int i, long long val) {
        for (; i <= n; i += i & -i) b[i] += val;
    }

    void range_add(int l, int r, long long val) {
        add_internal(bit1, l, val);
        add_internal(bit1, r + 1, -val);
        add_internal(bit2, l, val * (l - 1));
        add_internal(bit2, r + 1, -val * r);
    }

    long long query_prefix(int i) {
        long long sum1 = 0, sum2 = 0;
        for (int x = i; x > 0; x -= x & -x) {
            sum1 += bit1[x];
            sum2 += bit2[x];
        }
        return sum1 * i - sum2;
    }

    long long query_range(int l, int r) {
        return query_prefix(r) - query_prefix(l - 1);
    }
};

int main() {
    FenwickRange fr(5);
    fr.range_add(1, 3, 5); // [5, 5, 5, 0, 0]
    fr.range_add(2, 4, 2); // [5, 7, 7, 2, 0]

    assert(fr.query_range(1, 3) == 19);
    assert(fr.query_range(4, 5) == 2);
    return 0;
}
