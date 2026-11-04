#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Bucket Sort for Uniform Floating-Point Numbers
// Purpose: Sorts uniformly distributed floating-point numbers in range [0, 1) in linear expected time.
// Time Complexity: O(N) expected time, O(N^2) worst case
// Space Complexity: O(N) space
// Preconditions: All elements 0.0 <= x < 1.0.

class BucketSortFloating {
public:
    static void sort(std::vector<double>& a) {
        int n = a.size();
        if (n <= 1) return;

        std::vector<std::vector<double>> buckets(n);
        for (double x : a) {
            assert(x >= 0.0 && x < 1.0);
            int idx = static_cast<int>(n * x);
            buckets[idx].push_back(x);
        }

        for (int i = 0; i < n; ++i) {
            std::sort(buckets[i].begin(), buckets[i].end());
        }

        int cur = 0;
        for (int i = 0; i < n; ++i) {
            for (double x : buckets[i]) {
                a[cur++] = x;
            }
        }
    }
};

int main() {
    std::vector<double> a = {0.897, 0.565, 0.656, 0.1234, 0.665, 0.3434};
    BucketSortFloating::sort(a);
    for (size_t i = 1; i < a.size(); ++i) {
        assert(a[i] >= a[i - 1]);
    }

    std::cout << "bucket_sort_floating tests passed successfully.\n";
    return 0;
}
