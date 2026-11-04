#include <iostream>
#include <vector>
#include <cstdint>
#include <cassert>

// Algorithm: Gosper's Hack (K-Element Subsets)
// Purpose: Generates all bitmasks of size N containing exactly K set bits in lexicographic order in O(1) per subset.
// Time Complexity: O(C(N, K)) time
// Space Complexity: O(1) auxiliary space
// Preconditions: 1 <= K <= N <= 62.

class GosperHack {
public:
    static std::vector<uint64_t> generate_k_subsets(int n, int k) {
        if (k == 0) return {0};
        if (k > n) return {};

        std::vector<uint64_t> result;
        uint64_t mask = (1ULL << k) - 1ULL;
        uint64_t limit = (1ULL << n);

        while (mask < limit) {
            result.push_back(mask);

            // Gosper's hack step
            uint64_t c = mask & -mask;
            uint64_t r = mask + c;
            mask = (((r ^ mask) >> 2) / c) | r;
        }
        return result;
    }
};

int main() {
    // Generate all subsets of size 4 choose 2 -> 6 subsets
    auto subsets = GosperHack::generate_k_subsets(4, 2);
    assert(subsets.size() == 6);
    // Subsets: 0011(3), 0101(5), 0110(6), 1001(9), 1010(10), 1100(12)
    std::vector<uint64_t> expected = {3, 5, 6, 9, 10, 12};
    assert(subsets == expected);

    std::cout << "gosper_hack_k_subsets tests passed successfully.\n";
    return 0;
}
