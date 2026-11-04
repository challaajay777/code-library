#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Minimum XOR Pair in Array
// Purpose: Finds two distinct elements in array with minimum XOR value in O(N log N) by sorting adjacent elements.
// Time Complexity: O(N log N) time
// Space Complexity: O(1) auxiliary space beyond sort
// Preconditions: Array length >= 2.

class MinimumXorPair {
public:
    static int min_xor_pair(std::vector<int>& a) {
        assert(a.size() >= 2);
        std::sort(a.begin(), a.end());
        int min_xor = 2e9;

        for (size_t i = 0; i + 1 < a.size(); ++i) {
            min_xor = std::min(min_xor, a[i] ^ a[i + 1]);
        }
        return min_xor;
    }
};

int main() {
    std::vector<int> a = {9, 5, 3};
    assert(MinimumXorPair::min_xor_pair(a) == 6); // 5 ^ 3 = 6

    std::vector<int> b = {1, 2, 3, 4, 5};
    assert(MinimumXorPair::min_xor_pair(b) == 1); // 2 ^ 3 = 1

    std::cout << "minimum_xor_pair tests passed successfully.\n";
    return 0;
}
