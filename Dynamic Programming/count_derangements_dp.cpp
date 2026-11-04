// Algorithm: Count Derangements DP
// Purpose: Calculates number of permutations of N elements where no element appears in its original position.
// Time Complexity: O(N)
// Space Complexity: O(1)
// Preconditions: N >= 0.

#include <iostream>
#include <cassert>

long long count_derangements(int n) {
    static const int MOD = 1000000007;
    if (n <= 1) return 0;
    if (n == 2) return 1;

    long long prev2 = 0; // D(1)
    long long prev1 = 1; // D(2)

    for (int i = 3; i <= n; ++i) {
        long long cur = (1LL * (i - 1) * (prev1 + prev2)) % MOD;
        prev2 = prev1;
        prev1 = cur;
    }
    return prev1;
}

int main() {
    assert(count_derangements(1) == 0);
    assert(count_derangements(2) == 1);
    assert(count_derangements(3) == 2);
    assert(count_derangements(4) == 9);
    return 0;
}
