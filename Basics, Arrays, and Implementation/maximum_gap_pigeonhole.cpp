#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cassert>

// Algorithm: Maximum Gap (Bucket Pigeonhole Algorithm)
// Purpose: Computes maximum gap between successive elements in sorted form in O(N) time and O(N) space without full comparison sorting.
// Time Complexity: O(N) time
// Space Complexity: O(N) space
// Preconditions: Array length >= 2.

class MaximumGap {
public:
    static int maximum_gap(const std::vector<int>& a) {
        int n = a.size();
        if (n < 2) return 0;

        int min_val = *std::min_element(a.begin(), a.end());
        int max_val = *std::max_element(a.begin(), a.end());
        if (min_val == max_val) return 0;

        int bucket_size = std::max(1, (max_val - min_val) / (n - 1));
        int bucket_count = (max_val - min_val) / bucket_size + 1;

        std::vector<int> b_min(bucket_count, 1e9 + 7);
        std::vector<int> b_max(bucket_count, -1e9 - 7);
        std::vector<bool> b_used(bucket_count, false);

        for (int x : a) {
            int idx = (x - min_val) / bucket_size;
            b_min[idx] = std::min(b_min[idx], x);
            b_max[idx] = std::max(b_max[idx], x);
            b_used[idx] = true;
        }

        int max_gap = 0;
        int prev_max = min_val;

        for (int i = 0; i < bucket_count; ++i) {
            if (!b_used[i]) continue;
            max_gap = std::max(max_gap, b_min[i] - prev_max);
            prev_max = b_max[i];
        }
        return max_gap;
    }
};

int main() {
    std::vector<int> a = {3, 6, 9, 1};
    // Sorted: [1, 3, 6, 9]. Max gap = 3 (between 3 and 6, or 6 and 9)
    assert(MaximumGap::maximum_gap(a) == 3);

    std::vector<int> b = {10};
    assert(MaximumGap::maximum_gap(b) == 0);

    std::cout << "maximum_gap_pigeonhole tests passed successfully.\n";
    return 0;
}
