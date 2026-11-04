#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Patching Array (Greedy Range Expansion)
// Purpose: Finds minimum number of patches added to sorted array nums so that any number in [1, N] can be formed by subset sum.
// Time Complexity: O(M + log N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Nums sorted in non-decreasing order.

class PatchingArray {
public:
    static int min_patches(const std::vector<int>& nums, long long n) {
        long long miss = 1;
        int patches = 0;
        size_t i = 0;

        while (miss <= n) {
            if (i < nums.size() && nums[i] <= miss) {
                miss += nums[i++];
            } else {
                miss += miss;
                patches++;
            }
        }
        return patches;
    }
};

int main() {
    std::vector<int> nums = {1, 3};
    assert(PatchingArray::min_patches(nums, 6) == 1); // add 2 -> miss becomes 7

    std::vector<int> nums2 = {1, 5, 10};
    assert(PatchingArray::min_patches(nums2, 20) == 2);

    std::cout << "patching_array tests passed successfully.\n";
    return 0;
}
