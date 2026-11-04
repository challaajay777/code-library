// Algorithm: Aliens Trick (WQS Binary Search on Cost Multiplier)
// Purpose: Removes dimension constraint (e.g. choose exactly K elements) via convex Lagrange penalty.
// Time Complexity: O(N log(Range))
// Space Complexity: O(N)
// Preconditions: Objective function is convex/concave with respect to k.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

struct WQSCheck {
    long long max_val;
    int count;
};

WQSCheck check(const std::vector<int>& prices, long long penalty) {
    int n = prices.size();
    long long hold = -prices[0] - penalty;
    long long not_hold = 0;
    int hold_count = 1;
    int not_hold_count = 0;

    for (int i = 1; i < n; ++i) {
        if (hold + prices[i] > not_hold) {
            not_hold = hold + prices[i];
            not_hold_count = hold_count;
        }
        if (not_hold - prices[i] - penalty > hold) {
            hold = not_hold - prices[i] - penalty;
            hold_count = not_hold_count + 1;
        }
    }
    return {not_hold, not_hold_count};
}

long long max_profit_k_transactions(const std::vector<int>& prices, int k) {
    int n = prices.size();
    if (n <= 1 || k == 0) return 0;
    if (k >= n / 2) {
        long long sum = 0;
        for (int i = 1; i < n; ++i) if (prices[i] > prices[i - 1]) sum += prices[i] - prices[i - 1];
        return sum;
    }

    long long low = 0, high = 1e9, ans = 0;
    while (low <= high) {
        long long mid = low + (high - low) / 2;
        auto res = check(prices, mid);
        if (res.count >= k) {
            ans = res.max_val + mid * k;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return ans;
}

int main() {
    std::vector<int> prices = {3, 2, 6, 5, 0, 3};
    assert(max_profit_k_transactions(prices, 2) == 7); // Buy at 2, sell at 6; buy at 0, sell at 3
    return 0;
}
