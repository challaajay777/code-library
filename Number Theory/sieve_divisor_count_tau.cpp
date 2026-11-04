#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Linear Sieve for Divisor Count (Tau)
// Purpose: Calculates the number of divisors d(n) / tau(n) for all 1 <= n <= N in linear O(N) time.
// Time Complexity: O(N) time
// Space Complexity: O(N) auxiliary space
// Preconditions: 1 <= N <= 10^7.

class LinearSieveTau {
public:
    static std::vector<int> compute_tau(int n) {
        std::vector<int> tau(n + 1, 0);
        std::vector<int> min_prime_exp(n + 1, 0); // e where p^e || n
        std::vector<int> primes;
        std::vector<bool> is_prime(n + 1, true);

        tau[1] = 1;
        for (int i = 2; i <= n; ++i) {
            if (is_prime[i]) {
                primes.push_back(i);
                tau[i] = 2;
                min_prime_exp[i] = 1;
            }
            for (int p : primes) {
                if (i * p > n) break;
                is_prime[i * p] = false;
                if (i % p == 0) {
                    min_prime_exp[i * p] = min_prime_exp[i] + 1;
                    tau[i * p] = tau[i] / (min_prime_exp[i] + 1) * (min_prime_exp[i * p] + 1);
                    break;
                } else {
                    min_prime_exp[i * p] = 1;
                    tau[i * p] = tau[i] * 2;
                }
            }
        }
        return tau;
    }
};

int main() {
    auto tau = LinearSieveTau::compute_tau(12);
    // Divisors of 12: 1, 2, 3, 4, 6, 12 -> 6
    assert(tau[12] == 6);
    assert(tau[1] == 1);
    assert(tau[7] == 2);
    assert(tau[8] == 4);

    std::cout << "sieve_divisor_count_tau tests passed successfully.\n";
    return 0;
}
