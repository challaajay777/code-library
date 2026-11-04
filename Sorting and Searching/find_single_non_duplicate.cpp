#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Single Element in a Sorted Array
// Purpose: Finds the unique single non-duplicate element in a sorted array where all other elements appear twice in O(log N).
// Time Complexity: O(log N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Array length is odd; all elements except one appear exactly twice.

class SingleNonDuplicate {
public:
    static int single_non_duplicate(const std::vector<int>& a) {
        int low = 0, high = (int)a.size() - 1;

        while (low < high) {
            int mid = low + (high - low) / 2;
            if (mid % 2 == 1) mid--; // Ensure mid is even

            if (a[mid] == a[mid + 1]) {
                low = mid + 2;
            } else {
                high = mid;
            }
        }
        return a[low];
    }
};

int main() {
    std::vector<int> a = {1, 1, 2, 3, 3, 4, 4, 8, 8};
    assert(SingleNonDuplicate::single_non_duplicate(a) == 2);

    std::vector<int> b = {3, 3, 7, 7, 10, 11, 11};
    assert(SingleNonDuplicate::single_non_duplicate(b) == 10);

    std::cout << "find_single_non_duplicate tests passed successfully.\n";
    return 0;
}
