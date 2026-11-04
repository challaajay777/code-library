#include <iostream>
#include <numeric>
#include <cassert>

// Algorithm: Pollard's p-1 Factorization
// Purpose: Factors composite integer N when it possesses a prime factor p such that p - 1 is B-powersmooth in O(B log N).
// Time Complexity: O(B log N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: N is composite.

class PollardPMinusOne {
private:
    static __int128 power(__int128 base, __int128 exp, __int128 mod) {
        __int128 res = 1;
        base %= mod;
        while (exp > 0) {
            if (exp & 1) res = (res * base) % mod;
            base = (base * base) % mod;
            exp >>= 1;
        }
        return res;
    }

public:
    static long long factor(long long n, long long B = 1000) {
        if (n % 2 == 0) return 2;
        __int128 a = 2;

        for (long long j = 2; j <= B; ++j) {
            a = power(a, j, n);
            long long d = std::gcd((long long)(a - 1), n);
            if (d > 1 && d < n) {
                return d;
            }
            if (d == n) break; // Failed, choose different base or bound
        }
        return -1;
    }
};

int main() {
    // 299 = 13 * 23. (13 - 1 = 12 = 2^2 * 3, smooth)
    long long factor = PollardPMinusOne::factor(299, 50);
    assert(factor == 13 || factor == 23);

    std::cout << "pollard_p_minus_1 tests passed successfully.\n";
    return 0;
}
