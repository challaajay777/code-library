#include <iostream>
#include <cassert>

// Algorithm: Pisano Period Modulo M
// Purpose: Finds the period length pi(M) with which the Fibonacci sequence modulo M repeats in O(M^2).
// Time Complexity: O(M^2) time
// Space Complexity: O(1) auxiliary space
// Preconditions: M >= 2.

class PisanoPeriod {
public:
    static long long get_period(long long m) {
        long long prev = 0;
        long long curr = 1;
        long long period = 0;

        for (long long i = 0; i < m * m; ++i) {
            long long temp = (prev + curr) % m;
            prev = curr;
            curr = temp;
            period++;

            if (prev == 0 && curr == 1) {
                return period;
            }
        }
        return period;
    }
};

int main() {
    assert(PisanoPeriod::get_period(2) == 3);
    assert(PisanoPeriod::get_period(3) == 8);
    assert(PisanoPeriod::get_period(10) == 60);

    std::cout << "pisano_period tests passed successfully.\n";
    return 0;
}
