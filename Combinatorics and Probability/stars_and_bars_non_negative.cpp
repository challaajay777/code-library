#include <iostream>
#include <cassert>

// Algorithm: Stars and Bars Theorem
// Purpose: Calculates ways to distribute N identical items into K distinct bins for both non-negative and strictly positive cases.
// Time Complexity: O(K) time
// Space Complexity: O(1) auxiliary space
// Preconditions: n >= 0, k >= 1.

class StarsAndBars {
private:
    static long long power(long long base, long long exp, long long mod) {
        long long res = 1;
        base %= mod;
        while (exp > 0) {
            if (exp & 1) res = (res * base) % mod;
            base = (base * base) % mod;
            exp >>= 1;
        }
        return res;
    }

    static long long ncr(long long n, long long r, long long mod) {
        if (r < 0 || r > n) return 0;
        if (r == 0 || r == n) return 1;
        long long num = 1, den = 1;
        for (long long i = 0; i < r; ++i) {
            num = (num * (n - i)) % mod;
            den = (den * (i + 1)) % mod;
        }
        return (num * power(den, mod - 2, mod)) % mod;
    }

public:
    // x1 + x2 + ... + xk = n with xi >= 0: C(n + k - 1, k - 1)
    static long long non_negative(long long n, long long k, long long mod = 1e9 + 7) {
        return ncr(n + k - 1, k - 1, mod);
    }

    // x1 + x2 + ... + xk = n with xi >= 1: C(n - 1, k - 1)
    static long long strictly_positive(long long n, long long k, long long mod = 1e9 + 7) {
        if (n < k) return 0;
        return ncr(n - 1, k - 1, mod);
    }
};

int main() {
    // 3 items into 2 bins non-negative: (0,3), (1,2), (2,1), (3,0) -> 4 ways. C(3+2-1, 1) = C(4, 1) = 4
    assert(StarsAndBars::non_negative(3, 2) == 4);
    // 3 items into 2 bins positive: (1,2), (2,1) -> 2 ways. C(3-1, 1) = 2
    assert(StarsAndBars::strictly_positive(3, 2) == 2);

    std::cout << "stars_and_bars_non_negative tests passed successfully.\n";
    return 0;
}
