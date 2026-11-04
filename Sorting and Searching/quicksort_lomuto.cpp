#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Quick Sort (Lomuto Partition)
// Purpose: Sorts an array using recursive quicksort with Lomuto's single-pointer partition scheme.
// Time Complexity: O(N log N) average, O(N^2) worst case
// Space Complexity: O(log N) recursion stack
// Preconditions: Randomized pivot recommended for worst-case defense.

class QuickSortLomuto {
private:
    static int partition(std::vector<int>& a, int low, int high) {
        int pivot = a[high];
        int i = low - 1;
        for (int j = low; j < high; ++j) {
            if (a[j] <= pivot) {
                i++;
                std::swap(a[i], a[j]);
            }
        }
        std::swap(a[i + 1], a[high]);
        return i + 1;
    }

    static void sort_helper(std::vector<int>& a, int low, int high) {
        if (low < high) {
            int p = partition(a, low, high);
            sort_helper(a, low, p - 1);
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
    std::vector<int> a = {10, 7, 8, 9, 1, 5};
    QuickSortLomuto::sort(a);
    std::vector<int> expected = {1, 5, 7, 8, 9, 10};
    assert(a == expected);

    std::cout << "quicksort_lomuto tests passed successfully.\n";
    return 0;
}
