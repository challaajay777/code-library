#!/usr/bin/env python3
"""
Batch 4 Generator: Bit Manipulation (25 implementations)
Target Directory: Bit Manipulation
"""

import os
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent.parent
TARGET_DIR = REPO_ROOT / "Bit Manipulation"

FILES = [
    {
        "filename": "builtin_bit_operations.cpp",
        "algorithm": "Compiler Builtin Bit Operations",
        "purpose": "Wraps GCC/Clang bitwise intrinsics for popcount, count leading/trailing zeros, and parity across 32 and 64 bit integers.",
        "time_complexity": "O(1) CPU instructions",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "Non-zero inputs for clz/ctz to avoid undefined behavior.",
        "code": r"""#include <iostream>
#include <cstdint>
#include <cassert>

// Algorithm: Compiler Builtin Bit Operations
// Purpose: Wraps GCC/Clang bitwise intrinsics for popcount, count leading/trailing zeros, and parity across 32 and 64 bit integers.
// Time Complexity: O(1) CPU instructions
// Space Complexity: O(1) auxiliary space
// Preconditions: Non-zero inputs for clz/ctz to avoid undefined behavior.

class BitOps {
public:
    static int popcount(uint64_t x) {
        return __builtin_popcountll(x);
    }

    static int clz(uint64_t x) {
        assert(x != 0);
        return __builtin_clzll(x);
    }

    static int ctz(uint64_t x) {
        assert(x != 0);
        return __builtin_ctzll(x);
    }

    static int parity(uint64_t x) {
        return __builtin_parityll(x);
    }

    static uint64_t lowest_set_bit(uint64_t x) {
        return x & -x;
    }

    static uint64_t clear_lowest_set_bit(uint64_t x) {
        return x & (x - 1);
    }
};

int main() {
    uint64_t val = 18; // 10010 in binary
    assert(BitOps::popcount(val) == 2);
    assert(BitOps::ctz(val) == 1);
    assert(BitOps::parity(val) == 0); // Even number of set bits
    assert(BitOps::lowest_set_bit(val) == 2);
    assert(BitOps::clear_lowest_set_bit(val) == 16);

    std::cout << "builtin_bit_operations tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "submask_enumeration.cpp",
        "algorithm": "Submask Enumeration",
        "purpose": "Iterates over all submasks of a bitmask in descending order; enumerates all submasks of all masks in O(3^N).",
        "time_complexity": "O(2^k) for a mask with k set bits; O(3^N) for all masks up to N bits",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "0 <= mask < 2^63.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Submask Enumeration
// Purpose: Iterates over all submasks of a bitmask in descending order; enumerates all submasks of all masks in O(3^N).
// Time Complexity: O(2^k) for a mask with k set bits; O(3^N) for all masks up to N bits
// Space Complexity: O(1) auxiliary space
// Preconditions: 0 <= mask < 2^63.

class SubmaskEnumeration {
public:
    static std::vector<long long> get_submasks(long long mask) {
        std::vector<long long> submasks;
        for (long long s = mask; s > 0; s = (s - 1) & mask) {
            submasks.push_back(s);
        }
        submasks.push_back(0); // empty mask
        return submasks;
    }
};

int main() {
    long long mask = 5; // binary 101: submasks are 5 (101), 4 (100), 1 (001), 0 (000)
    auto res = SubmaskEnumeration::get_submasks(mask);
    std::vector<long long> expected = {5, 4, 1, 0};
    assert(res == expected);

    std::cout << "submask_enumeration tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "gosper_hack_k_subsets.cpp",
        "algorithm": "Gosper's Hack (K-Element Subsets)",
        "purpose": "Generates all bitmasks of size N containing exactly K set bits in lexicographic order in O(1) per subset.",
        "time_complexity": "O(C(N, K)) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "1 <= K <= N <= 62.",
        "code": r"""#include <iostream>
#include <vector>
#include <cstdint>
#include <cassert>

// Algorithm: Gosper's Hack (K-Element Subsets)
// Purpose: Generates all bitmasks of size N containing exactly K set bits in lexicographic order in O(1) per subset.
// Time Complexity: O(C(N, K)) time
// Space Complexity: O(1) auxiliary space
// Preconditions: 1 <= K <= N <= 62.

class GosperHack {
public:
    static std::vector<uint64_t> generate_k_subsets(int n, int k) {
        if (k == 0) return {0};
        if (k > n) return {};

        std::vector<uint64_t> result;
        uint64_t mask = (1ULL << k) - 1ULL;
        uint64_t limit = (1ULL << n);

        while (mask < limit) {
            result.push_back(mask);

            // Gosper's hack step
            uint64_t c = mask & -mask;
            uint64_t r = mask + c;
            mask = (((r ^ mask) >> 2) / c) | r;
        }
        return result;
    }
};

int main() {
    // Generate all subsets of size 4 choose 2 -> 6 subsets
    auto subsets = GosperHack::generate_k_subsets(4, 2);
    assert(subsets.size() == 6);
    // Subsets: 0011(3), 0101(5), 0110(6), 1001(9), 1010(10), 1100(12)
    std::vector<uint64_t> expected = {3, 5, 6, 9, 10, 12};
    assert(subsets == expected);

    std::cout << "gosper_hack_k_subsets tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "gray_code_generation.cpp",
        "algorithm": "Gray Code Generation and Conversion",
        "purpose": "Converts binary to reflected Gray code, inverts Gray code to binary, and generates N-bit Gray code sequences in O(2^N).",
        "time_complexity": "O(1) per conversion, O(2^N) for sequence generation",
        "space_complexity": "O(1) auxiliary space beyond result vector",
        "preconditions": "0 <= N <= 30.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Gray Code Generation and Conversion
// Purpose: Converts binary to reflected Gray code, inverts Gray code to binary, and generates N-bit Gray code sequences in O(2^N).
// Time Complexity: O(1) per conversion, O(2^N) for sequence generation
// Space Complexity: O(1) auxiliary space beyond result vector
// Preconditions: 0 <= N <= 30.

class GrayCode {
public:
    static unsigned int binary_to_gray(unsigned int n) {
        return n ^ (n >> 1);
    }

    static unsigned int gray_to_binary(unsigned int g) {
        unsigned int b = 0;
        for (; g; g >>= 1) {
            b ^= g;
        }
        return b;
    }

    static std::vector<unsigned int> generate_sequence(int n) {
        int total = 1 << n;
        std::vector<unsigned int> seq(total);
        for (int i = 0; i < total; ++i) {
            seq[i] = binary_to_gray(i);
        }
        return seq;
    }
};

int main() {
    for (unsigned int i = 0; i < 32; ++i) {
        unsigned int g = GrayCode::binary_to_gray(i);
        unsigned int b = GrayCode::gray_to_binary(g);
        assert(b == i);
    }

    auto seq = GrayCode::generate_sequence(3);
    assert(seq.size() == 8);
    // Adjacent codes differ by exactly 1 bit
    for (size_t i = 1; i < seq.size(); ++i) {
        assert(__builtin_popcount(seq[i] ^ seq[i - 1]) == 1);
    }

    std::cout << "gray_code_generation tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "bitwise_xor_range_1_to_n.cpp",
        "algorithm": "Prefix and Range XOR Sum (1 to N)",
        "purpose": "Calculates the XOR sum of all integers from 1 to N in O(1) time using periodicity of 4, and range XOR sum [L, R].",
        "time_complexity": "O(1) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "0 <= L <= R.",
        "code": r"""#include <iostream>
#include <cassert>

// Algorithm: Prefix and Range XOR Sum (1 to N)
// Purpose: Calculates the XOR sum of all integers from 1 to N in O(1) time using periodicity of 4, and range XOR sum [L, R].
// Time Complexity: O(1) time
// Space Complexity: O(1) auxiliary space
// Preconditions: 0 <= L <= R.

class RangeXorSum {
public:
    // Computes 1 ^ 2 ^ ... ^ n
    static long long xor_1_to_n(long long n) {
        if (n < 0) return 0;
        long long rem = n % 4;
        if (rem == 0) return n;
        if (rem == 1) return 1;
        if (rem == 2) return n + 1;
        return 0;
    }

    // Computes L ^ (L + 1) ^ ... ^ R
    static long long xor_range(long long l, long long r) {
        assert(l <= r);
        return xor_1_to_n(r) ^ xor_1_to_n(l - 1);
    }
};

int main() {
    assert(RangeXorSum::xor_1_to_n(5) == (1 ^ 2 ^ 3 ^ 4 ^ 5));
    assert(RangeXorSum::xor_1_to_n(6) == (1 ^ 2 ^ 3 ^ 4 ^ 5 ^ 6));
    assert(RangeXorSum::xor_range(3, 6) == (3 ^ 4 ^ 5 ^ 6));

    std::cout << "bitwise_xor_range_1_to_n tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "isolate_lowest_set_bit.cpp",
        "algorithm": "Lowbit and Bit Clearing Tricks",
        "purpose": "Implements classical lowbit tricks: x & (-x), x & (x - 1), x | (x + 1) in O(1).",
        "time_complexity": "O(1) time",
        "space_complexity": "O(1) space",
        "preconditions": "Any 64-bit integer.",
        "code": r"""#include <iostream>
#include <cstdint>
#include <cassert>

// Algorithm: Lowbit and Bit Clearing Tricks
// Purpose: Implements classical lowbit tricks: x & (-x), x & (x - 1), x | (x + 1) in O(1).
// Time Complexity: O(1) time
// Space Complexity: O(1) space
// Preconditions: Any 64-bit integer.

class BitTricks {
public:
    static uint64_t lowbit(uint64_t x) {
        return x & -x;
    }

    static uint64_t clear_lowest_bit(uint64_t x) {
        return x & (x - 1);
    }

    static uint64_t set_lowest_unset_bit(uint64_t x) {
        return x | (x + 1);
    }

    static bool is_power_of_two(uint64_t x) {
        return x > 0 && (x & (x - 1)) == 0;
    }
};

int main() {
    assert(BitTricks::lowbit(12) == 4); // 1100 -> lowest bit is 4
    assert(BitTricks::clear_lowest_bit(12) == 8); // 1100 -> 1000
    assert(BitTricks::set_lowest_unset_bit(10) == 11); // 1010 -> 1011
    assert(BitTricks::is_power_of_two(16) == true);
    assert(BitTricks::is_power_of_two(18) == false);

    std::cout << "isolate_lowest_set_bit tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "highest_set_bit.cpp",
        "algorithm": "Most Significant Set Bit (MSB)",
        "purpose": "Finds the highest set bit and the largest power of 2 less than or equal to X in O(1) time.",
        "time_complexity": "O(1) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "X > 0.",
        "code": r"""#include <iostream>
#include <cstdint>
#include <cassert>

// Algorithm: Most Significant Set Bit (MSB)
// Purpose: Finds the highest set bit and the largest power of 2 less than or equal to X in O(1) time.
// Time Complexity: O(1) time
// Space Complexity: O(1) auxiliary space
// Preconditions: X > 0.

class MostSignificantBit {
public:
    static int highest_bit_index(uint64_t x) {
        assert(x > 0);
        return 63 - __builtin_clzll(x);
    }

    static uint64_t largest_power_of_two_le(uint64_t x) {
        assert(x > 0);
        return 1ULL << highest_bit_index(x);
    }
};

int main() {
    assert(MostSignificantBit::highest_bit_index(16) == 4);
    assert(MostSignificantBit::highest_bit_index(18) == 4);
    assert(MostSignificantBit::largest_power_of_two_le(18) == 16);
    assert(MostSignificantBit::largest_power_of_two_le(31) == 16);

    std::cout << "highest_set_bit tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "bitset_fast_subset_sum.cpp",
        "algorithm": "Bitset-Accelerated Subset Sum",
        "purpose": "Computes subset sum reachability up to target W in O(N * W / 64) time using std::bitset.",
        "time_complexity": "O(N * W / 64) time",
        "space_complexity": "O(W / 64) space",
        "preconditions": "Non-negative items; W <= 100000.",
        "code": r"""#include <iostream>
#include <vector>
#include <bitset>
#include <cassert>

// Algorithm: Bitset-Accelerated Subset Sum
// Purpose: Computes subset sum reachability up to target W in O(N * W / 64) time using std::bitset.
// Time Complexity: O(N * W / 64) time
// Space Complexity: O(W / 64) space
// Preconditions: Non-negative items; W <= 100000.

class BitsetSubsetSum {
public:
    static const int MAX_W = 100005;

    static bool can_achieve_sum(const std::vector<int>& weights, int target) {
        assert(target >= 0 && target < MAX_W);
        std::bitset<MAX_W> bs;
        bs[0] = 1;

        for (int w : weights) {
            if (w < MAX_W) {
                bs |= (bs << w);
            }
        }
        return bs[target];
    }
};

int main() {
    std::vector<int> items = {3, 34, 4, 12, 5, 2};
    assert(BitsetSubsetSum::can_achieve_sum(items, 9) == true); // 4 + 5
    assert(BitsetSubsetSum::can_achieve_sum(items, 30) == false);

    std::cout << "bitset_fast_subset_sum tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "fwht_xor.cpp",
        "algorithm": "Fast Walsh-Hadamard Transform (XOR Convolution)",
        "purpose": "Computes the bitwise XOR convolution of two arrays C[k] = sum_{i ^ j = k} A[i] * B[j] in O(N log N).",
        "time_complexity": "O(N log N) where N = 2^k",
        "space_complexity": "O(1) auxiliary space in-place",
        "preconditions": "Size of array must be a power of two.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Fast Walsh-Hadamard Transform (XOR Convolution)
// Purpose: Computes the bitwise XOR convolution of two arrays C[k] = sum_{i ^ j = k} A[i] * B[j] in O(N log N).
// Time Complexity: O(N log N) where N = 2^k
// Space Complexity: O(1) auxiliary space in-place
// Preconditions: Size of array must be a power of two.

class FWHT_XOR {
public:
    static void transform(std::vector<long long>& a, bool invert) {
        int n = a.size();
        for (int len = 1; 2 * len <= n; len <<= 1) {
            for (int i = 0; i < n; i += 2 * len) {
                for (int j = 0; j < len; ++j) {
                    long long u = a[i + j];
                    long long v = a[i + len + j];
                    a[i + j] = u + v;
                    a[i + len + j] = u - v;
                }
            }
        }
        if (invert) {
            for (int i = 0; i < n; ++i) {
                a[i] /= n;
            }
        }
    }

    static std::vector<long long> convolve(std::vector<long long> a, std::vector<long long> b) {
        int n = a.size();
        transform(a, false);
        transform(b, false);
        for (int i = 0; i < n; ++i) {
            a[i] *= b[i];
        }
        transform(a, true);
        return a;
    }
};

int main() {
    std::vector<long long> a = {1, 2, 0, 0};
    std::vector<long long> b = {3, 4, 0, 0};
    auto c = FWHT_XOR::convolve(a, b);
    // c[0] = a[0]*b[0] + a[1]*b[1] = 1*3 + 2*4 = 11
    // c[1] = a[0]*b[1] + a[1]*b[0] = 1*4 + 2*3 = 10
    assert(c[0] == 11);
    assert(c[1] == 10);
    assert(c[2] == 0 && c[3] == 0);

    std::cout << "fwht_xor tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "fwht_and.cpp",
        "algorithm": "Fast Walsh-Hadamard Transform (AND Convolution)",
        "purpose": "Computes bitwise AND convolution C[k] = sum_{i & j = k} A[i] * B[j] in O(N log N).",
        "time_complexity": "O(N log N) where N = 2^k",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "Size of array must be a power of two.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Fast Walsh-Hadamard Transform (AND Convolution)
// Purpose: Computes bitwise AND convolution C[k] = sum_{i & j = k} A[i] * B[j] in O(N log N).
// Time Complexity: O(N log N) where N = 2^k
// Space Complexity: O(1) auxiliary space
// Preconditions: Size of array must be a power of two.

class FWHT_AND {
public:
    static void transform(std::vector<long long>& a, bool invert) {
        int n = a.size();
        for (int len = 1; 2 * len <= n; len <<= 1) {
            for (int i = 0; i < n; i += 2 * len) {
                for (int j = 0; j < len; ++j) {
                    long long u = a[i + j];
                    long long v = a[i + len + j];
                    if (!invert) {
                        a[i + j] = u + v;
                    } else {
                        a[i + j] = u - v;
                    }
                }
            }
        }
    }

    static std::vector<long long> convolve(std::vector<long long> a, std::vector<long long> b) {
        int n = a.size();
        transform(a, false);
        transform(b, false);
        for (int i = 0; i < n; ++i) {
            a[i] *= b[i];
        }
        transform(a, true);
        return a;
    }
};

int main() {
    std::vector<long long> a = {1, 2, 3, 4};
    std::vector<long long> b = {2, 1, 0, 5};
    auto c = FWHT_AND::convolve(a, b);

    // Naive check for index 0: sum of a[i]*b[j] where i & j == 0
    long long naive_0 = 0;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if ((i & j) == 0) naive_0 += a[i] * b[j];
        }
    }
    assert(c[0] == naive_0);

    std::cout << "fwht_and tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "fwht_or.cpp",
        "algorithm": "Fast Walsh-Hadamard Transform (OR Convolution)",
        "purpose": "Computes bitwise OR convolution C[k] = sum_{i | j = k} A[i] * B[j] in O(N log N).",
        "time_complexity": "O(N log N) where N = 2^k",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "Size of array must be a power of two.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Fast Walsh-Hadamard Transform (OR Convolution)
// Purpose: Computes bitwise OR convolution C[k] = sum_{i | j = k} A[i] * B[j] in O(N log N).
// Time Complexity: O(N log N) where N = 2^k
// Space Complexity: O(1) auxiliary space
// Preconditions: Size of array must be a power of two.

class FWHT_OR {
public:
    static void transform(std::vector<long long>& a, bool invert) {
        int n = a.size();
        for (int len = 1; 2 * len <= n; len <<= 1) {
            for (int i = 0; i < n; i += 2 * len) {
                for (int j = 0; j < len; ++j) {
                    long long u = a[i + j];
                    long long v = a[i + len + j];
                    if (!invert) {
                        a[i + len + j] = u + v;
                    } else {
                        a[i + len + j] = v - u;
                    }
                }
            }
        }
    }

    static std::vector<long long> convolve(std::vector<long long> a, std::vector<long long> b) {
        int n = a.size();
        transform(a, false);
        transform(b, false);
        for (int i = 0; i < n; ++i) {
            a[i] *= b[i];
        }
        transform(a, true);
        return a;
    }
};

int main() {
    std::vector<long long> a = {1, 2, 3, 4};
    std::vector<long long> b = {2, 1, 0, 5};
    auto c = FWHT_OR::convolve(a, b);

    // Naive check for index 3: sum of a[i]*b[j] where i | j == 3
    long long naive_3 = 0;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if ((i | j) == 3) naive_3 += a[i] * b[j];
        }
    }
    assert(c[3] == naive_3);

    std::cout << "fwht_or tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "sos_dp_submask_sums.cpp",
        "algorithm": "Sum Over Subsets (SOS) Dynamic Programming",
        "purpose": "Calculates F[mask] = sum_{sub subseteq mask} A[sub] for all 2^N masks in O(N * 2^N) time.",
        "time_complexity": "O(N * 2^N) time",
        "space_complexity": "O(2^N) space",
        "preconditions": "0 <= N <= 24.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Sum Over Subsets (SOS) Dynamic Programming
// Purpose: Calculates F[mask] = sum_{sub subseteq mask} A[sub] for all 2^N masks in O(N * 2^N) time.
// Time Complexity: O(N * 2^N) time
// Space Complexity: O(2^N) space
// Preconditions: 0 <= N <= 24.

class SumOverSubsets {
public:
    static std::vector<long long> compute_sos(int n, const std::vector<long long>& a) {
        int total = 1 << n;
        assert((int)a.size() == total);
        std::vector<long long> dp = a;

        for (int i = 0; i < n; ++i) {
            for (int mask = 0; mask < total; ++mask) {
                if (mask & (1 << i)) {
                    dp[mask] += dp[mask ^ (1 << i)];
                }
            }
        }
        return dp;
    }
};

int main() {
    // n = 2: masks 0, 1, 2, 3
    std::vector<long long> a = {1, 2, 4, 8};
    auto f = SumOverSubsets::compute_sos(2, a);
    // f[0] = a[0] = 1
    // f[1] = a[0] + a[1] = 3
    // f[2] = a[0] + a[2] = 5
    // f[3] = a[0] + a[1] + a[2] + a[3] = 15
    assert(f[0] == 1);
    assert(f[1] == 3);
    assert(f[2] == 5);
    assert(f[3] == 15);

    std::cout << "sos_dp_submask_sums tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "count_set_bits_1_to_n.cpp",
        "algorithm": "Count Total Set Bits from 1 to N",
        "purpose": "Calculates the total number of 1-bits across all integers from 1 through N in O(log N) time.",
        "time_complexity": "O(log N) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "N >= 0.",
        "code": r"""#include <iostream>
#include <cassert>

// Algorithm: Count Total Set Bits from 1 to N
// Purpose: Calculates the total number of 1-bits across all integers from 1 through N in O(log N) time.
// Time Complexity: O(log N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: N >= 0.

class CountSetBits1ToN {
public:
    static long long count_bits(long long n) {
        if (n <= 0) return 0;
        long long total = 0;
        long long i = 1;

        while (i <= n) {
            long long full_cycles = (n + 1) / (2 * i);
            total += full_cycles * i;

            long long remainder = (n + 1) % (2 * i);
            if (remainder > i) {
                total += remainder - i;
            }
            i <<= 1;
        }
        return total;
    }
};

int main() {
    // For n=4: 1(1), 2(1), 3(2), 4(1) -> total 5 set bits
    assert(CountSetBits1ToN::count_bits(4) == 5);
    // For n=7: 1(1), 2(1), 3(2), 4(1), 5(2), 6(2), 7(3) -> total 12
    assert(CountSetBits1ToN::count_bits(7) == 12);

    std::cout << "count_set_bits_1_to_n tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "bitwise_multiplication_russian_peasant.cpp",
        "algorithm": "Russian Peasant Multiplication",
        "purpose": "Multiplies two numbers using only bitwise shifts and additions in O(log B) time.",
        "time_complexity": "O(log B) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "Non-negative integers.",
        "code": r"""#include <iostream>
#include <cstdint>
#include <cassert>

// Algorithm: Russian Peasant Multiplication
// Purpose: Multiplies two numbers using only bitwise shifts and additions in O(log B) time.
// Time Complexity: O(log B) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Non-negative integers.

class RussianPeasantMultiplication {
public:
    static uint64_t multiply(uint64_t a, uint64_t b) {
        uint64_t res = 0;
        while (b > 0) {
            if (b & 1) {
                res += a;
            }
            a <<= 1;
            b >>= 1;
        }
        return res;
    }
};

int main() {
    assert(RussianPeasantMultiplication::multiply(18, 11) == 198);
    assert(RussianPeasantMultiplication::multiply(0, 100) == 0);
    assert(RussianPeasantMultiplication::multiply(12345, 6789) == 12345ULL * 6789ULL);

    std::cout << "bitwise_multiplication_russian_peasant tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "bitwise_division.cpp",
        "algorithm": "Bitwise Division",
        "purpose": "Computes quotient and remainder of two integers using bit shifts and subtraction without / or % operators.",
        "time_complexity": "O(log(dividend)) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "Divisor != 0.",
        "code": r"""#include <iostream>
#include <cstdint>
#include <cassert>

// Algorithm: Bitwise Division
// Purpose: Computes quotient and remainder of two integers using bit shifts and subtraction without / or % operators.
// Time Complexity: O(log(dividend)) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Divisor != 0.

class BitwiseDivision {
public:
    static std::pair<uint64_t, uint64_t> divide(uint64_t dividend, uint64_t divisor) {
        assert(divisor != 0);
        uint64_t quotient = 0;

        for (int i = 63; i >= 0; --i) {
            if ((dividend >> i) >= divisor) {
                quotient |= (1ULL << i);
                dividend -= (divisor << i);
            }
        }
        return {quotient, dividend}; // {quotient, remainder}
    }
};

int main() {
    auto [q, r] = BitwiseDivision::divide(43, 5);
    assert(q == 8 && r == 3);

    auto [q2, r2] = BitwiseDivision::divide(100, 10);
    assert(q2 == 10 && r2 == 0);

    std::cout << "bitwise_division tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "swap_bits_in_integer.cpp",
        "algorithm": "Swap Bits at Arbitrary Positions",
        "purpose": "Swaps the bits at index i and index j in an integer in O(1) time.",
        "time_complexity": "O(1) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "0 <= i, j < 64.",
        "code": r"""#include <iostream>
#include <cstdint>
#include <cassert>

// Algorithm: Swap Bits at Arbitrary Positions
// Purpose: Swaps the bits at index i and index j in an integer in O(1) time.
// Time Complexity: O(1) time
// Space Complexity: O(1) auxiliary space
// Preconditions: 0 <= i, j < 64.

class SwapBits {
public:
    static uint64_t swap_bits(uint64_t n, int i, int j) {
        if (((n >> i) & 1) != ((n >> j) & 1)) {
            uint64_t mask = (1ULL << i) | (1ULL << j);
            n ^= mask;
        }
        return n;
    }
};

int main() {
    // 28 = 0001 1100. Swap bit 0 and bit 3:
    // bit 0 is 0, bit 3 is 1 -> becomes 0001 0101 = 21
    assert(SwapBits::swap_bits(28, 0, 3) == 21);

    std::cout << "swap_bits_in_integer tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "reverse_bits_32.cpp",
        "algorithm": "Reverse 32-bit Integer",
        "purpose": "Reverses the 32 bits of an unsigned integer in O(1) time using parallel bitmask shifts.",
        "time_complexity": "O(1) time (5 bitwise swap steps)",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "32-bit unsigned integer.",
        "code": r"""#include <iostream>
#include <cstdint>
#include <cassert>

// Algorithm: Reverse 32-bit Integer
// Purpose: Reverses the 32 bits of an unsigned integer in O(1) time using parallel bitmask shifts.
// Time Complexity: O(1) time (5 bitwise swap steps)
// Space Complexity: O(1) auxiliary space
// Preconditions: 32-bit unsigned integer.

class ReverseBits32 {
public:
    static uint32_t reverse(uint32_t n) {
        n = ((n & 0xFFFF0000) >> 16) | ((n & 0x0000FFFF) << 16);
        n = ((n & 0xFF00FF00) >> 8)  | ((n & 0x00FF00FF) << 8);
        n = ((n & 0xF0F0F0F0) >> 4)  | ((n & 0x0F0F0F0F) << 4);
        n = ((n & 0xCCCCCCCC) >> 2)  | ((n & 0x33333333) << 2);
        n = ((n & 0xAAAAAAAA) >> 1)  | ((n & 0x55555555) << 1);
        return n;
    }
};

int main() {
    uint32_t x = 43261596; // 00000010100101000001111010011100
    uint32_t rev = ReverseBits32::reverse(x);
    assert(rev == 964176192); // 00111001011110000010100101000000

    std::cout << "reverse_bits_32 tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "find_two_non_repeating_elements.cpp",
        "algorithm": "Find Two Unique Non-Repeating Elements",
        "purpose": "Finds the two elements that appear once in an array where every other element appears twice in O(N) and O(1) space.",
        "time_complexity": "O(N) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "Array contains exactly two distinct elements appearing once, all others twice.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Find Two Unique Non-Repeating Elements
// Purpose: Finds the two elements that appear once in an array where every other element appears twice in O(N) and O(1) space.
// Time Complexity: O(N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Array contains exactly two distinct elements appearing once, all others twice.

class TwoUniqueElements {
public:
    static std::pair<int, int> find_unique_pair(const std::vector<int>& nums) {
        int xor_all = 0;
        for (int x : nums) xor_all ^= x;

        // Find any set bit in xor_all (lowest set bit)
        int diff_bit = xor_all & -xor_all;

        int a = 0, b = 0;
        for (int x : nums) {
            if (x & diff_bit) {
                a ^= x;
            } else {
                b ^= x;
            }
        }
        if (a > b) std::swap(a, b);
        return {a, b};
    }
};

int main() {
    std::vector<int> nums = {1, 2, 1, 3, 2, 5};
    auto [x, y] = TwoUniqueElements::find_unique_pair(nums);
    assert(x == 3 && y == 5);

    std::cout << "find_two_non_repeating_elements tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "find_single_number_thrice.cpp",
        "algorithm": "Single Number Among Triplets",
        "purpose": "Finds the single element in an array where every other element appears exactly three times in O(N) and O(1) space.",
        "time_complexity": "O(N * 32) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "Every element appears three times except one.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Single Number Among Triplets
// Purpose: Finds the single element in an array where every other element appears exactly three times in O(N) and O(1) space.
// Time Complexity: O(N * 32) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Every element appears three times except one.

class SingleNumberThrice {
public:
    static int single_number(const std::vector<int>& nums) {
        int result = 0;
        for (int i = 0; i < 32; ++i) {
            int bit_sum = 0;
            for (int x : nums) {
                if ((x >> i) & 1) {
                    bit_sum++;
                }
            }
            if (bit_sum % 3 != 0) {
                result |= (1 << i);
            }
        }
        return result;
    }
};

int main() {
    std::vector<int> a = {2, 2, 3, 2};
    assert(SingleNumberThrice::single_number(a) == 3);

    std::vector<int> b = {0, 1, 0, 1, 0, 1, 99};
    assert(SingleNumberThrice::single_number(b) == 99);

    std::cout << "find_single_number_thrice tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "power_of_four_check.cpp",
        "algorithm": "Power of Four Check",
        "purpose": "Determines whether a number is a power of 4 in O(1) time without loops or recursion.",
        "time_complexity": "O(1) time",
        "space_complexity": "O(1) space",
        "preconditions": "32-bit signed integer.",
        "code": r"""#include <iostream>
#include <cassert>

// Algorithm: Power of Four Check
// Purpose: Determines whether a number is a power of 4 in O(1) time without loops or recursion.
// Time Complexity: O(1) time
// Space Complexity: O(1) space
// Preconditions: 32-bit signed integer.

class PowerOfFour {
public:
    static bool is_power_of_four(int n) {
        // n > 0, exactly one bit set, and the bit is at an even position (0x55555555 mask)
        return n > 0 && (n & (n - 1)) == 0 && (n & 0x55555555) != 0;
    }
};

int main() {
    assert(PowerOfFour::is_power_of_four(16) == true);
    assert(PowerOfFour::is_power_of_four(5) == false);
    assert(PowerOfFour::is_power_of_four(1) == true);
    assert(PowerOfFour::is_power_of_four(8) == false); // power of 2, but not 4

    std::cout << "power_of_four_check tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "power_of_two_utilities.cpp",
        "algorithm": "Power of Two Utilities",
        "purpose": "Rounds up to next power of 2, rounds down to previous power of 2, and tests power of 2 in O(1).",
        "time_complexity": "O(1) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "X > 0.",
        "code": r"""#include <iostream>
#include <cstdint>
#include <cassert>

// Algorithm: Power of Two Utilities
// Purpose: Rounds up to next power of 2, rounds down to previous power of 2, and tests power of 2 in O(1).
// Time Complexity: O(1) time
// Space Complexity: O(1) auxiliary space
// Preconditions: X > 0.

class PowerOfTwoUtils {
public:
    static uint64_t next_power_of_two(uint64_t x) {
        if (x <= 1) return 1;
        return 1ULL << (64 - __builtin_clzll(x - 1));
    }

    static uint64_t prev_power_of_two(uint64_t x) {
        assert(x > 0);
        return 1ULL << (63 - __builtin_clzll(x));
    }
};

int main() {
    assert(PowerOfTwoUtils::next_power_of_two(5) == 8);
    assert(PowerOfTwoUtils::next_power_of_two(16) == 16);
    assert(PowerOfTwoUtils::prev_power_of_two(15) == 8);
    assert(PowerOfTwoUtils::prev_power_of_two(16) == 16);

    std::cout << "power_of_two_utilities tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "maximum_xor_two_numbers_trie.cpp",
        "algorithm": "Maximum XOR of Two Numbers (Binary Trie)",
        "purpose": "Finds the maximum bitwise XOR achievable by any pair of elements in array in O(N * 31) time.",
        "time_complexity": "O(N * 31) time",
        "space_complexity": "O(N * 31) space",
        "preconditions": "Non-negative integers.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Maximum XOR of Two Numbers (Binary Trie)
// Purpose: Finds the maximum bitwise XOR achievable by any pair of elements in array in O(N * 31) time.
// Time Complexity: O(N * 31) time
// Space Complexity: O(N * 31) space
// Preconditions: Non-negative integers.

class MaxXorPairTrie {
private:
    struct Node {
        int next[2];
        Node() { next[0] = next[1] = -1; }
    };
    std::vector<Node> trie;

public:
    MaxXorPairTrie() {
        trie.emplace_back();
    }

    void insert(int val) {
        int u = 0;
        for (int i = 30; i >= 0; --i) {
            int b = (val >> i) & 1;
            if (trie[u].next[b] == -1) {
                trie[u].next[b] = trie.size();
                trie.emplace_back();
            }
            u = trie[u].next[b];
        }
    }

    int query_max_xor(int val) const {
        int u = 0;
        int ans = 0;
        for (int i = 30; i >= 0; --i) {
            int b = (val >> i) & 1;
            int want = 1 - b;
            if (trie[u].next[want] != -1) {
                ans |= (1 << i);
                u = trie[u].next[want];
            } else {
                u = trie[u].next[b];
            }
        }
        return ans;
    }

    static int find_maximum_xor(const std::vector<int>& nums) {
        MaxXorPairTrie t;
        for (int x : nums) t.insert(x);

        int max_xor = 0;
        for (int x : nums) {
            max_xor = std::max(max_xor, t.query_max_xor(x));
        }
        return max_xor;
    }
};

int main() {
    std::vector<int> a = {3, 10, 5, 25, 2, 8};
    assert(MaxXorPairTrie::find_maximum_xor(a) == 28); // 5 ^ 25 = 28

    std::cout << "maximum_xor_two_numbers_trie tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "minimum_xor_pair.cpp",
        "algorithm": "Minimum XOR Pair in Array",
        "purpose": "Finds two distinct elements in array with minimum XOR value in O(N log N) by sorting adjacent elements.",
        "time_complexity": "O(N log N) time",
        "space_complexity": "O(1) auxiliary space beyond sort",
        "preconditions": "Array length >= 2.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Minimum XOR Pair in Array
// Purpose: Finds two distinct elements in array with minimum XOR value in O(N log N) by sorting adjacent elements.
// Time Complexity: O(N log N) time
// Space Complexity: O(1) auxiliary space beyond sort
// Preconditions: Array length >= 2.

class MinimumXorPair {
public:
    static int min_xor_pair(std::vector<int>& a) {
        assert(a.size() >= 2);
        std::sort(a.begin(), a.end());
        int min_xor = 2e9;

        for (size_t i = 0; i + 1 < a.size(); ++i) {
            min_xor = std::min(min_xor, a[i] ^ a[i + 1]);
        }
        return min_xor;
    }
};

int main() {
    std::vector<int> a = {9, 5, 3};
    assert(MinimumXorPair::min_xor_pair(a) == 6); // 5 ^ 3 = 6

    std::vector<int> b = {1, 2, 3, 4, 5};
    assert(MinimumXorPair::min_xor_pair(b) == 1); // 2 ^ 3 = 1

    std::cout << "minimum_xor_pair tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "bitwise_trie_xor_query.cpp",
        "algorithm": "Binary Trie with Dynamic Add and Remove",
        "purpose": "Maintains a multi-set of integers supporting insertion, deletion, and maximum/minimum XOR query with target in O(B).",
        "time_complexity": "O(B) per insertion, deletion, and query where B = 30",
        "space_complexity": "O(N * B) space",
        "preconditions": "Non-negative 30-bit integers.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Binary Trie with Dynamic Add and Remove
// Purpose: Maintains a multi-set of integers supporting insertion, deletion, and maximum/minimum XOR query with target in O(B).
// Time Complexity: O(B) per insertion, deletion, and query where B = 30
// Space Complexity: O(N * B) space
// Preconditions: Non-negative 30-bit integers.

class DynamicBinaryTrie {
private:
    struct Node {
        int next[2];
        int count;
        Node() : count(0) { next[0] = next[1] = -1; }
    };
    std::vector<Node> trie;

public:
    DynamicBinaryTrie() {
        trie.emplace_back();
    }

    void insert(int val) {
        int u = 0;
        trie[u].count++;
        for (int i = 29; i >= 0; --i) {
            int b = (val >> i) & 1;
            if (trie[u].next[b] == -1) {
                trie[u].next[b] = trie.size();
                trie.emplace_back();
            }
            u = trie[u].next[b];
            trie[u].count++;
        }
    }

    void erase(int val) {
        int u = 0;
        trie[u].count--;
        for (int i = 29; i >= 0; --i) {
            int b = (val >> i) & 1;
            u = trie[u].next[b];
            trie[u].count--;
        }
    }

    int query_max_xor(int val) const {
        int u = 0;
        int ans = 0;
        for (int i = 29; i >= 0; --i) {
            int b = (val >> i) & 1;
            int want = 1 - b;
            if (trie[u].next[want] != -1 && trie[trie[u].next[want]].count > 0) {
                ans |= (1 << i);
                u = trie[u].next[want];
            } else {
                u = trie[u].next[b];
            }
        }
        return ans;
    }
};

int main() {
    DynamicBinaryTrie t;
    t.insert(5);
    t.insert(10);
    assert(t.query_max_xor(10) == (10 ^ 5)); // 15

    t.erase(5);
    assert(t.query_max_xor(10) == 0); // Only 10 remains, 10 ^ 10 = 0

    std::cout << "bitwise_trie_xor_query tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "subset_xor_basis.cpp",
        "algorithm": "Linear Basis for XOR (Gaussian Elimination in GF(2))",
        "purpose": "Maintains a vector space basis under XOR to find max XOR subset, test subspace span, and query rank in O(B).",
        "time_complexity": "O(B) per insertion and max XOR query where B = 60",
        "space_complexity": "O(B) space",
        "preconditions": "64-bit unsigned integers.",
        "code": r"""#include <iostream>
#include <vector>
#include <cstdint>
#include <cassert>

// Algorithm: Linear Basis for XOR (Gaussian Elimination in GF(2))
// Purpose: Maintains a vector space basis under XOR to find max XOR subset, test subspace span, and query rank in O(B).
// Time Complexity: O(B) per insertion and max XOR query where B = 60
// Space Complexity: O(B) space
// Preconditions: 64-bit unsigned integers.

class LinearXorBasis {
private:
    static const int BITS = 62;
    uint64_t basis[BITS];
    int size;

public:
    LinearXorBasis() : size(0) {
        for (int i = 0; i < BITS; ++i) basis[i] = 0;
    }

    bool insert(uint64_t mask) {
        for (int i = BITS - 1; i >= 0; --i) {
            if ((mask >> i) & 1) {
                if (!basis[i]) {
                    basis[i] = mask;
                    size++;
                    return true;
                }
                mask ^= basis[i];
            }
        }
        return false; // Linearly dependent
    }

    uint64_t get_max_xor() const {
        uint64_t max_xor = 0;
        for (int i = BITS - 1; i >= 0; --i) {
            if ((max_xor ^ basis[i]) > max_xor) {
                max_xor ^= basis[i];
            }
        }
        return max_xor;
    }

    bool can_form(uint64_t mask) const {
        for (int i = BITS - 1; i >= 0; --i) {
            if ((mask >> i) & 1) {
                if (!basis[i]) return false;
                mask ^= basis[i];
            }
        }
        return true;
    }

    int rank() const { return size; }
};

int main() {
    LinearXorBasis b;
    b.insert(3); // 011
    b.insert(5); // 101
    assert(b.get_max_xor() == 6); // 3 ^ 5 = 6 (110)
    assert(b.can_form(6) == true);
    assert(b.can_form(7) == false);

    std::cout << "subset_xor_basis tests passed successfully.\n";
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
    print(f"\nBatch 4 completed: {count} implementations written to {TARGET_DIR.name}")

if __name__ == "__main__":
    main()
