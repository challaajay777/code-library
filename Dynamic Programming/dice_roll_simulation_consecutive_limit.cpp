// Algorithm: Dice Roll Simulation with Consecutive Face Limits DP
// Purpose: Counts distinct sequences of n dice rolls where face i cannot appear more than rollMax[i] consecutive times.
// Time Complexity: O(N * 6 * MaxRoll)
// Space Complexity: O(6 * MaxRoll)
// Preconditions: n >= 1, rollMax has length 6.

#include <iostream>
#include <vector>
#include <cassert>

int die_simulator(int n, const std::vector<int>& rollMax) {
    static const int MOD = 1000000007;
    // dp[face][consecutive_count]
    std::vector<std::vector<int>> dp(6, std::vector<int>(16, 0));
    for (int f = 0; f < 6; ++f) dp[f][1] = 1;

    for (int step = 2; step <= n; ++step) {
        std::vector<std::vector<int>> next_dp(6, std::vector<int>(16, 0));
        for (int f = 0; f < 6; ++f) {
            for (int prev_f = 0; prev_f < 6; ++prev_f) {
                if (f != prev_f) {
                    for (int k = 1; k <= rollMax[prev_f]; ++k) {
                        next_dp[f][1] = (next_dp[f][1] + dp[prev_f][k]) % MOD;
                    }
                } else {
                    for (int k = 1; k < rollMax[f]; ++k) {
                        next_dp[f][k + 1] = (next_dp[f][k + 1] + dp[f][k]) % MOD;
                    }
                }
            }
        }
        dp = next_dp;
    }

    long long total = 0;
    for (int f = 0; f < 6; ++f) {
        for (int k = 1; k <= rollMax[f]; ++k) {
            total = (total + dp[f][k]) % MOD;
        }
    }
    return total;
}

int main() {
    std::vector<int> rollMax = {1, 1, 2, 2, 2, 3};
    assert(die_simulator(2, rollMax) == 34); // 36 - 2 invalid ("11", "22")
    return 0;
}
