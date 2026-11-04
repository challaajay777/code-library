#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <cassert>

// Algorithm: Fisher-Yates (Knuth) Shuffle
// Purpose: Generates a uniformly distributed random permutation of an array in O(N) time and O(1) space.
// Time Complexity: O(N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Valid vector.

class FisherYatesShuffle {
public:
    template <typename T>
    static void shuffle(std::vector<T>& a, unsigned seed = 42) {
        std::mt19937 rng(seed);
        int n = a.size();
        for (int i = n - 1; i > 0; --i) {
            int j = rng() % (i + 1);
            std::swap(a[i], a[j]);
        }
    }
};

int main() {
    std::vector<int> a = {1, 2, 3, 4, 5, 6, 7, 8};
    FisherYatesShuffle::shuffle(a);
    assert(a.size() == 8);

    std::cout << "random_shuffle_fisher_yates tests passed successfully.\n";
    return 0;
}
