#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Subsets II (Subsets with Duplicates)
// Purpose: Generates all unique subsets from an array containing duplicate elements in O(N * 2^N).
// Time Complexity: O(N * 2^N) time
// Space Complexity: O(N) recursion depth
// Preconditions: General array of elements.

class SubsetsWithDuplicates {
private:
    static void dfs(int idx, const std::vector<int>& nums, std::vector<int>& cur,
                    std::vector<std::vector<int>>& result) {
        result.push_back(cur);
        for (int i = idx; i < (int)nums.size(); ++i) {
            if (i > idx && nums[i] == nums[i - 1]) continue;
            cur.push_back(nums[i]);
            dfs(i + 1, nums, cur, result);
            cur.pop_back();
        }
    }

public:
    static std::vector<std::vector<int>> subsets_with_dup(std::vector<int> nums) {
        std::sort(nums.begin(), nums.end());
        std::vector<std::vector<int>> result;
        std::vector<int> cur;
        dfs(0, nums, cur, result);
        return result;
    }
};

int main() {
    std::vector<int> nums = {1, 2, 2};
    auto subs = SubsetsWithDuplicates::subsets_with_dup(nums);
    // Unique subsets: [], [1], [1, 2], [1, 2, 2], [2], [2, 2] -> total 6
    assert(subs.size() == 6);

    std::cout << "subsets_with_duplicates tests passed successfully.\n";
    return 0;
}
