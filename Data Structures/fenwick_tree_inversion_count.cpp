// Algorithm: Inversion Counting via Fenwick Tree
// Purpose: Calculates number of inversions in an array in O(N log N) using coordinate compression and BIT.
// Time Complexity: O(N log N)
// Space Complexity: O(N)
// Preconditions: Array of integers.

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

struct BITInversion {
    int n;
    std::vector<int> tree;
    BITInversion(int n) : n(n), tree(n + 1, 0) {}
    void add(int i, int delta) {
        for (; i <= n; i += i & -i) tree[i] += delta;
    }
    int query(int i) {
        int sum = 0;
        for (; i > 0; i -= i & -i) sum += tree[i];
        return sum;
    }
};

long long count_inversions(std::vector<int> a) {
    int n = a.size();
    std::vector<int> sorted_a = a;
    std::sort(sorted_a.begin(), sorted_a.end());
    sorted_a.erase(std::unique(sorted_a.begin(), sorted_a.end()), sorted_a.end());

    BITInversion bit(sorted_a.size());
    long long inv = 0;

    for (int i = n - 1; i >= 0; --i) {
        int rank = std::lower_bound(sorted_a.begin(), sorted_a.end(), a[i]) - sorted_a.begin() + 1;
        inv += bit.query(rank - 1);
        bit.add(rank, 1);
    }
    return inv;
}

int main() {
    std::vector<int> a = {8, 4, 2, 1};
    // Pairs: (8,4), (8,2), (8,1), (4,2), (4,1), (2,1) -> 6 inversions
    assert(count_inversions(a) == 6);
    return 0;
}
