#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Majority Element in Sorted Array
// Purpose: Checks if a candidate is a majority element (frequency > N/2) in a sorted array in O(1) after lower_bound.
// Time Complexity: O(log N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Sorted array.

class MajorityElementSorted {
public:
    static bool is_majority(const std::vector<int>& a, int candidate) {
        int n = a.size();
        auto it = std::lower_bound(a.begin(), a.end(), candidate);
        if (it == a.end() || *it != candidate) return false;

        int first_idx = it - a.begin();
        int check_idx = first_idx + n / 2;

        return check_idx < n && a[check_idx] == candidate;
    }
};

int main() {
    std::vector<int> a = {1, 2, 3, 3, 3, 3, 10};
    assert(MajorityElementSorted::is_majority(a, 3) == true);
    assert(MajorityElementSorted::is_majority(a, 2) == false);

    std::cout << "majority_element_binary_search tests passed successfully.\n";
    return 0;
}
