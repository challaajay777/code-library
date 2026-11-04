#include <iostream>
#include <cmath>
#include <cassert>

// Algorithm: Fermat's Two Squares Representation
// Purpose: Determines whether N can be expressed as a sum of two squares a^2 + b^2 = N and finds a and b.
// Time Complexity: O(sqrt(N)) time
// Space Complexity: O(1) auxiliary space
// Preconditions: N >= 0.

class TwoSquaresRepresentation {
public:
    static bool can_represent(long long n) {
        for (long long d = 2; d * d <= n; ++d) {
            if (n % d == 0) {
                int count = 0;
                while (n % d == 0) {
                    count++;
                    n /= d;
                }
                if (d % 4 == 3 && count % 2 != 0) return false;
            }
        }
        return n % 4 != 3;
    }

    static std::pair<long long, long long> find_representation(long long n) {
        long long a = 0;
        while (a * a <= n) {
            long long rem = n - a * a;
            long long b = std::round(std::sqrt(rem));
            if (b * b == rem) {
                return {a, b};
            }
            a++;
        }
        return {-1, -1};
    }
};

int main() {
    assert(TwoSquaresRepresentation::can_represent(25) == true); // 3^2 + 4^2
    assert(TwoSquaresRepresentation::can_represent(7) == false);  // 7 = 3 mod 4

    auto [a, b] = TwoSquaresRepresentation::find_representation(25);
    assert(a * a + b * b == 25);

    std::cout << "sum_of_squares_two_squares tests passed successfully.\n";
    return 0;
}
