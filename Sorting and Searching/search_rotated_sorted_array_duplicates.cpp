#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Search in Rotated Sorted Array with Duplicates
// Purpose: Determines whether target exists in a rotated sorted array containing duplicate values in O(log N) average, O(N) worst case.
// Time Complexity: O(log N) average, O(N) worst case
// Space Complexity: O(1) auxiliary space
// Preconditions: Rotated sorted array possibly with duplicates.

class SearchRotatedWithDuplicates {
public:
    static bool search(const std::vector<int>& a, int target) {
        int low = 0, high = (int)a.size() - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (a[mid] == target) return true;

            if (a[low] == a[mid] && a[mid] == a[high]) {
                low++;
                high--;
            } else if (a[low] <= a[mid]) {
                if (a[low] <= target && target < a[mid]) {
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            } else {
                if (a[mid] < target && target <= a[high]) {
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }
        }
        return false;
    }
};

int main() {
    std::vector<int> a = {2, 5, 6, 0, 0, 1, 2};
    assert(SearchRotatedWithDuplicates::search(a, 0) == true);
    assert(SearchRotatedWithDuplicates::search(a, 3) == false);

    std::vector<int> b = {1, 0, 1, 1, 1};
    assert(SearchRotatedWithDuplicates::search(b, 0) == true);

    std::cout << "search_rotated_sorted_array_duplicates tests passed successfully.\n";
    return 0;
}
