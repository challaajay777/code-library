#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Count Subarrays with Sum at Most K
// Purpose: Counts all continuous subarrays whose sum does not exceed K in an array of non-negative numbers in linear time.
// Time Complexity: O(N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: All elements a[i] >= 0 and target K >= 0.

class CountSubarraysSumAtMostK {
public:
    static long long count(const std::vector<long long>& a, long long k) {
        if (k < 0) return 0;
        int n = a.size();
        long long ans = 0;
        long long current_sum = 0;
        int left = 0;

        for (int right = 0; right < n; ++right) {
            assert(a[right] >= 0);
            current_sum += a[right];
            while (current_sum > k && left <= right) {
                current_sum -= a[left++];
            }
            ans += (right - left + 1);
        }
        return ans;
    }
};

int main() {
    std::vector<long long> a = {1, 2, 3};
    // For k=3: [1], [2], [3], [1, 2] -> 4 subarrays
    assert(CountSubarraysSumAtMostK::count(a, 3) == 4);

    std::vector<long long> b = {1, 11, 2, 3, 15};
    // k = 10: [1], [2], [3], [2, 3] -> 4 subarrays
    assert(CountSubarraysSumAtMostK::count(b, 10) == 4);

    std::cout << "count_subarrays_sum_at_most_k tests passed successfully.\n";
    return 0;
}
