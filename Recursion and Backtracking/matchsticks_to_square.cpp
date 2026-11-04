#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cassert>

// Algorithm: Matchsticks to Square
// Purpose: Determines whether an array of matchstick lengths can form a square with 4 equal sides.
// Time Complexity: O(4^N) time with sorted pruning
// Space Complexity: O(N) recursion stack
// Preconditions: Matchstick lengths are positive.

class MatchsticksToSquare {
private:
    static bool dfs(int idx, const std::vector<int>& matchsticks, int target, int sides[4]) {
        if (idx == (int)matchsticks.size()) {
            return sides[0] == target && sides[1] == target && sides[2] == target && sides[3] == target;
        }

        for (int i = 0; i < 4; ++i) {
            if (sides[i] + matchsticks[idx] > target) continue;
            // Prune duplicate side values
            int j = i - 1;
            while (j >= 0 && sides[i] != sides[j]) j--;
            if (j >= 0) continue;

            sides[i] += matchsticks[idx];
            if (dfs(idx + 1, matchsticks, target, sides)) return true;
            sides[i] -= matchsticks[idx];
        }
        return false;
    }

public:
    static bool makesquare(std::vector<int> matchsticks) {
        if (matchsticks.size() < 4) return false;
        long long total = std::accumulate(matchsticks.begin(), matchsticks.end(), 0LL);
        if (total % 4 != 0) return false;
        int target = total / 4;

        std::sort(matchsticks.rbegin(), matchsticks.rend());
        if (matchsticks[0] > target) return false;

        int sides[4] = {0, 0, 0, 0};
        return dfs(0, matchsticks, target, sides);
    }
};

int main() {
    std::vector<int> m1 = {1, 1, 2, 2, 2};
    assert(MatchsticksToSquare::makesquare(m1) == true);

    std::vector<int> m2 = {3, 3, 3, 3, 4};
    assert(MatchsticksToSquare::makesquare(m2) == false);

    std::cout << "matchsticks_to_square tests passed successfully.\n";
    return 0;
}
