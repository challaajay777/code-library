#include <iostream>
#include <cmath>
#include <cassert>

// Algorithm: Pell's Equation Solver (x^2 - D*y^2 = 1)
// Purpose: Finds the fundamental smallest non-trivial integer solution (x, y) to x^2 - D*y^2 = 1 using continued fractions of sqrt(D).
// Time Complexity: O(period * log D) time
// Space Complexity: O(1) auxiliary space
// Preconditions: D is positive and not a perfect square.

class PellEquation {
public:
    static std::pair<unsigned __int128, unsigned __int128> find_fundamental_solution(long long D) {
        long long a0 = std::sqrt(D);
        assert(a0 * a0 != D); // Must not be square

        long long m = 0;
        long long d = 1;
        long long a = a0;

        unsigned __int128 num1 = 1, num = a0;
        unsigned __int128 den1 = 0, den = 1;

        while (num * num - (unsigned __int128)D * den * den != 1) {
            m = d * a - m;
            d = (D - m * m) / d;
            a = (a0 + m) / d;

            unsigned __int128 next_num = a * num + num1;
            num1 = num;
            num = next_num;

            unsigned __int128 next_den = a * den + den1;
            den1 = den;
            den = next_den;
        }
        return {num, den};
    }
};

int main() {
    // For D = 2: x^2 - 2y^2 = 1 -> (3, 2): 3^2 - 2*2^2 = 9 - 8 = 1
    auto [x2, y2] = PellEquation::find_fundamental_solution(2);
    assert(x2 == 3 && y2 == 2);

    // For D = 3: x^2 - 3y^2 = 1 -> (2, 1): 4 - 3 = 1
    auto [x3, y3] = PellEquation::find_fundamental_solution(3);
    assert(x3 == 2 && y3 == 1);

    std::cout << "pell_equation_solver tests passed successfully.\n";
    return 0;
}
