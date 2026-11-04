#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Bitonic Sort Network
// Purpose: Parallel sorting algorithm building bitonic sequences and recursively merging them in O(log^2 N) depth.
// Time Complexity: O(N log^2 N) sequential time, O(log^2 N) parallel depth
// Space Complexity: O(log N) recursion depth
// Preconditions: Size N must be a power of two.

class BitonicSort {
private:
    static void bitonic_merge(std::vector<int>& a, int low, int cnt, bool dir) {
        if (cnt > 1) {
            int k = cnt / 2;
            for (int i = low; i < low + k; ++i) {
                if ((a[i] > a[i + k]) == dir) {
                    std::swap(a[i], a[i + k]);
                }
            }
            bitonic_merge(a, low, k, dir);
            bitonic_merge(a, low + k, k, dir);
        }
    }

    static void bitonic_sort_rec(std::vector<int>& a, int low, int cnt, bool dir) {
        if (cnt > 1) {
            int k = cnt / 2;
            bitonic_sort_rec(a, low, k, true);        // Ascending
            bitonic_sort_rec(a, low + k, k, false);   // Descending
            bitonic_merge(a, low, cnt, dir);
        }
    }

public:
    static void sort(std::vector<int>& a) {
        int n = a.size();
        assert((n & (n - 1)) == 0 && n > 0); // Check power of two
        bitonic_sort_rec(a, 0, n, true);
    }
};

int main() {
    std::vector<int> a = {3, 7, 4, 8, 6, 2, 1, 5};
    BitonicSort::sort(a);
    std::vector<int> expected = {1, 2, 3, 4, 5, 6, 7, 8};
    assert(a == expected);

    std::cout << "bitonic_sort tests passed successfully.\n";
    return 0;
}
