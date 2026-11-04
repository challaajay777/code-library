#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cassert>

// Algorithm: Maximum Circular Subarray Sum
// Purpose: Finds the maximum subarray sum allowing the subarray to wrap around the ends of the array in O(N).
// Time Complexity: O(N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Non-empty array. Handles all-negative elements correctly.

class MaximumCircularSubarraySum {
public:
    static long long max_circular_sum(const std::vector<long long>& a) {
        assert(!a.empty());
        long long total_sum = 0;
        long long max_kadane = a[0], cur_max = 0;
        long long min_kadane = a[0], cur_min = 0;

        for (long long x : a) {
            total_sum += x;

            cur_max = std::max(x, cur_max + x);
            max_kadane = std::max(max_kadane, cur_max);

            cur_min = std::min(x, cur_min + x);
            min_kadane = std::min(min_kadane, cur_min);
        }

        // If all elements are negative, max_circular is simply the max single element
        if (max_kadane < 0) {
            return max_kadane;
        }

        return std::max(max_kadane, total_sum - min_kadane);
    }
};

int main() {
    std::vector<long long> a = {1, -2, 3, -2};
    assert(MaximumCircularSubarraySum::max_circular_sum(a) == 3);

    std::vector<long long> b = {5, -3, 5};
    assert(MaximumCircularSubarraySum::max_circular_sum(b) == 10); // [5] + [5] wrapped

    std::vector<long long> c = {-3, -2, -3};
    assert(MaximumCircularSubarraySum::max_circular_sum(c) == -2);

    std::cout << "maximum_circular_subarray_sum tests passed successfully.\n";
    return 0;
}
