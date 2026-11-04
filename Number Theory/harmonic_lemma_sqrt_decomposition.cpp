#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Harmonic Lemma (Block Square Root Division)
// Purpose: Iterates through all distinct values of floor(N / i) in contiguous blocks in O(sqrt(N)) time.
// Time Complexity: O(sqrt(N)) steps
// Space Complexity: O(1) auxiliary space
// Preconditions: N >= 1.

class HarmonicLemma {
public:
    // Returns list of intervals [L, R, floor(N / L)]
    static std::vector<std::tuple<long long, long long, long long>> get_blocks(long long n) {
        std::vector<std::tuple<long long, long long, long long>> blocks;
        for (long long l = 1, r; l <= n; l = r + 1) {
            long long val = n / l;
            r = n / val;
            blocks.emplace_back(l, r, val);
        }
        return blocks;
    }
};

int main() {
    auto blocks = HarmonicLemma::get_blocks(10);
    // For n=10:
    // l=1..1, val=10; l=2..2, val=5; l=3..3, val=3; l=4..5, val=2; l=6..10, val=1 -> 5 blocks
    assert(blocks.size() == 5);
    assert(std::get<2>(blocks.back()) == 1);

    std::cout << "harmonic_lemma_sqrt_decomposition tests passed successfully.\n";
    return 0;
}
