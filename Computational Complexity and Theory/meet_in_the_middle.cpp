// Algorithm: Meet in the Middle (Subset Sum)
// Supports: Finding exact subset sum or closest subset sum for n <= 40
// Indexing: 0-based array of size n
// Complexity: O(n * 2^(n/2)) time, O(2^(n/2)) memory
// Preconditions: n <= 42 to fit within memory/time bounds

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

struct MeetInTheMiddle {
    // Generates all subset sums of array a
    static vector<long long> get_subset_sums(const vector<long long>& a) {
        int n = (int)a.size();
        vector<long long> sums(1 << n, 0);
        for (int mask = 0; mask < (1 << n); ++mask) {
            long long s = 0;
            for (int i = 0; i < n; ++i) {
                if ((mask >> i) & 1) {
                    s += a[i];
                }
            }
            sums[mask] = s;
        }
        return sums;
    }

    // Returns true if there exists a subset summing exactly to target
    static bool has_subset_sum(const vector<long long>& a, long long target) {
        int n = (int)a.size();
        int mid = n / 2;
        vector<long long> left(a.begin(), a.begin() + mid);
        vector<long long> right(a.begin() + mid, a.end());

        auto left_sums = get_subset_sums(left);
        auto right_sums = get_subset_sums(right);
        sort(right_sums.begin(), right_sums.end());

        for (long long s : left_sums) {
            long long rem = target - s;
            if (binary_search(right_sums.begin(), right_sums.end(), rem)) {
                return true;
            }
        }
        return false;
    }

    // Finds maximum subset sum <= target
    static long long max_subset_sum_le(const vector<long long>& a, long long target) {
        int n = (int)a.size();
        int mid = n / 2;
        vector<long long> left(a.begin(), a.begin() + mid);
        vector<long long> right(a.begin() + mid, a.end());

        auto left_sums = get_subset_sums(left);
        auto right_sums = get_subset_sums(right);
        sort(right_sums.begin(), right_sums.end());

        long long best = numeric_limits<long long>::min();
        for (long long s : left_sums) {
            if (s > target) continue;
            auto it = upper_bound(right_sums.begin(), right_sums.end(), target - s);
            if (it != right_sums.begin()) {
                --it;
                best = max(best, s + *it);
            }
        }
        return best;
    }
};
