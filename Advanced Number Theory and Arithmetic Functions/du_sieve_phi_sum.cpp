#include <iostream>
#include <vector>
#include <unordered_map>
#include <cassert>

// Algorithm: Du Sieve for Euler Totient Prefix Sums
// Purpose: Calculates Phi(N) = sum_{i=1}^N phi(i) in O(N^(2/3)) time using identity Phi * 1 = n * (n+1) / 2.
// Time Complexity: O(N^(2/3)) time
// Space Complexity: O(N^(2/3)) space
// Preconditions: N >= 1.

class DuSievePhi {
private:
    static const int THRESHOLD = 5000000;
    std::vector<long long> phi;
    std::vector<long long> sum_phi;
    std::unordered_map<long long, long long> memo;

public:
    DuSievePhi() {
        phi.assign(THRESHOLD, 0);
        sum_phi.assign(THRESHOLD, 0);
        std::vector<int> primes;
        std::vector<bool> is_prime(THRESHOLD, true);
        phi[1] = 1;

        for (int i = 2; i < THRESHOLD; ++i) {
            if (is_prime[i]) {
                primes.push_back(i);
                phi[i] = i - 1;
            }
            for (int p : primes) {
                if (i * p >= THRESHOLD) break;
                is_prime[i * p] = false;
                if (i % p == 0) {
                    phi[i * p] = phi[i] * p;
                    break;
                } else {
                    phi[i * p] = phi[i] * (p - 1);
                }
            }
        }
        for (int i = 1; i < THRESHOLD; ++i) {
            sum_phi[i] = sum_phi[i - 1] + phi[i];
        }
    }

    long long query(long long n) {
        if (n < THRESHOLD) return sum_phi[n];
        if (memo.count(n)) return memo[n];

        long long ans = (unsigned __int128)n * (n + 1) / 2;
        for (long long l = 2, r; l <= n; l = r + 1) {
            r = n / (n / l);
            ans -= (r - l + 1) * query(n / l);
        }
        return memo[n] = ans;
    }
};

int main() {
    DuSievePhi ds;
    assert(ds.query(1) == 1);
    // phi(1..5) = 1 + 1 + 2 + 2 + 4 = 10
    assert(ds.query(5) == 10);
    assert(ds.query(10) == 32);

    std::cout << "du_sieve_phi_sum tests passed successfully.\n";
    return 0;
}
