#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <cassert>

// Algorithm: Distinct Bitwise OR of Subarrays
// Purpose: Finds all distinct bitwise OR values produced by contiguous subarrays in O(N * 30) time.
// Time Complexity: O(N * log(max_A)) time
// Space Complexity: O(log(max_A)) auxiliary space per step
// Preconditions: Elements non-negative 32/64-bit integers.

class DistinctSubarrayBitwiseOr {
public:
    static std::unordered_set<long long> get_all_distinct_ors(const std::vector<long long>& a) {
        std::unordered_set<long long> total_ors;
        std::vector<long long> cur_ors; // Stores unique ORs ending at current index

        for (long long x : a) {
            std::vector<long long> next_ors;
            next_ors.push_back(x);
            for (long long prev : cur_ors) {
                next_ors.push_back(prev | x);
            }
            // Remove duplicates
            std::sort(next_ors.begin(), next_ors.end());
            next_ors.erase(std::unique(next_ors.begin(), next_ors.end()), next_ors.end());

            for (long long v : next_ors) {
                total_ors.insert(v);
            }
            cur_ors = std::move(next_ors);
        }
        return total_ors;
    }
};

int main() {
    std::vector<long long> a = {1, 2, 4};
    // Subarrays: [1]=1, [2]=2, [4]=4, [1,2]=3, [2,4]=6, [1,2,4]=7 -> 6 distinct values
    auto ors = DistinctSubarrayBitwiseOr::get_all_distinct_ors(a);
    assert(ors.size() == 6);
    assert(ors.count(1) && ors.count(2) && ors.count(3) && ors.count(4) && ors.count(6) && ors.count(7));

    std::cout << "prefix_bitwise_or_and tests passed successfully.\n";
    return 0;
}
