#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Discrete Ternary Search on Unimodal Array
// Purpose: Finds maximum value in a discrete array that strictly increases then strictly decreases in O(log N).
// Time Complexity: O(log N) evaluations
// Space Complexity: O(1) auxiliary space
// Preconditions: Array elements strictly unimodal (increasing to peak then decreasing).

class DiscreteTernarySearch {
public:
    static int find_max_index(const std::vector<int>& a) {
        int low = 0, high = (int)a.size() - 1;

        while (high - low >= 3) {
            int m1 = low + (high - low) / 3;
            int m2 = high - (high - low) / 3;

            if (a[m1] < a[m2]) {
                low = m1;
            } else {
                high = m2;
            }
        }

        int best_idx = low;
        for (int i = low + 1; i <= high; ++i) {
            if (a[i] > a[best_idx]) {
                best_idx = i;
            }
        }
        return best_idx;
    }
};

int main() {
    std::vector<int> a = {1, 3, 8, 12, 17, 14, 9, 2};
    assert(DiscreteTernarySearch::find_max_index(a) == 4); // peak = 17

    std::vector<int> b = {10, 8, 5, 2}; // strictly decreasing
    assert(DiscreteTernarySearch::find_max_index(b) == 0);

    std::cout << "ternary_search_discrete tests passed successfully.\n";
    return 0;
}
