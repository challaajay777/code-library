#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Linear Sieve for Divisor Sum (Sigma)
// Purpose: Calculates the sum of positive divisors sigma(n) for all 1 <= n <= N in linear O(N) time.
// Time Complexity: O(N) time
// Space Complexity: O(N) auxiliary space
// Preconditions: 1 <= N <= 10^7.

class LinearSieveSigma {
public:
    static std::vector<long long> compute_sigma(int n) {
        std::vector<long long> sigma(n + 1, 0);
        std::vector<long long> sum_p_powers(n + 1, 0); // 1 + p + p^2 + ... + p^e
        std::vector<int> primes;
        std::vector<bool> is_prime(n + 1, true);

        sigma[1] = 1;
        for (int i = 2; i <= n; ++i) {
            if (is_prime[i]) {
                primes.push_back(i);
                sigma[i] = 1 + i;
                sum_p_powers[i] = 1 + i;
            }
            for (int p : primes) {
                if (i * p > n) break;
                is_prime[i * p] = false;
                if (i % p == 0) {
                    sum_p_powers[i * p] = sum_p_powers[i] * p + 1;
                    sigma[i * p] = sigma[i] / sum_p_powers[i] * sum_p_powers[i * p];
                    break;
                } else {
                    sum_p_powers[i * p] = 1 + p;
                    sigma[i * p] = sigma[i] * (1 + p);
                }
            }
        }
        return sigma;
    }
};

int main() {
    auto sigma = LinearSieveSigma::compute_sigma(12);
    // Divisors of 12: 1+2+3+4+6+12 = 28
    assert(sigma[12] == 28);
    assert(sigma[1] == 1);
    assert(sigma[7] == 8);

    std::cout << "sieve_divisor_sum_sigma tests passed successfully.\n";
    return 0;
}
