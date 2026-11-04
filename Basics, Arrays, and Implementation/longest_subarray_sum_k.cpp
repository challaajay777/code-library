#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cassert>

// Algorithm: Longest Subarray with Sum Equal to K
// Purpose: Finds the maximum length of a contiguous subarray that sums to K (handles positive, negative, and zero values).
// Time Complexity: O(N) time with hash table
// Space Complexity: O(N) space
// Preconditions: 64-bit integer sum calculations.

class LongestSubarraySumK {
public:
    static int max_length(const std::vector<long long>& a, long long k) {
        std::unordered_map<long long, int> first_idx;
        first_idx[0] = -1;

        long long pref = 0;
        int max_len = 0;

        for (int i = 0; i < (int)a.size(); ++i) {
            pref += a[i];
            long long need = pref - k;
            auto it = first_idx.find(need);
            if (it != first_idx.end()) {
                max_len = std::max(max_len, i - it->second);
            }
            if (first_idx.find(pref) == first_idx.end()) {
                first_idx[pref] = i;
            }
        }
        return max_len;
    }
};

int main() {
    std::vector<long long> a = {10, 5, 2, 7, 1, 9};
    // Subarray with sum 15: [5, 2, 7, 1] len 4
    assert(LongestSubarraySumK::max_length(a, 15) == 4);

    std::vector<long long> b = {-1, 2, 3};
    assert(LongestSubarraySumK::max_length(b, 6) == 0);

    std::vector<long long> c = {-5, 8, -14, 2, 4, 12};
    // sum -5: [-5] len 1
    assert(LongestSubarraySumK::max_length(c, -5) == 5); // [-5, 8, -14, 2, 4] sum = -5, len 5

    std::cout << "longest_subarray_sum_k tests passed successfully.\n";
    return 0;
}
