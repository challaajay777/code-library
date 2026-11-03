// Algorithm: Sieve of Eratosthenes
// Supports: Generating primes up to N, prime checking in O(1)
// Indexing: 0-based integer numbers [0, N]
// Complexity: O(N log log N) time, O(N) memory
// Preconditions: N >= 2

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

struct Sieve {
    int n;
    vector<bool> is_prime;
    vector<int> primes;

    explicit Sieve(int n) : n(n), is_prime(n + 1, true) {
        if (n >= 0) is_prime[0] = false;
        if (n >= 1) is_prime[1] = false;
        for (int p = 2; 1LL * p * p <= n; ++p) {
            if (is_prime[p]) {
                for (int i = p * p; i <= n; i += p) {
                    is_prime[i] = false;
                }
            }
        }
        for (int p = 2; p <= n; ++p) {
            if (is_prime[p]) {
                primes.push_back(p);
            }
        }
    }

    bool check(int x) const {
        assert(0 <= x && x <= n);
        return is_prime[x];
    }
};
