#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Subarray Sum Divisible by Array Length (Pigeonhole Subarray)
// Purpose: Finds a non-empty contiguous subarray whose sum is divisible by N using Pigeonhole Principle (guaranteed to exist).
// Time Complexity: O(N) time
// Space Complexity: O(N) space
// Preconditions: Array length N >= 1.

class PigeonholeSubarrayDivisibleN {
public:
    // Returns pair [start_idx, end_idx] (0-indexed inclusive)
    static std::pair<int, int> find_subarray(const std::vector<long long>& a) {
        int n = a.size();
        assert(n >= 1);
        std::vector<int> first_rem(n, -2);
        first_rem[0] = -1;

        long long pref = 0;
        for (int i = 0; i < n; ++i) {
            pref = (pref + a[i]) % n;
            if (pref < 0) pref += n;

            if (first_rem[pref] != -2) {
                return {first_rem[pref] + 1, i};
            }
            first_rem[pref] = i;
        }
        return {-1, -1}; // Should never happen by pigeonhole principle
    }
};

int main() {
    std::vector<long long> a = {3, 2, 7, 1}; // n = 4
    auto [l, r] = PigeonholeSubarrayDivisibleN::find_subarray(a);
    assert(l != -1 && l <= r);
    long long sum = 0;
    for (int i = l; i <= r; ++i) sum += a[i];
    assert(sum % 4 == 0);

    std::cout << "subarray_sum_divisible_by_length tests passed successfully.\n";
    return 0;
}
