#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Maximum Subarray Sum After One Operation
// Purpose: Finds the maximum subarray sum when exactly one element in the subarray can be modified (e.g. squared x^2).
// Time Complexity: O(N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Array length >= 1.

class MaxSubarraySumAfterOneOperation {
public:
    // Computes max subarray sum where exactly one chosen element in the subarray is replaced by x*x
    static long long max_sum_with_one_square(const std::vector<long long>& a) {
        assert(!a.empty());
        // dp0: max subarray ending here with 0 operations used
        // dp1: max subarray ending here with 1 operation used
        long long dp0 = a[0];
        long long dp1 = a[0] * a[0];
        long long max_ans = dp1;

        for (size_t i = 1; i < a.size(); ++i) {
            long long x = a[i];
            long long sq = x * x;
            dp1 = std::max({sq, dp0 + sq, dp1 + x});
            dp0 = std::max(x, dp0 + x);
            max_ans = std::max(max_ans, dp1);
        }
        return max_ans;
    }
};

int main() {
    std::vector<long long> a = {2, -1, -4, -3};
    // Squaring -4 gives 16: subarray [-1, (-4)^2, -3] or [(-4)^2] = 16 or [2, -1, 16] = 17
    assert(MaxSubarraySumAfterOneOperation::max_sum_with_one_square(a) == 17);

    std::vector<long long> b = {1, -1, 1};
    assert(MaxSubarraySumAfterOneOperation::max_sum_with_one_square(b) == 3);

    std::cout << "maximum_subarray_sum_after_one_operation tests passed successfully.\n";
    return 0;
}
