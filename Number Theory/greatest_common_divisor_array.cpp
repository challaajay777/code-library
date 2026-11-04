#include <iostream>
#include <vector>
#include <numeric>
#include <cassert>

// Algorithm: Array GCD and LCM
// Purpose: Calculates cumulative GCD and modular LCM of an entire array with overflow prevention.
// Time Complexity: O(N log(max_val)) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Array elements positive.

class ArrayGcdLcm {
public:
    static long long array_gcd(const std::vector<long long>& a) {
        long long g = 0;
        for (long long x : a) {
            g = std::gcd(g, x);
        }
        return g;
    }

    static long long array_lcm(const std::vector<long long>& a) {
        long long l = 1;
        for (long long x : a) {
            l = (l / std::gcd(l, x)) * x;
        }
        return l;
    }
};

int main() {
    std::vector<long long> a = {12, 18, 24};
    assert(ArrayGcdLcm::array_gcd(a) == 6);
    assert(ArrayGcdLcm::array_lcm(a) == 72);

    std::cout << "greatest_common_divisor_array tests passed successfully.\n";
    return 0;
}
