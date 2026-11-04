#include <iostream>
#include <cassert>

// Algorithm: Count Total Set Bits from 1 to N
// Purpose: Calculates the total number of 1-bits across all integers from 1 through N in O(log N) time.
// Time Complexity: O(log N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: N >= 0.

class CountSetBits1ToN {
public:
    static long long count_bits(long long n) {
        if (n <= 0) return 0;
        long long total = 0;
        long long i = 1;

        while (i <= n) {
            long long full_cycles = (n + 1) / (2 * i);
            total += full_cycles * i;

            long long remainder = (n + 1) % (2 * i);
            if (remainder > i) {
                total += remainder - i;
            }
            i <<= 1;
        }
        return total;
    }
};

int main() {
    // For n=4: 1(1), 2(1), 3(2), 4(1) -> total 5 set bits
    assert(CountSetBits1ToN::count_bits(4) == 5);
    // For n=7: 1(1), 2(1), 3(2), 4(1), 5(2), 6(2), 7(3) -> total 12
    assert(CountSetBits1ToN::count_bits(7) == 12);

    std::cout << "count_set_bits_1_to_n tests passed successfully.\n";
    return 0;
}
