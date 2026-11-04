#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Ordinary Generating Functions (Dice Sum Probability Distribution)
// Purpose: Computes exact probability distribution of the sum of N d-sided dice using polynomial multiplication in O(N^2 * D^2).
// Time Complexity: O(N * D * (N * D)) time
// Space Complexity: O(N * D) space
// Preconditions: N >= 1, D >= 1.

class DiceSumDistribution {
public:
    static std::vector<long long> count_ways(int n, int d) {
        // Base poly: (x + x^2 + ... + x^d)
        std::vector<long long> poly(d + 1, 0);
        for (int i = 1; i <= d; ++i) poly[i] = 1;

        std::vector<long long> res = {1}; // 1 * x^0

        for (int step = 0; step < n; ++step) {
            std::vector<long long> next_poly(res.size() + d, 0);
            for (size_t i = 0; i < res.size(); ++i) {
                if (res[i] == 0) continue;
                for (int j = 1; j <= d; ++j) {
                    next_poly[i + j] += res[i];
                }
            }
            res = std::move(next_poly);
        }
        return res;
    }
};

int main() {
    // 2 standard 6-sided dice: sum range 2 to 12. Most frequent is sum 7 (6 ways)
    auto ways = DiceSumDistribution::count_ways(2, 6);
    assert(ways[7] == 6);
    assert(ways[2] == 1);
    assert(ways[12] == 1);

    std::cout << "generating_functions_dice_sum tests passed successfully.\n";
    return 0;
}
