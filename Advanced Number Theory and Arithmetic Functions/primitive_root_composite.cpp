#include <iostream>
#include <vector>
#include <numeric>
#include <cassert>

// Algorithm: Primitive Roots for Composite Moduli
// Purpose: Verifies existence and finds primitive root for composite numbers of form 2, 4, p^k, 2p^k.
// Time Complexity: O(Ans * log^2 M) time
// Space Complexity: O(log M) auxiliary space
// Preconditions: M >= 2.

class CompositePrimitiveRoot {
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

    static long long phi(long long n) {
        long long res = n;
        for (long long p = 2; p * p <= n; ++p) {
            if (n % p == 0) {
                while (n % p == 0) n /= p;
                res -= res / p;
            }
        }
        if (n > 1) res -= res / n;
        return res;
    }

public:
    static bool has_primitive_root(long long m) {
        if (m == 2 || m == 4) return true;
        if (m % 2 == 0) m /= 2;
        if (m % 2 == 0) return false;
        for (long long p = 3; p * p <= m; ++p) {
            if (m % p == 0) {
                while (m % p == 0) m /= p;
                return m == 1; // Exactly one odd prime factor
            }
        }
        return m > 1; // Prime itself
    }

    static long long find_root(long long m) {
        if (!has_primitive_root(m)) return -1;
        long long p = phi(m);

        std::vector<long long> factors;
        long long temp = p;
        for (long long d = 2; d * d <= temp; ++d) {
            if (temp % d == 0) {
                factors.push_back(d);
                while (temp % d == 0) temp /= d;
            }
        }
        if (temp > 1) factors.push_back(temp);

        for (long long g = 2; g < m; ++g) {
            if (std::gcd(g, m) != 1) continue;
            bool ok = true;
            for (long long f : factors) {
                if (power(g, p / f, m) == 1) {
                    ok = false;
                    break;
                }
            }
            if (ok) return g;
        }
        return -1;
    }
};

int main() {
    assert(CompositePrimitiveRoot::has_primitive_root(9) == true);  // 3^2
    assert(CompositePrimitiveRoot::has_primitive_root(18) == true); // 2 * 3^2
    assert(CompositePrimitiveRoot::has_primitive_root(8) == false); // 2^3

    long long g9 = CompositePrimitiveRoot::find_root(9);
    assert(g9 == 2); // 2 is primitive root of 9: 2^1=2, 2^2=4, 2^3=8, 2^4=7, 2^5=5, 2^6=1

    std::cout << "primitive_root_composite tests passed successfully.\n";
    return 0;
}
