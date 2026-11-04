#include <iostream>
#include <cassert>

// Algorithm: Prefix and Range XOR Sum (1 to N)
// Purpose: Calculates the XOR sum of all integers from 1 to N in O(1) time using periodicity of 4, and range XOR sum [L, R].
// Time Complexity: O(1) time
// Space Complexity: O(1) auxiliary space
// Preconditions: 0 <= L <= R.

class RangeXorSum {
public:
    // Computes 1 ^ 2 ^ ... ^ n
    static long long xor_1_to_n(long long n) {
        if (n < 0) return 0;
        long long rem = n % 4;
        if (rem == 0) return n;
        if (rem == 1) return 1;
        if (rem == 2) return n + 1;
        return 0;
    }

    // Computes L ^ (L + 1) ^ ... ^ R
    static long long xor_range(long long l, long long r) {
        assert(l <= r);
        return xor_1_to_n(r) ^ xor_1_to_n(l - 1);
    }
};

int main() {
    assert(RangeXorSum::xor_1_to_n(5) == (1 ^ 2 ^ 3 ^ 4 ^ 5));
    assert(RangeXorSum::xor_1_to_n(6) == (1 ^ 2 ^ 3 ^ 4 ^ 5 ^ 6));
    assert(RangeXorSum::xor_range(3, 6) == (3 ^ 4 ^ 5 ^ 6));

    std::cout << "bitwise_xor_range_1_to_n tests passed successfully.\n";
    return 0;
}
