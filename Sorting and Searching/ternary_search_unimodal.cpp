#include <iostream>
#include <functional>
#include <cmath>
#include <cassert>

// Algorithm: Ternary Search on Unimodal Real Function
// Purpose: Finds the global maximum or minimum of a continuous unimodal function over [L, R] up to epsilon precision.
// Time Complexity: O(log((R - L) / eps)) time (typically ~80 to 100 iterations)
// Space Complexity: O(1) auxiliary space
// Preconditions: Function strictly unimodal on [L, R].

class TernarySearchUnimodal {
public:
    static double find_maximum(double left, double right, const std::function<double(double)>& f, int iterations = 100) {
        for (int i = 0; i < iterations; ++i) {
            double m1 = left + (right - left) / 3.0;
            double m2 = right - (right - left) / 3.0;

            if (f(m1) < f(m2)) {
                left = m1;
            } else {
                right = m2;
            }
        }
        return (left + right) / 2.0;
    }
};

int main() {
    // Parabola f(x) = -(x - 3)^2 + 10, max at x = 3
    auto f = [](double x) { return -(x - 3.0) * (x - 3.0) + 10.0; };
    double opt_x = TernarySearchUnimodal::find_maximum(-10.0, 10.0, f);
    assert(std::abs(opt_x - 3.0) < 1e-6);

    std::cout << "ternary_search_unimodal tests passed successfully.\n";
    return 0;
}
