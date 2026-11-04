#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Cycle Sort
// Purpose: In-place, unstable comparison sort that minimizes the total number of memory writes to the original array.
// Time Complexity: O(N^2) time with at most N - 1 writes
// Space Complexity: O(1) auxiliary space
// Preconditions: Comparable elements.

class CycleSort {
public:
    static int sort(std::vector<int>& a) {
        int n = a.size();
        int writes = 0;

        for (int cycle_start = 0; cycle_start <= n - 2; ++cycle_start) {
            int item = a[cycle_start];
            int pos = cycle_start;

            for (int i = cycle_start + 1; i < n; ++i) {
                if (a[i] < item) pos++;
            }
            if (pos == cycle_start) continue;

            while (item == a[pos]) pos++;
            if (pos != cycle_start) {
                std::swap(item, a[pos]);
                writes++;
            }

            while (pos != cycle_start) {
                pos = cycle_start;
                for (int i = cycle_start + 1; i < n; ++i) {
                    if (a[i] < item) pos++;
                }
                while (item == a[pos]) pos++;
                if (item != a[pos]) {
                    std::swap(item, a[pos]);
                    writes++;
                }
            }
        }
        return writes;
    }
};

int main() {
    std::vector<int> a = {1, 8, 3, 9, 10, 10, 2, 4};
    CycleSort::sort(a);
    for (size_t i = 1; i < a.size(); ++i) {
        assert(a[i] >= a[i - 1]);
    }

    std::cout << "cycle_sort tests passed successfully.\n";
    return 0;
}
