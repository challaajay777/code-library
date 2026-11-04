#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Sum Over Subsets (SOS) Dynamic Programming
// Purpose: Calculates F[mask] = sum_{sub subseteq mask} A[sub] for all 2^N masks in O(N * 2^N) time.
// Time Complexity: O(N * 2^N) time
// Space Complexity: O(2^N) space
// Preconditions: 0 <= N <= 24.

class SumOverSubsets {
public:
    static std::vector<long long> compute_sos(int n, const std::vector<long long>& a) {
        int total = 1 << n;
        assert((int)a.size() == total);
        std::vector<long long> dp = a;

        for (int i = 0; i < n; ++i) {
            for (int mask = 0; mask < total; ++mask) {
                if (mask & (1 << i)) {
                    dp[mask] += dp[mask ^ (1 << i)];
                }
            }
        }
        return dp;
    }
};

int main() {
    // n = 2: masks 0, 1, 2, 3
    std::vector<long long> a = {1, 2, 4, 8};
    auto f = SumOverSubsets::compute_sos(2, a);
    // f[0] = a[0] = 1
    // f[1] = a[0] + a[1] = 3
    // f[2] = a[0] + a[2] = 5
    // f[3] = a[0] + a[1] + a[2] + a[3] = 15
    assert(f[0] == 1);
    assert(f[1] == 3);
    assert(f[2] == 5);
    assert(f[3] == 15);

    std::cout << "sos_dp_submask_sums tests passed successfully.\n";
    return 0;
}
