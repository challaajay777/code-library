#include <iostream>
#include <cmath>
#include <cassert>

// Algorithm: 1D Random Walk Absorption (Gambler's Ruin)
// Purpose: Computes probability of hitting upper absorption boundary B before lower boundary 0 starting at position k in O(1).
// Time Complexity: O(log B) time
// Space Complexity: O(1) auxiliary space
// Preconditions: 0 <= k <= B; 0 < p < 1.

class GamblersRuin {
public:
    static double probability_reach_B(int k, int B, double p) {
        assert(k >= 0 && k <= B);
        if (k == 0) return 0.0;
        if (k == B) return 1.0;

        if (std::abs(p - 0.5) < 1e-9) {
            return (double)k / B; // Fair game
        }
        double q = 1.0 - p;
        double ratio = q / p;
        return (1.0 - std::pow(ratio, k)) / (1.0 - std::pow(ratio, B));
    }
};

int main() {
    // Fair walk from k=2, B=4 -> prob = 0.5
    assert(std::abs(GamblersRuin::probability_reach_B(2, 4, 0.5) - 0.5) < 1e-6);

    std::cout << "random_walk_1d_absorption tests passed successfully.\n";
    return 0;
}
