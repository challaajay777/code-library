#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Pigeonhole Sort
// Purpose: Sorts an array of integers when range of keys is approximately equal to number of elements.
// Time Complexity: O(N + Range) time
// Space Complexity: O(Range) auxiliary space
// Preconditions: Range = max_val - min_val + 1 is modest.

class PigeonholeSort {
public:
    static void sort(std::vector<int>& a) {
        if (a.empty()) return;
        int min_val = *std::min_element(a.begin(), a.end());
        int max_val = *std::max_element(a.begin(), a.end());
        int range = max_val - min_val + 1;

        std::vector<std::vector<int>> holes(range);
        for (int x : a) {
            holes[x - min_val].push_back(x);
        }

        int idx = 0;
        for (int i = 0; i < range; ++i) {
            for (int x : holes[i]) {
                a[idx++] = x;
            }
        }
    }
};

int main() {
    std::vector<int> a = {8, 3, 2, 7, 4, 6, 8};
    PigeonholeSort::sort(a);
    std::vector<int> expected = {2, 3, 4, 6, 7, 8, 8};
    assert(a == expected);

    std::cout << "pigeonhole_sort tests passed successfully.\n";
    return 0;
}
