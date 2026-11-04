#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Sort Colors (0, 1, 2 In-Place)
// Purpose: Sorts an array of 0s, 1s, and 2s in-place in a single pass using two pointers (Dutch National Flag).
// Time Complexity: O(N) time with one pass
// Space Complexity: O(1) auxiliary space
// Preconditions: Elements strictly in {0, 1, 2}.

class SortColors {
public:
    static void sort_colors(std::vector<int>& nums) {
        int low = 0, mid = 0, high = (int)nums.size() - 1;

        while (mid <= high) {
            if (nums[mid] == 0) {
                std::swap(nums[low++], nums[mid++]);
            } else if (nums[mid] == 1) {
                mid++;
            } else {
                std::swap(nums[mid], nums[high--]);
            }
        }
    }
};

int main() {
    std::vector<int> a = {2, 0, 2, 1, 1, 0};
    SortColors::sort_colors(a);
    std::vector<int> expected = {0, 0, 1, 1, 2, 2};
    assert(a == expected);

    std::cout << "sort_colors tests passed successfully.\n";
    return 0;
}
