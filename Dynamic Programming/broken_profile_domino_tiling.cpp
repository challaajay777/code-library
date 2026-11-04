// Algorithm: Broken Profile (Plug) DP for Domino Tiling
// Purpose: Calculates the exact number of ways to tile an N x M grid with 2x1 dominoes.
// Time Complexity: O(N * M * 2^M)
// Space Complexity: O(2^M)
// Preconditions: 1 <= N, M <= 16 with N * M even.

#include <iostream>
#include <vector>
#include <cassert>

long long domino_tiling_ways(int n, int m) {
    if (m > n) std::swap(n, m);
    if ((n * m) % 2 != 0) return 0;

    int mask_limit = 1 << m;
    std::vector<long long> dp(mask_limit, 0);
    dp[0] = 1;

    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            std::vector<long long> next_dp(mask_limit, 0);
            for (int mask = 0; mask < mask_limit; ++mask) {
                if (dp[mask] == 0) continue;
                if (mask & (1 << c)) {
                    // Current cell is already occupied by domino from cell above
                    next_dp[mask ^ (1 << c)] += dp[mask];
                } else {
                    // Try placing vertical domino (covers (r, c) and (r+1, c))
                    if (r + 1 < n) {
                        next_dp[mask | (1 << c)] += dp[mask];
                    }
                    // Try placing horizontal domino (covers (r, c) and (r, c+1))
                    if (c + 1 < m && !(mask & (1 << (c + 1)))) {
                        next_dp[mask | (1 << (c + 1))] += dp[mask];
                    }
                }
            }
            dp = next_dp;
        }
    }
    return dp[0];
}

int main() {
    assert(domino_tiling_ways(2, 2) == 2);
    assert(domino_tiling_ways(2, 3) == 3);
    assert(domino_tiling_ways(4, 4) == 36);
    return 0;
}
