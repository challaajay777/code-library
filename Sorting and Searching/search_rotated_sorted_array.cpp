#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Search in Rotated Sorted Array (Distinct Elements)
// Purpose: Finds index of target element in a circularly rotated sorted array with distinct values in O(log N).
// Time Complexity: O(log N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Elements in array are unique.

class SearchRotatedSortedArray {
public:
    static int search(const std::vector<int>& a, int target) {
        int low = 0, high = (int)a.size() - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (a[mid] == target) return mid;

            // Check if left half is sorted
            if (a[low] <= a[mid]) {
                if (a[low] <= target && target < a[mid]) {
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            } else { // Right half is sorted
                if (a[mid] < target && target <= a[high]) {
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }
        }
        return -1;
    }
};

int main() {
    std::vector<int> a = {4, 5, 6, 7, 0, 1, 2};
    assert(SearchRotatedSortedArray::search(a, 0) == 4);
    assert(SearchRotatedSortedArray::search(a, 3) == -1);

    std::vector<int> b = {1};
    assert(SearchRotatedSortedArray::search(b, 0) == -1);

    std::cout << "search_rotated_sorted_array tests passed successfully.\n";
    return 0;
}
