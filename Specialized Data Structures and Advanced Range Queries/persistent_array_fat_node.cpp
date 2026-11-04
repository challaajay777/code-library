// Algorithm: Persistent Array via Fat Nodes
// Purpose: Maintains versioned array with each position storing a timestamped log of modifications.
// Time Complexity: O(log V) get, O(1) set
// Space Complexity: O(N + Modifications)
// Preconditions: Version sequence.

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

class FatNodeArray {
    int n;
    std::vector<std::vector<std::pair<int, int>>> table;

public:
    FatNodeArray(int size, int init_val = 0) : n(size), table(size) {
        for (int i = 0; i < n; ++i) table[i].push_back({0, init_val});
    }

    void set(int idx, int val, int version) {
        table[idx].push_back({version, val});
    }

    int get(int idx, int version) const {
        auto it = std::upper_bound(table[idx].begin(), table[idx].end(),
                                   std::make_pair(version, (int)1e9));
        --it;
        return it->second;
    }
};

int main() {
    FatNodeArray arr(3, 0);
    arr.set(0, 10, 1);
    arr.set(1, 20, 2);
    arr.set(0, 30, 3);

    assert(arr.get(0, 1) == 10);
    assert(arr.get(0, 2) == 10);
    assert(arr.get(0, 3) == 30);
    assert(arr.get(1, 1) == 0);
    assert(arr.get(1, 2) == 20);
    return 0;
}
