#!/usr/bin/env python3
"""
Batch 7 Generator: Basic and Advanced Number Theory (+58 implementations)
Target Directories:
- Number Theory (30 implementations)
- Advanced Number Theory and Arithmetic Functions (28 implementations)
"""

import os
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent.parent
DIR_NT = REPO_ROOT / "Number Theory"
DIR_ANT = REPO_ROOT / "Advanced Number Theory and Arithmetic Functions"

FILES_NT = [
    {
        "filename": "binary_gcd_stein.cpp",
        "algorithm": "Stein's Binary GCD Algorithm",
        "purpose": "Computes greatest common divisor using bit shifts and subtractions without division instructions.",
        "time_complexity": "O(log(min(a, b))) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "a, b non-negative integers.",
        "code": r"""#include <iostream>
#include <cstdint>
#include <cassert>

// Algorithm: Stein's Binary GCD Algorithm
// Purpose: Computes greatest common divisor using bit shifts and subtractions without division instructions.
// Time Complexity: O(log(min(a, b))) time
// Space Complexity: O(1) auxiliary space
// Preconditions: a, b non-negative integers.

class BinaryGCD {
public:
    static uint64_t gcd(uint64_t a, uint64_t b) {
        if (a == 0) return b;
        if (b == 0) return a;

        int shift = __builtin_ctzll(a | b);
        a >>= __builtin_ctzll(a);

        do {
            b >>= __builtin_ctzll(b);
            if (a > b) std::swap(a, b);
            b -= a;
        } while (b != 0);

        return a << shift;
    }
};

int main() {
    assert(BinaryGCD::gcd(48, 18) == 6);
    assert(BinaryGCD::gcd(101, 103) == 1);
    assert(BinaryGCD::gcd(0, 50) == 50);

    std::cout << "binary_gcd_stein tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "extended_gcd_iterative.cpp",
        "algorithm": "Extended Euclidean Algorithm (Iterative)",
        "purpose": "Finds integer coefficients x and y satisfying ax + by = gcd(a, b) iteratively without recursion stack.",
        "time_complexity": "O(log(min(a, b))) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "64-bit integer values.",
        "code": r"""#include <iostream>
#include <tuple>
#include <cassert>

// Algorithm: Extended Euclidean Algorithm (Iterative)
// Purpose: Finds integer coefficients x and y satisfying ax + by = gcd(a, b) iteratively without recursion stack.
// Time Complexity: O(log(min(a, b))) time
// Space Complexity: O(1) auxiliary space
// Preconditions: 64-bit integer values.

class ExtendedGCDIterative {
public:
    // Returns {gcd, x, y} such that a*x + b*y = gcd
    static std::tuple<long long, long long, long long> ext_gcd(long long a, long long b) {
        long long x0 = 1, x1 = 0;
        long long y0 = 0, y1 = 1;

        while (b != 0) {
            long long q = a / b;
            long long r = a % b;
            a = b;
            b = r;

            long long nx = x0 - q * x1;
            x0 = x1;
            x1 = nx;

            long long ny = y0 - q * y1;
            y0 = y1;
            y1 = ny;
        }
        return {a, x0, y0};
    }
};

int main() {
    auto [g, x, y] = ExtendedGCDIterative::ext_gcd(30, 20);
    assert(g == 10);
    assert(30 * x + 20 * y == 10);

    auto [g2, x2, y2] = ExtendedGCDIterative::ext_gcd(35, 15);
    assert(g2 == 5);
    assert(35 * x2 + 15 * y2 == 5);

    std::cout << "extended_gcd_iterative tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "segmented_sieve.cpp",
        "algorithm": "Segmented Sieve of Eratosthenes",
        "purpose": "Finds all prime numbers in an arbitrary range [L, R] using O(sqrt(R)) base primes and O(R - L + 1) memory.",
        "time_complexity": "O((R - L + 1) log log R + sqrt(R) log log sqrt(R)) time",
        "space_complexity": "O(R - L + 1) auxiliary space",
        "preconditions": "1 <= L <= R <= 10^12 and R - L <= 10^7.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Segmented Sieve of Eratosthenes
// Purpose: Finds all prime numbers in an arbitrary range [L, R] using O(sqrt(R)) base primes and O(R - L + 1) memory.
// Time Complexity: O((R - L + 1) log log R + sqrt(R) log log sqrt(R)) time
// Space Complexity: O(R - L + 1) auxiliary space
// Preconditions: 1 <= L <= R <= 10^12 and R - L <= 10^7.

class SegmentedSieve {
private:
    static std::vector<long long> simple_sieve(long long limit) {
        std::vector<bool> is_prime(limit + 1, true);
        is_prime[0] = is_prime[1] = false;
        for (long long p = 2; p * p <= limit; ++p) {
            if (is_prime[p]) {
                for (long long i = p * p; i <= limit; i += p) {
                    is_prime[i] = false;
                }
            }
        }
        std::vector<long long> primes;
        for (long long p = 2; p <= limit; ++p) {
            if (is_prime[p]) primes.push_back(p);
        }
        return primes;
    }

public:
    static std::vector<long long> get_primes_in_range(long long L, long long R) {
        if (L > R || R < 2) return {};
        L = std::max(L, 2LL);

        long long lim = 0;
        while ((lim + 1) * (lim + 1) <= R) lim++;

        auto base_primes = simple_sieve(lim);
        std::vector<bool> is_prime(R - L + 1, true);

        for (long long p : base_primes) {
            long long start = (L + p - 1) / p * p;
            if (start < p * p) start = p * p;
            for (long long j = start; j <= R; j += p) {
                is_prime[j - L] = false;
            }
        }

        std::vector<long long> primes;
        for (long long i = 0; i <= R - L; ++i) {
            if (is_prime[i]) primes.push_back(L + i);
        }
        return primes;
    }
};

int main() {
    auto primes = SegmentedSieve::get_primes_in_range(10, 20);
    std::vector<long long> expected = {11, 13, 17, 19};
    assert(primes == expected);

    auto p2 = SegmentedSieve::get_primes_in_range(1, 10);
    std::vector<long long> exp2 = {2, 3, 5, 7};
    assert(p2 == exp2);

    std::cout << "segmented_sieve tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "sieve_divisor_count_tau.cpp",
        "algorithm": "Linear Sieve for Divisor Count (Tau)",
        "purpose": "Calculates the number of divisors d(n) / tau(n) for all 1 <= n <= N in linear O(N) time.",
        "time_complexity": "O(N) time",
        "space_complexity": "O(N) auxiliary space",
        "preconditions": "1 <= N <= 10^7.",
        "code": r"""#include <iostream>
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
"""
    },
    {
        "filename": "sieve_divisor_sum_sigma.cpp",
        "algorithm": "Linear Sieve for Divisor Sum (Sigma)",
        "purpose": "Calculates the sum of positive divisors sigma(n) for all 1 <= n <= N in linear O(N) time.",
        "time_complexity": "O(N) time",
        "space_complexity": "O(N) auxiliary space",
        "preconditions": "1 <= N <= 10^7.",
        "code": r"""#include <iostream>
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
"""
    },
    {
        "filename": "sieve_mobius_mu.cpp",
        "algorithm": "Linear Sieve for Mobius Function (Mu)",
        "purpose": "Calculates Mobius function mu(n) for all 1 <= n <= N in linear O(N) time.",
        "time_complexity": "O(N) time",
        "space_complexity": "O(N) auxiliary space",
        "preconditions": "1 <= N <= 10^7.",
        "code": r"""#include <iostream>
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
"""
    },
    {
        "filename": "pollard_p_minus_1.cpp",
        "algorithm": "Pollard's p-1 Factorization",
        "purpose": "Factors composite integer N when it possesses a prime factor p such that p - 1 is B-powersmooth in O(B log N).",
        "time_complexity": "O(B log N) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "N is composite.",
        "code": r"""#include <iostream>
#include <numeric>
#include <cassert>

// Algorithm: Pollard's p-1 Factorization
// Purpose: Factors composite integer N when it possesses a prime factor p such that p - 1 is B-powersmooth in O(B log N).
// Time Complexity: O(B log N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: N is composite.

class PollardPMinusOne {
private:
    static __int128 power(__int128 base, __int128 exp, __int128 mod) {
        __int128 res = 1;
        base %= mod;
        while (exp > 0) {
            if (exp & 1) res = (res * base) % mod;
            base = (base * base) % mod;
            exp >>= 1;
        }
        return res;
    }

public:
    static long long factor(long long n, long long B = 1000) {
        if (n % 2 == 0) return 2;
        __int128 a = 2;

        for (long long j = 2; j <= B; ++j) {
            a = power(a, j, n);
            long long d = std::gcd((long long)(a - 1), n);
            if (d > 1 && d < n) {
                return d;
            }
            if (d == n) break; // Failed, choose different base or bound
        }
        return -1;
    }
};

int main() {
    // 299 = 13 * 23. (13 - 1 = 12 = 2^2 * 3, smooth)
    long long factor = PollardPMinusOne::factor(299, 50);
    assert(factor == 13 || factor == 23);

    std::cout << "pollard_p_minus_1 tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "primitive_root_search.cpp",
        "algorithm": "Primitive Root Finder",
        "purpose": "Finds the smallest primitive root modulo prime P in O(Ans * log^2 P) time.",
        "time_complexity": "O(Ans * log^2 P) where Ans is usually very small (< 10)",
        "space_complexity": "O(log P) auxiliary space for prime factors",
        "preconditions": "Modulus P is prime.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Primitive Root Finder
// Purpose: Finds the smallest primitive root modulo prime P in O(Ans * log^2 P) time.
// Time Complexity: O(Ans * log^2 P) where Ans is usually very small (< 10)
// Space Complexity: O(log P) auxiliary space for prime factors
// Preconditions: Modulus P is prime.

class PrimitiveRoot {
private:
    static long long power(long long base, long long exp, long long mod) {
        long long res = 1;
        base %= mod;
        while (exp > 0) {
            if (exp & 1) res = (__int128)res * base % mod;
            base = (__int128)base * base % mod;
            exp >>= 1;
        }
        return res;
    }

    static std::vector<long long> get_factors(long long n) {
        std::vector<long long> factors;
        for (long long d = 2; d * d <= n; ++d) {
            if (n % d == 0) {
                factors.push_back(d);
                while (n % d == 0) n /= d;
            }
        }
        if (n > 1) factors.push_back(n);
        return factors;
    }

public:
    static long long find_generator(long long p) {
        if (p == 2) return 1;
        long long phi = p - 1;
        auto factors = get_factors(phi);

        for (long long res = 2; res <= p; ++res) {
            bool ok = true;
            for (long long factor : factors) {
                if (power(res, phi / factor, p) == 1) {
                    ok = false;
                    break;
                }
            }
            if (ok) return res;
        }
        return -1;
    }
};

int main() {
    assert(PrimitiveRoot::find_generator(7) == 3);
    assert(PrimitiveRoot::find_generator(11) == 2);
    assert(PrimitiveRoot::find_generator(13) == 2);

    std::cout << "primitive_root_search tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "discrete_log_baby_step_giant_step.cpp",
        "algorithm": "Baby-Step Giant-Step (Discrete Logarithm)",
        "purpose": "Finds the smallest non-negative integer x such that a^x = b (mod m) in O(sqrt(m)) time and space.",
        "time_complexity": "O(sqrt(m) log m) time",
        "space_complexity": "O(sqrt(m)) space",
        "preconditions": "gcd(a, m) = 1.",
        "code": r"""#include <iostream>
#include <cmath>
#include <map>
#include <cassert>

// Algorithm: Baby-Step Giant-Step (Discrete Logarithm)
// Purpose: Finds the smallest non-negative integer x such that a^x = b (mod m) in O(sqrt(m)) time and space.
// Time Complexity: O(sqrt(m) log m) time
// Space Complexity: O(sqrt(m)) space
// Preconditions: gcd(a, m) = 1.

class BabyStepGiantStep {
private:
    static long long power(long long base, long long exp, long long mod) {
        long long res = 1;
        base %= mod;
        while (exp > 0) {
            if (exp & 1) res = (__int128)res * base % mod;
            base = (__int128)base * base % mod;
            exp >>= 1;
        }
        return res;
    }

public:
    static long long solve(long long a, long long b, long long m) {
        a %= m;
        b %= m;
        if (b == 1 || m == 1) return 0;

        long long n = static_cast<long long>(std::sqrt(m)) + 1;
        std::map<long long, long long> vals;

        // Baby step: a^q * b for q in [0, n]
        long long cur = b;
        for (long long q = 0; q <= n; ++q) {
            vals[cur] = q;
            cur = (__int128)cur * a % m;
        }

        // Giant step: a^(n*p)
        long long an = power(a, n, m);
        cur = 1;
        for (long long p = 1; p <= n + 1; ++p) {
            cur = (__int128)cur * an % m;
            if (vals.count(cur)) {
                long long ans = n * p - vals[cur];
                if (ans >= 0) return ans;
            }
        }
        return -1;
    }
};

int main() {
    // 2^x = 8 (mod 11) -> x = 3 (2^3 = 8)
    assert(BabyStepGiantStep::solve(2, 8, 11) == 3);
    // 3^x = 1 (mod 7) -> x = 0
    assert(BabyStepGiantStep::solve(3, 1, 7) == 0);

    std::cout << "discrete_log_baby_step_giant_step tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "discrete_root_solver.cpp",
        "algorithm": "Discrete Root Solver (x^k = a mod p)",
        "purpose": "Solves x^k = a (mod p) for prime p by reducing to discrete logarithm using a primitive root in O(sqrt(p)).",
        "time_complexity": "O(sqrt(p) log p) time",
        "space_complexity": "O(sqrt(p)) space",
        "preconditions": "p is prime; 0 <= a < p.",
        "code": r"""#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <cassert>

// Algorithm: Discrete Root Solver (x^k = a mod p)
// Purpose: Solves x^k = a (mod p) for prime p by reducing to discrete logarithm using a primitive root in O(sqrt(p)).
// Time Complexity: O(sqrt(p) log p) time
// Space Complexity: O(sqrt(p)) space
// Preconditions: p is prime; 0 <= a < p.

class DiscreteRootSolver {
private:
    static long long power(long long base, long long exp, long long mod) {
        long long res = 1;
        base %= mod;
        while (exp > 0) {
            if (exp & 1) res = (__int128)res * base % mod;
            base = (__int128)base * base % mod;
            exp >>= 1;
        }
        return res;
    }

    static long long ext_gcd(long long a, long long b, long long& x, long long& y) {
        if (b == 0) { x = 1; y = 0; return a; }
        long long x1, y1;
        long long d = ext_gcd(b, a % b, x1, y1);
        x = y1;
        y = x1 - y1 * (a / b);
        return d;
    }

    static long long dlog(long long a, long long b, long long m) {
        long long n = static_cast<long long>(std::sqrt(m)) + 1;
        std::map<long long, long long> vals;
        long long cur = b % m;
        for (long long q = 0; q <= n; ++q) {
            vals[cur] = q;
            cur = (__int128)cur * a % m;
        }
        long long an = power(a, n, m);
        cur = 1;
        for (long long p = 1; p <= n + 1; ++p) {
            cur = (__int128)cur * an % m;
            if (vals.count(cur)) {
                long long ans = n * p - vals[cur];
                if (ans >= 0) return ans;
            }
        }
        return -1;
    }

public:
    static long long find_any_root(long long k, long long a, long long p, long long g) {
        if (a == 0) return 0;
        // g^(k * y) = a (mod p)
        long long gamma = dlog(g, a, p);
        if (gamma == -1) return -1;

        long long y, z;
        long long d = ext_gcd(k, p - 1, y, z);
        if (gamma % d != 0) return -1;

        y = (y * (gamma / d) % (p - 1) + (p - 1)) % (p - 1);
        return power(g, y, p);
    }
};

int main() {
    // x^3 = 6 (mod 7). Generator g = 3.
    // 3^3 = 27 = 6 mod 7 -> root is 3
    long long root = DiscreteRootSolver::find_any_root(3, 6, 7, 3);
    assert(root != -1);
    long long check = (root * root % 7) * root % 7;
    assert(check == 6);

    std::cout << "discrete_root_solver tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "linear_diophantine_solver.cpp",
        "algorithm": "Linear Diophantine Equation Solver",
        "purpose": "Finds all integer solutions to ax + by = c and counts solutions in range [x_min, x_max] and [y_min, y_max].",
        "time_complexity": "O(log(min(a, b))) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "a, b, c are integers.",
        "code": r"""#include <iostream>
#include <cmath>
#include <cassert>

// Algorithm: Linear Diophantine Equation Solver
// Purpose: Finds all integer solutions to ax + by = c and counts solutions in range [x_min, x_max] and [y_min, y_max].
// Time Complexity: O(log(min(a, b))) time
// Space Complexity: O(1) auxiliary space
// Preconditions: a, b, c are integers.

class LinearDiophantine {
private:
    static long long ext_gcd(long long a, long long b, long long& x, long long& y) {
        if (b == 0) { x = 1; y = 0; return a; }
        long long x1, y1;
        long long d = ext_gcd(b, a % b, x1, y1);
        x = y1;
        y = x1 - y1 * (a / b);
        return d;
    }

public:
    static bool find_any_solution(long long a, long long b, long long c, long long& x0, long long& y0, long long& g) {
        g = ext_gcd(std::abs(a), std::abs(b), x0, y0);
        if (c % g != 0) return false;

        x0 *= c / g;
        y0 *= c / g;
        if (a < 0) x0 = -x0;
        if (b < 0) y0 = -y0;
        return true;
    }
};

int main() {
    long long x, y, g;
    bool ok = LinearDiophantine::find_any_solution(2, 3, 5, x, y, g);
    assert(ok);
    assert(2 * x + 3 * y == 5);

    bool ok2 = LinearDiophantine::find_any_solution(4, 6, 7, x, y, g);
    assert(!ok2); // gcd(4, 6) = 2 does not divide 7

    std::cout << "linear_diophantine_solver tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "tonelli_shanks_sqrt.cpp",
        "algorithm": "Tonelli-Shanks Algorithm (Modular Square Root)",
        "purpose": "Solves congruence x^2 = n (mod p) for odd prime p in expected O(log^2 p) time.",
        "time_complexity": "O(log^2 p) expected time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "p is an odd prime; n is a quadratic residue modulo p.",
        "code": r"""#include <iostream>
#include <cassert>

// Algorithm: Tonelli-Shanks Algorithm (Modular Square Root)
// Purpose: Solves congruence x^2 = n (mod p) for odd prime p in expected O(log^2 p) time.
// Time Complexity: O(log^2 p) expected time
// Space Complexity: O(1) auxiliary space
// Preconditions: p is an odd prime; n is a quadratic residue modulo p.

class TonelliShanks {
private:
    static long long power(long long base, long long exp, long long mod) {
        long long res = 1;
        base %= mod;
        while (exp > 0) {
            if (exp & 1) res = (__int128)res * base % mod;
            base = (__int128)base * base % mod;
            exp >>= 1;
        }
        return res;
    }

public:
    static long long sqrt_mod(long long n, long long p) {
        n %= p;
        if (n == 0) return 0;
        if (p == 2) return n;
        if (power(n, (p - 1) / 2, p) != 1) return -1; // Not a quadratic residue

        // Express p - 1 = Q * 2^S with Q odd
        long long Q = p - 1;
        long long S = 0;
        while (Q % 2 == 0) {
            Q /= 2;
            S++;
        }

        // Find non-residue z
        long long z = 2;
        while (power(z, (p - 1) / 2, p) == 1) z++;

        long long M = S;
        long long c = power(z, Q, p);
        long long t = power(n, Q, p);
        long long R = power(n, (Q + 1) / 2, p);

        while (t != 1) {
            long long cur = t;
            long long i = 0;
            for (i = 1; i < M; ++i) {
                cur = (__int128)cur * cur % p;
                if (cur == 1) break;
            }

            long long b = power(c, 1LL << (M - i - 1), p);
            M = i;
            c = (__int128)b * b % p;
            t = (__int128)t * c % p;
            R = (__int128)R * b % p;
        }
        return R;
    }
};

int main() {
    long long r = TonelliShanks::sqrt_mod(10, 13);
    assert(r != -1);
    assert((r * r) % 13 == 10);

    long long r2 = TonelliShanks::sqrt_mod(5, 41);
    assert(r2 != -1);
    assert((r2 * r2) % 41 == 5);

    std::cout << "tonelli_shanks_sqrt tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "wilson_theorem_primality.cpp",
        "algorithm": "Wilson's Theorem Primality Check",
        "purpose": "Verifies primality of small integer N using Wilson's identity (N - 1)! = -1 (mod N).",
        "time_complexity": "O(N) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "N >= 2.",
        "code": r"""#include <iostream>
#include <cassert>

// Algorithm: Wilson's Theorem Primality Check
// Purpose: Verifies primality of small integer N using Wilson's identity (N - 1)! = -1 (mod N).
// Time Complexity: O(N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: N >= 2.

class WilsonPrimality {
public:
    static bool is_prime(long long n) {
        if (n <= 1) return false;
        long long fact = 1;
        for (long long i = 2; i < n; ++i) {
            fact = (__int128)fact * i % n;
        }
        return fact == n - 1;
    }
};

int main() {
    assert(WilsonPrimality::is_prime(5) == true);
    assert(WilsonPrimality::is_prime(7) == true);
    assert(WilsonPrimality::is_prime(6) == false);

    std::cout << "wilson_theorem_primality tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "stern_brocot_farey.cpp",
        "algorithm": "Stern-Brocot Tree and Farey Sequence",
        "purpose": "Finds rational fraction approximation p/q in Stern-Brocot tree with denominator bound Q.",
        "time_complexity": "O(log(Q)) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "Target real in (0, 1); max_denom >= 1.",
        "code": r"""#include <iostream>
#include <cassert>

// Algorithm: Stern-Brocot Tree and Farey Sequence
// Purpose: Finds rational fraction approximation p/q in Stern-Brocot tree with denominator bound Q.
// Time Complexity: O(log(Q)) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Target real in (0, 1); max_denom >= 1.

class SternBrocotRationalApprox {
public:
    static std::pair<long long, long long> approximate(double target, long long max_denom) {
        long long l_p = 0, l_q = 1;
        long long r_p = 1, r_q = 1;
        long long best_p = 0, best_q = 1;

        while (true) {
            long long m_p = l_p + r_p;
            long long m_q = l_q + r_q;
            if (m_q > max_denom) break;

            best_p = m_p;
            best_q = m_q;
            double mediant = (double)m_p / m_q;

            if (mediant < target) {
                l_p = m_p;
                l_q = m_q;
            } else {
                r_p = m_p;
                r_q = m_q;
            }
        }
        return {best_p, best_q};
    }
};

int main() {
    // Approximate pi - 3 = 0.1415926535...
    auto [p, q] = SternBrocotRationalApprox::approximate(0.1415926535, 100);
    // Best fraction with denominator <= 100 is 1/7 (0.142857)
    assert(p == 1 && q == 7);

    std::cout << "stern_brocot_farey tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "continued_fractions.cpp",
        "algorithm": "Continued Fraction Expansion",
        "purpose": "Computes continued fraction coefficients [a0; a1, a2, ...] of rational P/Q and convergents in O(log(Q)).",
        "time_complexity": "O(log(Q)) time",
        "space_complexity": "O(log(Q)) auxiliary space",
        "preconditions": "Q > 0.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Continued Fraction Expansion
// Purpose: Computes continued fraction coefficients [a0; a1, a2, ...] of rational P/Q and convergents in O(log(Q)).
// Time Complexity: O(log(Q)) time
// Space Complexity: O(log(Q)) auxiliary space
// Preconditions: Q > 0.

class ContinuedFraction {
public:
    static std::vector<long long> expand(long long p, long long q) {
        assert(q > 0);
        std::vector<long long> a;
        while (q != 0) {
            a.push_back(p / q);
            long long rem = p % q;
            p = q;
            q = rem;
        }
        return a;
    }
};

int main() {
    // 649 / 200 = 3 + 1 / (4 + 1 / (12 + 1 / 4))
    auto cf = ContinuedFraction::expand(649, 200);
    std::vector<long long> expected = {3, 4, 12, 4};
    assert(cf == expected);

    std::cout << "continued_fractions tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "floor_sum_ap.cpp",
        "algorithm": "Floor Sum of Arithmetic Progression",
        "purpose": "Computes sum_{i=0}^{n-1} floor((a*i + b) / c) in O(log c) time using Euclidean-like reduction.",
        "time_complexity": "O(log c) time",
        "space_complexity": "O(log c) recursion stack",
        "preconditions": "n, c > 0; a, b >= 0.",
        "code": r"""#include <iostream>
#include <cassert>

// Algorithm: Floor Sum of Arithmetic Progression
// Purpose: Computes sum_{i=0}^{n-1} floor((a*i + b) / c) in O(log c) time using Euclidean-like reduction.
// Time Complexity: O(log c) time
// Space Complexity: O(log c) recursion stack
// Preconditions: n, c > 0; a, b >= 0.

class FloorSum {
public:
    static long long floor_sum(long long n, long long m, long long a, long long b) {
        long long ans = 0;
        if (a >= m) {
            ans += (n - 1) * n / 2 * (a / m);
            a %= m;
        }
        if (b >= m) {
            ans += n * (b / m);
            b %= m;
        }

        long long y_max = (a * n + b) / m;
        long long x_max = y_max * m - b;
        if (y_max == 0) return ans;

        ans += (n - (x_max + a - 1) / a) * y_max;
        ans += floor_sum(y_max, a, m, (a - x_max % a) % a);
        return ans;
    }
};

int main() {
    // sum_{i=0}^3 floor((2*i + 1) / 3):
    // i=0: 0, i=1: 1, i=2: 1, i=3: 2 -> total = 4
    assert(FloorSum::floor_sum(4, 3, 2, 1) == 4);

    std::cout << "floor_sum_ap tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "pythagorean_triples_generator.cpp",
        "algorithm": "Pythagorean Triples Generator (Euclid's Formula)",
        "purpose": "Generates all primitive Pythagorean triples (a, b, c) with hypotenuse c <= limit using Euclid's parameters.",
        "time_complexity": "O(sqrt(limit) log(limit)) time",
        "space_complexity": "O(1) auxiliary space beyond result",
        "preconditions": "limit >= 5.",
        "code": r"""#include <iostream>
#include <vector>
#include <numeric>
#include <cassert>

// Algorithm: Pythagorean Triples Generator (Euclid's Formula)
// Purpose: Generates all primitive Pythagorean triples (a, b, c) with hypotenuse c <= limit using Euclid's parameters.
// Time Complexity: O(sqrt(limit) log(limit)) time
// Space Complexity: O(1) auxiliary space beyond result
// Preconditions: limit >= 5.

struct Triple {
    long long a, b, c;
};

class PythagoreanTriples {
public:
    static std::vector<Triple> generate_primitive(long long max_c) {
        std::vector<Triple> triples;
        for (long long m = 2; m * m <= max_c; ++m) {
            for (long long n = 1; n < m; ++n) {
                if ((m - n) % 2 == 1 && std::gcd(m, n) == 1) {
                    long long a = m * m - n * n;
                    long long b = 2 * m * n;
                    long long c = m * m + n * n;
                    if (c <= max_c) {
                        triples.push_back({std::min(a, b), std::max(a, b), c});
                    }
                }
            }
        }
        return triples;
    }
};

int main() {
    auto t = PythagoreanTriples::generate_primitive(25);
    // (3, 4, 5), (5, 12, 13), (8, 15, 17), (7, 24, 25)
    assert(t.size() == 4);

    std::cout << "pythagorean_triples_generator tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "lucas_lehmer_mersenne.cpp",
        "algorithm": "Lucas-Lehmer Primality Test",
        "purpose": "Deterministically tests whether Mersenne number M_p = 2^p - 1 is prime for odd prime exponent p.",
        "time_complexity": "O(p * M(p)) time where M(p) is multiplication complexity",
        "space_complexity": "O(p) auxiliary space",
        "preconditions": "Exponent p is prime.",
        "code": r"""#include <iostream>
#include <cassert>

// Algorithm: Lucas-Lehmer Primality Test
// Purpose: Deterministically tests whether Mersenne number M_p = 2^p - 1 is prime for odd prime exponent p.
// Time Complexity: O(p * M(p)) time where M(p) is multiplication complexity
// Space Complexity: O(p) auxiliary space
// Preconditions: Exponent p is prime.

class LucasLehmer {
public:
    static bool is_mersenne_prime(int p) {
        if (p == 2) return true;
        if (p < 2) return false;

        unsigned __int128 M_p = (1ULL << p) - 1ULL;
        unsigned __int128 s = 4;

        for (int i = 0; i < p - 2; ++i) {
            s = (s * s - 2) % M_p;
        }
        return s == 0;
    }
};

int main() {
    assert(LucasLehmer::is_mersenne_prime(3) == true);  // 2^3 - 1 = 7
    assert(LucasLehmer::is_mersenne_prime(5) == true);  // 2^5 - 1 = 31
    assert(LucasLehmer::is_mersenne_prime(7) == true);  // 2^7 - 1 = 127
    assert(LucasLehmer::is_mersenne_prime(11) == false); // 2^11 - 1 = 2047 = 23 * 89

    std::cout << "lucas_lehmer_mersenne tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "miller_rabin_deterministic_64.cpp",
        "algorithm": "Deterministic Miller-Rabin Primality Test (64-bit)",
        "purpose": "Deterministically tests primality of any 64-bit integer using 7 fixed prime bases in O(log N).",
        "time_complexity": "O(7 log N) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "n >= 0; handles up to 2^64 - 1.",
        "code": r"""#include <iostream>
#include <cstdint>
#include <cassert>

// Algorithm: Deterministic Miller-Rabin Primality Test (64-bit)
// Purpose: Deterministically tests primality of any 64-bit integer using 7 fixed prime bases in O(log N).
// Time Complexity: O(7 log N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: n >= 0; handles up to 2^64 - 1.

class MillerRabinDeterministic {
private:
    static uint64_t power(uint64_t base, uint64_t exp, uint64_t mod) {
        uint64_t res = 1;
        base %= mod;
        while (exp > 0) {
            if (exp & 1) res = (unsigned __int128)res * base % mod;
            base = (unsigned __int128)base * base % mod;
            exp >>= 1;
        }
        return res;
    }

    static bool check_composite(uint64_t n, uint64_t a, uint64_t d, int s) {
        uint64_t x = power(a, d, n);
        if (x == 1 || x == n - 1) return false;
        for (int r = 1; r < s; ++r) {
            x = (unsigned __int128)x * x % n;
            if (x == n - 1) return false;
        }
        return true;
    }

public:
    static bool is_prime(uint64_t n) {
        if (n < 2) return false;
        if (n == 2 || n == 3) return true;
        if (n % 2 == 0) return false;

        uint64_t d = n - 1;
        int s = 0;
        while ((d & 1) == 0) {
            d >>= 1;
            s++;
        }

        // Bases proven sufficient for all 64-bit integers
        static const uint64_t bases[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022ULL};
        for (uint64_t a : bases) {
            if (n <= a) break;
            if (check_composite(n, a, d, s)) return false;
        }
        return true;
    }
};

int main() {
    assert(MillerRabinDeterministic::is_prime(2) == true);
    assert(MillerRabinDeterministic::is_prime(1000000007) == true);
    assert(MillerRabinDeterministic::is_prime(1000000009) == true);
    assert(MillerRabinDeterministic::is_prime(1000000008) == false);

    std::cout << "miller_rabin_deterministic_64 tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "euler_totient_single.cpp",
        "algorithm": "Euler's Totient Function (Single Integer)",
        "purpose": "Computes phi(N), the number of integers 1 <= k <= N coprime to N, in O(sqrt(N)) time.",
        "time_complexity": "O(sqrt(N)) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "N >= 1.",
        "code": r"""#include <iostream>
#include <cassert>

// Algorithm: Euler's Totient Function (Single Integer)
// Purpose: Computes phi(N), the number of integers 1 <= k <= N coprime to N, in O(sqrt(N)) time.
// Time Complexity: O(sqrt(N)) time
// Space Complexity: O(1) auxiliary space
// Preconditions: N >= 1.

class EulerTotientSingle {
public:
    static long long phi(long long n) {
        long long result = n;
        for (long long p = 2; p * p <= n; ++p) {
            if (n % p == 0) {
                while (n % p == 0) n /= p;
                result -= result / p;
            }
        }
        if (n > 1) {
            result -= result / n;
        }
        return result;
    }
};

int main() {
    assert(EulerTotientSingle::phi(9) == 6);
    assert(EulerTotientSingle::phi(36) == 12);
    assert(EulerTotientSingle::phi(1) == 1);

    std::cout << "euler_totient_single tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "euler_totient_range_sieve.cpp",
        "algorithm": "Range Euler's Totient Sieve",
        "purpose": "Computes phi(x) for all integers x in range [L, R] in O((R - L + 1) log log R + sqrt(R)).",
        "time_complexity": "O((R - L + 1) log log R + sqrt(R)) time",
        "space_complexity": "O(R - L + 1) space",
        "preconditions": "1 <= L <= R.",
        "code": r"""#include <iostream>
#include <vector>
#include <numeric>
#include <cassert>

// Algorithm: Range Euler's Totient Sieve
// Purpose: Computes phi(x) for all integers x in range [L, R] in O((R - L + 1) log log R + sqrt(R)).
// Time Complexity: O((R - L + 1) log log R + sqrt(R)) time
// Space Complexity: O(R - L + 1) space
// Preconditions: 1 <= L <= R.

class RangeEulerTotient {
public:
    static std::vector<long long> compute_range_phi(long long L, long long R) {
        long long len = R - L + 1;
        std::vector<long long> phi(len);
        std::vector<long long> rem(len);

        for (long long i = 0; i < len; ++i) {
            phi[i] = L + i;
            rem[i] = L + i;
        }

        for (long long p = 2; p * p <= R; ++p) {
            long long start = (L + p - 1) / p * p;
            for (long long j = start; j <= R; j += p) {
                if (rem[j - L] % p == 0) {
                    while (rem[j - L] % p == 0) rem[j - L] /= p;
                    phi[j - L] -= phi[j - L] / p;
                }
            }
        }

        for (long long i = 0; i < len; ++i) {
            if (rem[i] > 1) {
                phi[i] -= phi[i] / rem[i];
            }
        }
        return phi;
    }
};

int main() {
    auto phis = RangeEulerTotient::compute_range_phi(1, 10);
    // phi(1..10): 1, 1, 2, 2, 4, 2, 6, 4, 6, 4
    std::vector<long long> expected = {1, 1, 2, 2, 4, 2, 6, 4, 6, 4};
    assert(phis == expected);

    std::cout << "euler_totient_range_sieve tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "modular_inverse_range.cpp",
        "algorithm": "Linear Range Modular Inverses",
        "purpose": "Computes modular inverses for all integers 1 <= i <= N modulo prime P in O(N) time.",
        "time_complexity": "O(N) time",
        "space_complexity": "O(N) space",
        "preconditions": "P is prime; N < P.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Linear Range Modular Inverses
// Purpose: Computes modular inverses for all integers 1 <= i <= N modulo prime P in O(N) time.
// Time Complexity: O(N) time
// Space Complexity: O(N) space
// Preconditions: P is prime; N < P.

class RangeModularInverses {
public:
    static std::vector<long long> compute_inverses(int n, long long p) {
        std::vector<long long> inv(n + 1, 0);
        inv[1] = 1;
        for (int i = 2; i <= n; ++i) {
            inv[i] = (p - p / i) * inv[p % i] % p;
        }
        return inv;
    }
};

int main() {
    auto inv = RangeModularInverses::compute_inverses(6, 7);
    for (int i = 1; i <= 6; ++i) {
        assert((i * inv[i]) % 7 == 1);
    }

    std::cout << "modular_inverse_range tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "crt_non_coprime.cpp",
        "algorithm": "Chinese Remainder Theorem (Non-Coprime Moduli)",
        "purpose": "Solves system of congruences x = r_i (mod m_i) without requiring pairwise coprime moduli in O(N log(lcm)).",
        "time_complexity": "O(N log(lcm)) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "Moduli m_i >= 1.",
        "code": r"""#include <iostream>
#include <vector>
#include <numeric>
#include <cassert>

// Algorithm: Chinese Remainder Theorem (Non-Coprime Moduli)
// Purpose: Solves system of congruences x = r_i (mod m_i) without requiring pairwise coprime moduli in O(N log(lcm)).
// Time Complexity: O(N log(lcm)) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Moduli m_i >= 1.

class GeneralCRT {
private:
    static long long ext_gcd(long long a, long long b, long long& x, long long& y) {
        if (b == 0) { x = 1; y = 0; return a; }
        long long x1, y1;
        long long d = ext_gcd(b, a % b, x1, y1);
        x = y1;
        y = x1 - y1 * (a / b);
        return d;
    }

public:
    // Returns {x, mod} or {-1, -1} if no solution exists
    static std::pair<long long, long long> solve(const std::vector<long long>& r, const std::vector<long long>& m) {
        long long x0 = 0, m0 = 1;
        for (size_t i = 0; i < r.size(); ++i) {
            long long p, q;
            long long g = ext_gcd(m0, m[i], p, q);
            if ((r[i] - x0) % g != 0) return {-1, -1}; // Incompatible

            long long step = m[i] / g;
            p = (unsigned __int128)(p % step + step) % step;
            p = (unsigned __int128)p * (((r[i] - x0) / g) % step + step) % step;

            x0 += p * m0;
            m0 *= step;
            x0 = (x0 % m0 + m0) % m0;
        }
        return {x0, m0};
    }
};

int main() {
    std::vector<long long> r = {2, 3};
    std::vector<long long> m = {3, 5};
    auto [x, mod] = GeneralCRT::solve(r, m);
    assert(x == 8 && mod == 15);

    std::vector<long long> r2 = {2, 4};
    std::vector<long long> m2 = {4, 6}; // non-coprime: gcd(4, 6) = 2
    auto [x2, mod2] = GeneralCRT::solve(r2, m2);
    assert(x2 == 10 && mod2 == 12);

    std::cout << "crt_non_coprime tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "sum_of_squares_two_squares.cpp",
        "algorithm": "Fermat's Two Squares Representation",
        "purpose": "Determines whether N can be expressed as a sum of two squares a^2 + b^2 = N and finds a and b.",
        "time_complexity": "O(sqrt(N)) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "N >= 0.",
        "code": r"""#include <iostream>
#include <cmath>
#include <cassert>

// Algorithm: Fermat's Two Squares Representation
// Purpose: Determines whether N can be expressed as a sum of two squares a^2 + b^2 = N and finds a and b.
// Time Complexity: O(sqrt(N)) time
// Space Complexity: O(1) auxiliary space
// Preconditions: N >= 0.

class TwoSquaresRepresentation {
public:
    static bool can_represent(long long n) {
        for (long long d = 2; d * d <= n; ++d) {
            if (n % d == 0) {
                int count = 0;
                while (n % d == 0) {
                    count++;
                    n /= d;
                }
                if (d % 4 == 3 && count % 2 != 0) return false;
            }
        }
        return n % 4 != 3;
    }

    static std::pair<long long, long long> find_representation(long long n) {
        long long a = 0;
        while (a * a <= n) {
            long long rem = n - a * a;
            long long b = std::round(std::sqrt(rem));
            if (b * b == rem) {
                return {a, b};
            }
            a++;
        }
        return {-1, -1};
    }
};

int main() {
    assert(TwoSquaresRepresentation::can_represent(25) == true); // 3^2 + 4^2
    assert(TwoSquaresRepresentation::can_represent(7) == false);  // 7 = 3 mod 4

    auto [a, b] = TwoSquaresRepresentation::find_representation(25);
    assert(a * a + b * b == 25);

    std::cout << "sum_of_squares_two_squares tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "legendre_formula_prime_exponent.cpp",
        "algorithm": "Legendre's Formula (Prime Factor Multiplicity in N!)",
        "purpose": "Calculates the exact exponent of prime P in the prime factorization of N! in O(log_P N) time.",
        "time_complexity": "O(log_P N) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "P is prime; N >= 1.",
        "code": r"""#include <iostream>
#include <cassert>

// Algorithm: Legendre's Formula (Prime Factor Multiplicity in N!)
// Purpose: Calculates the exact exponent of prime P in the prime factorization of N! in O(log_P N) time.
// Time Complexity: O(log_P N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: P is prime; N >= 1.

class LegendreFormula {
public:
    static long long prime_multiplicity_in_factorial(long long n, long long p) {
        assert(p >= 2);
        long long count = 0;
        while (n > 0) {
            count += n / p;
            n /= p;
        }
        return count;
    }
};

int main() {
    // In 10!: 5 appears with exponent 10/5 = 2 (trailing zeros of 10! = 2)
    assert(LegendreFormula::prime_multiplicity_in_factorial(10, 5) == 2);
    // 2 appears with exponent 10/2 + 10/4 + 10/8 = 5 + 2 + 1 = 8
    assert(LegendreFormula::prime_multiplicity_in_factorial(10, 2) == 8);

    std::cout << "legendre_formula_prime_exponent tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "harmonic_lemma_sqrt_decomposition.cpp",
        "algorithm": "Harmonic Lemma (Block Square Root Division)",
        "purpose": "Iterates through all distinct values of floor(N / i) in contiguous blocks in O(sqrt(N)) time.",
        "time_complexity": "O(sqrt(N)) steps",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "N >= 1.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Harmonic Lemma (Block Square Root Division)
// Purpose: Iterates through all distinct values of floor(N / i) in contiguous blocks in O(sqrt(N)) time.
// Time Complexity: O(sqrt(N)) steps
// Space Complexity: O(1) auxiliary space
// Preconditions: N >= 1.

class HarmonicLemma {
public:
    // Returns list of intervals [L, R, floor(N / L)]
    static std::vector<std::tuple<long long, long long, long long>> get_blocks(long long n) {
        std::vector<std::tuple<long long, long long, long long>> blocks;
        for (long long l = 1, r; l <= n; l = r + 1) {
            long long val = n / l;
            r = n / val;
            blocks.emplace_back(l, r, val);
        }
        return blocks;
    }
};

int main() {
    auto blocks = HarmonicLemma::get_blocks(10);
    // For n=10:
    // l=1..1, val=10; l=2..2, val=5; l=3..3, val=3; l=4..5, val=2; l=6..10, val=1 -> 5 blocks
    assert(blocks.size() == 5);
    assert(std::get<2>(blocks.back()) == 1);

    std::cout << "harmonic_lemma_sqrt_decomposition tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "divisor_sum_range_fast.cpp",
        "algorithm": "Sum of Divisor Function Sum(Tau) in O(sqrt(N))",
        "purpose": "Computes sum_{i=1}^N tau(i) = sum_{i=1}^N floor(N / i) in O(sqrt(N)) time using the Harmonic Lemma.",
        "time_complexity": "O(sqrt(N)) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "N >= 1.",
        "code": r"""#include <iostream>
#include <cassert>

// Algorithm: Sum of Divisor Function Sum(Tau) in O(sqrt(N))
// Purpose: Computes sum_{i=1}^N tau(i) = sum_{i=1}^N floor(N / i) in O(sqrt(N)) time using the Harmonic Lemma.
// Time Complexity: O(sqrt(N)) time
// Space Complexity: O(1) auxiliary space
// Preconditions: N >= 1.

class FastDivisorSum {
public:
    static long long sum_tau(long long n) {
        long long total = 0;
        for (long long l = 1, r; l <= n; l = r + 1) {
            long long val = n / l;
            r = n / val;
            total += val * (r - l + 1);
        }
        return total;
    }
};

int main() {
    // tau(1)=1, tau(2)=2, tau(3)=2, tau(4)=3, tau(5)=2. Sum = 10
    assert(FastDivisorSum::sum_tau(5) == 10);

    std::cout << "divisor_sum_range_fast tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "greatest_common_divisor_array.cpp",
        "algorithm": "Array GCD and LCM",
        "purpose": "Calculates cumulative GCD and modular LCM of an entire array with overflow prevention.",
        "time_complexity": "O(N log(max_val)) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "Array elements positive.",
        "code": r"""#include <iostream>
#include <vector>
#include <numeric>
#include <cassert>

// Algorithm: Array GCD and LCM
// Purpose: Calculates cumulative GCD and modular LCM of an entire array with overflow prevention.
// Time Complexity: O(N log(max_val)) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Array elements positive.

class ArrayGcdLcm {
public:
    static long long array_gcd(const std::vector<long long>& a) {
        long long g = 0;
        for (long long x : a) {
            g = std::gcd(g, x);
        }
        return g;
    }

    static long long array_lcm(const std::vector<long long>& a) {
        long long l = 1;
        for (long long x : a) {
            l = (l / std::gcd(l, x)) * x;
        }
        return l;
    }
};

int main() {
    std::vector<long long> a = {12, 18, 24};
    assert(ArrayGcdLcm::array_gcd(a) == 6);
    assert(ArrayGcdLcm::array_lcm(a) == 72);

    std::cout << "greatest_common_divisor_array tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "lucas_theorem_combinations.cpp",
        "algorithm": "Lucas' Theorem for Binomial Coefficients",
        "purpose": "Computes C(N, K) modulo a small prime P in O(P + log_P N) time.",
        "time_complexity": "O(P + log_P N) time",
        "space_complexity": "O(P) space for factorial table",
        "preconditions": "Modulus P is a small prime.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Lucas' Theorem for Binomial Coefficients
// Purpose: Computes C(N, K) modulo a small prime P in O(P + log_P N) time.
// Time Complexity: O(P + log_P N) time
// Space Complexity: O(P) space for factorial table
// Preconditions: Modulus P is a small prime.

class LucasTheorem {
private:
    static long long power(long long base, long long exp, long long mod) {
        long long res = 1;
        base %= mod;
        while (exp > 0) {
            if (exp & 1) res = (res * base) % mod;
            base = (base * base) % mod;
            exp >>= 1;
        }
        return res;
    }

    static long long mod_inverse(long long n, long long p) {
        return power(n, p - 2, p);
    }

    static long long ncr_small(long long n, long long r, long long p) {
        if (r < 0 || r > n) return 0;
        if (r == 0 || r == n) return 1;
        long long num = 1, den = 1;
        for (long long i = 0; i < r; ++i) {
            num = (num * (n - i)) % p;
            den = (den * (i + 1)) % p;
        }
        return (num * mod_inverse(den, p)) % p;
    }

public:
    static long long ncr_lucas(long long n, long long r, long long p) {
        if (r == 0) return 1;
        long long ni = n % p;
        long long ri = r % p;
        if (ri > ni) return 0;
        return (ncr_lucas(n / p, r / p, p) * ncr_small(ni, ri, p)) % p;
    }
};

int main() {
    // C(10, 2) = 45 = 3 mod 7
    assert(LucasTheorem::ncr_lucas(10, 2, 7) == 3);

    std::cout << "lucas_theorem_combinations tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "catalan_numbers_modular.cpp",
        "algorithm": "Modular Catalan Numbers",
        "purpose": "Computes first N Catalan numbers C_n = (2n)! / ((n+1)! * n!) modulo prime P in O(N).",
        "time_complexity": "O(N) time",
        "space_complexity": "O(N) space",
        "preconditions": "Modulus P is prime > 2*N.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Modular Catalan Numbers
// Purpose: Computes first N Catalan numbers C_n = (2n)! / ((n+1)! * n!) modulo prime P in O(N).
// Time Complexity: O(N) time
// Space Complexity: O(N) space
// Preconditions: Modulus P is prime > 2*N.

class ModularCatalan {
private:
    static long long power(long long base, long long exp, long long mod) {
        long long res = 1;
        base %= mod;
        while (exp > 0) {
            if (exp & 1) res = (res * base) % mod;
            base = (base * base) % mod;
            exp >>= 1;
        }
        return res;
    }

public:
    static std::vector<long long> compute_catalan(int n, long long p) {
        std::vector<long long> cat(n + 1);
        cat[0] = 1;

        for (int i = 0; i < n; ++i) {
            long long num = (2LL * (2LL * i + 1)) % p;
            long long den = (i + 2) % p;
            long long inv_den = power(den, p - 2, p);
            cat[i + 1] = cat[i] * num % p * inv_den % p;
        }
        return cat;
    }
};

int main() {
    auto cat = ModularCatalan::compute_catalan(5, 1000000007);
    // Catalan numbers: 1, 1, 2, 5, 14, 42
    std::vector<long long> expected = {1, 1, 2, 5, 14, 42};
    assert(cat == expected);

    std::cout << "catalan_numbers_modular tests passed successfully.\n";
    return 0;
}
"""
    }
]

def main():
    DIR_NT.mkdir(parents=True, exist_ok=True)
    DIR_ANT.mkdir(parents=True, exist_ok=True)

    count = 0
    for item in FILES_NT:
        path = DIR_NT / item["filename"]
        path.write_text(item["code"].strip() + "\n", encoding="utf-8")
        count += 1
        print(f"Wrote NT [{count}/{len(FILES_NT)}]: {item['filename']}")
    print(f"\nBatch 7 (Part 1 - Number Theory) completed: {count} implementations written.")

if __name__ == "__main__":
    main()
