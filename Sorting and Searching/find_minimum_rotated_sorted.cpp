#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Find Minimum in Rotated Sorted Array
// Purpose: Finds the minimum element in a rotated sorted array of distinct elements in O(log N) time.
// Time Complexity: O(log N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Array length >= 1, all elements unique.

class FindMinRotatedSorted {
public:
    static int find_min(const std::vector<int>& a) {
        assert(!a.empty());
        int low = 0, high = (int)a.size() - 1;

        while (low < high) {
            int mid = low + (high - low) / 2;
            if (a[mid] > a[high]) {
                low = mid + 1;
            } else {
                high = mid;
            }
        }
        return a[low];
    }
};

int main() {
    std::vector<int> a = {3, 4, 5, 1, 2};
    assert(FindMinRotatedSorted::find_min(a) == 1);

    std::vector<int> b = {4, 5, 6, 7, 0, 1, 2};
    assert(FindMinRotatedSorted::find_min(b) == 0);

    std::vector<int> c = {11, 13, 15, 17};
    assert(FindMinRotatedSorted::find_min(c) == 11);

    std::cout << "find_minimum_rotated_sorted tests passed successfully.\n";
    return 0;
}
