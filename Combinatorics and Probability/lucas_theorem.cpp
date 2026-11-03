// Algorithm: Lucas' Theorem for Large Binomial Coefficients
// Supports: nCr(n, r) mod p for n, r up to 10^18 where p is a small prime
// Indexing: Nonnegative integers n, r
// Complexity: O(p) precomputation, O(log_p(n)) per query, O(p) memory
// Preconditions: p is a prime number <= 10^6

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

struct LucasTheorem {
    int p;
    vector<int> fact, inv_fact;

    explicit LucasTheorem(int prime) : p(prime), fact(prime), inv_fact(prime) {
        fact[0] = inv_fact[0] = 1;
        vector<int> inv(p, 1);
        for (int i = 2; i < p; ++i) {
            inv[i] = (int)(1LL * (p - p / i) * inv[p % i] % p);
        }
        for (int i = 1; i < p; ++i) {
            fact[i] = (int)(1LL * fact[i - 1] * i % p);
            inv_fact[i] = (int)(1LL * inv_fact[i - 1] * inv[i] % p);
        }
    }

private:
    int nCr_small(int n, int r) const {
        if (r < 0 || r > n) return 0;
        return (int)(1LL * fact[n] * inv_fact[r] % p * inv_fact[n - r] % p);
    }

public:
    // Computes nCr(n, r) modulo prime p for n, r up to 10^18
    int nCr(long long n, long long r) const {
        if (r < 0 || r > n) return 0;
        if (r == 0 || r == n) return 1;
        long long ans = 1;
        while (n > 0 || r > 0) {
            int ni = (int)(n % p);
            int ri = (int)(r % p);
            ans = (ans * nCr_small(ni, ri)) % p;
            n /= p;
            r /= p;
        }
        return (int)ans;
    }
};
