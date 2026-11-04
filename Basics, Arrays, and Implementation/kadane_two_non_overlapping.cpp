#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Two Non-Overlapping Maximum Subarrays
// Purpose: Finds the maximum possible total sum of two contiguous, disjoint subarrays in O(N) time.
// Time Complexity: O(N) time
// Space Complexity: O(N) auxiliary space
// Preconditions: Array length >= 2.

class TwoNonOverlappingSubarrays {
public:
    static long long max_two_subarrays_sum(const std::vector<long long>& a) {
        int n = a.size();
        assert(n >= 2);

        // left_max[i]: max subarray sum ending at or before index i
        std::vector<long long> left_max(n);
        long long cur = a[0];
        left_max[0] = cur;
        long long best = cur;

        for (int i = 1; i < n; ++i) {
            cur = std::max(a[i], cur + a[i]);
            best = std::max(best, cur);
            left_max[i] = best;
        }

        // right_max[i]: max subarray sum starting at or after index i
        std::vector<long long> right_max(n);
        cur = a[n - 1];
        right_max[n - 1] = cur;
        best = cur;

        for (int i = n - 2; i >= 0; --i) {
            cur = std::max(a[i], cur + a[i]);
            best = std::max(best, cur);
            right_max[i] = best;
        }

        long long ans = -2e18;
        for (int i = 0; i < n - 1; ++i) {
            ans = std::max(ans, left_max[i] + right_max[i + 1]);
        }
        return ans;
    }
};

int main() {
    std::vector<long long> a = {1, 3, -1, 2, -1, 2};
    // Best two: [1, 3] sum=4 and [2, -1, 2] sum=3 -> total 7
    assert(TwoNonOverlappingSubarrays::max_two_subarrays_sum(a) == 7);

    std::vector<long long> b = {-1, -2, -3, -4};
    // Best two single elements: -1 and -2 -> total -3
    assert(TwoNonOverlappingSubarrays::max_two_subarrays_sum(b) == -3);

    std::cout << "kadane_two_non_overlapping tests passed successfully.\n";
    return 0;
}
