#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Remove Duplicates from Sorted Array II (At Most Twice)
// Purpose: Removes duplicates in-place such that each unique element appears at most twice in O(N) time and O(1) space.
// Time Complexity: O(N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Sorted array.

class RemoveDuplicatesAtMostTwice {
public:
    static int remove_duplicates(std::vector<int>& nums) {
        int n = nums.size();
        if (n <= 2) return n;

        int insert_pos = 2;
        for (int i = 2; i < n; ++i) {
            if (nums[i] != nums[insert_pos - 2]) {
                nums[insert_pos++] = nums[i];
            }
        }
        return insert_pos;
    }
};

int main() {
    std::vector<int> a = {1, 1, 1, 2, 2, 3};
    int len = RemoveDuplicatesAtMostTwice::remove_duplicates(a);
    assert(len == 5);
    std::vector<int> expected = {1, 1, 2, 2, 3};
    for (int i = 0; i < len; ++i) {
        assert(a[i] == expected[i]);
    }

    std::cout << "remove_duplicates_sorted_array_ii tests passed successfully.\n";
    return 0;
}
