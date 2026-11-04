#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Lexicographical Subsets Generation
// Purpose: Generates all 2^N subsets of an array in lexicographical order using recursive choice.
// Time Complexity: O(N * 2^N) time
// Space Complexity: O(N) recursion depth
// Preconditions: Array elements distinct and pre-sorted.

class LexicographicalSubsets {
private:
    static void dfs(int idx, const std::vector<int>& nums, std::vector<int>& cur,
                    std::vector<std::vector<int>>& result) {
        result.push_back(cur);
        for (int i = idx; i < (int)nums.size(); ++i) {
            cur.push_back(nums[i]);
            dfs(i + 1, nums, cur, result);
            cur.pop_back();
        }
    }

public:
    static std::vector<std::vector<int>> subsets(std::vector<int> nums) {
        std::sort(nums.begin(), nums.end());
        std::vector<std::vector<int>> result;
        std::vector<int> cur;
        dfs(0, nums, cur, result);
        return result;
    }
};

int main() {
    std::vector<int> nums = {1, 2, 3};
    auto subs = LexicographicalSubsets::subsets(nums);
    assert(subs.size() == 8);

    std::cout << "subsets_lexicographic tests passed successfully.\n";
    return 0;
}
