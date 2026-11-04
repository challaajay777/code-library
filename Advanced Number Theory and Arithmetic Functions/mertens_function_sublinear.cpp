#include <iostream>
#include <vector>
#include <unordered_map>
#include <cassert>

// Algorithm: Mertens Function (Sublinear Sum of Mobius)
// Purpose: Computes M(N) = sum_{i=1}^N mu(i) in O(N^(2/3)) time using Du Sieve / Min25 memoization.
// Time Complexity: O(N^(2/3)) time
// Space Complexity: O(N^(2/3)) space
// Preconditions: N >= 1.

class SublinearMertens {
private:
    static const int THRESHOLD = 5000000;
    std::vector<int> mu;
    std::vector<int> sum_mu;
    std::unordered_map<long long, long long> memo;

public:
    SublinearMertens() {
        mu.assign(THRESHOLD, 0);
        sum_mu.assign(THRESHOLD, 0);
        std::vector<int> primes;
        std::vector<bool> is_prime(THRESHOLD, true);
        mu[1] = 1;

        for (int i = 2; i < THRESHOLD; ++i) {
            if (is_prime[i]) {
                primes.push_back(i);
                mu[i] = -1;
            }
            for (int p : primes) {
                if (i * p >= THRESHOLD) break;
                is_prime[i * p] = false;
                if (i % p == 0) {
                    mu[i * p] = 0;
                    break;
                } else {
                    mu[i * p] = -mu[i];
                }
            }
        }
        for (int i = 1; i < THRESHOLD; ++i) {
            sum_mu[i] = sum_mu[i - 1] + mu[i];
        }
    }

    long long query(long long n) {
        if (n < THRESHOLD) return sum_mu[n];
        if (memo.count(n)) return memo[n];

        long long ans = 1;
        for (long long l = 2, r; l <= n; l = r + 1) {
            r = n / (n / l);
            ans -= (r - l + 1) * query(n / l);
        }
        return memo[n] = ans;
    }
};

int main() {
    SublinearMertens mertens;
    assert(mertens.query(1) == 1);
    assert(mertens.query(10) == -1);
    assert(mertens.query(100) == 1);

    std::cout << "mertens_function_sublinear tests passed successfully.\n";
    return 0;
}
