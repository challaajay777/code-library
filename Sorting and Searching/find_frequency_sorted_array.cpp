#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Count Frequency in Sorted Array
// Purpose: Calculates the total frequency of target in sorted array in O(log N) via upper_bound - lower_bound.
// Time Complexity: O(log N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Sorted array.

class FrequencyInSortedArray {
public:
    static int count(const std::vector<int>& a, int target) {
        auto it1 = std::lower_bound(a.begin(), a.end(), target);
        auto it2 = std::upper_bound(a.begin(), a.end(), target);
        return std::distance(it1, it2);
    }
};

int main() {
    std::vector<int> a = {1, 1, 2, 2, 2, 2, 3};
    assert(FrequencyInSortedArray::count(a, 2) == 4);
    assert(FrequencyInSortedArray::count(a, 1) == 2);
    assert(FrequencyInSortedArray::count(a, 4) == 0);

    std::cout << "find_frequency_sorted_array tests passed successfully.\n";
    return 0;
}
