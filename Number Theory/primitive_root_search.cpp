#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Primitive Root Finder
// Purpose: Finds the smallest primitive root modulo prime P in O(Ans * log^2 P) time.
// Time Complexity: O(Ans * log^2 P) where Ans is usually very small (< 10)
// Space Complexity: O(log P) auxiliary space for prime factors
// Preconditions: Modulus P is prime.

class PrimitiveRoot {
private:
    static long long power(long long base, long long exp, long long mod) {
        long long res = 1;
        base %= mod;
        while (exp > 0) {
            if (exp & 1) res = (__int128)res * base % mod;
            base = (__int128)base * base % mod;
            exp >>= 1;
        }
        return res;
    }

    static std::vector<long long> get_factors(long long n) {
        std::vector<long long> factors;
        for (long long d = 2; d * d <= n; ++d) {
            if (n % d == 0) {
                factors.push_back(d);
                while (n % d == 0) n /= d;
            }
        }
        if (n > 1) factors.push_back(n);
        return factors;
    }

public:
    static long long find_generator(long long p) {
        if (p == 2) return 1;
        long long phi = p - 1;
        auto factors = get_factors(phi);

        for (long long res = 2; res <= p; ++res) {
            bool ok = true;
            for (long long factor : factors) {
                if (power(res, phi / factor, p) == 1) {
                    ok = false;
                    break;
                }
            }
            if (ok) return res;
        }
        return -1;
    }
};

int main() {
    assert(PrimitiveRoot::find_generator(7) == 3);
    assert(PrimitiveRoot::find_generator(11) == 2);
    assert(PrimitiveRoot::find_generator(13) == 2);

    std::cout << "primitive_root_search tests passed successfully.\n";
    return 0;
}
