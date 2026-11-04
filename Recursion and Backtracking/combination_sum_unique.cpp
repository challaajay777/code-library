#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Combination Sum II (Single Use with Duplicates)
// Purpose: Finds all unique combinations in candidates that sum to target where each candidate may only be used once.
// Time Complexity: O(2^N) time
// Space Complexity: O(N) recursion stack
// Preconditions: All elements positive.

class CombinationSumUnique {
private:
    static void backtrack(int start, const std::vector<int>& candidates, int target,
                          std::vector<int>& cur, std::vector<std::vector<int>>& res) {
        if (target == 0) {
            res.push_back(cur);
            return;
        }
        for (int i = start; i < (int)candidates.size(); ++i) {
            if (candidates[i] > target) break;
            if (i > start && candidates[i] == candidates[i - 1]) continue;

            cur.push_back(candidates[i]);
            backtrack(i + 1, candidates, target - candidates[i], cur, res);
            cur.pop_back();
        }
    }

public:
    static std::vector<std::vector<int>> combination_sum2(std::vector<int> candidates, int target) {
        std::sort(candidates.begin(), candidates.end());
        std::vector<std::vector<int>> res;
        std::vector<int> cur;
        backtrack(0, candidates, target, cur, res);
        return res;
    }
};

int main() {
    std::vector<int> c = {10, 1, 2, 7, 6, 1, 5};
    auto res = CombinationSumUnique::combination_sum2(c, 8);
    // [1, 1, 6], [1, 2, 5], [1, 7], [2, 6] -> 4 combinations
    assert(res.size() == 4);

    std::cout << "combination_sum_unique tests passed successfully.\n";
    return 0;
}
