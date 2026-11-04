// Algorithm: Disjoint Sparse Table for O(1) Semigroup RMQ
// Purpose: Answers range queries for any associative operation (non-idempotent inclusive) in O(1) time.
// Time Complexity: O(N log N) build, O(1) query
// Space Complexity: O(N log N)
// Preconditions: Array of elements with associative operation.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

struct DisjointSparseTable {
    int n, levels;
    std::vector<std::vector<long long>> table;

    DisjointSparseTable(const std::vector<long long>& a) {
        n = a.size();
        levels = 1;
        while ((1 << levels) < n) levels++;
        table.assign(levels, std::vector<long long>(n));

        for (int i = 0; i < n; ++i) table[0][i] = a[i];

        for (int l = 1; l < levels; ++l) {
            int block_size = 1 << (l + 1);
            int half = block_size >> 1;
            for (int i = 0; i < n; i += block_size) {
                int mid = std::min(n, i + half);
                // Backward from mid - 1
                table[l][mid - 1] = a[mid - 1];
                for (int j = mid - 2; j >= i; --j) table[l][j] = table[l][j + 1] + a[j];
                // Forward from mid
                if (mid < n) {
                    table[l][mid] = a[mid];
                    int end = std::min(n, i + block_size);
                    for (int j = mid + 1; j < end; ++j) table[l][j] = table[l][j - 1] + a[j];
                }
            }
        }
    }

    long long query(int l, int r) { // [l, r] inclusive
        if (l == r) return table[0][l];
        int level = 31 - __builtin_clz(l ^ r);
        return table[level][l] + table[level][r];
    }
};

int main() {
    std::vector<long long> a = {1, 2, 3, 4, 5, 6, 7, 8};
    DisjointSparseTable dst(a);
    assert(dst.query(1, 4) == 2 + 3 + 4 + 5);
    return 0;
}
