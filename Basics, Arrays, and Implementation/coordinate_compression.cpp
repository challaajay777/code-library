// Algorithm: Coordinate Compression
// Supports: Mapping arbitrary comparable values to 0-based contiguous ranks, rank-to-value lookup
// Indexing: 0-based compressed ranks [0, unique_count - 1]
// Complexity: O(n log n) sorting, O(log n) per value query, O(1) per rank lookup
// Preconditions: Values of type T support operator<

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

template <typename T>
struct CoordinateCompression {
    vector<T> vals;

    CoordinateCompression() = default;
    explicit CoordinateCompression(const vector<T>& raw) {
        vals = raw;
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());
    }

    // Number of distinct compressed coordinates
    int size() const {
        return (int)vals.size();
    }

    // Returns the 0-based rank of val, or -1 if not present
    int get_rank(const T& val) const {
        auto it = lower_bound(vals.begin(), vals.end(), val);
        if (it != vals.end() && *it == val) {
            return (int)(it - vals.begin());
        }
        return -1;
    }

    // Returns lower_bound rank (first element >= val)
    int lower_rank(const T& val) const {
        return (int)(lower_bound(vals.begin(), vals.end(), val) - vals.begin());
    }

    // Returns original value corresponding to 0-based rank
    const T& get_value(int rank) const {
        assert(0 <= rank && rank < (int)vals.size());
        return vals[rank];
    }
};
