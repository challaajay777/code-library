#include <iostream>
#include <vector>
#include <numeric>
#include <cassert>

// Algorithm: Chinese Remainder Theorem (Non-Coprime Moduli)
// Purpose: Solves system of congruences x = r_i (mod m_i) without requiring pairwise coprime moduli in O(N log(lcm)).
// Time Complexity: O(N log(lcm)) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Moduli m_i >= 1.

class GeneralCRT {
private:
    static long long ext_gcd(long long a, long long b, long long& x, long long& y) {
        if (b == 0) { x = 1; y = 0; return a; }
        long long x1, y1;
        long long d = ext_gcd(b, a % b, x1, y1);
        x = y1;
        y = x1 - y1 * (a / b);
        return d;
    }

public:
    // Returns {x, mod} or {-1, -1} if no solution exists
    static std::pair<long long, long long> solve(const std::vector<long long>& r, const std::vector<long long>& m) {
        long long x0 = 0, m0 = 1;
        for (size_t i = 0; i < r.size(); ++i) {
            long long p, q;
            long long g = ext_gcd(m0, m[i], p, q);
            if ((r[i] - x0) % g != 0) return {-1, -1}; // Incompatible

            long long step = m[i] / g;
            p = (unsigned __int128)(p % step + step) % step;
            p = (unsigned __int128)p * (((r[i] - x0) / g) % step + step) % step;

            x0 += p * m0;
            m0 *= step;
            x0 = (x0 % m0 + m0) % m0;
        }
        return {x0, m0};
    }
};

int main() {
    std::vector<long long> r = {2, 3};
    std::vector<long long> m = {3, 5};
    auto [x, mod] = GeneralCRT::solve(r, m);
    assert(x == 8 && mod == 15);

    std::vector<long long> r2 = {2, 4};
    std::vector<long long> m2 = {4, 6}; // non-coprime: gcd(4, 6) = 2
    auto [x2, mod2] = GeneralCRT::solve(r2, m2);
    assert(x2 == 10 && mod2 == 12);

    std::cout << "crt_non_coprime tests passed successfully.\n";
    return 0;
}
