#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Permutations Generator
// Purpose: Generates all N! permutations of an array of distinct elements via recursive backtracking swaps.
// Time Complexity: O(N * N!) time
// Space Complexity: O(N) recursion depth
// Preconditions: Elements are distinct.

class PermutationsGenerator {
private:
    static void backtrack(int start, std::vector<int>& nums, std::vector<std::vector<int>>& res) {
        if (start == (int)nums.size()) {
            res.push_back(nums);
            return;
        }
        for (int i = start; i < (int)nums.size(); ++i) {
            std::swap(nums[start], nums[i]);
            backtrack(start + 1, nums, res);
            std::swap(nums[start], nums[i]);
        }
    }

public:
    static std::vector<std::vector<int>> permute(std::vector<int> nums) {
        std::vector<std::vector<int>> res;
        backtrack(0, nums, res);
        return res;
    }
};

int main() {
    std::vector<int> nums = {1, 2, 3};
    auto p = PermutationsGenerator::permute(nums);
    assert(p.size() == 6);

    std::cout << "permutations_all tests passed successfully.\n";
    return 0;
}
