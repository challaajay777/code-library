#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <cassert>

// Algorithm: Longest Consecutive Sequence
// Purpose: Finds the length of the longest sequence of consecutive integers present in an unsorted array in O(N) average time.
// Time Complexity: O(N) average time
// Space Complexity: O(N) space
// Preconditions: Any sequence of integers.

class LongestConsecutiveSequence {
public:
    static int longest_consecutive(const std::vector<int>& a) {
        std::unordered_set<int> nums(a.begin(), a.end());
        int longest = 0;

        for (int x : nums) {
            // Check if x is the start of a streak
            if (nums.find(x - 1) == nums.end()) {
                int current_num = x;
                int current_streak = 1;
                while (nums.find(current_num + 1) != nums.end()) {
                    current_num++;
                    current_streak++;
                }
                longest = std::max(longest, current_streak);
            }
        }
        return longest;
    }
};

int main() {
    std::vector<int> a = {100, 4, 200, 1, 3, 2};
    // Consecutive sequence: [1, 2, 3, 4] length 4
    assert(LongestConsecutiveSequence::longest_consecutive(a) == 4);

    std::vector<int> b = {0, 3, 7, 2, 5, 8, 4, 6, 0, 1};
    // Consecutive sequence: 0 through 8, length 9
    assert(LongestConsecutiveSequence::longest_consecutive(b) == 9);

    std::cout << "longest_consecutive_sequence tests passed successfully.\n";
    return 0;
}
