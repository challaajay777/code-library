#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cassert>

// Algorithm: Candy Distribution Problem
// Purpose: Computes minimum candies required to distribute to children such that children with higher rating get more candies than neighbors.
// Time Complexity: O(N) time with two passes
// Space Complexity: O(N) auxiliary space
// Preconditions: Non-empty ratings array.

class CandyDistribution {
public:
    static int candy(const std::vector<int>& ratings) {
        int n = ratings.size();
        std::vector<int> candies(n, 1);

        // Left-to-right pass
        for (int i = 1; i < n; ++i) {
            if (ratings[i] > ratings[i - 1]) {
                candies[i] = candies[i - 1] + 1;
            }
        }

        // Right-to-left pass
        for (int i = n - 2; i >= 0; --i) {
            if (ratings[i] > ratings[i + 1]) {
                candies[i] = std::max(candies[i], candies[i + 1] + 1);
            }
        }

        return std::accumulate(candies.begin(), candies.end(), 0);
    }
};

int main() {
    std::vector<int> r1 = {1, 0, 2};
    assert(CandyDistribution::candy(r1) == 5); // [2, 1, 2]

    std::vector<int> r2 = {1, 2, 2};
    assert(CandyDistribution::candy(r2) == 4); // [1, 2, 1]

    std::cout << "candy_distribution tests passed successfully.\n";
    return 0;
}
