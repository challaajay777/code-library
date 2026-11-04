#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Magic Index (A[i] == i) Finder
// Purpose: Finds an index i such that a[i] == i in a sorted array in O(log N) for distinct or recursive divide-and-conquer for duplicates.
// Time Complexity: O(log N) for distinct elements
// Space Complexity: O(1) auxiliary space
// Preconditions: Sorted integer array.

class MagicIndex {
public:
    static int find_magic_index_distinct(const std::vector<int>& a) {
        int low = 0, high = (int)a.size() - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (a[mid] == mid) {
                return mid;
            } else if (a[mid] < mid) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return -1;
    }
};

int main() {
    std::vector<int> a = {-10, -5, 0, 3, 7};
    // a[3] == 3
    assert(MagicIndex::find_magic_index_distinct(a) == 3);

    std::vector<int> b = {1, 2, 3, 4};
    assert(MagicIndex::find_magic_index_distinct(b) == -1);

    std::cout << "index_equals_value_search tests passed successfully.\n";
    return 0;
}
