#include <iostream>
#include <cassert>

// Algorithm: Floor Sum of Arithmetic Progression
// Purpose: Computes sum_{i=0}^{n-1} floor((a*i + b) / c) in O(log c) time using Euclidean-like reduction.
// Time Complexity: O(log c) time
// Space Complexity: O(log c) recursion stack
// Preconditions: n, c > 0; a, b >= 0.

class FloorSum {
public:
    static long long floor_sum(long long n, long long m, long long a, long long b) {
        long long ans = 0;
        if (a >= m) {
            ans += (n - 1) * n / 2 * (a / m);
            a %= m;
        }
        if (b >= m) {
            ans += n * (b / m);
            b %= m;
        }

        long long y_max = (a * n + b) / m;
        long long x_max = y_max * m - b;
        if (y_max == 0) return ans;

        ans += (n - (x_max + a - 1) / a) * y_max;
        ans += floor_sum(y_max, a, m, (a - x_max % a) % a);
        return ans;
    }
};

int main() {
    // sum_{i=0}^3 floor((2*i + 1) / 3):
    // i=0: 0, i=1: 1, i=2: 1, i=3: 2 -> total = 4
    assert(FloorSum::floor_sum(4, 3, 2, 1) == 4);

    std::cout << "floor_sum_ap tests passed successfully.\n";
    return 0;
}
