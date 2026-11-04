#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Count Subarrays with Bounded Maximum
// Purpose: Counts contiguous subarrays where the maximum value lies in range [L, R] in O(N) time and O(1) space.
// Time Complexity: O(N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: L <= R.

class SubarraysBoundedMaximum {
public:
    static long long num_subarrays_bounded_max(const std::vector<int>& a, int left, int right) {
        // Count subarrays with max <= B minus subarrays with max <= A - 1
        return count_at_most(a, right) - count_at_most(a, left - 1);
    }

private:
    static long long count_at_most(const std::vector<int>& a, int bound) {
        long long total = 0;
        long long current_len = 0;
        for (int x : a) {
            if (x <= bound) {
                current_len++;
                total += current_len;
            } else {
                current_len = 0;
            }
        }
        return total;
    }
};

int main() {
    std::vector<int> a = {2, 1, 4, 3};
    // Subarrays with max in [2, 3]: [2], [2, 1], [3] -> 3
    assert(SubarraysBoundedMaximum::num_subarrays_bounded_max(a, 2, 3) == 3);

    std::vector<int> b = {2, 9, 2, 5, 6};
    // max in [2, 8]: [2], [2], [5], [2, 5], [6], [5, 6], [2, 5, 6] -> 7
    assert(SubarraysBoundedMaximum::num_subarrays_bounded_max(b, 2, 8) == 7);

    std::cout << "count_subarrays_bounded_maximum tests passed successfully.\n";
    return 0;
}
