// Algorithm: Sum Over Subsets (SOS DP / Yates' Algorithm)
// Supports: Computing sum/aggregation over all submasks or supermasks
// Indexing: 0-based bit positions [0, N - 1], mask range [0, 2^N - 1]
// Complexity: O(N * 2^N) time, O(2^N) memory
// Preconditions: 1 <= N <= 24 (due to 2^N memory constraints)

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

template <typename T>
struct SOS_DP {
    int N; // number of bits
    int total_masks;

    explicit SOS_DP(int bits) : N(bits), total_masks(1 << bits) {
        assert(1 <= bits && bits <= 24);
    }

    // Computes F[mask] = sum_{submask in mask} A[submask] in-place
    void compute_submask_sums(vector<T>& dp) const {
        assert((int)dp.size() == total_masks);
        for (int i = 0; i < N; ++i) {
            for (int mask = 0; mask < total_masks; ++mask) {
                if (mask & (1 << i)) {
                    dp[mask] += dp[mask ^ (1 << i)];
                }
            }
        }
    }

    // Computes F[mask] = sum_{supermask contains mask} A[supermask] in-place
    void compute_supermask_sums(vector<T>& dp) const {
        assert((int)dp.size() == total_masks);
        for (int i = 0; i < N; ++i) {
            for (int mask = total_masks - 1; mask >= 0; --mask) {
                if (!(mask & (1 << i))) {
                    dp[mask] += dp[mask | (1 << i)];
                }
            }
        }
    }
};
