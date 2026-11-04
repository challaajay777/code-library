#include <iostream>
#include <cmath>
#include <cassert>

// Algorithm: Coupon Collector's Expected Value and Variance
// Purpose: Calculates expected number of draws and variance to collect all N distinct coupons in O(N).
// Time Complexity: O(N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: N >= 1.

class CouponCollector {
public:
    static double expected_draws(int n) {
        double exp = 0.0;
        for (int i = 1; i <= n; ++i) {
            exp += (double)n / i;
        }
        return exp;
    }

    static double variance_draws(int n) {
        double var = 0.0;
        for (int i = 1; i <= n; ++i) {
            double p = (double)i / n;
            var += (1.0 - p) / (p * p);
        }
        return var;
    }
};

int main() {
    // For n=1: expected = 1.0
    assert(std::abs(CouponCollector::expected_draws(1) - 1.0) < 1e-6);
    // For n=2: 1 + 2 = 3.0
    assert(std::abs(CouponCollector::expected_draws(2) - 3.0) < 1e-6);

    std::cout << "coupon_collector_expected_value tests passed successfully.\n";
    return 0;
}
