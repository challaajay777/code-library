// Algorithm: Divide and Conquer DP Optimization
// Supports: Accelerating 2D DP recurrences dp[i][j] = min_{k < j} (dp[i-1][k] + cost(k, j))
// Indexing: 1-based indexing for partitions and elements
// Complexity: O(k * n log n) time, O(k * n) space (or O(n) space rolling)
// Preconditions: Monotonicity of optimal split points: opt[i][j] <= opt[i][j+1]

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

template <typename CostFunc>
struct DCOptimizationDP {
    static constexpr long long INF_VAL = 1e18;

    int n, K;
    CostFunc cost;
    vector<vector<long long>> dp;

    DCOptimizationDP(int n, int K, CostFunc cost)
        : n(n), K(K), cost(cost), dp(K + 1, vector<long long>(n + 1, INF_VAL)) {}

private:
    void compute(int i, int l, int r, int opt_l, int opt_r) {
        if (l > r) return;
        int mid = l + (r - l) / 2;
        pair<long long, int> best = {INF_VAL, -1};

        for (int k = opt_l; k <= min(mid, opt_r); ++k) {
            long long cur = dp[i - 1][k] + cost(k, mid);
            if (cur < best.first) {
                best = {cur, k};
            }
        }

        dp[i][mid] = best.first;
        int opt = best.second;

        compute(i, l, mid - 1, opt_l, opt);
        compute(i, mid + 1, r, opt, opt_r);
    }

public:
    long long solve() {
        dp[0][0] = 0;
        for (int i = 1; i <= K; ++i) {
            compute(i, 1, n, 0, n - 1);
        }
        return dp[K][n];
    }
};
