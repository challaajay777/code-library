#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Subarrays with Sum Divisible by K
// Purpose: Counts the number of non-empty continuous subarrays whose sum is evenly divisible by K using prefix remainders.
// Time Complexity: O(N) time
// Space Complexity: O(K) auxiliary space
// Preconditions: K >= 1. Handles negative integers correctly.

class SubarraySumDivisibleByK {
public:
    static long long count_subarrays(const std::vector<long long>& a, long long k) {
        assert(k > 0);
        std::vector<long long> rem_count(k, 0);
        rem_count[0] = 1;

        long long running_sum = 0;
        long long ans = 0;

        for (long long x : a) {
            running_sum += x;
            long long rem = (running_sum % k + k) % k;
            ans += rem_count[rem];
            rem_count[rem]++;
        }
        return ans;
    }
};

int main() {
    std::vector<long long> a = {4, 5, 0, -2, -3, 1};
    // Subarrays divisible by 5:
    // [5], [5, 0], [0], [4, 5, 0, -2, -3, 1] sum=5, [-2, -3], [5, 0, -2, -3], [0, -2, -3] -> total 7
    assert(SubarraySumDivisibleByK::count_subarrays(a, 5) == 7);

    std::vector<long long> b = {5};
    assert(SubarraySumDivisibleByK::count_subarrays(b, 9) == 0);

    std::cout << "subarray_sum_divisible_by_k tests passed successfully.\n";
    return 0;
}
