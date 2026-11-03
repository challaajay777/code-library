// Algorithm: Extended GCD and Modular Inverse
// Supports: Solving ax + by = gcd(a, b) (Bézout's identity), modular inverse for coprime a, m
// Indexing: Continuous integer domain
// Complexity: O(log(min(a, b))) time, O(1) space
// Preconditions: Modular inverse requires gcd(a, m) == 1

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

struct ExtendedGCD {
    // Computes g = gcd(a, b) and finds x, y such that a*x + b*y = g
    static long long extgcd(long long a, long long b, long long& x, long long& y) {
        if (b == 0) {
            x = 1;
            y = 0;
            return a;
        }
        long long x1, y1;
        long long g = extgcd(b, a % b, x1, y1);
        x = y1;
        y = x1 - y1 * (a / b);
        return g;
    }

    // Computes modular inverse of a modulo m: (a * inv) % m == 1
    // Returns -1 if modular inverse does not exist
    static long long mod_inverse(long long a, long long m) {
        assert(m > 0);
        long long x, y;
        long long g = extgcd(a, m, x, y);
        if (g != 1) return -1; // Not coprime
        return (x % m + m) % m;
    }
};
