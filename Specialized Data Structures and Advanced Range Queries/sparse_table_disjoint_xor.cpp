// Algorithm: Sparse Table Range XOR Query
// Purpose: Queries XOR sum of subarray in O(1) time using prefix XOR table.
// Time Complexity: O(1) query, O(N) build
// Space Complexity: O(N)
// Preconditions: Array of integers.

#include <iostream>
#include <vector>
#include <cassert>

int main() {
    std::vector<int> a = {3, 8, 2, 6};
    std::vector<int> pref = {0};
    for (int x : a) pref.push_back(pref.back() ^ x);

    // XOR of [1, 2] is 8 ^ 2 = 10
    assert((pref[3] ^ pref[1]) == 10);
    return 0;
}
