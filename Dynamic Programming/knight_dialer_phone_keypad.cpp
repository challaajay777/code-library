// Algorithm: Knight Dialer Distinct Numbers DP
// Purpose: Calculates number of distinct phone numbers of length n dialed by valid chess knight moves.
// Time Complexity: O(N)
// Space Complexity: O(1)
// Preconditions: n >= 1.

#include <iostream>
#include <vector>
#include <cassert>

int knight_dialer(int n) {
    static const int MOD = 1000000007;
    std::vector<std::vector<int>> moves = {
        {4, 6},    // 0
        {6, 8},    // 1
        {7, 9},    // 2
        {4, 8},    // 3
        {0, 3, 9}, // 4
        {},        // 5
        {0, 1, 7}, // 6
        {2, 6},    // 7
        {1, 3},    // 8
        {2, 4}     // 9
    };

    std::vector<long long> dp(10, 1);

    for (int step = 2; step <= n; ++step) {
        std::vector<long long> next_dp(10, 0);
        for (int digit = 0; digit < 10; ++digit) {
            for (int neighbor : moves[digit]) {
                next_dp[neighbor] = (next_dp[neighbor] + dp[digit]) % MOD;
            }
        }
        dp = next_dp;
    }

    long long sum = 0;
    for (long long x : dp) sum = (sum + x) % MOD;
    return sum;
}

int main() {
    assert(knight_dialer(1) == 10);
    assert(knight_dialer(2) == 20);
    assert(knight_dialer(3) == 46);
    return 0;
}
