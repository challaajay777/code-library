// Algorithm: Longest Increasing Subsequence (LIS)
// Supports: Strict and non-decreasing LIS in O(n log n), optimal subsequence reconstruction
// Indexing: 0-based array indices [0, n - 1]
// Complexity: O(n log n) time, O(n) memory
// Preconditions: Comparable elements supporting operator<

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

template <typename T>
struct LIS {
    // Computes strictly increasing LIS. Returns indices of elements forming the LIS.
    static vector<int> solve_strict(const vector<T>& a) {
        int n = (int)a.size();
        if (n == 0) return {};

        vector<T> tails;
        vector<int> tail_idx;
        vector<int> parent(n, -1);

        for (int i = 0; i < n; ++i) {
            auto it = lower_bound(tails.begin(), tails.end(), a[i]);
            int pos = (int)(it - tails.begin());

            if (it == tails.end()) {
                tails.push_back(a[i]);
                tail_idx.push_back(i);
            } else {
                *it = a[i];
                tail_idx[pos] = i;
            }

            if (pos > 0) {
                parent[i] = tail_idx[pos - 1];
            }
        }

        vector<int> res;
        for (int cur = tail_idx.back(); cur != -1; cur = parent[cur]) {
            res.push_back(cur);
        }
        reverse(res.begin(), res.end());
        return res;
    }

    // Computes length of non-decreasing LIS using upper_bound
    static int length_non_decreasing(const vector<T>& a) {
        vector<T> tails;
        for (const auto& x : a) {
            auto it = upper_bound(tails.begin(), tails.end(), x);
            if (it == tails.end()) {
                tails.push_back(x);
            } else {
                *it = x;
            }
        }
        return (int)tails.size();
    }
};
