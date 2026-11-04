// Algorithm: Russian Doll Envelopes 2D LIS
// Purpose: Finds maximum number of envelopes that can fit inside one another (w1 < w2 and h1 < h2).
// Time Complexity: O(N log N)
// Space Complexity: O(N)
// Preconditions: List of (width, height) pairs.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

int max_envelopes(std::vector<std::pair<int, int>>& envs) {
    std::sort(envs.begin(), envs.end(), [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
        if (a.first != b.first) return a.first < b.first;
        return a.second > b.second; // descending on height to avoid picking same width
    });

    std::vector<int> tails;
    for (const auto& p : envs) {
        int h = p.second;
        auto it = std::lower_bound(tails.begin(), tails.end(), h);
        if (it == tails.end()) tails.push_back(h);
        else *it = h;
    }
    return tails.size();
}

int main() {
    std::vector<std::pair<int, int>> envs = {{5, 4}, {6, 4}, {6, 7}, {2, 3}};
    assert(max_envelopes(envs) == 3); // [2,3] => [5,4] => [6,7]
    return 0;
}
