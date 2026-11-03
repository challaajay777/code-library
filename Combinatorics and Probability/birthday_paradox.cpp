// Algorithm: Birthday Paradox and Probability Utilities
// Supports: Hash collision probability estimation, required sample size, binomial PMF/CDF
// Indexing: Continuous floating point probability domain [0.0, 1.0]
// Complexity: O(k) or O(1) approximation
// Preconditions: Sample size k <= domain_size

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

struct ProbabilityUtils {
    // Exact probability that at least two items collide when drawing k items from domain of size d
    static double collision_probability(long long k, long long d) {
        if (k > d) return 1.0;
        double p_no_collision = 1.0;
        for (long long i = 1; i < k; ++i) {
            p_no_collision *= (double)(d - i) / (double)d;
        }
        return 1.0 - p_no_collision;
    }

    // Minimum k such that collision probability >= target_p (e.g. 0.5)
    static long long required_samples_for_collision(long long d, double target_p = 0.5) {
        assert(target_p > 0.0 && target_p < 1.0);
        // Approximation: k ~ sqrt(2 * d * ln(1 / (1 - p)))
        double approx = sqrt(2.0 * d * log(1.0 / (1.0 - target_p)));
        long long k = (long long)approx;
        if (k < 1) k = 1;
        while (collision_probability(k, d) < target_p) k++;
        return k;
    }

    // Binomial PMF: P(X = k) = C(n, k) * p^k * (1-p)^(n-k)
    static double binomial_pmf(int n, int k, double p) {
        assert(0 <= k && k <= n && p >= 0.0 && p <= 1.0);
        if (p == 0.0) return (k == 0) ? 1.0 : 0.0;
        if (p == 1.0) return (k == n) ? 1.0 : 0.0;
        double log_prob = 0.0;
        for (int i = 1; i <= k; ++i) {
            log_prob += log((double)(n - k + i) / (double)i);
        }
        log_prob += k * log(p) + (n - k) * log(1.0 - p);
        return exp(log_prob);
    }
};
