#include <iostream>
#include <cmath>
#include <map>
#include <cassert>

// Algorithm: Baby-Step Giant-Step (Discrete Logarithm)
// Purpose: Finds the smallest non-negative integer x such that a^x = b (mod m) in O(sqrt(m)) time and space.
// Time Complexity: O(sqrt(m) log m) time
// Space Complexity: O(sqrt(m)) space
// Preconditions: gcd(a, m) = 1.

class BabyStepGiantStep {
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

public:
    static long long solve(long long a, long long b, long long m) {
        a %= m;
        b %= m;
        if (b == 1 || m == 1) return 0;

        long long n = static_cast<long long>(std::sqrt(m)) + 1;
        std::map<long long, long long> vals;

        // Baby step: a^q * b for q in [0, n]
        long long cur = b;
        for (long long q = 0; q <= n; ++q) {
            vals[cur] = q;
            cur = (__int128)cur * a % m;
        }

        // Giant step: a^(n*p)
        long long an = power(a, n, m);
        cur = 1;
        for (long long p = 1; p <= n + 1; ++p) {
            cur = (__int128)cur * an % m;
            if (vals.count(cur)) {
                long long ans = n * p - vals[cur];
                if (ans >= 0) return ans;
            }
        }
        return -1;
    }
};

int main() {
    // 2^x = 8 (mod 11) -> x = 3 (2^3 = 8)
    assert(BabyStepGiantStep::solve(2, 8, 11) == 3);
    // 3^x = 1 (mod 7) -> x = 0
    assert(BabyStepGiantStep::solve(3, 1, 7) == 0);

    std::cout << "discrete_log_baby_step_giant_step tests passed successfully.\n";
    return 0;
}
