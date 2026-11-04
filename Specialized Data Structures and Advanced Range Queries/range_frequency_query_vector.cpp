// Algorithm: Range Frequency Query via Position Vectors
// Purpose: Queries the frequency of value X in subarray [L, R] in O(log N) using index vectors.
// Time Complexity: O(log N) query, O(N) build
// Space Complexity: O(N)
// Preconditions: 1-indexed or 0-indexed bounds.

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cassert>

class RangeFreqQuery {
    std::unordered_map<int, std::vector<int>> pos;

public:
    RangeFreqQuery(const std::vector<int>& arr) {
        for (int i = 0; i < (int)arr.size(); ++i) {
            pos[arr[i]].push_back(i);
        }
    }

    int query(int l, int r, int value) {
        if (!pos.count(value)) return 0;
        const auto& vec = pos[value];
        auto right_it = std::upper_bound(vec.begin(), vec.end(), r);
        auto left_it = std::lower_bound(vec.begin(), vec.end(), l);
        return right_it - left_it;
    }
};

int main() {
    std::vector<int> a = {12, 33, 4, 56, 22, 2, 34, 33, 22, 12, 34, 56};
    RangeFreqQuery rfq(a);
    assert(rfq.query(1, 2, 4) == 1);
    assert(rfq.query(0, 11, 33) == 2);
    return 0;
}
