#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <cassert>

// Algorithm: Discrete Root Solver (x^k = a mod p)
// Purpose: Solves x^k = a (mod p) for prime p by reducing to discrete logarithm using a primitive root in O(sqrt(p)).
// Time Complexity: O(sqrt(p) log p) time
// Space Complexity: O(sqrt(p)) space
// Preconditions: p is prime; 0 <= a < p.

class DiscreteRootSolver {
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

    static long long ext_gcd(long long a, long long b, long long& x, long long& y) {
        if (b == 0) { x = 1; y = 0; return a; }
        long long x1, y1;
        long long d = ext_gcd(b, a % b, x1, y1);
        x = y1;
        y = x1 - y1 * (a / b);
        return d;
    }

    static long long dlog(long long a, long long b, long long m) {
        long long n = static_cast<long long>(std::sqrt(m)) + 1;
        std::map<long long, long long> vals;
        long long cur = b % m;
        for (long long q = 0; q <= n; ++q) {
            vals[cur] = q;
            cur = (__int128)cur * a % m;
        }
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

public:
    static long long find_any_root(long long k, long long a, long long p, long long g) {
        if (a == 0) return 0;
        // g^(k * y) = a (mod p)
        long long gamma = dlog(g, a, p);
        if (gamma == -1) return -1;

        long long y, z;
        long long d = ext_gcd(k, p - 1, y, z);
        if (gamma % d != 0) return -1;

        y = (y * (gamma / d) % (p - 1) + (p - 1)) % (p - 1);
        return power(g, y, p);
    }
};

int main() {
    // x^3 = 6 (mod 7). Generator g = 3.
    // 3^3 = 27 = 6 mod 7 -> root is 3
    long long root = DiscreteRootSolver::find_any_root(3, 6, 7, 3);
    assert(root != -1);
    long long check = (root * root % 7) * root % 7;
    assert(check == 6);

    std::cout << "discrete_root_solver tests passed successfully.\n";
    return 0;
}
