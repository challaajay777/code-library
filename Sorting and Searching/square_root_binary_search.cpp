#include <iostream>
#include <cmath>
#include <cassert>

// Algorithm: Integer and Real Square Root via Binary Search
// Purpose: Computes floor(sqrt(X)) and high-precision sqrt(X) using binary search without standard floating-point functions.
// Time Complexity: O(log X) integer sqrt, O(iterations) floating-point sqrt
// Space Complexity: O(1) auxiliary space
// Preconditions: X >= 0.

class SqrtBinarySearch {
public:
    static long long isqrt(long long x) {
        assert(x >= 0);
        if (x <= 1) return x;

        long long low = 1, high = x / 2;
        long long ans = 1;

        while (low <= high) {
            long long mid = low + (high - low) / 2;
            if (mid <= x / mid) {
                ans = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return ans;
    }

    static double fsqrt(double x, int iterations = 80) {
        assert(x >= 0.0);
        if (x == 0.0) return 0.0;
        double low = (x < 1.0) ? x : 1.0;
        double high = (x < 1.0) ? 1.0 : x;

        for (int i = 0; i < iterations; ++i) {
            double mid = low + (high - low) / 2.0;
            if (mid * mid <= x) {
                low = mid;
            } else {
                high = mid;
            }
        }
        return (low + high) / 2.0;
    }
};

int main() {
    assert(SqrtBinarySearch::isqrt(16) == 4);
    assert(SqrtBinarySearch::isqrt(8) == 2);
    assert(SqrtBinarySearch::isqrt(2147395599LL) == 46339LL);

    assert(std::abs(SqrtBinarySearch::fsqrt(2.0) - 1.41421356) < 1e-6);

    std::cout << "square_root_binary_search tests passed successfully.\n";
    return 0;
}
