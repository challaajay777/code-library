#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Prefix and Suffix Extrema Arrays
// Purpose: Computes prefix and suffix min/max arrays to query extrema of array excluding any single element or subsegment in O(1).
// Time Complexity: O(N) preprocessing, O(1) query
// Space Complexity: O(N) auxiliary space
// Preconditions: Non-empty array.

class PrefixSuffixExtrema {
private:
    int n;
    std::vector<long long> pref_max, suff_max;
    std::vector<long long> pref_min, suff_min;

public:
    explicit PrefixSuffixExtrema(const std::vector<long long>& a) : n(a.size()) {
        assert(n > 0);
        pref_max.resize(n);
        suff_max.resize(n);
        pref_min.resize(n);
        suff_min.resize(n);

        pref_max[0] = pref_min[0] = a[0];
        for (int i = 1; i < n; ++i) {
            pref_max[i] = std::max(pref_max[i - 1], a[i]);
            pref_min[i] = std::min(pref_min[i - 1], a[i]);
        }

        suff_max[n - 1] = suff_min[n - 1] = a[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            suff_max[i] = std::max(suff_max[i + 1], a[i]);
            suff_min[i] = std::min(suff_min[i + 1], a[i]);
        }
    }

    // Queries max element of array excluding index i (0 <= i < n)
    long long query_max_excluding(int i) const {
        assert(n >= 2 && i >= 0 && i < n);
        if (i == 0) return suff_max[1];
        if (i == n - 1) return pref_max[n - 2];
        return std::max(pref_max[i - 1], suff_max[i + 1]);
    }

    // Queries min element of array excluding range [l, r]
    long long query_min_excluding_range(int l, int r) const {
        assert(l <= r && (l > 0 || r < n - 1));
        if (l == 0) return suff_min[r + 1];
        if (r == n - 1) return pref_min[l - 1];
        return std::min(pref_min[l - 1], suff_min[r + 1]);
    }
};

int main() {
    std::vector<long long> a = {5, 2, 8, 1, 9, 3};
    PrefixSuffixExtrema pse(a);

    assert(pse.query_max_excluding(4) == 8); // exclude 9 -> max is 8
    assert(pse.query_max_excluding(2) == 9); // exclude 8 -> max is 9
    assert(pse.query_min_excluding_range(2, 3) == 2); // exclude [8, 1] -> min is 2

    std::cout << "prefix_maximums_and_minimums tests passed successfully.\n";
    return 0;
}
