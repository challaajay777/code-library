// Algorithm: Euler's Totient Function (Phi)
// Supports: Single value phi(n) in O(sqrt(n)), range sieve for phi(1..N) in O(N)
// Indexing: 1-based positive integers
// Complexity: O(sqrt(n)) single value, O(N) for sieve range [1, N]
// Preconditions: n >= 1

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

struct EulerTotient {
    // Computes phi(n) in O(sqrt(n)) time
    static long long phi(long long n) {
        assert(n >= 1);
        long long result = n;
        for (long long p = 2; p * p <= n; ++p) {
            if (n % p == 0) {
                while (n % p == 0) {
                    n /= p;
                }
                result -= result / p;
            }
        }
        if (n > 1) {
            result -= result / n;
        }
        return result;
    }

    // Computes phi array for all values 1..N in O(N) time using linear sieve
    static vector<int> sieve_phi(int n) {
        assert(n >= 1);
        vector<int> phi(n + 1);
        iota(phi.begin(), phi.end(), 0);
        vector<int> primes;
        vector<bool> is_composite(n + 1, false);

        for (int i = 2; i <= n; ++i) {
            if (!is_composite[i]) {
                primes.push_back(i);
                phi[i] = i - 1;
            }
            for (int p : primes) {
                if (1LL * i * p > n) break;
                is_composite[i * p] = true;
                if (i % p == 0) {
                    phi[i * p] = phi[i] * p;
                    break;
                } else {
                    phi[i * p] = phi[i] * (p - 1);
                }
            }
        }
        return phi;
    }
};
