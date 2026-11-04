#include <iostream>
#include <tuple>
#include <cassert>

// Algorithm: Extended Euclidean Algorithm (Iterative)
// Purpose: Finds integer coefficients x and y satisfying ax + by = gcd(a, b) iteratively without recursion stack.
// Time Complexity: O(log(min(a, b))) time
// Space Complexity: O(1) auxiliary space
// Preconditions: 64-bit integer values.

class ExtendedGCDIterative {
public:
    // Returns {gcd, x, y} such that a*x + b*y = gcd
    static std::tuple<long long, long long, long long> ext_gcd(long long a, long long b) {
        long long x0 = 1, x1 = 0;
        long long y0 = 0, y1 = 1;

        while (b != 0) {
            long long q = a / b;
            long long r = a % b;
            a = b;
            b = r;

            long long nx = x0 - q * x1;
            x0 = x1;
            x1 = nx;

            long long ny = y0 - q * y1;
            y0 = y1;
            y1 = ny;
        }
        return {a, x0, y0};
    }
};

int main() {
    auto [g, x, y] = ExtendedGCDIterative::ext_gcd(30, 20);
    assert(g == 10);
    assert(30 * x + 20 * y == 10);

    auto [g2, x2, y2] = ExtendedGCDIterative::ext_gcd(35, 15);
    assert(g2 == 5);
    assert(35 * x2 + 15 * y2 == 5);

    std::cout << "extended_gcd_iterative tests passed successfully.\n";
    return 0;
}
