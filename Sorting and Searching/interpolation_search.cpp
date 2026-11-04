#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Interpolation Search
// Purpose: Searches for a key in uniformly distributed sorted numeric arrays in O(log log N) average time.
// Time Complexity: O(log log N) average, O(N) worst case
// Space Complexity: O(1) auxiliary space
// Preconditions: Sorted array with approximately uniform value distribution.

class InterpolationSearch {
public:
    static int search(const std::vector<int>& a, int target) {
        int low = 0;
        int high = (int)a.size() - 1;

        while (low <= high && target >= a[low] && target <= a[high]) {
            if (low == high) {
                if (a[low] == target) return low;
                return -1;
            }

            // Estimate probe position using linear interpolation
            long long pos = low + ((long long)(target - a[low]) * (high - low)) / (a[high] - a[low]);

            if (a[pos] == target) {
                return pos;
            } else if (a[pos] < target) {
                low = pos + 1;
            } else {
                high = pos - 1;
            }
        }
        return -1;
    }
};

int main() {
    std::vector<int> a = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    assert(InterpolationSearch::search(a, 40) == 3);
    assert(InterpolationSearch::search(a, 70) == 6);
    assert(InterpolationSearch::search(a, 35) == -1);

    std::cout << "interpolation_search tests passed successfully.\n";
    return 0;
}
