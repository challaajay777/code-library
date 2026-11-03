// Algorithm: Maximum Subarray Sum (Kadane's Algorithm)
// Supports: Maximum contiguous subarray sum, subarray indices, maximum circular subarray sum
// Indexing: 0-based array indexing
// Complexity: O(n) time, O(1) auxiliary space
// Preconditions: Array is non-empty

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

struct SubarrayResult {
    long long sum;
    int left, right; // inclusive [left, right]
};

// Standard Kadane's algorithm tracking best subarray sum and bounds
SubarrayResult kadane(const vector<long long>& a) {
    int n = (int)a.size();
    assert(n > 0);
    long long max_so_far = a[0];
    long long current_max = a[0];
    int start = 0, best_l = 0, best_r = 0;

    for (int i = 1; i < n; ++i) {
        if (current_max + a[i] < a[i]) {
            current_max = a[i];
            start = i;
        } else {
            current_max += a[i];
        }
        if (current_max > max_so_far) {
            max_so_far = current_max;
            best_l = start;
            best_r = i;
        }
    }
    return {max_so_far, best_l, best_r};
}

// Maximum circular subarray sum (wraps around array boundaries)
long long max_circular_subarray_sum(const vector<long long>& a) {
    int n = (int)a.size();
    assert(n > 0);
    long long total_sum = 0;
    long long cur_max = 0, max_sum = a[0];
    long long cur_min = 0, min_sum = a[0];

    for (int i = 0; i < n; ++i) {
        total_sum += a[i];
        cur_max = max(a[i], cur_max + a[i]);
        max_sum = max(max_sum, cur_max);

        cur_min = min(a[i], cur_min + a[i]);
        min_sum = min(min_sum, cur_min);
    }

    // If all numbers are negative, max_sum is the single largest negative number
    if (max_sum < 0) return max_sum;
    return max(max_sum, total_sum - min_sum);
}
