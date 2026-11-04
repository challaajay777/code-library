#include <iostream>
#include <cstdint>
#include <cassert>

// Algorithm: Compiler Builtin Bit Operations
// Purpose: Wraps GCC/Clang bitwise intrinsics for popcount, count leading/trailing zeros, and parity across 32 and 64 bit integers.
// Time Complexity: O(1) CPU instructions
// Space Complexity: O(1) auxiliary space
// Preconditions: Non-zero inputs for clz/ctz to avoid undefined behavior.

class BitOps {
public:
    static int popcount(uint64_t x) {
        return __builtin_popcountll(x);
    }

    static int clz(uint64_t x) {
        assert(x != 0);
        return __builtin_clzll(x);
    }

    static int ctz(uint64_t x) {
        assert(x != 0);
        return __builtin_ctzll(x);
    }

    static int parity(uint64_t x) {
        return __builtin_parityll(x);
    }

    static uint64_t lowest_set_bit(uint64_t x) {
        return x & -x;
    }

    static uint64_t clear_lowest_set_bit(uint64_t x) {
        return x & (x - 1);
    }
};

int main() {
    uint64_t val = 18; // 10010 in binary
    assert(BitOps::popcount(val) == 2);
    assert(BitOps::ctz(val) == 1);
    assert(BitOps::parity(val) == 0); // Even number of set bits
    assert(BitOps::lowest_set_bit(val) == 2);
    assert(BitOps::clear_lowest_set_bit(val) == 16);

    std::cout << "builtin_bit_operations tests passed successfully.\n";
    return 0;
}
