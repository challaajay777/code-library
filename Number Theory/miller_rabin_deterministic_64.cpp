#include <iostream>
#include <cstdint>
#include <cassert>

// Algorithm: Deterministic Miller-Rabin Primality Test (64-bit)
// Purpose: Deterministically tests primality of any 64-bit integer using 7 fixed prime bases in O(log N).
// Time Complexity: O(7 log N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: n >= 0; handles up to 2^64 - 1.

class MillerRabinDeterministic {
private:
    static uint64_t power(uint64_t base, uint64_t exp, uint64_t mod) {
        uint64_t res = 1;
        base %= mod;
        while (exp > 0) {
            if (exp & 1) res = (unsigned __int128)res * base % mod;
            base = (unsigned __int128)base * base % mod;
            exp >>= 1;
        }
        return res;
    }

    static bool check_composite(uint64_t n, uint64_t a, uint64_t d, int s) {
        uint64_t x = power(a, d, n);
        if (x == 1 || x == n - 1) return false;
        for (int r = 1; r < s; ++r) {
            x = (unsigned __int128)x * x % n;
            if (x == n - 1) return false;
        }
        return true;
    }

public:
    static bool is_prime(uint64_t n) {
        if (n < 2) return false;
        if (n == 2 || n == 3) return true;
        if (n % 2 == 0) return false;

        uint64_t d = n - 1;
        int s = 0;
        while ((d & 1) == 0) {
            d >>= 1;
            s++;
        }

        // Bases proven sufficient for all 64-bit integers
        static const uint64_t bases[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022ULL};
        for (uint64_t a : bases) {
            if (n <= a) break;
            if (check_composite(n, a, d, s)) return false;
        }
        return true;
    }
};

int main() {
    assert(MillerRabinDeterministic::is_prime(2) == true);
    assert(MillerRabinDeterministic::is_prime(1000000007) == true);
    assert(MillerRabinDeterministic::is_prime(1000000009) == true);
    assert(MillerRabinDeterministic::is_prime(1000000008) == false);

    std::cout << "miller_rabin_deterministic_64 tests passed successfully.\n";
    return 0;
}
