#include <iostream>
#include <vector>
#include <unordered_map>
#include <cassert>

// Algorithm: Split Array into Consecutive Subsequences
// Purpose: Determines if sorted array can be partitioned into consecutive subsequences of length 3 or more in O(N).
// Time Complexity: O(N) time
// Space Complexity: O(N) space for frequency hash tables
// Preconditions: Array sorted in non-decreasing order.

class SplitConsecutiveSubsequences {
public:
    static bool is_possible(const std::vector<int>& nums) {
        std::unordered_map<int, int> count, need;
        for (int x : nums) count[x]++;

        for (int x : nums) {
            if (count[x] == 0) continue;
            count[x]--;

            if (need[x] > 0) {
                need[x]--;
                need[x + 1]++;
            } else if (count[x + 1] > 0 && count[x + 2] > 0) {
                count[x + 1]--;
                count[x + 2]--;
                need[x + 3]++;
            } else {
                return false;
            }
        }
        return true;
    }
};

int main() {
    std::vector<int> a = {1, 2, 3, 3, 4, 5};
    assert(SplitConsecutiveSubsequences::is_possible(a) == true);

    std::vector<int> b = {1, 2, 3, 4, 4, 5};
    assert(SplitConsecutiveSubsequences::is_possible(b) == false);

    std::cout << "split_array_consecutive_subsequences tests passed successfully.\n";
    return 0;
}
