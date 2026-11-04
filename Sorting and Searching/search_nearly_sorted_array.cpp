#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Search in K-Nearly Sorted Array
// Purpose: Finds target in an array where each element is at most K positions away from its sorted index in O(log N).
// Time Complexity: O(log N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Element is at most K away from sorted location (here K = 1).

class NearlySortedSearch {
public:
    static int search(const std::vector<int>& a, int target) {
        int low = 0, high = (int)a.size() - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (a[mid] == target) return mid;
            if (mid > low && a[mid - 1] == target) return mid - 1;
            if (mid < high && a[mid + 1] == target) return mid + 1;

            if (a[mid] > target) {
                high = mid - 2;
            } else {
                low = mid + 2;
            }
        }
        return -1;
    }
};

int main() {
    std::vector<int> a = {10, 3, 40, 20, 50, 80, 70};
    assert(NearlySortedSearch::search(a, 40) == 2);
    assert(NearlySortedSearch::search(a, 20) == 3);
    assert(NearlySortedSearch::search(a, 90) == -1);

    std::cout << "search_nearly_sorted_array tests passed successfully.\n";
    return 0;
}
