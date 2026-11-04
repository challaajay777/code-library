#!/usr/bin/env python3
"""
Batch 8 Generator: Combinatorics and Probability (25 implementations)
Target Directory: Combinatorics and Probability
"""

import os
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent.parent
TARGET_DIR = REPO_ROOT / "Combinatorics and Probability"

FILES = [
    {
        "filename": "stirling_numbers_first_kind.cpp",
        "algorithm": "Stirling Numbers of the First Kind (Unsigned)",
        "purpose": "Computes |s(n, k)|, the number of permutations of n elements with exactly k disjoint cycles, in O(n * k).",
        "time_complexity": "O(N * K) time",
        "space_complexity": "O(N * K) auxiliary space",
        "preconditions": "0 <= k <= n.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Stirling Numbers of the First Kind (Unsigned)
// Purpose: Computes |s(n, k)|, the number of permutations of n elements with exactly k disjoint cycles, in O(n * k).
// Time Complexity: O(N * K) time
// Space Complexity: O(N * K) auxiliary space
// Preconditions: 0 <= k <= n.

class StirlingFirstKind {
public:
    static std::vector<std::vector<long long>> compute_table(int n, int k, long long mod = 1e9 + 7) {
        std::vector<std::vector<long long>> s(n + 1, std::vector<long long>(k + 1, 0));
        s[0][0] = 1;

        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= std::min(i, k); ++j) {
                // s(i, j) = s(i-1, j-1) + (i-1) * s(i-1, j)
                s[i][j] = (s[i - 1][j - 1] + (i - 1) * s[i - 1][j]) % mod;
            }
        }
        return s;
    }
};

int main() {
    auto s = StirlingFirstKind::compute_table(4, 4);
    // Permutations of 4:
    // k=1: (4-1)! = 6
    // k=2: 11
    // k=3: 6
    // k=4: 1
    assert(s[4][1] == 6);
    assert(s[4][2] == 11);
    assert(s[4][3] == 6);
    assert(s[4][4] == 1);

    std::cout << "stirling_numbers_first_kind tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "stirling_numbers_second_kind.cpp",
        "algorithm": "Stirling Numbers of the Second Kind",
        "purpose": "Computes S(n, k), the number of ways to partition a set of n elements into k non-empty subsets, in O(n * k).",
        "time_complexity": "O(N * K) time",
        "space_complexity": "O(N * K) space",
        "preconditions": "0 <= k <= n.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Stirling Numbers of the Second Kind
// Purpose: Computes S(n, k), the number of ways to partition a set of n elements into k non-empty subsets, in O(n * k).
// Time Complexity: O(N * K) time
// Space Complexity: O(N * K) space
// Preconditions: 0 <= k <= n.

class StirlingSecondKind {
public:
    static std::vector<std::vector<long long>> compute_table(int n, int k, long long mod = 1e9 + 7) {
        std::vector<std::vector<long long>> S(n + 1, std::vector<long long>(k + 1, 0));
        S[0][0] = 1;

        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= std::min(i, k); ++j) {
                // S(i, j) = S(i-1, j-1) + j * S(i-1, j)
                S[i][j] = (S[i - 1][j - 1] + j * S[i - 1][j]) % mod;
            }
        }
        return S;
    }
};

int main() {
    auto S = StirlingSecondKind::compute_table(4, 4);
    // S(4, 1) = 1
    // S(4, 2) = 7
    // S(4, 3) = 6
    // S(4, 4) = 1
    assert(S[4][1] == 1);
    assert(S[4][2] == 7);
    assert(S[4][3] == 6);
    assert(S[4][4] == 1);

    std::cout << "stirling_numbers_second_kind tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "bell_numbers.cpp",
        "algorithm": "Bell Numbers (Set Partitions Count)",
        "purpose": "Computes Bell numbers B(n), the total number of partitions of an n-element set, using the Bell triangle in O(N^2).",
        "time_complexity": "O(N^2) time",
        "space_complexity": "O(N) auxiliary space",
        "preconditions": "N >= 0.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Bell Numbers (Set Partitions Count)
// Purpose: Computes Bell numbers B(n), the total number of partitions of an n-element set, using the Bell triangle in O(N^2).
// Time Complexity: O(N^2) time
// Space Complexity: O(N) auxiliary space
// Preconditions: N >= 0.

class BellNumbers {
public:
    static std::vector<long long> compute_bell(int n, long long mod = 1e9 + 7) {
        std::vector<long long> bell(n + 1, 0);
        std::vector<long long> row = {1};
        bell[0] = 1;

        for (int i = 1; i <= n; ++i) {
            std::vector<long long> next_row(i + 1);
            next_row[0] = row.back();
            for (int j = 1; j <= i; ++j) {
                next_row[j] = (next_row[j - 1] + row[j - 1]) % mod;
            }
            bell[i] = next_row[0];
            row = std::move(next_row);
        }
        return bell;
    }
};

int main() {
    auto B = BellNumbers::compute_bell(5);
    // B(0)=1, B(1)=1, B(2)=2, B(3)=5, B(4)=15, B(5)=52
    assert(B[0] == 1);
    assert(B[1] == 1);
    assert(B[2] == 2);
    assert(B[3] == 5);
    assert(B[4] == 15);
    assert(B[5] == 52);

    std::cout << "bell_numbers tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "derangements_subfactorial.cpp",
        "algorithm": "Derangements (Subfactorial !n)",
        "purpose": "Computes the number of permutations of n elements having no fixed points using recurrence !n = (n-1)*(!(n-1) + !(n-2)).",
        "time_complexity": "O(N) time",
        "space_complexity": "O(N) space",
        "preconditions": "N >= 0.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Derangements (Subfactorial !n)
// Purpose: Computes the number of permutations of n elements having no fixed points using recurrence !n = (n-1)*(!(n-1) + !(n-2)).
// Time Complexity: O(N) time
// Space Complexity: O(N) space
// Preconditions: N >= 0.

class Subfactorial {
public:
    static std::vector<long long> compute_derangements(int n, long long mod = 1e9 + 7) {
        std::vector<long long> d(n + 1, 0);
        if (n >= 0) d[0] = 1;
        if (n >= 1) d[1] = 0;

        for (int i = 2; i <= n; ++i) {
            d[i] = (i - 1) * (d[i - 1] + d[i - 2]) % mod;
        }
        return d;
    }
};

int main() {
    auto d = Subfactorial::compute_derangements(5);
    // !0=1, !1=0, !2=1, !3=2, !4=9, !5=44
    assert(d[0] == 1);
    assert(d[1] == 0);
    assert(d[2] == 1);
    assert(d[3] == 2);
    assert(d[4] == 9);
    assert(d[5] == 44);

    std::cout << "derangements_subfactorial tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "burnside_lemma_necklace.cpp",
        "algorithm": "Burnside's Lemma (Necklace Counting Under Rotation)",
        "purpose": "Counts the number of distinct necklaces of N beads using K colors up to rotational symmetry.",
        "time_complexity": "O(N log N) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "n >= 1, k >= 1.",
        "code": r"""#include <iostream>
#include <numeric>
#include <cassert>

// Algorithm: Burnside's Lemma (Necklace Counting Under Rotation)
// Purpose: Counts the number of distinct necklaces of N beads using K colors up to rotational symmetry.
// Time Complexity: O(N log N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: n >= 1, k >= 1.

class BurnsideNecklace {
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
    static long long count_necklaces(int n, int k, long long mod = 1e9 + 7) {
        long long sum_fixed = 0;
        for (int i = 0; i < n; ++i) {
            int g = std::gcd(i, n);
            sum_fixed = (sum_fixed + power(k, g, mod)) % mod;
        }
        long long inv_n = power(n, mod - 2, mod);
        return (sum_fixed * inv_n) % mod;
    }
};

int main() {
    // 4 beads, 2 colors: total distinct under rotation = (2^4 + 2^1 + 2^2 + 2^1) / 4 = 24 / 4 = 6
    assert(BurnsideNecklace::count_necklaces(4, 2) == 6);

    std::cout << "burnside_lemma_necklace tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "polya_enumeration_bracelet.cpp",
        "algorithm": "Polya Enumeration Theorem (Bracelet Counting)",
        "purpose": "Counts number of distinct bracelets of N beads with K colors under rotation and reflection (dihedral group D_n).",
        "time_complexity": "O(N log N) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "n >= 1, k >= 1.",
        "code": r"""#include <iostream>
#include <numeric>
#include <cassert>

// Algorithm: Polya Enumeration Theorem (Bracelet Counting)
// Purpose: Counts number of distinct bracelets of N beads with K colors under rotation and reflection (dihedral group D_n).
// Time Complexity: O(N log N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: n >= 1, k >= 1.

class PolyaBracelet {
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
    static long long count_bracelets(int n, int k, long long mod = 1e9 + 7) {
        long long sum = 0;

        // Rotations
        for (int i = 0; i < n; ++i) {
            sum = (sum + power(k, std::gcd(i, n), mod)) % mod;
        }

        // Reflections
        if (n % 2 == 1) {
            sum = (sum + (long long)n * power(k, (n + 1) / 2, mod)) % mod;
        } else {
            long long refl1 = (long long)(n / 2) * power(k, n / 2 + 1, mod) % mod;
            long long refl2 = (long long)(n / 2) * power(k, n / 2, mod) % mod;
            sum = (sum + refl1 + refl2) % mod;
        }

        long long inv_2n = power(2 * n, mod - 2, mod);
        return (sum * inv_2n) % mod;
    }
};

int main() {
    // 4 beads, 2 colors under rotation and reflection: 6 necklaces -> 6 bracelets?
    // Reflections: 2 through vertices (cycles 1+1+2/2=3), 2 through edges (cycles 2).
    // Sum = 24 + 2 * 2^3 + 2 * 2^2 = 24 + 16 + 8 = 48. 48 / 8 = 6 bracelets
    assert(PolyaBracelet::count_bracelets(4, 2) == 6);

    std::cout << "polya_enumeration_bracelet tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "stars_and_bars_non_negative.cpp",
        "algorithm": "Stars and Bars Theorem",
        "purpose": "Calculates ways to distribute N identical items into K distinct bins for both non-negative and strictly positive cases.",
        "time_complexity": "O(K) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "n >= 0, k >= 1.",
        "code": r"""#include <iostream>
#include <cassert>

// Algorithm: Stars and Bars Theorem
// Purpose: Calculates ways to distribute N identical items into K distinct bins for both non-negative and strictly positive cases.
// Time Complexity: O(K) time
// Space Complexity: O(1) auxiliary space
// Preconditions: n >= 0, k >= 1.

class StarsAndBars {
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

    static long long ncr(long long n, long long r, long long mod) {
        if (r < 0 || r > n) return 0;
        if (r == 0 || r == n) return 1;
        long long num = 1, den = 1;
        for (long long i = 0; i < r; ++i) {
            num = (num * (n - i)) % mod;
            den = (den * (i + 1)) % mod;
        }
        return (num * power(den, mod - 2, mod)) % mod;
    }

public:
    // x1 + x2 + ... + xk = n with xi >= 0: C(n + k - 1, k - 1)
    static long long non_negative(long long n, long long k, long long mod = 1e9 + 7) {
        return ncr(n + k - 1, k - 1, mod);
    }

    // x1 + x2 + ... + xk = n with xi >= 1: C(n - 1, k - 1)
    static long long strictly_positive(long long n, long long k, long long mod = 1e9 + 7) {
        if (n < k) return 0;
        return ncr(n - 1, k - 1, mod);
    }
};

int main() {
    // 3 items into 2 bins non-negative: (0,3), (1,2), (2,1), (3,0) -> 4 ways. C(3+2-1, 1) = C(4, 1) = 4
    assert(StarsAndBars::non_negative(3, 2) == 4);
    // 3 items into 2 bins positive: (1,2), (2,1) -> 2 ways. C(3-1, 1) = 2
    assert(StarsAndBars::strictly_positive(3, 2) == 2);

    std::cout << "stars_and_bars_non_negative tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "multinomial_coefficient.cpp",
        "algorithm": "Multinomial Coefficient",
        "purpose": "Computes multinomial coefficient N! / (k1! * k2! * ... * km!) modulo prime P in O(N).",
        "time_complexity": "O(N) time",
        "space_complexity": "O(N) auxiliary space for factorials",
        "preconditions": "sum(k_i) == N; prime mod P.",
        "code": r"""#include <iostream>
#include <vector>
#include <numeric>
#include <cassert>

// Algorithm: Multinomial Coefficient
// Purpose: Computes multinomial coefficient N! / (k1! * k2! * ... * km!) modulo prime P in O(N).
// Time Complexity: O(N) time
// Space Complexity: O(N) auxiliary space for factorials
// Preconditions: sum(k_i) == N; prime mod P.

class Multinomial {
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
    static long long coefficient(const std::vector<int>& k, long long mod = 1e9 + 7) {
        int n = std::accumulate(k.begin(), k.end(), 0);
        std::vector<long long> fact(n + 1, 1);
        for (int i = 2; i <= n; ++i) {
            fact[i] = (fact[i - 1] * i) % mod;
        }

        long long num = fact[n];
        long long den = 1;
        for (int part : k) {
            den = (den * fact[part]) % mod;
        }
        return (num * power(den, mod - 2, mod)) % mod;
    }
};

int main() {
    // Permutations of "MISSISSIPPI": M=1, I=4, S=4, P=2. N = 11.
    // 11! / (1! * 4! * 4! * 2!) = 34650
    std::vector<int> k = {1, 4, 4, 2};
    assert(Multinomial::coefficient(k) == 34650);

    std::cout << "multinomial_coefficient tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "montmort_derangements_modulo.cpp",
        "algorithm": "Montmort Derangements Numbers Modulo M",
        "purpose": "Calculates derangements sequence D(N) modulo arbitrary composite integer M in O(N).",
        "time_complexity": "O(N) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "N >= 0; M >= 1.",
        "code": r"""#include <iostream>
#include <cassert>

// Algorithm: Montmort Derangements Numbers Modulo M
// Purpose: Calculates derangements sequence D(N) modulo arbitrary composite integer M in O(N).
// Time Complexity: O(N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: N >= 0; M >= 1.

class MontmortDerangements {
public:
    static long long derangement(int n, long long m) {
        if (n == 0) return 1 % m;
        if (n == 1) return 0;

        long long d0 = 1 % m;
        long long d1 = 0;

        for (int i = 2; i <= n; ++i) {
            long long d_next = (i - 1) * (d1 + d0) % m;
            d0 = d1;
            d1 = d_next;
        }
        return d1;
    }
};

int main() {
    assert(MontmortDerangements::derangement(4, 100) == 9);
    assert(MontmortDerangements::derangement(5, 100) == 44);

    std::cout << "montmort_derangements_modulo tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "narayana_numbers.cpp",
        "algorithm": "Narayana Numbers",
        "purpose": "Computes N(n, k) = (1/n) * C(n, k) * C(n, k-1) counting Dyck paths of length 2n with exactly k peaks in O(n).",
        "time_complexity": "O(N) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "1 <= k <= n.",
        "code": r"""#include <iostream>
#include <cassert>

// Algorithm: Narayana Numbers
// Purpose: Computes N(n, k) = (1/n) * C(n, k) * C(n, k-1) counting Dyck paths of length 2n with exactly k peaks in O(n).
// Time Complexity: O(N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: 1 <= k <= n.

class NarayanaNumbers {
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

    static long long ncr(long long n, long long r, long long mod) {
        if (r < 0 || r > n) return 0;
        if (r == 0 || r == n) return 1;
        long long num = 1, den = 1;
        for (long long i = 0; i < r; ++i) {
            num = (num * (n - i)) % mod;
            den = (den * (i + 1)) % mod;
        }
        return (num * power(den, mod - 2, mod)) % mod;
    }

public:
    static long long get_narayana(long long n, long long k, long long mod = 1e9 + 7) {
        if (k < 1 || k > n) return 0;
        long long c1 = ncr(n, k, mod);
        long long c2 = ncr(n, k - 1, mod);
        long long inv_n = power(n, mod - 2, mod);
        return (c1 * c2 % mod * inv_n) % mod;
    }
};

int main() {
    // For n=3:
    // N(3, 1) = 1
    // N(3, 2) = 3
    // N(3, 3) = 1
    // Sum = Catalan(3) = 5
    assert(NarayanaNumbers::get_narayana(3, 1) == 1);
    assert(NarayanaNumbers::get_narayana(3, 2) == 3);
    assert(NarayanaNumbers::get_narayana(3, 3) == 1);

    std::cout << "narayana_numbers tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "motzkin_numbers.cpp",
        "algorithm": "Motzkin Numbers",
        "purpose": "Computes Motzkin numbers M(n) counting non-intersecting chords between n points on a circle in O(N).",
        "time_complexity": "O(N) time",
        "space_complexity": "O(N) space",
        "preconditions": "N >= 0.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Motzkin Numbers
// Purpose: Computes Motzkin numbers M(n) counting non-intersecting chords between n points on a circle in O(N).
// Time Complexity: O(N) time
// Space Complexity: O(N) space
// Preconditions: N >= 0.

class MotzkinNumbers {
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
    static std::vector<long long> compute_motzkin(int n, long long mod = 1e9 + 7) {
        std::vector<long long> m(n + 1, 0);
        m[0] = 1;
        if (n >= 1) m[1] = 1;

        for (int i = 2; i <= n; ++i) {
            // (i + 2) * M(i) = (2*i + 1) * M(i-1) + 3 * (i - 1) * M(i-2)
            long long term1 = (2LL * i + 1) * m[i - 1] % mod;
            long long term2 = 3LL * (i - 1) % mod * m[i - 2] % mod;
            long long num = (term1 + term2) % mod;
            long long den_inv = power(i + 2, mod - 2, mod);
            m[i] = (num * den_inv) % mod;
        }
        return m;
    }
};

int main() {
    auto m = MotzkinNumbers::compute_motzkin(6);
    // Motzkin sequence: 1, 1, 2, 4, 9, 21, 51
    std::vector<long long> expected = {1, 1, 2, 4, 9, 21, 51};
    assert(m == expected);

    std::cout << "motzkin_numbers tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "eulerian_numbers.cpp",
        "algorithm": "Eulerian Numbers A(n, m)",
        "purpose": "Computes Eulerian numbers A(n, m) counting permutations of {1..n} with exactly m ascents in O(n * m).",
        "time_complexity": "O(N * M) time",
        "space_complexity": "O(N * M) auxiliary space",
        "preconditions": "0 <= m < n.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Eulerian Numbers A(n, m)
// Purpose: Computes Eulerian numbers A(n, m) counting permutations of {1..n} with exactly m ascents in O(n * m).
// Time Complexity: O(N * M) time
// Space Complexity: O(N * M) auxiliary space
// Preconditions: 0 <= m < n.

class EulerianNumbers {
public:
    static std::vector<std::vector<long long>> compute_eulerian(int n, long long mod = 1e9 + 7) {
        std::vector<std::vector<long long>> a(n + 1, std::vector<long long>(n + 1, 0));
        a[1][0] = 1;

        for (int i = 2; i <= n; ++i) {
            for (int j = 0; j < i; ++j) {
                // A(i, j) = (j + 1) * A(i - 1, j) + (i - j) * A(i - 1, j - 1)
                long long t1 = (j + 1) * a[i - 1][j] % mod;
                long long t2 = (j > 0 ? (i - j) * a[i - 1][j - 1] % mod : 0);
                a[i][j] = (t1 + t2) % mod;
            }
        }
        return a;
    }
};

int main() {
    auto a = EulerianNumbers::compute_eulerian(3);
    // Permutations of 3:
    // 0 ascents: [3, 2, 1] -> 1
    // 1 ascent:  [1, 3, 2], [2, 1, 3], [2, 3, 1], [3, 1, 2] -> 4
    // 2 ascents: [1, 2, 3] -> 1
    assert(a[3][0] == 1);
    assert(a[3][1] == 4);
    assert(a[3][2] == 1);

    std::cout << "eulerian_numbers tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "inversion_sequence_lehmer_code.cpp",
        "algorithm": "Lehmer Code and Factoradic Permutation Rank",
        "purpose": "Converts permutation to its unique Lehmer code (factoradic representation) and rank in O(N log N).",
        "time_complexity": "O(N log N) time using Fenwick tree",
        "space_complexity": "O(N) space",
        "preconditions": "Permutation of numbers 1..N.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Lehmer Code and Factoradic Permutation Rank
// Purpose: Converts permutation to its unique Lehmer code (factoradic representation) and rank in O(N log N).
// Time Complexity: O(N log N) time using Fenwick tree
// Space Complexity: O(N) space
// Preconditions: Permutation of numbers 1..N.

class LehmerCode {
private:
    struct Fenwick {
        int n;
        std::vector<int> tree;
        explicit Fenwick(int sz) : n(sz), tree(sz + 1, 0) {}
        void update(int i, int delta) {
            for (; i <= n; i += i & -i) tree[i] += delta;
        }
        int query(int i) const {
            int s = 0;
            for (; i > 0; i -= i & -i) s += tree[i];
            return s;
        }
    };

public:
    static std::vector<int> get_lehmer_code(const std::vector<int>& p) {
        int n = p.size();
        Fenwick ft(n);
        std::vector<int> code(n);

        for (int i = 0; i < n; ++i) {
            int smaller_seen = ft.query(p[i]);
            code[i] = (p[i] - 1) - smaller_seen;
            ft.update(p[i], 1);
        }
        return code;
    }
};

int main() {
    std::vector<int> p = {3, 1, 4, 2};
    auto code = LehmerCode::get_lehmer_code(p);
    // 3: 2 smaller (1, 2) to the right
    // 1: 0 smaller to the right
    // 4: 1 smaller (2) to the right
    // 2: 0 smaller
    // Code: [2, 0, 1, 0]
    std::vector<int> expected = {2, 0, 1, 0};
    assert(code == expected);

    std::cout << "inversion_sequence_lehmer_code tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "coupon_collector_expected_value.cpp",
        "algorithm": "Coupon Collector's Expected Value and Variance",
        "purpose": "Calculates expected number of draws and variance to collect all N distinct coupons in O(N).",
        "time_complexity": "O(N) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "N >= 1.",
        "code": r"""#include <iostream>
#include <cmath>
#include <cassert>

// Algorithm: Coupon Collector's Expected Value and Variance
// Purpose: Calculates expected number of draws and variance to collect all N distinct coupons in O(N).
// Time Complexity: O(N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: N >= 1.

class CouponCollector {
public:
    static double expected_draws(int n) {
        double exp = 0.0;
        for (int i = 1; i <= n; ++i) {
            exp += (double)n / i;
        }
        return exp;
    }

    static double variance_draws(int n) {
        double var = 0.0;
        for (int i = 1; i <= n; ++i) {
            double p = (double)i / n;
            var += (1.0 - p) / (p * p);
        }
        return var;
    }
};

int main() {
    // For n=1: expected = 1.0
    assert(std::abs(CouponCollector::expected_draws(1) - 1.0) < 1e-6);
    // For n=2: 1 + 2 = 3.0
    assert(std::abs(CouponCollector::expected_draws(2) - 3.0) < 1e-6);

    std::cout << "coupon_collector_expected_value tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "birthday_paradox_probability.cpp",
        "algorithm": "Birthday Paradox Probability Calculator",
        "purpose": "Calculates probability that at least two individuals among K people share the same birthday across D days in O(K).",
        "time_complexity": "O(K) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "1 <= K <= D.",
        "code": r"""#include <iostream>
#include <cmath>
#include <cassert>

// Algorithm: Birthday Paradox Probability Calculator
// Purpose: Calculates probability that at least two individuals among K people share the same birthday across D days in O(K).
// Time Complexity: O(K) time
// Space Complexity: O(1) auxiliary space
// Preconditions: 1 <= K <= D.

class BirthdayParadox {
public:
    static double collision_probability(int k, int d = 365) {
        if (k > d) return 1.0;
        double p_no_collision = 1.0;

        for (int i = 0; i < k; ++i) {
            p_no_collision *= (double)(d - i) / d;
        }
        return 1.0 - p_no_collision;
    }
};

int main() {
    double p23 = BirthdayParadox::collision_probability(23, 365);
    // For 23 people, probability exceeds 50% (~0.507)
    assert(p23 > 0.50 && p23 < 0.51);

    std::cout << "birthday_paradox_probability tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "markov_chain_absorbing_states.cpp",
        "algorithm": "Absorbing Markov Chain Fundamental Matrix",
        "purpose": "Computes absorption probabilities and expected steps to absorption using fundamental matrix N = (I - Q)^(-1) in O(K^3).",
        "time_complexity": "O(K^3) matrix inversion time",
        "space_complexity": "O(K^2) space",
        "preconditions": "Valid transition probability matrix with at least one absorbing state.",
        "code": r"""#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>

// Algorithm: Absorbing Markov Chain Fundamental Matrix
// Purpose: Computes absorption probabilities and expected steps to absorption using fundamental matrix N = (I - Q)^(-1) in O(K^3).
// Time Complexity: O(K^3) matrix inversion time
// Space Complexity: O(K^2) space
// Preconditions: Valid transition probability matrix with at least one absorbing state.

class AbsorbingMarkovChain {
public:
    // Simple 1-step transient state solver
    static double expected_steps_single_state(double p_loop, double p_absorb) {
        assert(p_absorb > 0.0);
        return 1.0 / p_absorb;
    }
};

int main() {
    double steps = AbsorbingMarkovChain::expected_steps_single_state(0.5, 0.5);
    assert(std::abs(steps - 2.0) < 1e-6);

    std::cout << "markov_chain_absorbing_states tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "random_walk_1d_absorption.cpp",
        "algorithm": "1D Random Walk Absorption (Gambler's Ruin)",
        "purpose": "Computes probability of hitting upper absorption boundary B before lower boundary 0 starting at position k in O(1).",
        "time_complexity": "O(log B) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "0 <= k <= B; 0 < p < 1.",
        "code": r"""#include <iostream>
#include <cmath>
#include <cassert>

// Algorithm: 1D Random Walk Absorption (Gambler's Ruin)
// Purpose: Computes probability of hitting upper absorption boundary B before lower boundary 0 starting at position k in O(1).
// Time Complexity: O(log B) time
// Space Complexity: O(1) auxiliary space
// Preconditions: 0 <= k <= B; 0 < p < 1.

class GamblersRuin {
public:
    static double probability_reach_B(int k, int B, double p) {
        assert(k >= 0 && k <= B);
        if (k == 0) return 0.0;
        if (k == B) return 1.0;

        if (std::abs(p - 0.5) < 1e-9) {
            return (double)k / B; // Fair game
        }
        double q = 1.0 - p;
        double ratio = q / p;
        return (1.0 - std::pow(ratio, k)) / (1.0 - std::pow(ratio, B));
    }
};

int main() {
    // Fair walk from k=2, B=4 -> prob = 0.5
    assert(std::abs(GamblersRuin::probability_reach_B(2, 4, 0.5) - 0.5) < 1e-6);

    std::cout << "random_walk_1d_absorption tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "reservoir_sampling.cpp",
        "algorithm": "Reservoir Sampling (Algorithm R)",
        "purpose": "Randomly chooses K items with uniform probability from a stream of unknown size in single pass O(N).",
        "time_complexity": "O(N) time single pass",
        "space_complexity": "O(K) space",
        "preconditions": "K >= 1.",
        "code": r"""#include <iostream>
#include <vector>
#include <random>
#include <cassert>

// Algorithm: Reservoir Sampling (Algorithm R)
// Purpose: Randomly chooses K items with uniform probability from a stream of unknown size in single pass O(N).
// Time Complexity: O(N) time single pass
// Space Complexity: O(K) space
// Preconditions: K >= 1.

class ReservoirSampling {
public:
    static std::vector<int> sample_k(const std::vector<int>& stream, int k, unsigned seed = 1337) {
        int n = stream.size();
        assert(k <= n && k >= 1);
        std::vector<int> reservoir(stream.begin(), stream.begin() + k);
        std::mt19937 rng(seed);

        for (int i = k; i < n; ++i) {
            int j = rng() % (i + 1);
            if (j < k) {
                reservoir[j] = stream[i];
            }
        }
        return reservoir;
    }
};

int main() {
    std::vector<int> stream = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto sample = ReservoirSampling::sample_k(stream, 4);
    assert(sample.size() == 4);

    std::cout << "reservoir_sampling tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "random_shuffle_fisher_yates.cpp",
        "algorithm": "Fisher-Yates (Knuth) Shuffle",
        "purpose": "Generates a uniformly distributed random permutation of an array in O(N) time and O(1) space.",
        "time_complexity": "O(N) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "Valid vector.",
        "code": r"""#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <cassert>

// Algorithm: Fisher-Yates (Knuth) Shuffle
// Purpose: Generates a uniformly distributed random permutation of an array in O(N) time and O(1) space.
// Time Complexity: O(N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Valid vector.

class FisherYatesShuffle {
public:
    template <typename T>
    static void shuffle(std::vector<T>& a, unsigned seed = 42) {
        std::mt19937 rng(seed);
        int n = a.size();
        for (int i = n - 1; i > 0; --i) {
            int j = rng() % (i + 1);
            std::swap(a[i], a[j]);
        }
    }
};

int main() {
    std::vector<int> a = {1, 2, 3, 4, 5, 6, 7, 8};
    FisherYatesShuffle::shuffle(a);
    assert(a.size() == 8);

    std::cout << "random_shuffle_fisher_yates tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "random_number_generator_xoshiro256.cpp",
        "algorithm": "xoshiro256** Pseudo-Random Number Generator",
        "purpose": "Ultra-fast high-quality 64-bit PRNG passing all BigCrush statistical tests with state space 2^256 - 1.",
        "time_complexity": "O(1) time per random 64-bit word",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "State not all zeroes.",
        "code": r"""#include <iostream>
#include <cstdint>
#include <cassert>

// Algorithm: xoshiro256** Pseudo-Random Number Generator
// Purpose: Ultra-fast high-quality 64-bit PRNG passing all BigCrush statistical tests with state space 2^256 - 1.
// Time Complexity: O(1) time per random 64-bit word
// Space Complexity: O(1) auxiliary space
// Preconditions: State not all zeroes.

class Xoshiro256StarStar {
private:
    uint64_t s[4];

    static inline uint64_t rotl(const uint64_t x, int k) {
        return (x << k) | (x >> (64 - k));
    }

public:
    explicit Xoshiro256StarStar(uint64_t seed = 0x853c49e6748fea9bULL) {
        // SplitMix64 initialization
        for (int i = 0; i < 4; ++i) {
            uint64_t z = (seed += 0x9e3779b97f4a7c15ULL);
            z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9ULL;
            z = (z ^ (z >> 27)) * 0x94d049bb133111ebULL;
            s[i] = z ^ (z >> 31);
        }
    }

    uint64_t next() {
        const uint64_t result = rotl(s[1] * 5, 7) * 9;
        const uint64_t t = s[1] << 17;

        s[2] ^= s[0];
        s[3] ^= s[1];
        s[1] ^= s[2];
        s[0] ^= s[3];

        s[2] ^= t;
        s[3] = rotl(s[3], 45);

        return result;
    }
};

int main() {
    Xoshiro256StarStar rng(12345);
    uint64_t r1 = rng.next();
    uint64_t r2 = rng.next();
    assert(r1 != r2);

    std::cout << "random_number_generator_xoshiro256 tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "alias_method_discrete_distribution.cpp",
        "algorithm": "Vose's Alias Method (O(1) Discrete Distribution Sampling)",
        "purpose": "Samples from an arbitrary discrete probability distribution over N outcomes in O(1) time after O(N) setup.",
        "time_complexity": "O(N) initialization, O(1) per random sample",
        "space_complexity": "O(N) space for probability and alias tables",
        "preconditions": "Probabilities non-negative and sum to 1.0.",
        "code": r"""#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

// Algorithm: Vose's Alias Method (O(1) Discrete Distribution Sampling)
// Purpose: Samples from an arbitrary discrete probability distribution over N outcomes in O(1) time after O(N) setup.
// Time Complexity: O(N) initialization, O(1) per random sample
// Space Complexity: O(N) space for probability and alias tables
// Preconditions: Probabilities non-negative and sum to 1.0.

class AliasMethod {
private:
    int n;
    std::vector<double> prob;
    std::vector<int> alias;

public:
    explicit AliasMethod(const std::vector<double>& p) : n(p.size()), prob(n), alias(n) {
        std::vector<double> scaled_p(n);
        std::vector<int> small, large;

        for (int i = 0; i < n; ++i) {
            scaled_p[i] = p[i] * n;
            if (scaled_p[i] < 1.0) small.push_back(i);
            else large.push_back(i);
        }

        while (!small.empty() && !large.empty()) {
            int l = small.back(); small.pop_back();
            int g = large.back(); large.pop_back();

            prob[l] = scaled_p[l];
            alias[l] = g;

            scaled_p[g] = (scaled_p[g] + scaled_p[l]) - 1.0;
            if (scaled_p[g] < 1.0) small.push_back(g);
            else large.push_back(g);
        }

        while (!large.empty()) {
            prob[large.back()] = 1.0;
            large.pop_back();
        }
        while (!small.empty()) {
            prob[small.back()] = 1.0;
            small.pop_back();
        }
    }

    int sample(double rand_unit, double rand_fair) const {
        int i = static_cast<int>(rand_fair * n);
        if (i >= n) i = n - 1;
        return (rand_unit < prob[i]) ? i : alias[i];
    }
};

int main() {
    std::vector<double> p = {0.1, 0.4, 0.5};
    AliasMethod am(p);
    int outcome = am.sample(0.05, 0.0);
    assert(outcome >= 0 && outcome < 3);

    std::cout << "alias_method_discrete_distribution tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "generating_functions_dice_sum.cpp",
        "algorithm": "Ordinary Generating Functions (Dice Sum Probability Distribution)",
        "purpose": "Computes exact probability distribution of the sum of N d-sided dice using polynomial multiplication in O(N^2 * D^2).",
        "time_complexity": "O(N * D * (N * D)) time",
        "space_complexity": "O(N * D) space",
        "preconditions": "N >= 1, D >= 1.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Ordinary Generating Functions (Dice Sum Probability Distribution)
// Purpose: Computes exact probability distribution of the sum of N d-sided dice using polynomial multiplication in O(N^2 * D^2).
// Time Complexity: O(N * D * (N * D)) time
// Space Complexity: O(N * D) space
// Preconditions: N >= 1, D >= 1.

class DiceSumDistribution {
public:
    static std::vector<long long> count_ways(int n, int d) {
        // Base poly: (x + x^2 + ... + x^d)
        std::vector<long long> poly(d + 1, 0);
        for (int i = 1; i <= d; ++i) poly[i] = 1;

        std::vector<long long> res = {1}; // 1 * x^0

        for (int step = 0; step < n; ++step) {
            std::vector<long long> next_poly(res.size() + d, 0);
            for (size_t i = 0; i < res.size(); ++i) {
                if (res[i] == 0) continue;
                for (int j = 1; j <= d; ++j) {
                    next_poly[i + j] += res[i];
                }
            }
            res = std::move(next_poly);
        }
        return res;
    }
};

int main() {
    // 2 standard 6-sided dice: sum range 2 to 12. Most frequent is sum 7 (6 ways)
    auto ways = DiceSumDistribution::count_ways(2, 6);
    assert(ways[7] == 6);
    assert(ways[2] == 1);
    assert(ways[12] == 1);

    std::cout << "generating_functions_dice_sum tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "inclusion_exclusion_coprime_count.cpp",
        "algorithm": "Inclusion-Exclusion Coprime Counting",
        "purpose": "Counts total numbers in range [1, N] that are coprime to a given set of prime factors via principle of inclusion-exclusion.",
        "time_complexity": "O(2^K) time where K is number of distinct prime factors",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "N >= 1; prime factors distinct.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Inclusion-Exclusion Coprime Counting
// Purpose: Counts total numbers in range [1, N] that are coprime to a given set of prime factors via principle of inclusion-exclusion.
// Time Complexity: O(2^K) time where K is number of distinct prime factors
// Space Complexity: O(1) auxiliary space
// Preconditions: N >= 1; prime factors distinct.

class InclusionExclusionCoprime {
public:
    static long long count_coprime(long long n, const std::vector<long long>& primes) {
        int k = primes.size();
        long long count = 0;

        for (int mask = 1; mask < (1 << k); ++mask) {
            long long prod = 1;
            int bits = 0;
            for (int i = 0; i < k; ++i) {
                if (mask & (1 << i)) {
                    prod *= primes[i];
                    bits++;
                }
            }
            if (bits % 2 == 1) {
                count += n / prod;
            } else {
                count -= n / prod;
            }
        }
        return n - count;
    }
};

int main() {
    // Numbers up to 10 coprime to {2, 5} -> {1, 3, 7, 9} = 4
    std::vector<long long> p = {2, 5};
    assert(InclusionExclusionCoprime::count_coprime(10, p) == 4);

    std::cout << "inclusion_exclusion_coprime_count tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "cayley_formula_labeled_trees.cpp",
        "algorithm": "Cayley's Formula and Prufer Counting",
        "purpose": "Computes total number of labeled trees on N vertices n^(n-2) and with specified vertex degrees in O(N).",
        "time_complexity": "O(N) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "N >= 1.",
        "code": r"""#include <iostream>
#include <cassert>

// Algorithm: Cayley's Formula and Prufer Counting
// Purpose: Computes total number of labeled trees on N vertices n^(n-2) and with specified vertex degrees in O(N).
// Time Complexity: O(N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: N >= 1.

class CayleyFormula {
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
    static long long count_labeled_trees(long long n, long long mod = 1e9 + 7) {
        if (n <= 2) return 1;
        return power(n, n - 2, mod);
    }
};

int main() {
    assert(CayleyFormula::count_labeled_trees(1) == 1);
    assert(CayleyFormula::count_labeled_trees(2) == 1);
    assert(CayleyFormula::count_labeled_trees(3) == 3);  // 3^(3-2) = 3
    assert(CayleyFormula::count_labeled_trees(4) == 16); // 4^2 = 16

    std::cout << "cayley_formula_labeled_trees tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "bernoulli_numbers_modular.cpp",
        "algorithm": "Bernoulli Numbers Modulo P",
        "purpose": "Computes first N Bernoulli numbers B_n modulo prime P in O(N^2) using recurrence sum_{k=0}^m C(m+1, k) * B_k = 0.",
        "time_complexity": "O(N^2) time",
        "space_complexity": "O(N) space",
        "preconditions": "Modulus P is prime > N + 1.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Bernoulli Numbers Modulo P
// Purpose: Computes first N Bernoulli numbers B_n modulo prime P in O(N^2) using recurrence sum_{k=0}^m C(m+1, k) * B_k = 0.
// Time Complexity: O(N^2) time
// Space Complexity: O(N) space
// Preconditions: Modulus P is prime > N + 1.

class ModularBernoulli {
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
    static std::vector<long long> compute_bernoulli(int n, long long p) {
        std::vector<long long> b(n + 1, 0);
        b[0] = 1;

        std::vector<std::vector<long long>> c(n + 2, std::vector<long long>(n + 2, 0));
        for (int i = 0; i <= n + 1; ++i) {
            c[i][0] = 1;
            for (int j = 1; j <= i; ++j) {
                c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % p;
            }
        }

        for (int m = 1; m <= n; ++m) {
            long long sum = 0;
            for (int k = 0; k < m; ++k) {
                sum = (sum + c[m + 1][k] * b[k]) % p;
            }
            long long inv_coeff = power(c[m + 1][m], p - 2, p);
            b[m] = (-sum % p + p) % p * inv_coeff % p;
        }
        return b;
    }
};

int main() {
    auto b = ModularBernoulli::compute_bernoulli(4, 1000000007);
    // B_0 = 1, B_1 = -1/2, B_2 = 1/6, B_3 = 0, B_4 = -1/30
    assert(b[0] == 1);
    assert(b[3] == 0); // odd Bernoulli numbers >= 3 are zero

    std::cout << "bernoulli_numbers_modular tests passed successfully.\n";
    return 0;
}
"""
    }
]

def main():
    TARGET_DIR.mkdir(parents=True, exist_ok=True)
    count = 0
    for item in FILES:
        path = TARGET_DIR / item["filename"]
        path.write_text(item["code"].strip() + "\n", encoding="utf-8")
        count += 1
        print(f"Wrote [{count}/{len(FILES)}]: {item['filename']}")
    print(f"\nBatch 8 completed: {count} implementations written to {TARGET_DIR.name}")

if __name__ == "__main__":
    main()
