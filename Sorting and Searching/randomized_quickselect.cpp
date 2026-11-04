#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <cassert>

// Algorithm: Randomized Quickselect
// Purpose: Finds the k-th smallest element (0-indexed) in an unsorted array in expected linear time.
// Time Complexity: O(N) expected time, O(N^2) worst case
// Space Complexity: O(1) auxiliary space iterative
// Preconditions: 0 <= k < N.

class Quickselect {
public:
    static int select(std::vector<int>& a, int k) {
        int n = a.size();
        assert(k >= 0 && k < n);
        int low = 0, high = n - 1;

        std::mt19937 rng(1337);

        while (low <= high) {
            int p_idx = low + rng() % (high - low + 1);
            std::swap(a[p_idx], a[high]);
            int pivot = a[high];

            int i = low;
            for (int j = low; j < high; ++j) {
                if (a[j] <= pivot) {
                    std::swap(a[i++], a[j]);
                }
            }
            std::swap(a[i], a[high]);

            if (i == k) {
                return a[i];
            } else if (i < k) {
                low = i + 1;
            } else {
                high = i - 1;
            }
        }
        return -1;
    }
};

int main() {
    std::vector<int> a = {7, 10, 4, 3, 20, 15};
    // Sorted: 3, 4, 7, 10, 15, 20
    assert(Quickselect::select(a, 0) == 3);
    assert(Quickselect::select(a, 2) == 7);
    assert(Quickselect::select(a, 5) == 20);

    std::cout << "randomized_quickselect tests passed successfully.\n";
    return 0;
}
