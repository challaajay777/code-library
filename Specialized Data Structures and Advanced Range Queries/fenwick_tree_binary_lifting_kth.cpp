// Algorithm: Fenwick Tree Binary Lifting K-th Element
// Purpose: Finds smallest index with prefix sum >= K using internal power-of-two jumps in O(log N).
// Time Complexity: O(log N)
// Space Complexity: O(N)
// Preconditions: Non-negative array elements.

#include <iostream>
#include <vector>
#include <cassert>

struct FenwickLifting {
    int n, LOGN;
    std::vector<int> tree;

    FenwickLifting(int n) : n(n), tree(n + 1, 0) {
        LOGN = 1;
        while ((1 << LOGN) <= n) LOGN++;
    }

    void add(int i, int val) {
        for (; i <= n; i += i & -i) tree[i] += val;
    }

    int lower_bound(int k) {
        int idx = 0;
        for (int i = 1 << (LOGN - 1); i > 0; i >>= 1) {
            if (idx + i <= n && tree[idx + i] < k) {
                idx += i;
                k -= tree[idx];
            }
        }
        return idx + 1;
    }
};

int main() {
    FenwickLifting fl(5);
    fl.add(1, 2);
    fl.add(2, 3);
    fl.add(3, 5);

    // Prefix sums: [2, 5, 10, 10, 10]. First index with sum >= 5 is 2
    assert(fl.lower_bound(5) == 2);
    assert(fl.lower_bound(6) == 3);
    return 0;
}
