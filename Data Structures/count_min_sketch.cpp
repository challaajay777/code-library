// Algorithm: Count-Min Sketch Frequency Estimator
// Purpose: Estimates frequencies of streaming data items in sublinear space with guaranteed error bounds.
// Time Complexity: O(Depth) per update and query
// Space Complexity: O(Width * Depth)
// Preconditions: Integer or string stream elements.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

class CountMinSketch {
    int w, d;
    std::vector<std::vector<int>> table;

    int hash(int item, int i) const {
        return (1LL * item * (10007 + i * 31) + 1337) % w;
    }

public:
    CountMinSketch(int width = 1000, int depth = 5) : w(width), d(depth), table(depth, std::vector<int>(width, 0)) {}

    void add(int item, int count = 1) {
        for (int i = 0; i < d; ++i) {
            table[i][hash(item, i)] += count;
        }
    }

    int estimate(int item) const {
        int min_count = 1e9;
        for (int i = 0; i < d; ++i) {
            min_count = std::min(min_count, table[i][hash(item, i)]);
        }
        return min_count;
    }
};

int main() {
    CountMinSketch cms(100, 4);
    cms.add(42, 5);
    cms.add(42, 3);
    cms.add(10, 2);

    assert(cms.estimate(42) >= 8);
    assert(cms.estimate(10) >= 2);
    return 0;
}
