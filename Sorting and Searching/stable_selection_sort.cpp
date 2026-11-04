#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Stable Selection Sort
// Purpose: Sorts array by moving min element to position via shifting instead of swapping, preserving relative order of equals.
// Time Complexity: O(N^2) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Comparable elements.

class StableSelectionSort {
public:
    struct Item {
        int key;
        int original_idx;
        bool operator<(const Item& other) const { return key < other.key; }
    };

    static void sort(std::vector<Item>& a) {
        int n = a.size();
        for (int i = 0; i < n - 1; ++i) {
            int min_idx = i;
            for (int j = i + 1; j < n; ++j) {
                if (a[j] < a[min_idx]) {
                    min_idx = j;
                }
            }
            Item min_item = a[min_idx];
            // Shift elements right to insert min_item stably
            for (int k = min_idx; k > i; --k) {
                a[k] = a[k - 1];
            }
            a[i] = min_item;
        }
    }
};

int main() {
    std::vector<StableSelectionSort::Item> a = {{4, 0}, {5, 1}, {3, 2}, {2, 3}, {4, 4}, {1, 5}};
    StableSelectionSort::sort(a);

    // Verify sorted keys
    for (size_t i = 1; i < a.size(); ++i) {
        assert(a[i].key >= a[i - 1].key);
    }
    // Verify stability for duplicate key 4
    assert(a[3].key == 4 && a[3].original_idx == 0);
    assert(a[4].key == 4 && a[4].original_idx == 4);

    std::cout << "stable_selection_sort tests passed successfully.\n";
    return 0;
}
