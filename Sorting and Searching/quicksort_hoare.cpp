#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Quick Sort (Hoare Partition)
// Purpose: Sorts array using Hoare's two-pointer bidirectional partition scheme, doing roughly 3x fewer swaps than Lomuto.
// Time Complexity: O(N log N) average, O(N^2) worst case
// Space Complexity: O(log N) recursion stack
// Preconditions: Handles duplicates efficiently.

class QuickSortHoare {
private:
    static int partition(std::vector<int>& a, int low, int high) {
        int pivot = a[low + (high - low) / 2];
        int i = low - 1;
        int j = high + 1;
        while (true) {
            do { i++; } while (a[i] < pivot);
            do { j--; } while (a[j] > pivot);
            if (i >= j) return j;
            std::swap(a[i], a[j]);
        }
    }

    static void sort_helper(std::vector<int>& a, int low, int high) {
        if (low < high) {
            int p = partition(a, low, high);
            sort_helper(a, low, p);
            sort_helper(a, p + 1, high);
        }
    }

public:
    static void sort(std::vector<int>& a) {
        if (!a.empty()) {
            sort_helper(a, 0, (int)a.size() - 1);
        }
    }
};

int main() {
    std::vector<int> a = {19, 22, 63, 105, 2, 46};
    QuickSortHoare::sort(a);
    std::vector<int> expected = {2, 19, 22, 46, 63, 105};
    assert(a == expected);

    std::cout << "quicksort_hoare tests passed successfully.\n";
    return 0;
}
