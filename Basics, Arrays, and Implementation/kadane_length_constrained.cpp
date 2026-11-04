#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <cassert>

// Algorithm: Length-Constrained Maximum Subarray Sum
// Purpose: Finds the maximum subarray sum among all subarrays of length between L and R inclusive using monotonic deque.
// Time Complexity: O(N) time
// Space Complexity: O(N) space for prefix sums and deque
// Preconditions: 1 <= L <= R <= N.

class LengthConstrainedKadane {
public:
    static long long max_subarray_sum(const std::vector<long long>& a, int min_len, int max_len) {
        int n = a.size();
        assert(min_len >= 1 && min_len <= max_len && max_len <= n);

        std::vector<long long> pref(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            pref[i + 1] = pref[i] + a[i];
        }

        std::deque<int> dq;
        long long best = -2e18;

        for (int i = min_len; i <= n; ++i) {
            // Push pref[i - min_len] into deque maintaining monotonic increasing order
            int add_idx = i - min_len;
            while (!dq.empty() && pref[dq.back()] >= pref[add_idx]) {
                dq.pop_back();
            }
            dq.push_back(add_idx);

            // Pop elements that are too far away (length > max_len)
            while (!dq.empty() && dq.front() < i - max_len) {
                dq.pop_front();
            }

            if (!dq.empty()) {
                best = std::max(best, pref[i] - pref[dq.front()]);
            }
        }
        return best;
    }
};

int main() {
    std::vector<long long> a = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    // Lengths 2 to 4: subarray [4, -1, 2, 1] len 4 sum = 6
    assert(LengthConstrainedKadane::max_subarray_sum(a, 2, 4) == 6);

    std::vector<long long> b = {1, 2, 3, 4, 5};
    assert(LengthConstrainedKadane::max_subarray_sum(b, 2, 2) == 9); // [4, 5]

    std::cout << "kadane_length_constrained tests passed successfully.\n";
    return 0;
}
