#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Permutations II (Unique Permutations with Duplicates)
// Purpose: Generates all unique permutations of an array containing duplicate elements in O(N * N!).
// Time Complexity: O(N * N!) time
// Space Complexity: O(N) auxiliary space
// Preconditions: General array of elements.

class PermutationsWithDuplicates {
private:
    static void backtrack(std::vector<int>& nums, std::vector<bool>& used, std::vector<int>& cur,
                          std::vector<std::vector<int>>& res) {
        if (cur.size() == nums.size()) {
            res.push_back(cur);
            return;
        }
        for (size_t i = 0; i < nums.size(); ++i) {
            if (used[i]) continue;
            if (i > 0 && nums[i] == nums[i - 1] && !used[i - 1]) continue;

            used[i] = true;
            cur.push_back(nums[i]);
            backtrack(nums, used, cur, res);
            cur.pop_back();
            used[i] = false;
        }
    }

public:
    static std::vector<std::vector<int>> permute_unique(std::vector<int> nums) {
        std::sort(nums.begin(), nums.end());
        std::vector<std::vector<int>> res;
        std::vector<int> cur;
        std::vector<bool> used(nums.size(), false);
        backtrack(nums, used, cur, res);
        return res;
    }
};

int main() {
    std::vector<int> a = {1, 1, 2};
    auto p = PermutationsWithDuplicates::permute_unique(a);
    // [1, 1, 2], [1, 2, 1], [2, 1, 1] -> 3 permutations
    assert(p.size() == 3);

    std::cout << "permutations_with_duplicates tests passed successfully.\n";
    return 0;
}
