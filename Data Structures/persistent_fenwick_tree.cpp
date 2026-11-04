// Algorithm: Partially Persistent Fenwick Tree
// Purpose: Maintains version history of point updates and allows prefix sum queries at historical version.
// Time Complexity: O(log N) per update/query
// Space Complexity: O(N + Updates * log N)
// Preconditions: Monotonically increasing version timestamps.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

struct PersistentFenwick {
    int n;
    std::vector<std::vector<std::pair<int, long long>>> history;

    PersistentFenwick(int n) : n(n), history(n + 1) {
        for (int i = 1; i <= n; ++i) history[i].push_back({0, 0});
    }

    void add(int i, long long delta, int version) {
        for (; i <= n; i += i & -i) {
            long long prev = history[i].back().second;
            history[i].push_back({version, prev + delta});
        }
    }

    long long query(int i, int version) {
        long long sum = 0;
        for (; i > 0; i -= i & -i) {
            auto it = std::upper_bound(history[i].begin(), history[i].end(),
                                       std::make_pair(version, (long long)1e18));
            --it;
            sum += it->second;
        }
        return sum;
    }
};

int main() {
    PersistentFenwick pf(5);
    pf.add(1, 10, 1);
    pf.add(2, 20, 2);
    pf.add(1, 5, 3); // index 1 becomes 15 at version 3

    assert(pf.query(2, 1) == 10);
    assert(pf.query(2, 2) == 30);
    assert(pf.query(2, 3) == 35);
    return 0;
}
