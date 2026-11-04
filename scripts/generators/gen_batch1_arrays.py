#!/usr/bin/env python3
"""
Batch 1 Generator: Arrays and Prefix Techniques (+33 implementations)
Target Directory: Basics, Arrays, and Implementation
"""

import os
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent.parent
TARGET_DIR = REPO_ROOT / "Basics, Arrays, and Implementation"

FILES = [
    {
        "filename": "prefix_xor_1d.cpp",
        "algorithm": "1D Prefix XOR",
        "purpose": "Computes range XOR sum queries on static array in O(1) time after O(N) preprocessing.",
        "time_complexity": "O(N) preprocessing, O(1) per query",
        "space_complexity": "O(N) auxiliary space",
        "preconditions": "Array indices 0 <= L <= R < N.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: 1D Prefix XOR
// Purpose: Computes range XOR sum queries on static array in O(1) time after O(N) preprocessing.
// Time Complexity: O(N) preprocessing, O(1) per query
// Space Complexity: O(N) auxiliary space
// Preconditions: Array indices 0 <= L <= R < N.

class PrefixXor1D {
private:
    std::vector<long long> px;

public:
    PrefixXor1D() = default;
    explicit PrefixXor1D(const std::vector<long long>& a) {
        int n = a.size();
        px.assign(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            px[i + 1] = px[i] ^ a[i];
        }
    }

    // Returns XOR sum of elements in [l, r] (0-indexed, inclusive)
    long long query(int l, int r) const {
        assert(l >= 0 && r + 1 < (int)px.size() && l <= r);
        return px[r + 1] ^ px[l];
    }
};

int main() {
    std::vector<long long> a = {3, 8, 2, 5, 1, 4, 7};
    PrefixXor1D px(a);

    assert(px.query(0, 0) == 3);
    assert(px.query(0, 1) == (3 ^ 8));
    assert(px.query(1, 3) == (8 ^ 2 ^ 5));
    assert(px.query(0, 6) == (3 ^ 8 ^ 2 ^ 5 ^ 1 ^ 4 ^ 7));
    assert(px.query(2, 4) == (2 ^ 5 ^ 1));

    std::cout << "prefix_xor_1d tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "prefix_frequencies.cpp",
        "algorithm": "Prefix Frequency Counts",
        "purpose": "Maintains prefix count histograms for bounded alphabets/values to answer range frequency queries in O(Sigma).",
        "time_complexity": "O(N * Sigma) preprocessing, O(Sigma) per range query",
        "space_complexity": "O(N * Sigma) auxiliary space",
        "preconditions": "Alphabet size Sigma is small (typically <= 26 for lowercase letters).",
        "code": r"""#include <iostream>
#include <vector>
#include <string>
#include <cassert>

// Algorithm: Prefix Frequency Counts
// Purpose: Maintains prefix count histograms for bounded alphabets/values to answer range frequency queries in O(Sigma).
// Time Complexity: O(N * Sigma) preprocessing, O(Sigma) per range query
// Space Complexity: O(N * Sigma) auxiliary space
// Preconditions: Alphabet size Sigma is small (typically <= 26 for lowercase letters).

class PrefixFrequencies {
private:
    int n;
    int sigma;
    std::vector<std::vector<int>> pref;

public:
    PrefixFrequencies(const std::string& s, int alphabet_size = 26, char base_char = 'a')
        : n(s.size()), sigma(alphabet_size), pref(alphabet_size, std::vector<int>(n + 1, 0)) {
        for (int i = 0; i < n; ++i) {
            int c = s[i] - base_char;
            for (int ch = 0; ch < sigma; ++ch) {
                pref[ch][i + 1] = pref[ch][i] + (ch == c ? 1 : 0);
            }
        }
    }

    int count(int l, int r, char ch, char base_char = 'a') const {
        assert(l >= 0 && r < n && l <= r);
        int c = ch - base_char;
        assert(c >= 0 && c < sigma);
        return pref[c][r + 1] - pref[c][l];
    }

    // Check if substring s[l..r] can be rearranged into a palindrome
    bool can_form_palindrome(int l, int r) const {
        int odd_count = 0;
        for (int c = 0; c < sigma; ++c) {
            if ((pref[c][r + 1] - pref[c][l]) % 2 != 0) {
                odd_count++;
            }
        }
        return odd_count <= 1;
    }
};

int main() {
    std::string s = "abacaba";
    PrefixFrequencies pf(s, 26, 'a');

    assert(pf.count(0, 6, 'a') == 4);
    assert(pf.count(0, 6, 'b') == 2);
    assert(pf.count(0, 6, 'c') == 1);
    assert(pf.count(1, 3, 'a') == 1);
    assert(pf.count(1, 3, 'b') == 1);

    assert(pf.can_form_palindrome(0, 6) == true);
    assert(pf.can_form_palindrome(0, 2) == true); // "aba"
    assert(pf.can_form_palindrome(0, 3) == false); // "abac"

    std::cout << "prefix_frequencies tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "equilibrium_index.cpp",
        "algorithm": "Equilibrium Index Finder",
        "purpose": "Finds all indices in an array where the sum of lower indices equals the sum of higher indices in O(N).",
        "time_complexity": "O(N) time",
        "space_complexity": "O(1) auxiliary space beyond input",
        "preconditions": "64-bit integers prevent sum overflow.",
        "code": r"""#include <iostream>
#include <vector>
#include <numeric>
#include <cassert>

// Algorithm: Equilibrium Index Finder
// Purpose: Finds all indices in an array where the sum of lower indices equals the sum of higher indices in O(N).
// Time Complexity: O(N) time
// Space Complexity: O(1) auxiliary space beyond input
// Preconditions: 64-bit integers prevent sum overflow.

class EquilibriumIndexFinder {
public:
    static std::vector<int> find_all(const std::vector<long long>& a) {
        long long total_sum = std::accumulate(a.begin(), a.end(), 0LL);
        long long left_sum = 0;
        std::vector<int> result;

        for (int i = 0; i < (int)a.size(); ++i) {
            long long right_sum = total_sum - left_sum - a[i];
            if (left_sum == right_sum) {
                result.push_back(i);
            }
            left_sum += a[i];
        }
        return result;
    }

    static int find_first(const std::vector<long long>& a) {
        auto all = find_all(a);
        return all.empty() ? -1 : all.front();
    }
};

int main() {
    std::vector<long long> a = {-7, 1, 5, 2, -4, 3, 0};
    auto eq = EquilibriumIndexFinder::find_all(a);
    // Index 3: left = -7+1+5 = -1, right = -4+3+0 = -1
    // Index 6: left = -7+1+5+2-4+3 = 0, right = 0
    assert(eq.size() == 2);
    assert(eq[0] == 3);
    assert(eq[1] == 6);

    std::vector<long long> b = {1, 2, 3};
    assert(EquilibriumIndexFinder::find_first(b) == -1);

    std::cout << "equilibrium_index tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "difference_array_linear.cpp",
        "algorithm": "Linear Difference Array (Arithmetic Progression Range Update)",
        "purpose": "Supports range addition of an arithmetic progression A[i] += a*i + b in O(1) time using second-order difference arrays.",
        "time_complexity": "O(1) per range addition, O(N) array reconstruction",
        "space_complexity": "O(N) auxiliary space",
        "preconditions": "0 <= l <= r < N.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Linear Difference Array (Arithmetic Progression Range Update)
// Purpose: Supports range addition of an arithmetic progression A[i] += a*i + b in O(1) time using second-order difference arrays.
// Time Complexity: O(1) per range addition, O(N) array reconstruction
// Space Complexity: O(N) auxiliary space
// Preconditions: 0 <= l <= r < N.

class LinearDifferenceArray {
private:
    int n;
    std::vector<long long> d2;

public:
    explicit LinearDifferenceArray(int size) : n(size), d2(size + 3, 0) {}

    // Adds (start_val + k * diff) to index (l + k) for k = 0, 1, ..., r - l
    void add_ap(int l, int r, long long start_val, long long diff) {
        assert(l >= 0 && r < n && l <= r);
        long long len = r - l + 1;
        long long end_val = start_val + (len - 1) * diff;

        d2[l] += start_val;
        d2[l + 1] += diff - start_val;
        d2[r + 1] -= end_val + diff;
        d2[r + 2] += end_val;
    }

    std::vector<long long> reconstruct() const {
        std::vector<long long> d1(n + 1, 0);
        long long run = 0;
        for (int i = 0; i < n; ++i) {
            run += d2[i];
            d1[i] = run;
        }
        std::vector<long long> res(n, 0);
        long long val = 0;
        for (int i = 0; i < n; ++i) {
            val += d1[i];
            res[i] = val;
        }
        return res;
    }
};

int main() {
    LinearDifferenceArray lda(5);
    // Add AP [2, 5, 8] from index 1 to 3: start=2, diff=3
    lda.add_ap(1, 3, 2, 3);
    auto res = lda.reconstruct();
    std::vector<long long> expected = {0, 2, 5, 8, 0};
    assert(res == expected);

    // Add another constant AP [4, 4] from index 2 to 3: start=4, diff=0
    lda.add_ap(2, 3, 4, 0);
    res = lda.reconstruct();
    expected = {0, 2, 9, 12, 0};
    assert(res == expected);

    std::cout << "difference_array_linear tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "difference_array_3d.cpp",
        "algorithm": "3D Difference Array",
        "purpose": "Performs subvolume updates in O(1) time and reconstructs the full 3D array in O(X*Y*Z).",
        "time_complexity": "O(1) per 3D box update, O(X*Y*Z) prefix reconstruction",
        "space_complexity": "O(X*Y*Z) space",
        "preconditions": "Coordinates 0 <= x1 <= x2 < X, 0 <= y1 <= y2 < Y, 0 <= z1 <= z2 < Z.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: 3D Difference Array
// Purpose: Performs subvolume updates in O(1) time and reconstructs the full 3D array in O(X*Y*Z).
// Time Complexity: O(1) per 3D box update, O(X*Y*Z) prefix reconstruction
// Space Complexity: O(X*Y*Z) space
// Preconditions: Coordinates 0 <= x1 <= x2 < X, 0 <= y1 <= y2 < Y, 0 <= z1 <= z2 < Z.

class DifferenceArray3D {
private:
    int X, Y, Z;
    std::vector<std::vector<std::vector<long long>>> d;

    void add_corner(int x, int y, int z, long long val) {
        if (x <= X && y <= Y && z <= Z) {
            d[x][y][z] += val;
        }
    }

public:
    DifferenceArray3D(int x, int y, int z) : X(x), Y(y), Z(z),
        d(x + 2, std::vector<std::vector<long long>>(y + 2, std::vector<long long>(z + 2, 0))) {}

    void add_box(int x1, int y1, int z1, int x2, int y2, int z2, long long val) {
        assert(x1 >= 0 && x1 <= x2 && x2 < X);
        assert(y1 >= 0 && y1 <= y2 && y2 < Y);
        assert(z1 >= 0 && z1 <= z2 && z2 < Z);

        add_corner(x1, y1, z1, val);
        add_corner(x2 + 1, y1, z1, -val);
        add_corner(x1, y2 + 1, z1, -val);
        add_corner(x1, y1, z2 + 1, -val);
        add_corner(x2 + 1, y2 + 1, z1, val);
        add_corner(x2 + 1, y1, z2 + 1, val);
        add_corner(x1, y2 + 1, z2 + 1, val);
        add_corner(x2 + 1, y2 + 1, z2 + 1, -val);
    }

    std::vector<std::vector<std::vector<long long>>> reconstruct() {
        auto res = d;
        for (int i = 0; i < X; ++i) {
            for (int j = 0; j < Y; ++j) {
                for (int k = 0; k < Z; ++k) {
                    long long cur = res[i][j][k];
                    if (i > 0) cur += res[i - 1][j][k];
                    if (j > 0) cur += res[i][j - 1][k];
                    if (k > 0) cur += res[i][j][k - 1];
                    if (i > 0 && j > 0) cur -= res[i - 1][j - 1][k];
                    if (i > 0 && k > 0) cur -= res[i - 1][j][k - 1];
                    if (j > 0 && k > 0) cur -= res[i][j - 1][k - 1];
                    if (i > 0 && j > 0 && k > 0) cur += res[i - 1][j - 1][k - 1];
                    res[i][j][k] = cur;
                }
            }
        }
        res.resize(X);
        for (auto& plane : res) {
            plane.resize(Y);
            for (auto& row : plane) {
                row.resize(Z);
            }
        }
        return res;
    }
};

int main() {
    DifferenceArray3D da(3, 3, 3);
    da.add_box(0, 0, 0, 1, 1, 1, 5);
    da.add_box(1, 1, 1, 2, 2, 2, 3);
    auto grid = da.reconstruct();

    assert(grid[0][0][0] == 5);
    assert(grid[1][1][1] == 8); // 5 + 3
    assert(grid[2][2][2] == 3);
    assert(grid[0][2][2] == 0);

    std::cout << "difference_array_3d tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "subarray_sum_divisible_by_k.cpp",
        "algorithm": "Subarrays with Sum Divisible by K",
        "purpose": "Counts the number of non-empty continuous subarrays whose sum is evenly divisible by K using prefix remainders.",
        "time_complexity": "O(N) time",
        "space_complexity": "O(K) auxiliary space",
        "preconditions": "K >= 1. Handles negative integers correctly.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Subarrays with Sum Divisible by K
// Purpose: Counts the number of non-empty continuous subarrays whose sum is evenly divisible by K using prefix remainders.
// Time Complexity: O(N) time
// Space Complexity: O(K) auxiliary space
// Preconditions: K >= 1. Handles negative integers correctly.

class SubarraySumDivisibleByK {
public:
    static long long count_subarrays(const std::vector<long long>& a, long long k) {
        assert(k > 0);
        std::vector<long long> rem_count(k, 0);
        rem_count[0] = 1;

        long long running_sum = 0;
        long long ans = 0;

        for (long long x : a) {
            running_sum += x;
            long long rem = (running_sum % k + k) % k;
            ans += rem_count[rem];
            rem_count[rem]++;
        }
        return ans;
    }
};

int main() {
    std::vector<long long> a = {4, 5, 0, -2, -3, 1};
    // Subarrays divisible by 5:
    // [5], [5, 0], [0], [4, 5, 0, -2, -3, 1] sum=5, [-2, -3], [5, 0, -2, -3], [0, -2, -3] -> total 7
    assert(SubarraySumDivisibleByK::count_subarrays(a, 5) == 7);

    std::vector<long long> b = {5};
    assert(SubarraySumDivisibleByK::count_subarrays(b, 9) == 0);

    std::cout << "subarray_sum_divisible_by_k tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "subarray_xor_equals_k.cpp",
        "algorithm": "Subarrays with XOR Sum Equal to K",
        "purpose": "Counts total contiguous subarrays whose cumulative XOR sum equals a given target K using a hash map or frequency array.",
        "time_complexity": "O(N) average time",
        "space_complexity": "O(N) auxiliary space",
        "preconditions": "Valid non-negative XOR targets.",
        "code": r"""#include <iostream>
#include <vector>
#include <unordered_map>
#include <cassert>

// Algorithm: Subarrays with XOR Sum Equal to K
// Purpose: Counts total contiguous subarrays whose cumulative XOR sum equals a given target K using a hash map or frequency array.
// Time Complexity: O(N) average time
// Space Complexity: O(N) auxiliary space
// Preconditions: Valid non-negative XOR targets.

class SubarrayXorEqualsK {
public:
    static long long count_subarrays(const std::vector<long long>& a, long long k) {
        std::unordered_map<long long, long long> freq;
        freq[0] = 1;

        long long current_xor = 0;
        long long count = 0;

        for (long long val : a) {
            current_xor ^= val;
            long long required = current_xor ^ k;
            auto it = freq.find(required);
            if (it != freq.end()) {
                count += it->second;
            }
            freq[current_xor]++;
        }
        return count;
    }
};

int main() {
    std::vector<long long> a = {4, 2, 2, 6, 4};
    // Subarrays with XOR = 6:
    // [4, 2], [4, 2, 2, 6, 4], [2, 2, 6], [6] -> 4 subarrays
    assert(SubarrayXorEqualsK::count_subarrays(a, 6) == 4);

    std::vector<long long> b = {5, 6, 7, 8, 9};
    assert(SubarrayXorEqualsK::count_subarrays(b, 5) == 2); // [5], [6, 7, 8, 9] (6^7^8^9 = 1^1^? 6^7=1, 8^9=1 => 1^1=0? no, 6^7^8^9=1^1=0? wait 6=0110, 7=0111, 8=1000, 9=1001 => 0001^0001 = 0 => 5^0=5)

    std::cout << "subarray_xor_equals_k tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "longest_subarray_sum_k.cpp",
        "algorithm": "Longest Subarray with Sum Equal to K",
        "purpose": "Finds the maximum length of a contiguous subarray that sums to K (handles positive, negative, and zero values).",
        "time_complexity": "O(N) time with hash table",
        "space_complexity": "O(N) space",
        "preconditions": "64-bit integer sum calculations.",
        "code": r"""#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cassert>

// Algorithm: Longest Subarray with Sum Equal to K
// Purpose: Finds the maximum length of a contiguous subarray that sums to K (handles positive, negative, and zero values).
// Time Complexity: O(N) time with hash table
// Space Complexity: O(N) space
// Preconditions: 64-bit integer sum calculations.

class LongestSubarraySumK {
public:
    static int max_length(const std::vector<long long>& a, long long k) {
        std::unordered_map<long long, int> first_idx;
        first_idx[0] = -1;

        long long pref = 0;
        int max_len = 0;

        for (int i = 0; i < (int)a.size(); ++i) {
            pref += a[i];
            long long need = pref - k;
            auto it = first_idx.find(need);
            if (it != first_idx.end()) {
                max_len = std::max(max_len, i - it->second);
            }
            if (first_idx.find(pref) == first_idx.end()) {
                first_idx[pref] = i;
            }
        }
        return max_len;
    }
};

int main() {
    std::vector<long long> a = {10, 5, 2, 7, 1, 9};
    // Subarray with sum 15: [5, 2, 7, 1] len 4
    assert(LongestSubarraySumK::max_length(a, 15) == 4);

    std::vector<long long> b = {-1, 2, 3};
    assert(LongestSubarraySumK::max_length(b, 6) == 0);

    std::vector<long long> c = {-5, 8, -14, 2, 4, 12};
    // sum -5: [-5] len 1
    assert(LongestSubarraySumK::max_length(c, -5) == 5); // [-5, 8, -14, 2, 4] sum = -5, len 5

    std::cout << "longest_subarray_sum_k tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "count_subarrays_sum_at_most_k.cpp",
        "algorithm": "Count Subarrays with Sum at Most K",
        "purpose": "Counts all continuous subarrays whose sum does not exceed K in an array of non-negative numbers in linear time.",
        "time_complexity": "O(N) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "All elements a[i] >= 0 and target K >= 0.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Count Subarrays with Sum at Most K
// Purpose: Counts all continuous subarrays whose sum does not exceed K in an array of non-negative numbers in linear time.
// Time Complexity: O(N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: All elements a[i] >= 0 and target K >= 0.

class CountSubarraysSumAtMostK {
public:
    static long long count(const std::vector<long long>& a, long long k) {
        if (k < 0) return 0;
        int n = a.size();
        long long ans = 0;
        long long current_sum = 0;
        int left = 0;

        for (int right = 0; right < n; ++right) {
            assert(a[right] >= 0);
            current_sum += a[right];
            while (current_sum > k && left <= right) {
                current_sum -= a[left++];
            }
            ans += (right - left + 1);
        }
        return ans;
    }
};

int main() {
    std::vector<long long> a = {1, 2, 3};
    // For k=3: [1], [2], [3], [1, 2] -> 4 subarrays
    assert(CountSubarraysSumAtMostK::count(a, 3) == 4);

    std::vector<long long> b = {1, 11, 2, 3, 15};
    // k = 10: [1], [2], [3], [2, 3] -> 4 subarrays
    assert(CountSubarraysSumAtMostK::count(b, 10) == 4);

    std::cout << "count_subarrays_sum_at_most_k tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "cyclic_shifts_and_rotations.cpp",
        "algorithm": "Array Cyclic Rotations (Reversal and Juggling)",
        "purpose": "Rotates an array by K positions left or right in-place using O(1) extra memory.",
        "time_complexity": "O(N) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "Valid vector, any integer k (positive, negative, or zero).",
        "code": r"""#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cassert>

// Algorithm: Array Cyclic Rotations (Reversal and Juggling)
// Purpose: Rotates an array by K positions left or right in-place using O(1) extra memory.
// Time Complexity: O(N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Valid vector, any integer k (positive, negative, or zero).

class CyclicRotations {
public:
    // Rotates array to the left by k positions via 3-step reversal
    template <typename T>
    static void rotate_left_reversal(std::vector<T>& a, int k) {
        int n = a.size();
        if (n <= 1) return;
        k = (k % n + n) % n;
        if (k == 0) return;

        std::reverse(a.begin(), a.begin() + k);
        std::reverse(a.begin() + k, a.end());
        std::reverse(a.begin(), a.end());
    }

    // Rotates array to the right by k positions
    template <typename T>
    static void rotate_right(std::vector<T>& a, int k) {
        int n = a.size();
        if (n <= 1) return;
        k = (k % n + n) % n;
        rotate_left_reversal(a, n - k);
    }

    // Juggling algorithm for left rotation
    template <typename T>
    static void rotate_left_juggling(std::vector<T>& a, int k) {
        int n = a.size();
        if (n <= 1) return;
        k = (k % n + n) % n;
        if (k == 0) return;

        int num_cycles = std::gcd(n, k);
        for (int i = 0; i < num_cycles; ++i) {
            T temp = a[i];
            int j = i;
            while (true) {
                int next_idx = (j + k) % n;
                if (next_idx == i) break;
                a[j] = a[next_idx];
                j = next_idx;
            }
            a[j] = temp;
        }
    }
};

int main() {
    std::vector<int> a = {1, 2, 3, 4, 5, 6, 7};
    CyclicRotations::rotate_left_reversal(a, 2);
    std::vector<int> exp1 = {3, 4, 5, 6, 7, 1, 2};
    assert(a == exp1);

    CyclicRotations::rotate_right(a, 2);
    std::vector<int> exp2 = {1, 2, 3, 4, 5, 6, 7};
    assert(a == exp2);

    CyclicRotations::rotate_left_juggling(a, 3);
    std::vector<int> exp3 = {4, 5, 6, 7, 1, 2, 3};
    assert(a == exp3);

    std::cout << "cyclic_shifts_and_rotations tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "dutch_national_flag_partition.cpp",
        "algorithm": "Dutch National Flag 3-Way Partitioning",
        "purpose": "Partitions an array into three segments (< pivot, == pivot, > pivot) in a single linear pass with O(1) space.",
        "time_complexity": "O(N) time with at most N element swaps",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "Elements comparable with < and == operators.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Dutch National Flag 3-Way Partitioning
// Purpose: Partitions an array into three segments (< pivot, == pivot, > pivot) in a single linear pass with O(1) space.
// Time Complexity: O(N) time with at most N element swaps
// Space Complexity: O(1) auxiliary space
// Preconditions: Elements comparable with < and == operators.

class DutchNationalFlag {
public:
    // Returns pair of indices [mid_start, mid_end] indicating the range of elements equal to pivot
    template <typename T>
    static std::pair<int, int> partition(std::vector<T>& a, const T& pivot) {
        int low = 0;
        int mid = 0;
        int high = (int)a.size() - 1;

        while (mid <= high) {
            if (a[mid] < pivot) {
                std::swap(a[low++], a[mid++]);
            } else if (pivot < a[mid]) {
                std::swap(a[mid], a[high--]);
            } else {
                mid++;
            }
        }
        return {low, high};
    }
};

int main() {
    std::vector<int> a = {2, 0, 2, 1, 1, 0, 1, 2, 0};
    auto [l, r] = DutchNationalFlag::partition(a, 1);

    for (int i = 0; i < l; ++i) assert(a[i] < 1);
    for (int i = l; i <= r; ++i) assert(a[i] == 1);
    for (int i = r + 1; i < (int)a.size(); ++i) assert(a[i] > 1);

    std::cout << "dutch_national_flag_partition tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "kadane_length_constrained.cpp",
        "algorithm": "Length-Constrained Maximum Subarray Sum",
        "purpose": "Finds the maximum subarray sum among all subarrays of length between L and R inclusive using monotonic deque.",
        "time_complexity": "O(N) time",
        "space_complexity": "O(N) space for prefix sums and deque",
        "preconditions": "1 <= L <= R <= N.",
        "code": r"""#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <cassert>

// Algorithm: Length-Constrained Maximum Subarray Sum
// Purpose: Finds the maximum subarray sum among all subarrays of length between L and R inclusive using monotonic deque.
// Time Complexity: O(N) time
// Space Complexity: O(N) space for prefix sums and deque
// Preconditions: 1 <= L <= R <= N.

class LengthConstrainedKadane {
public:
    static long long max_subarray_sum(const std::vector<long long>& a, int min_len, int max_len) {
        int n = a.size();
        assert(min_len >= 1 && min_len <= max_len && max_len <= n);

        std::vector<long long> pref(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            pref[i + 1] = pref[i] + a[i];
        }

        std::deque<int> dq;
        long long best = -2e18;

        for (int i = min_len; i <= n; ++i) {
            // Push pref[i - min_len] into deque maintaining monotonic increasing order
            int add_idx = i - min_len;
            while (!dq.empty() && pref[dq.back()] >= pref[add_idx]) {
                dq.pop_back();
            }
            dq.push_back(add_idx);

            // Pop elements that are too far away (length > max_len)
            while (!dq.empty() && dq.front() < i - max_len) {
                dq.pop_front();
            }

            if (!dq.empty()) {
                best = std::max(best, pref[i] - pref[dq.front()]);
            }
        }
        return best;
    }
};

int main() {
    std::vector<long long> a = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    // Lengths 2 to 4: subarray [4, -1, 2, 1] len 4 sum = 6
    assert(LengthConstrainedKadane::max_subarray_sum(a, 2, 4) == 6);

    std::vector<long long> b = {1, 2, 3, 4, 5};
    assert(LengthConstrainedKadane::max_subarray_sum(b, 2, 2) == 9); // [4, 5]

    std::cout << "kadane_length_constrained tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "maximum_circular_subarray_sum.cpp",
        "algorithm": "Maximum Circular Subarray Sum",
        "purpose": "Finds the maximum subarray sum allowing the subarray to wrap around the ends of the array in O(N).",
        "time_complexity": "O(N) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "Non-empty array. Handles all-negative elements correctly.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cassert>

// Algorithm: Maximum Circular Subarray Sum
// Purpose: Finds the maximum subarray sum allowing the subarray to wrap around the ends of the array in O(N).
// Time Complexity: O(N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Non-empty array. Handles all-negative elements correctly.

class MaximumCircularSubarraySum {
public:
    static long long max_circular_sum(const std::vector<long long>& a) {
        assert(!a.empty());
        long long total_sum = 0;
        long long max_kadane = a[0], cur_max = 0;
        long long min_kadane = a[0], cur_min = 0;

        for (long long x : a) {
            total_sum += x;

            cur_max = std::max(x, cur_max + x);
            max_kadane = std::max(max_kadane, cur_max);

            cur_min = std::min(x, cur_min + x);
            min_kadane = std::min(min_kadane, cur_min);
        }

        // If all elements are negative, max_circular is simply the max single element
        if (max_kadane < 0) {
            return max_kadane;
        }

        return std::max(max_kadane, total_sum - min_kadane);
    }
};

int main() {
    std::vector<long long> a = {1, -2, 3, -2};
    assert(MaximumCircularSubarraySum::max_circular_sum(a) == 3);

    std::vector<long long> b = {5, -3, 5};
    assert(MaximumCircularSubarraySum::max_circular_sum(b) == 10); // [5] + [5] wrapped

    std::vector<long long> c = {-3, -2, -3};
    assert(MaximumCircularSubarraySum::max_circular_sum(c) == -2);

    std::cout << "maximum_circular_subarray_sum tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "maximum_subarray_sum_after_one_operation.cpp",
        "algorithm": "Maximum Subarray Sum After One Operation",
        "purpose": "Finds the maximum subarray sum when exactly one element in the subarray can be modified (e.g. squared x^2).",
        "time_complexity": "O(N) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "Array length >= 1.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Maximum Subarray Sum After One Operation
// Purpose: Finds the maximum subarray sum when exactly one element in the subarray can be modified (e.g. squared x^2).
// Time Complexity: O(N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Array length >= 1.

class MaxSubarraySumAfterOneOperation {
public:
    // Computes max subarray sum where exactly one chosen element in the subarray is replaced by x*x
    static long long max_sum_with_one_square(const std::vector<long long>& a) {
        assert(!a.empty());
        // dp0: max subarray ending here with 0 operations used
        // dp1: max subarray ending here with 1 operation used
        long long dp0 = a[0];
        long long dp1 = a[0] * a[0];
        long long max_ans = dp1;

        for (size_t i = 1; i < a.size(); ++i) {
            long long x = a[i];
            long long sq = x * x;
            dp1 = std::max({sq, dp0 + sq, dp1 + x});
            dp0 = std::max(x, dp0 + x);
            max_ans = std::max(max_ans, dp1);
        }
        return max_ans;
    }
};

int main() {
    std::vector<long long> a = {2, -1, -4, -3};
    // Squaring -4 gives 16: subarray [-1, (-4)^2, -3] or [(-4)^2] = 16 or [2, -1, 16] = 17
    assert(MaxSubarraySumAfterOneOperation::max_sum_with_one_square(a) == 17);

    std::vector<long long> b = {1, -1, 1};
    assert(MaxSubarraySumAfterOneOperation::max_sum_with_one_square(b) == 3);

    std::cout << "maximum_subarray_sum_after_one_operation tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "in_place_matrix_rotation.cpp",
        "algorithm": "In-Place Matrix Rotation",
        "purpose": "Rotates an N x N square 2D matrix by 90 degrees clockwise or counter-clockwise in-place using O(1) memory.",
        "time_complexity": "O(N^2) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "Square matrix (N x N).",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: In-Place Matrix Rotation
// Purpose: Rotates an N x N square 2D matrix by 90 degrees clockwise or counter-clockwise in-place using O(1) memory.
// Time Complexity: O(N^2) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Square matrix (N x N).

class InPlaceMatrixRotation {
public:
    template <typename T>
    static void rotate_90_clockwise(std::vector<std::vector<T>>& mat) {
        int n = mat.size();
        // Transpose
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                std::swap(mat[i][j], mat[j][i]);
            }
        }
        // Reverse each row
        for (int i = 0; i < n; ++i) {
            std::reverse(mat[i].begin(), mat[i].end());
        }
    }

    template <typename T>
    static void rotate_90_counter_clockwise(std::vector<std::vector<T>>& mat) {
        int n = mat.size();
        // Transpose
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                std::swap(mat[i][j], mat[j][i]);
            }
        }
        // Reverse each column
        for (int j = 0; j < n; ++j) {
            for (int i = 0; i < n / 2; ++i) {
                std::swap(mat[i][j], mat[n - 1 - i][j]);
            }
        }
    }
};

int main() {
    std::vector<std::vector<int>> mat = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    InPlaceMatrixRotation::rotate_90_clockwise(mat);
    std::vector<std::vector<int>> exp_cw = {
        {7, 4, 1},
        {8, 5, 2},
        {9, 6, 3}
    };
    assert(mat == exp_cw);

    InPlaceMatrixRotation::rotate_90_counter_clockwise(mat);
    std::vector<std::vector<int>> exp_orig = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    assert(mat == exp_orig);

    std::cout << "in_place_matrix_rotation tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "in_place_matrix_transpose.cpp",
        "algorithm": "In-Place Matrix Transpose",
        "purpose": "Transposes an N x N matrix in-place by swapping elements across the main diagonal in O(1) auxiliary memory.",
        "time_complexity": "O(N^2) time with N*(N-1)/2 swaps",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "Square matrix (N x N).",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: In-Place Matrix Transpose
// Purpose: Transposes an N x N matrix in-place by swapping elements across the main diagonal in O(1) auxiliary memory.
// Time Complexity: O(N^2) time with N*(N-1)/2 swaps
// Space Complexity: O(1) auxiliary space
// Preconditions: Square matrix (N x N).

class InPlaceMatrixTranspose {
public:
    template <typename T>
    static void transpose(std::vector<std::vector<T>>& mat) {
        int n = mat.size();
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                std::swap(mat[i][j], mat[j][i]);
            }
        }
    }
};

int main() {
    std::vector<std::vector<int>> mat = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };
    InPlaceMatrixTranspose::transpose(mat);
    assert(mat[0][1] == 5);
    assert(mat[1][0] == 2);
    assert(mat[2][3] == 15);
    assert(mat[3][2] == 12);

    std::cout << "in_place_matrix_transpose tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "spiral_matrix_traversal.cpp",
        "algorithm": "Spiral Matrix Traversal and Generation",
        "purpose": "Traverses an R x C matrix in spiral order or constructs an N x N matrix filled with 1 to N^2 in spiral order.",
        "time_complexity": "O(R * C) time",
        "space_complexity": "O(1) auxiliary space beyond result vector",
        "preconditions": "R, C >= 1.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Spiral Matrix Traversal and Generation
// Purpose: Traverses an R x C matrix in spiral order or constructs an N x N matrix filled with 1 to N^2 in spiral order.
// Time Complexity: O(R * C) time
// Space Complexity: O(1) auxiliary space beyond result vector
// Preconditions: R, C >= 1.

class SpiralMatrix {
public:
    template <typename T>
    static std::vector<T> traverse(const std::vector<std::vector<T>>& mat) {
        if (mat.empty() || mat[0].empty()) return {};
        int top = 0, bottom = mat.size() - 1;
        int left = 0, right = mat[0].size() - 1;
        std::vector<T> order;

        while (top <= bottom && left <= right) {
            for (int j = left; j <= right; ++j) order.push_back(mat[top][j]);
            top++;
            for (int i = top; i <= bottom; ++i) order.push_back(mat[i][right]);
            right--;
            if (top <= bottom) {
                for (int j = right; j >= left; --j) order.push_back(mat[bottom][j]);
                bottom--;
            }
            if (left <= right) {
                for (int i = bottom; i >= top; --i) order.push_back(mat[i][left]);
                left++;
            }
        }
        return order;
    }

    static std::vector<std::vector<int>> generate(int n) {
        std::vector<std::vector<int>> mat(n, std::vector<int>(n, 0));
        int top = 0, bottom = n - 1, left = 0, right = n - 1;
        int val = 1;

        while (top <= bottom && left <= right) {
            for (int j = left; j <= right; ++j) mat[top][j] = val++;
            top++;
            for (int i = top; i <= bottom; ++i) mat[i][right] = val++;
            right--;
            if (top <= bottom) {
                for (int j = right; j >= left; --j) mat[bottom][j] = val++;
                bottom--;
            }
            if (left <= right) {
                for (int i = bottom; i >= top; --i) mat[i][left] = val++;
                left++;
            }
        }
        return mat;
    }
};

int main() {
    std::vector<std::vector<int>> mat = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    auto spiral = SpiralMatrix::traverse(mat);
    std::vector<int> expected = {1, 2, 3, 6, 9, 8, 7, 4, 5};
    assert(spiral == expected);

    auto gen = SpiralMatrix::generate(3);
    assert(gen == mat);

    std::cout << "spiral_matrix_traversal tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "diagonal_matrix_traversal.cpp",
        "algorithm": "Diagonal Matrix Traversal",
        "purpose": "Traverses an R x C matrix diagonally (anti-diagonals where i + j is constant) in zigzag or uniform order.",
        "time_complexity": "O(R * C) time",
        "space_complexity": "O(1) auxiliary space beyond result vector",
        "preconditions": "Non-empty 2D matrix.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Diagonal Matrix Traversal
// Purpose: Traverses an R x C matrix diagonally (anti-diagonals where i + j is constant) in zigzag or uniform order.
// Time Complexity: O(R * C) time
// Space Complexity: O(1) auxiliary space beyond result vector
// Preconditions: Non-empty 2D matrix.

class DiagonalMatrixTraversal {
public:
    template <typename T>
    static std::vector<T> traverse_zigzag(const std::vector<std::vector<T>>& mat) {
        if (mat.empty() || mat[0].empty()) return {};
        int r = mat.size(), c = mat[0].size();
        std::vector<T> result;
        result.reserve(r * c);

        for (int diag = 0; diag < r + c - 1; ++diag) {
            if (diag % 2 == 0) {
                // Traverse upwards
                int row = std::min(diag, r - 1);
                int col = diag - row;
                while (row >= 0 && col < c) {
                    result.push_back(mat[row][col]);
                    row--;
                    col++;
                }
            } else {
                // Traverse downwards
                int col = std::min(diag, c - 1);
                int row = diag - col;
                while (col >= 0 && row < r) {
                    result.push_back(mat[row][col]);
                    row++;
                    col--;
                }
            }
        }
        return result;
    }
};

int main() {
    std::vector<std::vector<int>> mat = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    auto diag = DiagonalMatrixTraversal::traverse_zigzag(mat);
    std::vector<int> expected = {1, 2, 4, 7, 5, 3, 6, 8, 9};
    assert(diag == expected);

    std::cout << "diagonal_matrix_traversal tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "max_consecutive_ones_k_flips.cpp",
        "algorithm": "Max Consecutive Ones with K Flips",
        "purpose": "Finds maximum length of contiguous 1s achievable by flipping at most K zeros to 1s using sliding window.",
        "time_complexity": "O(N) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "Array elements in {0, 1}, K >= 0.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Max Consecutive Ones with K Flips
// Purpose: Finds maximum length of contiguous 1s achievable by flipping at most K zeros to 1s using sliding window.
// Time Complexity: O(N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Array elements in {0, 1}, K >= 0.

class MaxConsecutiveOnesKFlips {
public:
    static int longest_ones(const std::vector<int>& a, int k) {
        int left = 0;
        int zero_count = 0;
        int max_len = 0;

        for (int right = 0; right < (int)a.size(); ++right) {
            if (a[right] == 0) {
                zero_count++;
            }
            while (zero_count > k) {
                if (a[left] == 0) {
                    zero_count--;
                }
                left++;
            }
            max_len = std::max(max_len, right - left + 1);
        }
        return max_len;
    }
};

int main() {
    std::vector<int> a = {1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0};
    assert(MaxConsecutiveOnesKFlips::longest_ones(a, 2) == 6);

    std::vector<int> b = {0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1};
    assert(MaxConsecutiveOnesKFlips::longest_ones(b, 3) == 10);

    std::cout << "max_consecutive_ones_k_flips tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "boyer_moore_majority_two_elements.cpp",
        "algorithm": "Boyer-Moore Majority Vote (Extended to N/3 Frequency)",
        "purpose": "Finds all elements appearing strictly more than floor(N/3) times (at most two elements) in linear time and O(1) space.",
        "time_complexity": "O(N) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "General array of elements.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Boyer-Moore Majority Vote (Extended to N/3 Frequency)
// Purpose: Finds all elements appearing strictly more than floor(N/3) times (at most two elements) in linear time and O(1) space.
// Time Complexity: O(N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: General array of elements.

class MajorityVoteNThirds {
public:
    template <typename T>
    static std::vector<T> find_majority(const std::vector<T>& a) {
        int n = a.size();
        if (n == 0) return {};

        T cand1 = a[0], cand2 = a[0];
        int count1 = 0, count2 = 0;

        for (const auto& x : a) {
            if (count1 > 0 && x == cand1) {
                count1++;
            } else if (count2 > 0 && x == cand2) {
                count2++;
            } else if (count1 == 0) {
                cand1 = x;
                count1 = 1;
            } else if (count2 == 0) {
                cand2 = x;
                count2 = 1;
            } else {
                count1--;
                count2--;
            }
        }

        // Verification step
        int actual1 = 0, actual2 = 0;
        for (const auto& x : a) {
            if (count1 > 0 && x == cand1) actual1++;
            else if (count2 > 0 && x == cand2) actual2++;
        }

        std::vector<T> res;
        if (actual1 > n / 3) res.push_back(cand1);
        if (actual2 > n / 3) res.push_back(cand2);
        return res;
    }
};

int main() {
    std::vector<int> a = {3, 2, 3};
    auto res = MajorityVoteNThirds::find_majority(a);
    assert(res.size() == 1 && res[0] == 3);

    std::vector<int> b = {1, 1, 1, 3, 3, 2, 2, 2};
    auto res2 = MajorityVoteNThirds::find_majority(b);
    assert(res2.size() == 2); // 1 and 2 appear 3 times (> 8/3 = 2)

    std::cout << "boyer_moore_majority_two_elements tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "boyer_moore_majority_k_elements.cpp",
        "algorithm": "Generalized Boyer-Moore Majority Vote (N/K Frequency)",
        "purpose": "Finds all elements appearing strictly more than floor(N/K) times in an array using at most K-1 candidate registers.",
        "time_complexity": "O(N * K) time",
        "space_complexity": "O(K) auxiliary space",
        "preconditions": "K >= 2.",
        "code": r"""#include <iostream>
#include <vector>
#include <map>
#include <cassert>

// Algorithm: Generalized Boyer-Moore Majority Vote (N/K Frequency)
// Purpose: Finds all elements appearing strictly more than floor(N/K) times in an array using at most K-1 candidate registers.
// Time Complexity: O(N * K) time
// Space Complexity: O(K) auxiliary space
// Preconditions: K >= 2.

class GeneralizedMajorityVote {
public:
    template <typename T>
    static std::vector<T> find_majority_nk(const std::vector<T>& a, int k) {
        assert(k >= 2);
        int n = a.size();
        if (n == 0) return {};

        std::map<T, int> candidates;

        for (const auto& x : a) {
            if (candidates.count(x)) {
                candidates[x]++;
            } else if ((int)candidates.size() < k - 1) {
                candidates[x] = 1;
            } else {
                for (auto it = candidates.begin(); it != candidates.end();) {
                    it->second--;
                    if (it->second == 0) {
                        it = candidates.erase(it);
                    } else {
                        ++it;
                    }
                }
            }
        }

        // Verification pass
        std::map<T, int> actual_counts;
        for (const auto& x : a) {
            if (candidates.count(x)) {
                actual_counts[x]++;
            }
        }

        std::vector<T> result;
        for (const auto& pair : actual_counts) {
            if (pair.second > n / k) {
                result.push_back(pair.first);
            }
        }
        return result;
    }
};

int main() {
    std::vector<int> a = {3, 1, 2, 2, 1, 2, 3, 3}; // n=8, k=4, threshold > 2
    auto res = GeneralizedMajorityVote::find_majority_nk(a, 4);
    // Elements appearing > 2 times: 2 (3 times), 3 (3 times)
    assert(res.size() == 2);
    assert(res[0] == 2 && res[1] == 3);

    std::cout << "boyer_moore_majority_k_elements tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "prefix_maximums_and_minimums.cpp",
        "algorithm": "Prefix and Suffix Extrema Arrays",
        "purpose": "Computes prefix and suffix min/max arrays to query extrema of array excluding any single element or subsegment in O(1).",
        "time_complexity": "O(N) preprocessing, O(1) query",
        "space_complexity": "O(N) auxiliary space",
        "preconditions": "Non-empty array.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Prefix and Suffix Extrema Arrays
// Purpose: Computes prefix and suffix min/max arrays to query extrema of array excluding any single element or subsegment in O(1).
// Time Complexity: O(N) preprocessing, O(1) query
// Space Complexity: O(N) auxiliary space
// Preconditions: Non-empty array.

class PrefixSuffixExtrema {
private:
    int n;
    std::vector<long long> pref_max, suff_max;
    std::vector<long long> pref_min, suff_min;

public:
    explicit PrefixSuffixExtrema(const std::vector<long long>& a) : n(a.size()) {
        assert(n > 0);
        pref_max.resize(n);
        suff_max.resize(n);
        pref_min.resize(n);
        suff_min.resize(n);

        pref_max[0] = pref_min[0] = a[0];
        for (int i = 1; i < n; ++i) {
            pref_max[i] = std::max(pref_max[i - 1], a[i]);
            pref_min[i] = std::min(pref_min[i - 1], a[i]);
        }

        suff_max[n - 1] = suff_min[n - 1] = a[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            suff_max[i] = std::max(suff_max[i + 1], a[i]);
            suff_min[i] = std::min(suff_min[i + 1], a[i]);
        }
    }

    // Queries max element of array excluding index i (0 <= i < n)
    long long query_max_excluding(int i) const {
        assert(n >= 2 && i >= 0 && i < n);
        if (i == 0) return suff_max[1];
        if (i == n - 1) return pref_max[n - 2];
        return std::max(pref_max[i - 1], suff_max[i + 1]);
    }

    // Queries min element of array excluding range [l, r]
    long long query_min_excluding_range(int l, int r) const {
        assert(l <= r && (l > 0 || r < n - 1));
        if (l == 0) return suff_min[r + 1];
        if (r == n - 1) return pref_min[l - 1];
        return std::min(pref_min[l - 1], suff_min[r + 1]);
    }
};

int main() {
    std::vector<long long> a = {5, 2, 8, 1, 9, 3};
    PrefixSuffixExtrema pse(a);

    assert(pse.query_max_excluding(4) == 8); // exclude 9 -> max is 8
    assert(pse.query_max_excluding(2) == 9); // exclude 8 -> max is 9
    assert(pse.query_min_excluding_range(2, 3) == 2); // exclude [8, 1] -> min is 2

    std::cout << "prefix_maximums_and_minimums tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "prefix_product_with_zeros.cpp",
        "algorithm": "Prefix Products with Zero Counts",
        "purpose": "Answers range modular products in O(1) time in arrays containing zero values by tracking zero frequencies.",
        "time_complexity": "O(N) preprocessing, O(1) query",
        "space_complexity": "O(N) space",
        "preconditions": "Modulus M is prime for modular inverse.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Prefix Products with Zero Counts
// Purpose: Answers range modular products in O(1) time in arrays containing zero values by tracking zero frequencies.
// Time Complexity: O(N) preprocessing, O(1) query
// Space Complexity: O(N) space
// Preconditions: Modulus M is prime for modular inverse.

class PrefixProductWithZeros {
private:
    int n;
    long long mod;
    std::vector<int> zero_pref;
    std::vector<long long> non_zero_prod;
    std::vector<long long> inv_prod;

    long long power(long long base, long long exp) const {
        long long res = 1;
        base %= mod;
        while (exp > 0) {
            if (exp & 1) res = (res * base) % mod;
            base = (base * base) % mod;
            exp >>= 1;
        }
        return res;
    }

    long long mod_inverse(long long x) const {
        return power(x, mod - 2);
    }

public:
    PrefixProductWithZeros(const std::vector<long long>& a, long long m = 1e9 + 7) : n(a.size()), mod(m) {
        zero_pref.assign(n + 1, 0);
        non_zero_prod.assign(n + 1, 1);
        inv_prod.assign(n + 1, 1);

        for (int i = 0; i < n; ++i) {
            zero_pref[i + 1] = zero_pref[i] + (a[i] == 0 ? 1 : 0);
            long long val = (a[i] == 0 ? 1LL : (a[i] % mod + mod) % mod);
            non_zero_prod[i + 1] = (non_zero_prod[i] * val) % mod;
            inv_prod[i + 1] = mod_inverse(non_zero_prod[i + 1]);
        }
    }

    long long query(int l, int r) const {
        assert(l >= 0 && r < n && l <= r);
        int zeros = zero_pref[r + 1] - zero_pref[l];
        if (zeros > 0) return 0;
        return (non_zero_prod[r + 1] * inv_prod[l]) % mod;
    }
};

int main() {
    std::vector<long long> a = {2, 3, 0, 4, 5};
    PrefixProductWithZeros pp(a, 1000000007);

    assert(pp.query(0, 1) == 6);
    assert(pp.query(0, 2) == 0);
    assert(pp.query(1, 3) == 0);
    assert(pp.query(3, 4) == 20);

    std::cout << "prefix_product_with_zeros tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "prefix_gcd_array.cpp",
        "algorithm": "Prefix and Suffix GCD",
        "purpose": "Computes GCD of the entire array excluding one element in O(1) per candidate using prefix and suffix GCD tables.",
        "time_complexity": "O(N log(max_A)) preprocessing, O(1) query",
        "space_complexity": "O(N) auxiliary space",
        "preconditions": "Elements are non-negative integers.",
        "code": r"""#include <iostream>
#include <vector>
#include <numeric>
#include <cassert>

// Algorithm: Prefix and Suffix GCD
// Purpose: Computes GCD of the entire array excluding one element in O(1) per candidate using prefix and suffix GCD tables.
// Time Complexity: O(N log(max_A)) preprocessing, O(1) query
// Space Complexity: O(N) auxiliary space
// Preconditions: Elements are non-negative integers.

class PrefixSuffixGcd {
private:
    int n;
    std::vector<long long> pref;
    std::vector<long long> suff;

public:
    explicit PrefixSuffixGcd(const std::vector<long long>& a) : n(a.size()), pref(n), suff(n) {
        assert(n > 0);
        pref[0] = a[0];
        for (int i = 1; i < n; ++i) {
            pref[i] = std::gcd(pref[i - 1], a[i]);
        }
        suff[n - 1] = a[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            suff[i] = std::gcd(suff[i + 1], a[i]);
        }
    }

    // Returns GCD of all elements except a[i]
    long long gcd_excluding(int i) const {
        assert(n >= 2 && i >= 0 && i < n);
        if (i == 0) return suff[1];
        if (i == n - 1) return pref[n - 2];
        return std::gcd(pref[i - 1], suff[i + 1]);
    }

    // Finds maximum GCD achievable by removing exactly one element
    long long max_gcd_after_removal() const {
        long long best = 0;
        for (int i = 0; i < n; ++i) {
            best = std::max(best, gcd_excluding(i));
        }
        return best;
    }
};

int main() {
    std::vector<long long> a = {12, 15, 18, 7};
    PrefixSuffixGcd psg(a);

    // Removing 7 leaves {12, 15, 18} with gcd = 3
    assert(psg.gcd_excluding(3) == 3);
    assert(psg.max_gcd_after_removal() == 3);

    std::cout << "prefix_gcd_array tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "prefix_bitwise_or_and.cpp",
        "algorithm": "Distinct Bitwise OR of Subarrays",
        "purpose": "Finds all distinct bitwise OR values produced by contiguous subarrays in O(N * 30) time.",
        "time_complexity": "O(N * log(max_A)) time",
        "space_complexity": "O(log(max_A)) auxiliary space per step",
        "preconditions": "Elements non-negative 32/64-bit integers.",
        "code": r"""#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <cassert>

// Algorithm: Distinct Bitwise OR of Subarrays
// Purpose: Finds all distinct bitwise OR values produced by contiguous subarrays in O(N * 30) time.
// Time Complexity: O(N * log(max_A)) time
// Space Complexity: O(log(max_A)) auxiliary space per step
// Preconditions: Elements non-negative 32/64-bit integers.

class DistinctSubarrayBitwiseOr {
public:
    static std::unordered_set<long long> get_all_distinct_ors(const std::vector<long long>& a) {
        std::unordered_set<long long> total_ors;
        std::vector<long long> cur_ors; // Stores unique ORs ending at current index

        for (long long x : a) {
            std::vector<long long> next_ors;
            next_ors.push_back(x);
            for (long long prev : cur_ors) {
                next_ors.push_back(prev | x);
            }
            // Remove duplicates
            std::sort(next_ors.begin(), next_ors.end());
            next_ors.erase(std::unique(next_ors.begin(), next_ors.end()), next_ors.end());

            for (long long v : next_ors) {
                total_ors.insert(v);
            }
            cur_ors = std::move(next_ors);
        }
        return total_ors;
    }
};

int main() {
    std::vector<long long> a = {1, 2, 4};
    // Subarrays: [1]=1, [2]=2, [4]=4, [1,2]=3, [2,4]=6, [1,2,4]=7 -> 6 distinct values
    auto ors = DistinctSubarrayBitwiseOr::get_all_distinct_ors(a);
    assert(ors.size() == 6);
    assert(ors.count(1) && ors.count(2) && ors.count(3) && ors.count(4) && ors.count(6) && ors.count(7));

    std::cout << "prefix_bitwise_or_and tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "longest_consecutive_sequence.cpp",
        "algorithm": "Longest Consecutive Sequence",
        "purpose": "Finds the length of the longest sequence of consecutive integers present in an unsorted array in O(N) average time.",
        "time_complexity": "O(N) average time",
        "space_complexity": "O(N) space",
        "preconditions": "Any sequence of integers.",
        "code": r"""#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <cassert>

// Algorithm: Longest Consecutive Sequence
// Purpose: Finds the length of the longest sequence of consecutive integers present in an unsorted array in O(N) average time.
// Time Complexity: O(N) average time
// Space Complexity: O(N) space
// Preconditions: Any sequence of integers.

class LongestConsecutiveSequence {
public:
    static int longest_consecutive(const std::vector<int>& a) {
        std::unordered_set<int> nums(a.begin(), a.end());
        int longest = 0;

        for (int x : nums) {
            // Check if x is the start of a streak
            if (nums.find(x - 1) == nums.end()) {
                int current_num = x;
                int current_streak = 1;
                while (nums.find(current_num + 1) != nums.end()) {
                    current_num++;
                    current_streak++;
                }
                longest = std::max(longest, current_streak);
            }
        }
        return longest;
    }
};

int main() {
    std::vector<int> a = {100, 4, 200, 1, 3, 2};
    // Consecutive sequence: [1, 2, 3, 4] length 4
    assert(LongestConsecutiveSequence::longest_consecutive(a) == 4);

    std::vector<int> b = {0, 3, 7, 2, 5, 8, 4, 6, 0, 1};
    // Consecutive sequence: 0 through 8, length 9
    assert(LongestConsecutiveSequence::longest_consecutive(b) == 9);

    std::cout << "longest_consecutive_sequence tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "maximum_gap_pigeonhole.cpp",
        "algorithm": "Maximum Gap (Bucket Pigeonhole Algorithm)",
        "purpose": "Computes maximum gap between successive elements in sorted form in O(N) time and O(N) space without full comparison sorting.",
        "time_complexity": "O(N) time",
        "space_complexity": "O(N) space",
        "preconditions": "Array length >= 2.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cassert>

// Algorithm: Maximum Gap (Bucket Pigeonhole Algorithm)
// Purpose: Computes maximum gap between successive elements in sorted form in O(N) time and O(N) space without full comparison sorting.
// Time Complexity: O(N) time
// Space Complexity: O(N) space
// Preconditions: Array length >= 2.

class MaximumGap {
public:
    static int maximum_gap(const std::vector<int>& a) {
        int n = a.size();
        if (n < 2) return 0;

        int min_val = *std::min_element(a.begin(), a.end());
        int max_val = *std::max_element(a.begin(), a.end());
        if (min_val == max_val) return 0;

        int bucket_size = std::max(1, (max_val - min_val) / (n - 1));
        int bucket_count = (max_val - min_val) / bucket_size + 1;

        std::vector<int> b_min(bucket_count, 1e9 + 7);
        std::vector<int> b_max(bucket_count, -1e9 - 7);
        std::vector<bool> b_used(bucket_count, false);

        for (int x : a) {
            int idx = (x - min_val) / bucket_size;
            b_min[idx] = std::min(b_min[idx], x);
            b_max[idx] = std::max(b_max[idx], x);
            b_used[idx] = true;
        }

        int max_gap = 0;
        int prev_max = min_val;

        for (int i = 0; i < bucket_count; ++i) {
            if (!b_used[i]) continue;
            max_gap = std::max(max_gap, b_min[i] - prev_max);
            prev_max = b_max[i];
        }
        return max_gap;
    }
};

int main() {
    std::vector<int> a = {3, 6, 9, 1};
    // Sorted: [1, 3, 6, 9]. Max gap = 3 (between 3 and 6, or 6 and 9)
    assert(MaximumGap::maximum_gap(a) == 3);

    std::vector<int> b = {10};
    assert(MaximumGap::maximum_gap(b) == 0);

    std::cout << "maximum_gap_pigeonhole tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "subarray_with_given_xor_product.cpp",
        "algorithm": "Subarray Zero XOR and Target Product Check",
        "purpose": "Verifies existence of any subarray whose XOR sum is 0 or product equals a target in O(N).",
        "time_complexity": "O(N) average time",
        "space_complexity": "O(N) auxiliary space",
        "preconditions": "64-bit integer values.",
        "code": r"""#include <iostream>
#include <vector>
#include <unordered_set>
#include <cassert>

// Algorithm: Subarray Zero XOR and Target Product Check
// Purpose: Verifies existence of any subarray whose XOR sum is 0 or product equals a target in O(N).
// Time Complexity: O(N) average time
// Space Complexity: O(N) auxiliary space
// Preconditions: 64-bit integer values.

class SubarrayZeroXorProduct {
public:
    static bool has_zero_xor_subarray(const std::vector<long long>& a) {
        std::unordered_set<long long> seen;
        seen.insert(0);
        long long pref_xor = 0;

        for (long long x : a) {
            pref_xor ^= x;
            if (seen.count(pref_xor)) {
                return true;
            }
            seen.insert(pref_xor);
        }
        return false;
    }
};

int main() {
    std::vector<long long> a = {4, 7, 2, 5};
    // Subarray [7, 2, 5]: 7^2^5 = 0
    assert(SubarrayZeroXorProduct::has_zero_xor_subarray(a) == true);

    std::vector<long long> b = {1, 2, 4};
    assert(SubarrayZeroXorProduct::has_zero_xor_subarray(b) == false);

    std::cout << "subarray_with_given_xor_product tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "array_rank_transform.cpp",
        "algorithm": "Dense Array Rank Transform",
        "purpose": "Replaces each element with its 1-based rank (ties receiving the same rank) in O(N log N) time.",
        "time_complexity": "O(N log N) time",
        "space_complexity": "O(N) auxiliary space",
        "preconditions": "Vector of comparable elements.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Dense Array Rank Transform
// Purpose: Replaces each element with its 1-based rank (ties receiving the same rank) in O(N log N) time.
// Time Complexity: O(N log N) time
// Space Complexity: O(N) auxiliary space
// Preconditions: Vector of comparable elements.

class ArrayRankTransform {
public:
    template <typename T>
    static std::vector<int> rank_transform(const std::vector<T>& a) {
        std::vector<T> sorted_unique = a;
        std::sort(sorted_unique.begin(), sorted_unique.end());
        sorted_unique.erase(std::unique(sorted_unique.begin(), sorted_unique.end()), sorted_unique.end());

        std::vector<int> ranks(a.size());
        for (size_t i = 0; i < a.size(); ++i) {
            auto it = std::lower_bound(sorted_unique.begin(), sorted_unique.end(), a[i]);
            ranks[i] = std::distance(sorted_unique.begin(), it) + 1;
        }
        return ranks;
    }
};

int main() {
    std::vector<int> a = {40, 10, 20, 30};
    auto ranks = ArrayRankTransform::rank_transform(a);
    std::vector<int> expected = {4, 1, 2, 3};
    assert(ranks == expected);

    std::vector<int> b = {100, 100, 100};
    auto ranks2 = ArrayRankTransform::rank_transform(b);
    std::vector<int> expected2 = {1, 1, 1};
    assert(ranks2 == expected2);

    std::cout << "array_rank_transform tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "next_greater_element_circular.cpp",
        "algorithm": "Next Greater Element in Circular Array",
        "purpose": "Finds the first greater element for each index in a circular array in O(N) time using a monotonic stack.",
        "time_complexity": "O(N) time",
        "space_complexity": "O(N) auxiliary space",
        "preconditions": "Returns -1 if no greater element exists in circular array.",
        "code": r"""#include <iostream>
#include <vector>
#include <stack>
#include <cassert>

// Algorithm: Next Greater Element in Circular Array
// Purpose: Finds the first greater element for each index in a circular array in O(N) time using a monotonic stack.
// Time Complexity: O(N) time
// Space Complexity: O(N) auxiliary space
// Preconditions: Returns -1 if no greater element exists in circular array.

class CircularNextGreaterElement {
public:
    static std::vector<int> next_greater(const std::vector<int>& a) {
        int n = a.size();
        std::vector<int> res(n, -1);
        std::stack<int> st;

        for (int i = 0; i < 2 * n; ++i) {
            int cur = a[i % n];
            while (!st.empty() && a[st.top()] < cur) {
                res[st.top()] = cur;
                st.pop();
            }
            if (i < n) {
                st.push(i);
            }
        }
        return res;
    }
};

int main() {
    std::vector<int> a = {1, 2, 1};
    auto res = CircularNextGreaterElement::next_greater(a);
    std::vector<int> expected = {2, -1, 2};
    assert(res == expected);

    std::vector<int> b = {1, 2, 3, 4, 3};
    auto res2 = CircularNextGreaterElement::next_greater(b);
    std::vector<int> expected2 = {2, 3, 4, -1, 4};
    assert(res2 == expected2);

    std::cout << "next_greater_element_circular tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "trapping_rainwater_prefix_max.cpp",
        "algorithm": "Trapping Rainwater via Prefix & Suffix Extrema",
        "purpose": "Calculates total units of rainwater trapped between elevation bars in O(N) time using prefix/suffix elevation maxima.",
        "time_complexity": "O(N) time",
        "space_complexity": "O(N) space",
        "preconditions": "Elevation heights are non-negative.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Trapping Rainwater via Prefix & Suffix Extrema
// Purpose: Calculates total units of rainwater trapped between elevation bars in O(N) time using prefix/suffix elevation maxima.
// Time Complexity: O(N) time
// Space Complexity: O(N) space
// Preconditions: Elevation heights are non-negative.

class TrappingRainwaterPrefixMax {
public:
    static long long trap(const std::vector<int>& height) {
        int n = height.size();
        if (n <= 2) return 0;

        std::vector<int> left_max(n);
        std::vector<int> right_max(n);

        left_max[0] = height[0];
        for (int i = 1; i < n; ++i) {
            left_max[i] = std::max(left_max[i - 1], height[i]);
        }

        right_max[n - 1] = height[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            right_max[i] = std::max(right_max[i + 1], height[i]);
        }

        long long trapped = 0;
        for (int i = 0; i < n; ++i) {
            trapped += std::min(left_max[i], right_max[i]) - height[i];
        }
        return trapped;
    }
};

int main() {
    std::vector<int> h = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    assert(TrappingRainwaterPrefixMax::trap(h) == 6);

    std::vector<int> h2 = {4, 2, 0, 3, 2, 5};
    assert(TrappingRainwaterPrefixMax::trap(h2) == 9);

    std::cout << "trapping_rainwater_prefix_max tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "count_subarrays_bounded_maximum.cpp",
        "algorithm": "Count Subarrays with Bounded Maximum",
        "purpose": "Counts contiguous subarrays where the maximum value lies in range [L, R] in O(N) time and O(1) space.",
        "time_complexity": "O(N) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "L <= R.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Count Subarrays with Bounded Maximum
// Purpose: Counts contiguous subarrays where the maximum value lies in range [L, R] in O(N) time and O(1) space.
// Time Complexity: O(N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: L <= R.

class SubarraysBoundedMaximum {
public:
    static long long num_subarrays_bounded_max(const std::vector<int>& a, int left, int right) {
        // Count subarrays with max <= B minus subarrays with max <= A - 1
        return count_at_most(a, right) - count_at_most(a, left - 1);
    }

private:
    static long long count_at_most(const std::vector<int>& a, int bound) {
        long long total = 0;
        long long current_len = 0;
        for (int x : a) {
            if (x <= bound) {
                current_len++;
                total += current_len;
            } else {
                current_len = 0;
            }
        }
        return total;
    }
};

int main() {
    std::vector<int> a = {2, 1, 4, 3};
    // Subarrays with max in [2, 3]: [2], [2, 1], [3] -> 3
    assert(SubarraysBoundedMaximum::num_subarrays_bounded_max(a, 2, 3) == 3);

    std::vector<int> b = {2, 9, 2, 5, 6};
    // max in [2, 8]: [2], [2], [5], [2, 5], [6], [5, 6], [2, 5, 6] -> 7
    assert(SubarraysBoundedMaximum::num_subarrays_bounded_max(b, 2, 8) == 7);

    std::cout << "count_subarrays_bounded_maximum tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "min_increments_to_make_unique.cpp",
        "algorithm": "Minimum Increments to Make Array Unique",
        "purpose": "Computes minimum number of +1 increment operations required to make all elements in an array unique.",
        "time_complexity": "O(N log N) time",
        "space_complexity": "O(1) auxiliary space beyond sort",
        "preconditions": "Elements non-negative.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Minimum Increments to Make Array Unique
// Purpose: Computes minimum number of +1 increment operations required to make all elements in an array unique.
// Time Complexity: O(N log N) time
// Space Complexity: O(1) auxiliary space beyond sort
// Preconditions: Elements non-negative.

class MinIncrementsUnique {
public:
    static long long min_increment_for_unique(std::vector<int>& a) {
        if (a.empty()) return 0;
        std::sort(a.begin(), a.end());
        long long moves = 0;
        int needed = a[0];

        for (int x : a) {
            if (x < needed) {
                moves += (needed - x);
                needed++;
            } else {
                needed = x + 1;
            }
        }
        return moves;
    }
};

int main() {
    std::vector<int> a = {1, 2, 2};
    assert(MinIncrementsUnique::min_increment_for_unique(a) == 1); // 2 -> 3

    std::vector<int> b = {3, 2, 1, 2, 1, 7};
    assert(MinIncrementsUnique::min_increment_for_unique(b) == 6);

    std::cout << "min_increments_to_make_unique tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "subarray_sum_divisible_by_length.cpp",
        "algorithm": "Subarray Sum Divisible by Array Length (Pigeonhole Subarray)",
        "purpose": "Finds a non-empty contiguous subarray whose sum is divisible by N using Pigeonhole Principle (guaranteed to exist).",
        "time_complexity": "O(N) time",
        "space_complexity": "O(N) space",
        "preconditions": "Array length N >= 1.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Subarray Sum Divisible by Array Length (Pigeonhole Subarray)
// Purpose: Finds a non-empty contiguous subarray whose sum is divisible by N using Pigeonhole Principle (guaranteed to exist).
// Time Complexity: O(N) time
// Space Complexity: O(N) space
// Preconditions: Array length N >= 1.

class PigeonholeSubarrayDivisibleN {
public:
    // Returns pair [start_idx, end_idx] (0-indexed inclusive)
    static std::pair<int, int> find_subarray(const std::vector<long long>& a) {
        int n = a.size();
        assert(n >= 1);
        std::vector<int> first_rem(n, -2);
        first_rem[0] = -1;

        long long pref = 0;
        for (int i = 0; i < n; ++i) {
            pref = (pref + a[i]) % n;
            if (pref < 0) pref += n;

            if (first_rem[pref] != -2) {
                return {first_rem[pref] + 1, i};
            }
            first_rem[pref] = i;
        }
        return {-1, -1}; // Should never happen by pigeonhole principle
    }
};

int main() {
    std::vector<long long> a = {3, 2, 7, 1}; // n = 4
    auto [l, r] = PigeonholeSubarrayDivisibleN::find_subarray(a);
    assert(l != -1 && l <= r);
    long long sum = 0;
    for (int i = l; i <= r; ++i) sum += a[i];
    assert(sum % 4 == 0);

    std::cout << "subarray_sum_divisible_by_length tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "prefix_sums_3d.cpp",
        "algorithm": "3D Prefix Sums",
        "purpose": "Queries arbitrary sub-volume sums in a 3D grid in O(1) time after O(X*Y*Z) preprocessing using inclusion-exclusion.",
        "time_complexity": "O(X*Y*Z) preprocessing, O(1) per box sum query",
        "space_complexity": "O(X*Y*Z) auxiliary space",
        "preconditions": "Coordinates satisfy 0 <= x1 <= x2 < X, 0 <= y1 <= y2 < Y, 0 <= z1 <= z2 < Z.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: 3D Prefix Sums
// Purpose: Queries arbitrary sub-volume sums in a 3D grid in O(1) time after O(X*Y*Z) preprocessing using inclusion-exclusion.
// Time Complexity: O(X*Y*Z) preprocessing, O(1) per box sum query
// Space Complexity: O(X*Y*Z) auxiliary space
// Preconditions: Coordinates satisfy 0 <= x1 <= x2 < X, 0 <= y1 <= y2 < Y, 0 <= z1 <= z2 < Z.

class PrefixSums3D {
private:
    int X, Y, Z;
    std::vector<std::vector<std::vector<long long>>> pref;

public:
    PrefixSums3D(const std::vector<std::vector<std::vector<long long>>>& a) {
        X = a.size();
        Y = (X > 0 ? a[0].size() : 0);
        Z = (Y > 0 ? a[0][0].size() : 0);

        pref.assign(X + 1, std::vector<std::vector<long long>>(Y + 1, std::vector<long long>(Z + 1, 0)));

        for (int i = 0; i < X; ++i) {
            for (int j = 0; j < Y; ++j) {
                for (int k = 0; k < Z; ++k) {
                    pref[i + 1][j + 1][k + 1] = a[i][j][k]
                        + pref[i][j + 1][k + 1] + pref[i + 1][j][k + 1] + pref[i + 1][j + 1][k]
                        - pref[i][j][k + 1] - pref[i][j + 1][k] - pref[i + 1][j][k]
                        + pref[i][j][k];
                }
            }
        }
    }

    long long query(int x1, int y1, int z1, int x2, int y2, int z2) const {
        assert(x1 >= 0 && x1 <= x2 && x2 < X);
        assert(y1 >= 0 && y1 <= y2 && y2 < Y);
        assert(z1 >= 0 && z1 <= z2 && z2 < Z);

        int xa = x1, xb = x2 + 1;
        int ya = y1, yb = y2 + 1;
        int za = z1, zb = z2 + 1;

        return pref[xb][yb][zb]
             - pref[xa][yb][zb] - pref[xb][ya][zb] - pref[xb][yb][za]
             + pref[xa][ya][zb] + pref[xa][yb][za] + pref[xb][ya][za]
             - pref[xa][ya][za];
    }
};

int main() {
    int X = 2, Y = 2, Z = 2;
    std::vector<std::vector<std::vector<long long>>> a(X, std::vector<std::vector<long long>>(Y, std::vector<long long>(Z, 1)));
    PrefixSums3D p3(a);

    assert(p3.query(0, 0, 0, 1, 1, 1) == 8);
    assert(p3.query(0, 0, 0, 0, 0, 0) == 1);
    assert(p3.query(0, 0, 0, 1, 0, 0) == 2);

    std::cout << "prefix_sums_3d tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "longest_subarray_equal_zeros_ones.cpp",
        "algorithm": "Longest Subarray with Equal 0s and 1s",
        "purpose": "Finds the maximum length of a contiguous binary subarray having equal numbers of 0 and 1 in O(N) time.",
        "time_complexity": "O(N) time",
        "space_complexity": "O(N) space",
        "preconditions": "Binary array (elements are 0 or 1).",
        "code": r"""#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cassert>

// Algorithm: Longest Subarray with Equal 0s and 1s
// Purpose: Finds the maximum length of a contiguous binary subarray having equal numbers of 0 and 1 in O(N) time.
// Time Complexity: O(N) time
// Space Complexity: O(N) space
// Preconditions: Binary array (elements are 0 or 1).

class EqualZerosAndOnes {
public:
    static int find_max_length(const std::vector<int>& a) {
        std::unordered_map<int, int> first_seen;
        first_seen[0] = -1;

        int pref = 0;
        int max_len = 0;

        for (int i = 0; i < (int)a.size(); ++i) {
            pref += (a[i] == 1 ? 1 : -1);
            auto it = first_seen.find(pref);
            if (it != first_seen.end()) {
                max_len = std::max(max_len, i - it->second);
            } else {
                first_seen[pref] = i;
            }
        }
        return max_len;
    }
};

int main() {
    std::vector<int> a = {0, 1, 0};
    assert(EqualZerosAndOnes::find_max_length(a) == 2);

    std::vector<int> b = {0, 1, 1, 0, 1, 1, 1, 0};
    assert(EqualZerosAndOnes::find_max_length(b) == 4); // [0, 1, 1, 0]

    std::cout << "longest_subarray_equal_zeros_ones tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "longest_subarray_divisible_by_k.cpp",
        "algorithm": "Longest Subarray with Sum Divisible by K",
        "purpose": "Finds maximum length of a contiguous subarray whose sum is a multiple of K in linear time.",
        "time_complexity": "O(N) time",
        "space_complexity": "O(K) auxiliary space",
        "preconditions": "K >= 1.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Longest Subarray with Sum Divisible by K
// Purpose: Finds maximum length of a contiguous subarray whose sum is a multiple of K in linear time.
// Time Complexity: O(N) time
// Space Complexity: O(K) auxiliary space
// Preconditions: K >= 1.

class LongestSubarrayDivisibleByK {
public:
    static int max_len(const std::vector<long long>& a, long long k) {
        assert(k > 0);
        std::vector<int> first_idx(k, -2);
        first_idx[0] = -1;

        long long pref = 0;
        int ans = 0;

        for (int i = 0; i < (int)a.size(); ++i) {
            pref = (pref + a[i]) % k;
            if (pref < 0) pref += k;

            if (first_idx[pref] != -2) {
                ans = std::max(ans, i - first_idx[pref]);
            } else {
                first_idx[pref] = i;
            }
        }
        return ans;
    }
};

int main() {
    std::vector<long long> a = {2, 7, 6, 1, 4, 5};
    // Sum = 25. For k=3: max subarray [7, 6, 1, 4] sum=18 len=4
    assert(LongestSubarrayDivisibleByK::max_len(a, 3) == 4);

    std::vector<long long> b = {-2, 2, -5, 12, -11, -1, 7};
    assert(LongestSubarrayDivisibleByK::max_len(b, 3) == 7);

    std::cout << "longest_subarray_divisible_by_k tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "product_of_array_except_self.cpp",
        "algorithm": "Product of Array Except Self",
        "purpose": "Computes an array where output[i] is the product of all elements in array except a[i] in O(N) without division.",
        "time_complexity": "O(N) time",
        "space_complexity": "O(1) auxiliary space beyond the output array",
        "preconditions": "64-bit integer calculations.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Product of Array Except Self
// Purpose: Computes an array where output[i] is the product of all elements in array except a[i] in O(N) without division.
// Time Complexity: O(N) time
// Space Complexity: O(1) auxiliary space beyond the output array
// Preconditions: 64-bit integer calculations.

class ProductExceptSelf {
public:
    static std::vector<long long> calculate(const std::vector<long long>& a) {
        int n = a.size();
        std::vector<long long> res(n, 1);

        long long left_prod = 1;
        for (int i = 0; i < n; ++i) {
            res[i] = left_prod;
            left_prod *= a[i];
        }

        long long right_prod = 1;
        for (int i = n - 1; i >= 0; --i) {
            res[i] *= right_prod;
            right_prod *= a[i];
        }

        return res;
    }
};

int main() {
    std::vector<long long> a = {1, 2, 3, 4};
    auto p = ProductExceptSelf::calculate(a);
    std::vector<long long> expected = {24, 12, 8, 6};
    assert(p == expected);

    std::vector<long long> b = {-1, 1, 0, -3, 3};
    auto p2 = ProductExceptSelf::calculate(b);
    std::vector<long long> expected2 = {0, 0, 9, 0, 0};
    assert(p2 == expected2);

    std::cout << "product_of_array_except_self tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "circular_array_loop_detection.cpp",
        "algorithm": "Circular Array Loop Detection",
        "purpose": "Determines if a cycle exists in a circular array where index transitions are given by (i + a[i]) % n.",
        "time_complexity": "O(N) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "Cycle length must be > 1 and unidirectional.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Circular Array Loop Detection
// Purpose: Determines if a cycle exists in a circular array where index transitions are given by (i + a[i]) % n.
// Time Complexity: O(N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Cycle length must be > 1 and unidirectional.

class CircularArrayLoop {
public:
    static bool circular_array_loop(std::vector<int>& nums) {
        int n = nums.size();
        auto next_idx = [&](int i) {
            return ((i + nums[i]) % n + n) % n;
        };

        for (int i = 0; i < n; ++i) {
            if (nums[i] == 0) continue;
            int slow = i, fast = i;

            while (nums[slow] * nums[next_idx(slow)] > 0 &&
                   nums[fast] * nums[next_idx(fast)] > 0 &&
                   nums[fast] * nums[next_idx(next_idx(fast))] > 0) {
                slow = next_idx(slow);
                fast = next_idx(next_idx(fast));

                if (slow == fast) {
                    if (slow == next_idx(slow)) {
                        break; // Cycle of length 1 is invalid
                    }
                    return true;
                }
            }

            // Mark visited path as 0
            int cur = i;
            int val = nums[i];
            while (nums[cur] * val > 0) {
                int nxt = next_idx(cur);
                nums[cur] = 0;
                cur = nxt;
            }
        }
        return false;
    }
};

int main() {
    std::vector<int> a = {2, -1, 1, 2, 2};
    assert(CircularArrayLoop::circular_array_loop(a) == true);

    std::vector<int> b = {-1, 2};
    assert(CircularArrayLoop::circular_array_loop(b) == false);

    std::cout << "circular_array_loop_detection tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "matrix_prefix_sum_xor_2d.cpp",
        "algorithm": "2D Matrix Prefix XOR",
        "purpose": "Calculates 2D subgrid XOR sums in O(1) time after O(R * C) preprocessing.",
        "time_complexity": "O(R * C) preprocessing, O(1) per range query",
        "space_complexity": "O(R * C) auxiliary space",
        "preconditions": "0 <= r1 <= r2 < R, 0 <= c1 <= c2 < C.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: 2D Matrix Prefix XOR
// Purpose: Calculates 2D subgrid XOR sums in O(1) time after O(R * C) preprocessing.
// Time Complexity: O(R * C) preprocessing, O(1) per range query
// Space Complexity: O(R * C) auxiliary space
// Preconditions: 0 <= r1 <= r2 < R, 0 <= c1 <= c2 < C.

class PrefixXor2D {
private:
    int R, C;
    std::vector<std::vector<long long>> px;

public:
    PrefixXor2D(const std::vector<std::vector<long long>>& mat) {
        R = mat.size();
        C = (R > 0 ? mat[0].size() : 0);
        px.assign(R + 1, std::vector<long long>(C + 1, 0));

        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                px[i + 1][j + 1] = mat[i][j] ^ px[i][j + 1] ^ px[i + 1][j] ^ px[i][j];
            }
        }
    }

    long long query(int r1, int c1, int r2, int c2) const {
        assert(r1 >= 0 && r1 <= r2 && r2 < R);
        assert(c1 >= 0 && c1 <= c2 && c2 < C);
        return px[r2 + 1][c2 + 1] ^ px[r1][c2 + 1] ^ px[r2 + 1][c1] ^ px[r1][c1];
    }
};

int main() {
    std::vector<std::vector<long long>> mat = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    PrefixXor2D px2(mat);

    assert(px2.query(0, 0, 0, 0) == 1);
    assert(px2.query(0, 0, 1, 1) == (1 ^ 2 ^ 4 ^ 5));
    assert(px2.query(1, 1, 2, 2) == (5 ^ 6 ^ 8 ^ 9));

    std::cout << "matrix_prefix_sum_xor_2d tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "kadane_two_non_overlapping.cpp",
        "algorithm": "Two Non-Overlapping Maximum Subarrays",
        "purpose": "Finds the maximum possible total sum of two contiguous, disjoint subarrays in O(N) time.",
        "time_complexity": "O(N) time",
        "space_complexity": "O(N) auxiliary space",
        "preconditions": "Array length >= 2.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Two Non-Overlapping Maximum Subarrays
// Purpose: Finds the maximum possible total sum of two contiguous, disjoint subarrays in O(N) time.
// Time Complexity: O(N) time
// Space Complexity: O(N) auxiliary space
// Preconditions: Array length >= 2.

class TwoNonOverlappingSubarrays {
public:
    static long long max_two_subarrays_sum(const std::vector<long long>& a) {
        int n = a.size();
        assert(n >= 2);

        // left_max[i]: max subarray sum ending at or before index i
        std::vector<long long> left_max(n);
        long long cur = a[0];
        left_max[0] = cur;
        long long best = cur;

        for (int i = 1; i < n; ++i) {
            cur = std::max(a[i], cur + a[i]);
            best = std::max(best, cur);
            left_max[i] = best;
        }

        // right_max[i]: max subarray sum starting at or after index i
        std::vector<long long> right_max(n);
        cur = a[n - 1];
        right_max[n - 1] = cur;
        best = cur;

        for (int i = n - 2; i >= 0; --i) {
            cur = std::max(a[i], cur + a[i]);
            best = std::max(best, cur);
            right_max[i] = best;
        }

        long long ans = -2e18;
        for (int i = 0; i < n - 1; ++i) {
            ans = std::max(ans, left_max[i] + right_max[i + 1]);
        }
        return ans;
    }
};

int main() {
    std::vector<long long> a = {1, 3, -1, 2, -1, 2};
    // Best two: [1, 3] sum=4 and [2, -1, 2] sum=3 -> total 7
    assert(TwoNonOverlappingSubarrays::max_two_subarrays_sum(a) == 7);

    std::vector<long long> b = {-1, -2, -3, -4};
    // Best two single elements: -1 and -2 -> total -3
    assert(TwoNonOverlappingSubarrays::max_two_subarrays_sum(b) == -3);

    std::cout << "kadane_two_non_overlapping tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "count_subarrays_sum_exact_k.cpp",
        "algorithm": "Count Subarrays with Sum Equal to K",
        "purpose": "Counts total number of continuous subarrays whose elements sum up exactly to target K.",
        "time_complexity": "O(N) average time",
        "space_complexity": "O(N) space",
        "preconditions": "64-bit integer values.",
        "code": r"""#include <iostream>
#include <vector>
#include <unordered_map>
#include <cassert>

// Algorithm: Count Subarrays with Sum Equal to K
// Purpose: Counts total number of continuous subarrays whose elements sum up exactly to target K.
// Time Complexity: O(N) average time
// Space Complexity: O(N) space
// Preconditions: 64-bit integer values.

class CountSubarraysSumExactK {
public:
    static long long count(const std::vector<long long>& a, long long k) {
        std::unordered_map<long long, long long> prefix_counts;
        prefix_counts[0] = 1;

        long long pref = 0;
        long long total = 0;

        for (long long x : a) {
            pref += x;
            auto it = prefix_counts.find(pref - k);
            if (it != prefix_counts.end()) {
                total += it->second;
            }
            prefix_counts[pref]++;
        }
        return total;
    }
};

int main() {
    std::vector<long long> a = {1, 1, 1};
    assert(CountSubarraysSumExactK::count(a, 2) == 2);

    std::vector<long long> b = {1, 2, 3, -3, 1, 1, 1, 4, 2, -3};
    // Subarrays with sum 3:
    assert(CountSubarraysSumExactK::count(b, 3) == 8);

    std::cout << "count_subarrays_sum_exact_k tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "in_place_rearrange_elements.cpp",
        "algorithm": "In-Place Permutation Rearrange A[i] = A[A[i]]",
        "purpose": "Rearranges an array such that a[i] becomes a[a[i]] in-place using O(1) extra space via modular arithmetic encoding.",
        "time_complexity": "O(N) time with two passes",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "All elements 0 <= a[i] < N.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: In-Place Permutation Rearrange A[i] = A[A[i]]
// Purpose: Rearranges an array such that a[i] becomes a[a[i]] in-place using O(1) extra space via modular arithmetic encoding.
// Time Complexity: O(N) time with two passes
// Space Complexity: O(1) auxiliary space
// Preconditions: All elements 0 <= a[i] < N.

class InPlacePermutationRearrange {
public:
    static void rearrange(std::vector<int>& a) {
        int n = a.size();
        for (int i = 0; i < n; ++i) {
            a[i] += (a[a[i]] % n) * n;
        }
        for (int i = 0; i < n; ++i) {
            a[i] /= n;
        }
    }
};

int main() {
    std::vector<int> a = {3, 2, 0, 1};
    // a[0] = a[3] = 1
    // a[1] = a[2] = 0
    // a[2] = a[0] = 3
    // a[3] = a[1] = 2
    InPlacePermutationRearrange::rearrange(a);
    std::vector<int> expected = {1, 0, 3, 2};
    assert(a == expected);

    std::vector<int> b = {4, 0, 2, 1, 3};
    InPlacePermutationRearrange::rearrange(b);
    std::vector<int> expected2 = {3, 4, 2, 0, 1};
    assert(b == expected2);

    std::cout << "in_place_rearrange_elements tests passed successfully.\n";
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
    print(f"\nBatch 1 completed: {count} implementations written to {TARGET_DIR.name}")

if __name__ == "__main__":
    main()
