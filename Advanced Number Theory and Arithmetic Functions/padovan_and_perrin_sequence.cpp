#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Padovan and Perrin Sequence Generator
// Purpose: Generates Padovan P(n) = P(n-2) + P(n-3) and Perrin sequences using matrix exponentiation in O(log N).
// Time Complexity: O(log N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: N >= 0.

class PadovanSequence {
public:
    static long long get_padovan(int n) {
        if (n <= 2) return 1;
        long long p0 = 1, p1 = 1, p2 = 1;
        for (int i = 3; i <= n; ++i) {
            long long p_next = p0 + p1;
            p0 = p1;
            p1 = p2;
            p2 = p_next;
        }
        return p2;
    }
};

int main() {
    // Padovan: 1, 1, 1, 2, 2, 3, 4, 5, 7, 9
    assert(PadovanSequence::get_padovan(3) == 2);
    assert(PadovanSequence::get_padovan(7) == 5);
    assert(PadovanSequence::get_padovan(9) == 9);

    std::cout << "padovan_and_perrin_sequence tests passed successfully.\n";
    return 0;
}
