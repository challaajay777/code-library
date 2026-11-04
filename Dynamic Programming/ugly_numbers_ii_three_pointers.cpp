// Algorithm: N-th Ugly Number Three-Pointer DP
// Purpose: Finds the n-th positive integer whose prime factors are limited to 2, 3, and 5.
// Time Complexity: O(N)
// Space Complexity: O(N)
// Preconditions: n >= 1.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

long long nth_ugly_number(int n) {
    std::vector<long long> dp(n);
    dp[0] = 1;
    int p2 = 0, p3 = 0, p5 = 0;

    for (int i = 1; i < n; ++i) {
        long long next2 = dp[p2] * 2;
        long long next3 = dp[p3] * 3;
        long long next5 = dp[p5] * 5;

        long long next_ugly = std::min({next2, next3, next5});
        dp[i] = next_ugly;

        if (next_ugly == next2) p2++;
        if (next_ugly == next3) p3++;
        if (next_ugly == next5) p5++;
    }
    return dp[n - 1];
}

int main() {
    assert(nth_ugly_number(1) == 1);
    assert(nth_ugly_number(10) == 12); // [1, 2, 3, 4, 5, 6, 8, 9, 10, 12]
    return 0;
}
