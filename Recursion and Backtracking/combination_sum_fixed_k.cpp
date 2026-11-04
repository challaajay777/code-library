#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Combination Sum III (K Numbers from 1 to 9)
// Purpose: Finds all valid combinations of K distinct numbers selected from 1..9 that add up to target N.
// Time Complexity: O(C(9, K)) time
// Space Complexity: O(K) recursion depth
// Preconditions: 1 <= K <= 9, 1 <= N <= 60.

class CombinationSumFixedK {
private:
    static void backtrack(int start, int k, int n, std::vector<int>& cur,
                          std::vector<std::vector<int>>& res) {
        if (cur.size() == (size_t)k && n == 0) {
            res.push_back(cur);
            return;
        }
        if (cur.size() >= (size_t)k || n < 0) return;

        for (int i = start; i <= 9; ++i) {
            if (i > n) break;
            cur.push_back(i);
            backtrack(i + 1, k, n - i, cur, res);
            cur.pop_back();
        }
    }

public:
    static std::vector<std::vector<int>> combination_sum3(int k, int n) {
        std::vector<std::vector<int>> res;
        std::vector<int> cur;
        backtrack(1, k, n, cur, res);
        return res;
    }
};

int main() {
    auto res1 = CombinationSumFixedK::combination_sum3(3, 7);
    assert(res1.size() == 1 && res1[0] == std::vector<int>({1, 2, 4}));

    auto res2 = CombinationSumFixedK::combination_sum3(3, 9);
    assert(res2.size() == 3); // [1,2,6], [1,3,5], [2,3,4]

    std::cout << "combination_sum_fixed_k tests passed successfully.\n";
    return 0;
}
