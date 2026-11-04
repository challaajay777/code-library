#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Pancake Sorting
// Purpose: Sorts an array using only prefix reversal operations in at most 2*N flips.
// Time Complexity: O(N^2) time with at most 2*N flip operations
// Space Complexity: O(1) auxiliary space
// Preconditions: Array length >= 1.

class PancakeSort {
public:
    // Returns sequence of k values representing prefix reversals of a[0..k-1]
    static std::vector<int> sort(std::vector<int>& a) {
        int n = a.size();
        std::vector<int> flips;

        for (int cur_size = n; cur_size > 1; --cur_size) {
            int max_idx = std::max_element(a.begin(), a.begin() + cur_size) - a.begin();

            if (max_idx != cur_size - 1) {
                if (max_idx != 0) {
                    flips.push_back(max_idx + 1);
                    std::reverse(a.begin(), a.begin() + max_idx + 1);
                }
                flips.push_back(cur_size);
                std::reverse(a.begin(), a.begin() + cur_size);
            }
        }
        return flips;
    }
};

int main() {
    std::vector<int> a = {3, 2, 4, 1};
    auto flips = PancakeSort::sort(a);
    assert(std::is_sorted(a.begin(), a.end()));
    assert((int)flips.size() <= 2 * 4);

    std::cout << "pancake_sorting tests passed successfully.\n";
    return 0;
}
