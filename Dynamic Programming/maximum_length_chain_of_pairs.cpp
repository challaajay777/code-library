// Algorithm: Maximum Length Chain of Pairs DP
// Purpose: Finds the longest chain of pairs (a, b) such that pair[i].b < pair[i+1].a.
// Time Complexity: O(N log N)
// Space Complexity: O(N)
// Preconditions: Pairs with first < second.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

int find_longest_chain(std::vector<std::pair<int, int>>& pairs) {
    std::sort(pairs.begin(), pairs.end(), [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
        return a.second < b.second;
    });

    int count = 0;
    int cur_end = -1e9;
    for (const auto& p : pairs) {
        if (p.first > cur_end) {
            count++;
            cur_end = p.second;
        }
    }
    return count;
}

int main() {
    std::vector<std::pair<int, int>> pairs = {{1, 2}, {2, 3}, {3, 4}};
    assert(find_longest_chain(pairs) == 2); // {1, 2} and {3, 4}
    return 0;
}
