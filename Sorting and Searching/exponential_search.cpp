#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Exponential (Galloping) Search
// Purpose: Finds a target in a sorted unbounded or large array by doubling range boundaries in O(log i) time.
// Time Complexity: O(log i) where i is the target index position
// Space Complexity: O(1) auxiliary space
// Preconditions: Sorted array.

class ExponentialSearch {
public:
    static int search(const std::vector<int>& a, int target) {
        int n = a.size();
        if (n == 0) return -1;
        if (a[0] == target) return 0;

        int bound = 1;
        while (bound < n && a[bound] < target) {
            bound *= 2;
        }

        int low = bound / 2;
        int high = std::min(bound, n - 1);

        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (a[mid] == target) {
                return mid;
            } else if (a[mid] < target) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return -1;
    }
};

int main() {
    std::vector<int> a = {2, 3, 4, 10, 40, 50, 60, 70, 80, 90, 100};
    assert(ExponentialSearch::search(a, 10) == 3);
    assert(ExponentialSearch::search(a, 90) == 9);
    assert(ExponentialSearch::search(a, 25) == -1);

    std::cout << "exponential_search tests passed successfully.\n";
    return 0;
}
