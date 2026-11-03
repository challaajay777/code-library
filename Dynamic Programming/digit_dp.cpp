// Algorithm: Digit DP
// Supports: Counting valid numbers in range [0, N] under digit constraints via memoized DFS
// Indexing: 0-based digit positions from most significant to least
// Complexity: O(len(N) * states) time, O(len(N) * states) memory
// Preconditions: Range bounds >= 0

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

struct DigitDP {
    string S;
    int n;
    // DP state: [index][sum_digits][tight][leading_zero]
    long long memo[20][180][2][2];

    long long dfs(int idx, int sum, bool tight, bool leading_zero) {
        if (idx == n) {
            return sum; // returns total sum of digits, or condition check
        }
        if (memo[idx][sum][tight][leading_zero] != -1) {
            return memo[idx][sum][tight][leading_zero];
        }

        int limit = tight ? (S[idx] - '0') : 9;
        long long ans = 0;

        for (int d = 0; d <= limit; ++d) {
            bool next_tight = tight && (d == limit);
            bool next_lz = leading_zero && (d == 0);
            int next_sum = sum + (next_lz ? 0 : d);
            ans += dfs(idx + 1, next_sum, next_tight, next_lz);
        }

        return memo[idx][sum][tight][leading_zero] = ans;
    }

    // Computes sum of digits of all numbers in [0, val]
    long long solve_up_to(long long val) {
        if (val < 0) return 0;
        S = to_string(val);
        n = (int)S.size();
        memset(memo, -1, sizeof(memo));
        return dfs(0, 0, true, true);
    }

    // Computes sum of digits in range [L, R]
    long long count_range(long long L, long long R) {
        assert(0 <= L && L <= R);
        return solve_up_to(R) - solve_up_to(L - 1);
    }
};
