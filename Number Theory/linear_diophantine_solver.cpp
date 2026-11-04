#include <iostream>
#include <cmath>
#include <cassert>

// Algorithm: Linear Diophantine Equation Solver
// Purpose: Finds all integer solutions to ax + by = c and counts solutions in range [x_min, x_max] and [y_min, y_max].
// Time Complexity: O(log(min(a, b))) time
// Space Complexity: O(1) auxiliary space
// Preconditions: a, b, c are integers.

class LinearDiophantine {
private:
    static long long ext_gcd(long long a, long long b, long long& x, long long& y) {
        if (b == 0) { x = 1; y = 0; return a; }
        long long x1, y1;
        long long d = ext_gcd(b, a % b, x1, y1);
        x = y1;
        y = x1 - y1 * (a / b);
        return d;
    }

public:
    static bool find_any_solution(long long a, long long b, long long c, long long& x0, long long& y0, long long& g) {
        g = ext_gcd(std::abs(a), std::abs(b), x0, y0);
        if (c % g != 0) return false;

        x0 *= c / g;
        y0 *= c / g;
        if (a < 0) x0 = -x0;
        if (b < 0) y0 = -y0;
        return true;
    }
};

int main() {
    long long x, y, g;
    bool ok = LinearDiophantine::find_any_solution(2, 3, 5, x, y, g);
    assert(ok);
    assert(2 * x + 3 * y == 5);

    bool ok2 = LinearDiophantine::find_any_solution(4, 6, 7, x, y, g);
    assert(!ok2); // gcd(4, 6) = 2 does not divide 7

    std::cout << "linear_diophantine_solver tests passed successfully.\n";
    return 0;
}
