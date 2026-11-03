// Algorithm: 1D Difference Array
// Supports: O(1) range additions, O(n) array restoration
// Indexing: 0-based indexing
// Complexity: O(1) per range add, O(n) prefix sum reconstruction, O(n) space
// Preconditions: Ranges [l, r] satisfy 0 <= l <= r < n

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

template <typename T>
struct DifferenceArray1D {
    int n;
    vector<T> diff;

    explicit DifferenceArray1D(int n) : n(n), diff(n + 1, 0) {}

    // Add value val to all elements in range [l, r] inclusive
    void add_range(int l, int r, T val) {
        assert(0 <= l && l <= r && r < n);
        diff[l] += val;
        diff[r + 1] -= val;
    }

    // Reconstruct the final array values after all updates
    vector<T> build() const {
        vector<T> res(n);
        T cur = 0;
        for (int i = 0; i < n; ++i) {
            cur += diff[i];
            res[i] = cur;
        }
        return res;
    }
};
