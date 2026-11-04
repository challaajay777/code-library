// Algorithm: Matchsticks to Square Bitmask DP
// Purpose: Determines whether all matchsticks can be assembled into a perimeter of a square.
// Time Complexity: O(2^N)
// Space Complexity: O(2^N)
// Preconditions: Matchsticks array of positive lengths.

#include <iostream>
#include <vector>
#include <numeric>
#include <cassert>

bool makesquare(const std::vector<int>& matchsticks) {
    int n = matchsticks.size();
    if (n < 4) return false;
    int perimeter = std::accumulate(matchsticks.begin(), matchsticks.end(), 0);
    if (perimeter % 4 != 0) return false;
    int side = perimeter / 4;

    int total_states = 1 << n;
    std::vector<int> dp(total_states, -1);
    dp[0] = 0;

    for (int mask = 0; mask < total_states; ++mask) {
        if (dp[mask] == -1) continue;
        for (int i = 0; i < n; ++i) {
            if (!(mask & (1 << i)) && dp[mask] + matchsticks[i] <= side) {
                dp[mask | (1 << i)] = (dp[mask] + matchsticks[i]) % side;
            }
        }
    }
    return dp[total_states - 1] == 0;
}

int main() {
    assert(makesquare({1, 1, 2, 2, 2}));
    assert(!makesquare({3, 3, 3, 3, 4}));
    return 0;
}
