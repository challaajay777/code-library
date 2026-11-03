// Algorithm: Interval Operations
// Supports: Merging overlapping intervals, interval intersection, total covered length
// Indexing: Closed intervals [l, r]
// Complexity: O(n log n) sorting, O(n) scan
// Preconditions: Intervals have l <= r

#include <bits/stdc++.h>
using namespace std;

struct Interval {
    long long l, r;
    bool operator<(const Interval& o) const {
        if (l != o.l) return l < o.l;
        return r < o.r;
    }
};

// Merge overlapping or contiguous intervals
vector<Interval> merge_intervals(vector<Interval> intervals) {
    if (intervals.empty()) return {};
    sort(intervals.begin(), intervals.end());
    vector<Interval> merged;
    merged.push_back(intervals[0]);

    for (size_t i = 1; i < intervals.size(); ++i) {
        if (intervals[i].l <= merged.back().r) {
            merged.back().r = max(merged.back().r, intervals[i].r);
        } else {
            merged.push_back(intervals[i]);
        }
    }
    return merged;
}

// Compute total 1D continuous length covered by a set of intervals
long long total_covered_length(const vector<Interval>& intervals) {
    auto merged = merge_intervals(intervals);
    long long len = 0;
    for (const auto& iv : merged) {
        len += (iv.r - iv.l);
    }
    return len;
}

// Compute intersection of two sorted disjoint interval lists
vector<Interval> intersect_interval_lists(const vector<Interval>& A, const vector<Interval>& B) {
    vector<Interval> res;
    size_t i = 0, j = 0;
    while (i < A.size() && j < B.size()) {
        long long start = max(A[i].l, B[j].l);
        long long end = min(A[i].r, B[j].r);
        if (start <= end) {
            res.push_back({start, end});
        }
        if (A[i].r < B[j].r) {
            i++;
        } else {
            j++;
        }
    }
    return res;
}
