#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Inversion Counting via Fenwick Tree
// Purpose: Calculates total inversions in O(N log N) using coordinate compression and a Fenwick tree (Binary Indexed Tree).
// Time Complexity: O(N log N) time
// Space Complexity: O(N) space
// Preconditions: Arbitrary integer array.

class FenwickInversions {
private:
    int n;
    std::vector<int> tree;

    void update(int i, int delta) {
        for (; i <= n; i += i & -i) tree[i] += delta;
    }

    int query(int i) const {
        int sum = 0;
        for (; i > 0; i -= i & -i) sum += tree[i];
        return sum;
    }

public:
    explicit FenwickInversions(int sz) : n(sz), tree(sz + 1, 0) {}

    static long long count(const std::vector<long long>& a) {
        int n = a.size();
        if (n <= 1) return 0;

        // Coordinate compression
        std::vector<long long> sorted_unique = a;
        std::sort(sorted_unique.begin(), sorted_unique.end());
        sorted_unique.erase(std::unique(sorted_unique.begin(), sorted_unique.end()), sorted_unique.end());

        FenwickInversions ft(sorted_unique.size());
        long long inv_count = 0;

        for (int i = n - 1; i >= 0; --i) {
            int rank = std::lower_bound(sorted_unique.begin(), sorted_unique.end(), a[i]) - sorted_unique.begin() + 1;
            inv_count += ft.query(rank - 1);
            ft.update(rank, 1);
        }
        return inv_count;
    }
};

int main() {
    std::vector<long long> a = {2, 4, 1, 3, 5};
    // (2,1), (4,1), (4,3) -> 3 inversions
    assert(FenwickInversions::count(a) == 3);

    std::vector<long long> b = {5, 4, 3, 2, 1};
    assert(FenwickInversions::count(b) == 10);

    std::cout << "inversion_count_fenwick tests passed successfully.\n";
    return 0;
}
