#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Comb Sort
// Purpose: Improves bubble sort by eliminating turtles using gap sequence with shrink factor 1.3.
// Time Complexity: O(N^2) worst case, O(N log N) typical competitive programming performance
// Space Complexity: O(1) auxiliary space
// Preconditions: Comparable array elements.

class CombSort {
public:
    static void sort(std::vector<int>& a) {
        int n = a.size();
        int gap = n;
        const double shrink = 1.3;
        bool sorted = false;

        while (!sorted) {
            gap = static_cast<int>(gap / shrink);
            if (gap <= 1) {
                gap = 1;
                sorted = true; // tentative: confirm no swaps occurred
            }
            for (int i = 0; i + gap < n; ++i) {
                if (a[i] > a[i + gap]) {
                    std::swap(a[i], a[i + gap]);
                    sorted = false;
                }
            }
        }
    }
};

int main() {
    std::vector<int> a = {8, 4, 1, 56, 3, -44, 23, -6, 28, 0};
    CombSort::sort(a);
    for (size_t i = 1; i < a.size(); ++i) {
        assert(a[i] >= a[i - 1]);
    }

    std::cout << "comb_sort tests passed successfully.\n";
    return 0;
}
