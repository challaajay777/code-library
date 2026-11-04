#include <iostream>
#include <cmath>
#include <cassert>

// Algorithm: Birthday Paradox Probability Calculator
// Purpose: Calculates probability that at least two individuals among K people share the same birthday across D days in O(K).
// Time Complexity: O(K) time
// Space Complexity: O(1) auxiliary space
// Preconditions: 1 <= K <= D.

class BirthdayParadox {
public:
    static double collision_probability(int k, int d = 365) {
        if (k > d) return 1.0;
        double p_no_collision = 1.0;

        for (int i = 0; i < k; ++i) {
            p_no_collision *= (double)(d - i) / d;
        }
        return 1.0 - p_no_collision;
    }
};

int main() {
    double p23 = BirthdayParadox::collision_probability(23, 365);
    // For 23 people, probability exceeds 50% (~0.507)
    assert(p23 > 0.50 && p23 < 0.51);

    std::cout << "birthday_paradox_probability tests passed successfully.\n";
    return 0;
}
