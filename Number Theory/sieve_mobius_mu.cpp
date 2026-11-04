#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Linear Sieve for Mobius Function (Mu)
// Purpose: Calculates Mobius function mu(n) for all 1 <= n <= N in linear O(N) time.
// Time Complexity: O(N) time
// Space Complexity: O(N) auxiliary space
// Preconditions: 1 <= N <= 10^7.

class LinearSieveMobius {
public:
    static std::vector<int> compute_mu(int n) {
        std::vector<int> mu(n + 1, 0);
        std::vector<int> primes;
        std::vector<bool> is_prime(n + 1, true);

        mu[1] = 1;
        for (int i = 2; i <= n; ++i) {
            if (is_prime[i]) {
                primes.push_back(i);
                mu[i] = -1;
            }
            for (int p : primes) {
                if (i * p > n) break;
                is_prime[i * p] = false;
                if (i % p == 0) {
                    mu[i * p] = 0; // Contains square prime factor
                    break;
                } else {
                    mu[i * p] = -mu[i];
                }
            }
        }
        return mu;
    }
};

int main() {
    auto mu = LinearSieveMobius::compute_mu(12);
    assert(mu[1] == 1);
    assert(mu[2] == -1);
    assert(mu[4] == 0); // 2^2
    assert(mu[6] == 1); // 2 * 3
    assert(mu[12] == 0);

    std::cout << "sieve_mobius_mu tests passed successfully.\n";
    return 0;
}
