#include <iostream>
#include <vector>
#include <random>
#include <cassert>

// Algorithm: Reservoir Sampling (Algorithm R)
// Purpose: Randomly chooses K items with uniform probability from a stream of unknown size in single pass O(N).
// Time Complexity: O(N) time single pass
// Space Complexity: O(K) space
// Preconditions: K >= 1.

class ReservoirSampling {
public:
    static std::vector<int> sample_k(const std::vector<int>& stream, int k, unsigned seed = 1337) {
        int n = stream.size();
        assert(k <= n && k >= 1);
        std::vector<int> reservoir(stream.begin(), stream.begin() + k);
        std::mt19937 rng(seed);

        for (int i = k; i < n; ++i) {
            int j = rng() % (i + 1);
            if (j < k) {
                reservoir[j] = stream[i];
            }
        }
        return reservoir;
    }
};

int main() {
    std::vector<int> stream = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto sample = ReservoirSampling::sample_k(stream, 4);
    assert(sample.size() == 4);

    std::cout << "reservoir_sampling tests passed successfully.\n";
    return 0;
}
