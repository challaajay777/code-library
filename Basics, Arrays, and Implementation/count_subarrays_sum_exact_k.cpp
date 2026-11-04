#include <iostream>
#include <vector>
#include <unordered_map>
#include <cassert>

// Algorithm: Count Subarrays with Sum Equal to K
// Purpose: Counts total number of continuous subarrays whose elements sum up exactly to target K.
// Time Complexity: O(N) average time
// Space Complexity: O(N) space
// Preconditions: 64-bit integer values.

class CountSubarraysSumExactK {
public:
    static long long count(const std::vector<long long>& a, long long k) {
        std::unordered_map<long long, long long> prefix_counts;
        prefix_counts[0] = 1;

        long long pref = 0;
        long long total = 0;

        for (long long x : a) {
            pref += x;
            auto it = prefix_counts.find(pref - k);
            if (it != prefix_counts.end()) {
                total += it->second;
            }
            prefix_counts[pref]++;
        }
        return total;
    }
};

int main() {
    std::vector<long long> a = {1, 1, 1};
    assert(CountSubarraysSumExactK::count(a, 2) == 2);

    std::vector<long long> b = {1, 2, 3, -3, 1, 1, 1, 4, 2, -3};
    // Subarrays with sum 3:
    assert(CountSubarraysSumExactK::count(b, 3) == 8);

    std::cout << "count_subarrays_sum_exact_k tests passed successfully.\n";
    return 0;
}
