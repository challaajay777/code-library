// Algorithm: Paint Fence DP (At Most Two Adjacent Same)
// Purpose: Calculates number of ways to paint fence of n posts with k colors with at most two consecutive posts same.
// Time Complexity: O(N)
// Space Complexity: O(1)
// Preconditions: n >= 1, k >= 1.

#include <iostream>
#include <cassert>

long long num_ways_paint_fence(int n, int k) {
    if (n == 0 || k == 0) return 0;
    if (n == 1) return k;
    long long same = k;
    long long diff = 1LL * k * (k - 1);

    for (int i = 3; i <= n; ++i) {
        long long prev_diff = diff;
        diff = (same + diff) * (k - 1);
        same = prev_diff;
    }
    return same + diff;
}

int main() {
    assert(num_ways_paint_fence(3, 2) == 6);
    return 0;
}
