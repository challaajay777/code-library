// Algorithm: Fast Exponentiation & Fast Doubling Fibonacci
// Supports: Integer power, modular power, fast doubling Fibonacci in O(log n)
// Indexing: 0-indexed Fibonacci (F(0) = 0, F(1) = 1)
// Complexity: O(log n) time, O(1) space
// Preconditions: Exponents and indices n >= 0

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

// Standard binary exponentiation for integers with modulo
long long power_mod(long long base, long long exp, long long mod) {
    assert(exp >= 0 && mod > 0);
    long long res = 1 % mod;
    base %= mod;
    if (base < 0) base += mod;
    while (exp > 0) {
        if (exp & 1) res = (__int128)res * base % mod;
        base = (__int128)base * base % mod;
        exp >>= 1;
    }
    return res;
}

// Fast doubling Fibonacci: returns pair {F(n), F(n+1)} modulo mod
// Uses identities:
// F(2k)   = F(k) * (2*F(k+1) - F(k))
// F(2k+1) = F(k+1)^2 + F(k)^2
pair<long long, long long> fib_fast_doubling(long long n, long long mod) {
    if (n == 0) return {0 % mod, 1 % mod};
    auto p = fib_fast_doubling(n >> 1, mod);
    long long c = ((__int128)p.first * (2 * p.second - p.first + mod)) % mod;
    long long d = ((__int128)p.first * p.first + (__int128)p.second * p.second) % mod;
    if (n & 1) {
        return {d, (c + d) % mod};
    } else {
        return {c, d};
    }
}

long long get_fibonacci(long long n, long long mod) {
    assert(n >= 0 && mod > 0);
    return fib_fast_doubling(n, mod).first;
}
