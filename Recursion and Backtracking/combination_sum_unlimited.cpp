#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Combination Sum (Unlimited Use)
// Purpose: Finds all distinct combinations of candidates where each number may be used an unlimited number of times.
// Time Complexity: O(2^Target) worst case
// Space Complexity: O(Target) recursion stack
// Preconditions: Candidate numbers are positive and distinct; target > 0.

class CombinationSumUnlimited {
private:
    static void backtrack(int start, const std::vector<int>& candidates, int target,
                          std::vector<int>& cur, std::vector<std::vector<int>>& res) {
        if (target == 0) {
            res.push_back(cur);
            return;
        }
        for (int i = start; i < (int)candidates.size(); ++i) {
            if (candidates[i] > target) break;
            cur.push_back(candidates[i]);
            backtrack(i, candidates, target - candidates[i], cur, res);
            cur.pop_back();
        }
    }

public:
    static std::vector<std::vector<int>> combination_sum(std::vector<int> candidates, int target) {
        std::sort(candidates.begin(), candidates.end());
        std::vector<std::vector<int>> res;
        std::vector<int> cur;
        backtrack(0, candidates, target, cur, res);
        return res;
    }
};

int main() {
    std::vector<int> c = {2, 3, 6, 7};
    auto res = CombinationSumUnlimited::combination_sum(c, 7);
    // [2, 2, 3] and [7] -> 2 combinations
    assert(res.size() == 2);

    std::cout << "combination_sum_unlimited tests passed successfully.\n";
    return 0;
}
