#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Gray Code Generation and Conversion
// Purpose: Converts binary to reflected Gray code, inverts Gray code to binary, and generates N-bit Gray code sequences in O(2^N).
// Time Complexity: O(1) per conversion, O(2^N) for sequence generation
// Space Complexity: O(1) auxiliary space beyond result vector
// Preconditions: 0 <= N <= 30.

class GrayCode {
public:
    static unsigned int binary_to_gray(unsigned int n) {
        return n ^ (n >> 1);
    }

    static unsigned int gray_to_binary(unsigned int g) {
        unsigned int b = 0;
        for (; g; g >>= 1) {
            b ^= g;
        }
        return b;
    }

    static std::vector<unsigned int> generate_sequence(int n) {
        int total = 1 << n;
        std::vector<unsigned int> seq(total);
        for (int i = 0; i < total; ++i) {
            seq[i] = binary_to_gray(i);
        }
        return seq;
    }
};

int main() {
    for (unsigned int i = 0; i < 32; ++i) {
        unsigned int g = GrayCode::binary_to_gray(i);
        unsigned int b = GrayCode::gray_to_binary(g);
        assert(b == i);
    }

    auto seq = GrayCode::generate_sequence(3);
    assert(seq.size() == 8);
    // Adjacent codes differ by exactly 1 bit
    for (size_t i = 1; i < seq.size(); ++i) {
        assert(__builtin_popcount(seq[i] ^ seq[i - 1]) == 1);
    }

    std::cout << "gray_code_generation tests passed successfully.\n";
    return 0;
}
