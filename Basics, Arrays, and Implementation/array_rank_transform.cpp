#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Dense Array Rank Transform
// Purpose: Replaces each element with its 1-based rank (ties receiving the same rank) in O(N log N) time.
// Time Complexity: O(N log N) time
// Space Complexity: O(N) auxiliary space
// Preconditions: Vector of comparable elements.

class ArrayRankTransform {
public:
    template <typename T>
    static std::vector<int> rank_transform(const std::vector<T>& a) {
        std::vector<T> sorted_unique = a;
        std::sort(sorted_unique.begin(), sorted_unique.end());
        sorted_unique.erase(std::unique(sorted_unique.begin(), sorted_unique.end()), sorted_unique.end());

        std::vector<int> ranks(a.size());
        for (size_t i = 0; i < a.size(); ++i) {
            auto it = std::lower_bound(sorted_unique.begin(), sorted_unique.end(), a[i]);
            ranks[i] = std::distance(sorted_unique.begin(), it) + 1;
        }
        return ranks;
    }
};

int main() {
    std::vector<int> a = {40, 10, 20, 30};
    auto ranks = ArrayRankTransform::rank_transform(a);
    std::vector<int> expected = {4, 1, 2, 3};
    assert(ranks == expected);

    std::vector<int> b = {100, 100, 100};
    auto ranks2 = ArrayRankTransform::rank_transform(b);
    std::vector<int> expected2 = {1, 1, 1};
    assert(ranks2 == expected2);

    std::cout << "array_rank_transform tests passed successfully.\n";
    return 0;
}
