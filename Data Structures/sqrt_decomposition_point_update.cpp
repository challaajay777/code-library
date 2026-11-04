// Algorithm: Square Root Decomposition Point Update Range Query
// Purpose: Partitions array into blocks of size sqrt(N) for O(1) point update and O(sqrt N) range query.
// Time Complexity: O(1) update, O(sqrt N) query
// Space Complexity: O(N)
// Preconditions: Array of integers.

#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>

struct SqrtDecomp {
    int n, block_sz;
    std::vector<int> a, blocks;

    SqrtDecomp(const std::vector<int>& arr) : n(arr.size()), a(arr) {
        block_sz = std::max(1, (int)std::sqrt(n));
        blocks.assign((n + block_sz - 1) / block_sz, 0);
        for (int i = 0; i < n; ++i) {
            blocks[i / block_sz] += a[i];
        }
    }

    void update(int idx, int val) {
        blocks[idx / block_sz] += val - a[idx];
        a[idx] = val;
    }

    int query(int l, int r) {
        int sum = 0;
        int b_start = l / block_sz, b_end = r / block_sz;
        if (b_start == b_end) {
            for (int i = l; i <= r; ++i) sum += a[i];
        } else {
            for (int i = l; i < (b_start + 1) * block_sz; ++i) sum += a[i];
            for (int b = b_start + 1; b < b_end; ++b) sum += blocks[b];
            for (int i = b_end * block_sz; i <= r; ++i) sum += a[i];
        }
        return sum;
    }
};

int main() {
    std::vector<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    SqrtDecomp sd(a);
    assert(sd.query(1, 5) == 2 + 3 + 4 + 5 + 6);
    sd.update(3, 10); // replace 4 with 10
    assert(sd.query(1, 5) == 2 + 3 + 10 + 5 + 6);
    return 0;
}
