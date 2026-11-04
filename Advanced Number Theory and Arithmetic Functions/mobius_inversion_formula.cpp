#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Mobius Inversion Framework
// Purpose: Applies Mobius inversion g(n) = sum_{d | n} mu(d) * f(n / d) to recover prime/coprimality aggregations in O(N log N).
// Time Complexity: O(N log N) time
// Space Complexity: O(N) auxiliary space
// Preconditions: 1 <= N <= 10^7.

class MobiusInversion {
public:
    static std::vector<int> get_mu(int n) {
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
                    mu[i * p] = 0;
                    break;
                } else {
                    mu[i * p] = -mu[i];
                }
            }
        }
        return mu;
    }

    static std::vector<long long> invert(const std::vector<long long>& f) {
        int n = f.size() - 1;
        auto mu = get_mu(n);
        std::vector<long long> g(n + 1, 0);

        for (int i = 1; i <= n; ++i) {
            if (mu[i] == 0) continue;
            for (int j = 1; i * j <= n; ++j) {
                g[i * j] += (long long)mu[i] * f[j];
            }
        }
        return g;
    }
};

int main() {
    // If f(n) = n, then g(n) = phi(n) because n = sum_{d|n} phi(d)
    int n = 10;
    std::vector<long long> f(n + 1);
    for (int i = 1; i <= n; ++i) f[i] = i;

    auto phi = MobiusInversion::invert(f);
    assert(phi[6] == 2);
    assert(phi[7] == 6);
    assert(phi[1] == 1);

    std::cout << "mobius_inversion_formula tests passed successfully.\n";
    return 0;
}
