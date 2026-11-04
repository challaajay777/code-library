#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Remove Duplicates from Sorted Array (In-Place)
// Purpose: Removes duplicate elements in-place from a sorted array such that each unique element appears once.
// Time Complexity: O(N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Sorted array.

class RemoveDuplicatesSorted {
public:
    static int remove_duplicates(std::vector<int>& nums) {
        if (nums.empty()) return 0;
        int insert_pos = 1;

        for (size_t i = 1; i < nums.size(); ++i) {
            if (nums[i] != nums[i - 1]) {
                nums[insert_pos++] = nums[i];
            }
        }
        return insert_pos;
    }
};

int main() {
    std::vector<int> a = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4};
    int len = RemoveDuplicatesSorted::remove_duplicates(a);
    assert(len == 5);
    for (int i = 0; i < len; ++i) {
        assert(a[i] == i);
    }

    std::cout << "remove_duplicates_sorted_array tests passed successfully.\n";
    return 0;
}
