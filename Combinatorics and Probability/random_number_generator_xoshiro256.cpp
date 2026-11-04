#include <iostream>
#include <cstdint>
#include <cassert>

// Algorithm: xoshiro256** Pseudo-Random Number Generator
// Purpose: Ultra-fast high-quality 64-bit PRNG passing all BigCrush statistical tests with state space 2^256 - 1.
// Time Complexity: O(1) time per random 64-bit word
// Space Complexity: O(1) auxiliary space
// Preconditions: State not all zeroes.

class Xoshiro256StarStar {
private:
    uint64_t s[4];

    static inline uint64_t rotl(const uint64_t x, int k) {
        return (x << k) | (x >> (64 - k));
    }

public:
    explicit Xoshiro256StarStar(uint64_t seed = 0x853c49e6748fea9bULL) {
        // SplitMix64 initialization
        for (int i = 0; i < 4; ++i) {
            uint64_t z = (seed += 0x9e3779b97f4a7c15ULL);
            z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9ULL;
            z = (z ^ (z >> 27)) * 0x94d049bb133111ebULL;
            s[i] = z ^ (z >> 31);
        }
    }

    uint64_t next() {
        const uint64_t result = rotl(s[1] * 5, 7) * 9;
        const uint64_t t = s[1] << 17;

        s[2] ^= s[0];
        s[3] ^= s[1];
        s[1] ^= s[2];
        s[0] ^= s[3];

        s[2] ^= t;
        s[3] = rotl(s[3], 45);

        return result;
    }
};

int main() {
    Xoshiro256StarStar rng(12345);
    uint64_t r1 = rng.next();
    uint64_t r2 = rng.next();
    assert(r1 != r2);

    std::cout << "random_number_generator_xoshiro256 tests passed successfully.\n";
    return 0;
}
