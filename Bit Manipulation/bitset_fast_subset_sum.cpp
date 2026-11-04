#include <iostream>
#include <vector>
#include <bitset>
#include <cassert>

// Algorithm: Bitset-Accelerated Subset Sum
// Purpose: Computes subset sum reachability up to target W in O(N * W / 64) time using std::bitset.
// Time Complexity: O(N * W / 64) time
// Space Complexity: O(W / 64) space
// Preconditions: Non-negative items; W <= 100000.

class BitsetSubsetSum {
public:
    static const int MAX_W = 100005;

    static bool can_achieve_sum(const std::vector<int>& weights, int target) {
        assert(target >= 0 && target < MAX_W);
        std::bitset<MAX_W> bs;
        bs[0] = 1;

        for (int w : weights) {
            if (w < MAX_W) {
                bs |= (bs << w);
            }
        }
        return bs[target];
    }
};

int main() {
    std::vector<int> items = {3, 34, 4, 12, 5, 2};
    assert(BitsetSubsetSum::can_achieve_sum(items, 9) == true); // 4 + 5
    assert(BitsetSubsetSum::can_achieve_sum(items, 30) == false);

    std::cout << "bitset_fast_subset_sum tests passed successfully.\n";
    return 0;
}
