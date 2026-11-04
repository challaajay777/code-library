// Algorithm: Super Ugly Numbers Multi-Prime DP
// Purpose: Finds the n-th positive integer whose prime factors are all in a given prime list.
// Time Complexity: O(N * K)
// Space Complexity: O(N + K)
// Preconditions: n >= 1, primes is a sorted array of distinct primes.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <climits>

long long nth_super_ugly_number(int n, const std::vector<int>& primes) {
    int k = primes.size();
    std::vector<long long> dp(n);
    dp[0] = 1;
    std::vector<int> ptr(k, 0);

    for (int i = 1; i < n; ++i) {
        long long next_val = LLONG_MAX;
        for (int j = 0; j < k; ++j) {
            next_val = std::min(next_val, dp[ptr[j]] * primes[j]);
        }
        dp[i] = next_val;
        for (int j = 0; j < k; ++j) {
            if (dp[ptr[j]] * primes[j] == next_val) {
                ptr[j]++;
            }
        }
    }
    return dp[n - 1];
}

int main() {
    std::vector<int> primes = {2, 7, 13, 19};
    assert(nth_super_ugly_number(12, primes) == 32);
    return 0;
}
