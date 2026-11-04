#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Longest Subarray with Sum Divisible by K
// Purpose: Finds maximum length of a contiguous subarray whose sum is a multiple of K in linear time.
// Time Complexity: O(N) time
// Space Complexity: O(K) auxiliary space
// Preconditions: K >= 1.

class LongestSubarrayDivisibleByK {
public:
    static int max_len(const std::vector<long long>& a, long long k) {
        assert(k > 0);
        std::vector<int> first_idx(k, -2);
        first_idx[0] = -1;

        long long pref = 0;
        int ans = 0;

        for (int i = 0; i < (int)a.size(); ++i) {
            pref = (pref + a[i]) % k;
            if (pref < 0) pref += k;

            if (first_idx[pref] != -2) {
                ans = std::max(ans, i - first_idx[pref]);
            } else {
                first_idx[pref] = i;
            }
        }
        return ans;
    }
};

int main() {
    std::vector<long long> a = {2, 7, 6, 1, 4, 5};
    // Sum = 25. For k=3: max subarray [7, 6, 1, 4] sum=18 len=4
    assert(LongestSubarrayDivisibleByK::max_len(a, 3) == 4);

    std::vector<long long> b = {-2, 2, -5, 12, -11, -1, 7};
    assert(LongestSubarrayDivisibleByK::max_len(b, 3) == 7);

    std::cout << "longest_subarray_divisible_by_k tests passed successfully.\n";
    return 0;
}
