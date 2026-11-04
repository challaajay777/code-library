#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Stooge Sort
// Purpose: Recursive sorting algorithm sorting first 2/3, last 2/3, then first 2/3 again.
// Time Complexity: O(N^(log 3 / log 1.5)) = O(N^2.7095) time
// Space Complexity: O(log N) recursion stack
// Preconditions: Educational baseline.

class StoogeSort {
private:
    static void sort_rec(std::vector<int>& a, int l, int h) {
        if (l >= h) return;
        if (a[l] > a[h]) {
            std::swap(a[l], a[h]);
        }
        if (h - l + 1 > 2) {
            int t = (h - l + 1) / 3;
            sort_rec(a, l, h - t);
            sort_rec(a, l + t, h);
            sort_rec(a, l, h - t);
        }
    }

public:
    static void sort(std::vector<int>& a) {
        if (!a.empty()) {
            sort_rec(a, 0, (int)a.size() - 1);
        }
    }
};

int main() {
    std::vector<int> a = {2, 4, 5, 3, 1};
    StoogeSort::sort(a);
    std::vector<int> expected = {1, 2, 3, 4, 5};
    assert(a == expected);

    std::cout << "stooge_sort tests passed successfully.\n";
    return 0;
}
