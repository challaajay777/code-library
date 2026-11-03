// Algorithm: 1D Prefix Sums
// Supports: Static range sum queries in O(1)
// Indexing: 0-based input, 1-based internal prefix table
// Complexity: O(n) preprocessing, O(1) per range sum query, O(n) space
// Preconditions: Range [l, r] satisfies 0 <= l <= r < n

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

template <typename T>
struct PrefixSums1D {
    int n;
    vector<T> pref;

    PrefixSums1D() : n(0) {}
    explicit PrefixSums1D(const vector<T>& a) : n((int)a.size()), pref(n + 1, 0) {
        for (int i = 0; i < n; ++i) {
            pref[i + 1] = pref[i] + a[i];
        }
    }

    // Returns sum of a[l..r] inclusive
    T query(int l, int r) const {
        assert(0 <= l && l <= r && r < n);
        return pref[r + 1] - pref[l];
    }
};
