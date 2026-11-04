#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Counting Sort for Signed Integers
// Purpose: Sorts integer array in linear time over any range [min_val, max_val] maintaining stability.
// Time Complexity: O(N + K) where K = max_val - min_val + 1
// Space Complexity: O(N + K) space
// Preconditions: Range K is reasonably bounded.

class CountingSortSigned {
public:
    static void sort(std::vector<int>& a) {
        if (a.empty()) return;
        int min_val = *std::min_element(a.begin(), a.end());
        int max_val = *std::max_element(a.begin(), a.end());
        int range = max_val - min_val + 1;

        std::vector<int> count(range, 0);
        for (int x : a) {
            count[x - min_val]++;
        }

        for (int i = 1; i < range; ++i) {
            count[i] += count[i - 1];
        }

        std::vector<int> output(a.size());
        for (int i = (int)a.size() - 1; i >= 0; --i) {
            output[count[a[i] - min_val] - 1] = a[i];
            count[a[i] - min_val]--;
        }
        a = std::move(output);
    }
};

int main() {
    std::vector<int> a = {-5, -10, 0, -3, 8, 5, -1, 10};
    CountingSortSigned::sort(a);
    std::vector<int> expected = {-10, -5, -3, -1, 0, 5, 8, 10};
    assert(a == expected);

    std::cout << "counting_sort_signed tests passed successfully.\n";
    return 0;
}
