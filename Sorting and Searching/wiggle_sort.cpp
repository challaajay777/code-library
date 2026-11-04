#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Wiggle Sort (Odd-Even Peak Rearrangement)
// Purpose: Rearranges an array such that nums[0] <= nums[1] >= nums[2] <= nums[3]... in O(N) time and O(1) space.
// Time Complexity: O(N) time with a single pass
// Space Complexity: O(1) auxiliary space
// Preconditions: General array of elements.

class WiggleSort {
public:
    static void wiggle_sort(std::vector<int>& a) {
        for (size_t i = 0; i + 1 < a.size(); ++i) {
            if ((i % 2 == 0 && a[i] > a[i + 1]) || (i % 2 == 1 && a[i] < a[i + 1])) {
                std::swap(a[i], a[i + 1]);
            }
        }
    }
};

int main() {
    std::vector<int> a = {3, 5, 2, 1, 6, 4};
    WiggleSort::wiggle_sort(a);
    for (size_t i = 0; i + 1 < a.size(); ++i) {
        if (i % 2 == 0) assert(a[i] <= a[i + 1]);
        else assert(a[i] >= a[i + 1]);
    }

    std::cout << "wiggle_sort tests passed successfully.\n";
    return 0;
}
