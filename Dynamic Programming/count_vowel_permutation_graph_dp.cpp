// Algorithm: Count Vowel Permutation Graph DP
// Purpose: Counts strings of length n made of vowels obeying specific transition rules modulo 10^9+7.
// Time Complexity: O(N)
// Space Complexity: O(1)
// Preconditions: n >= 1.

#include <iostream>
#include <vector>
#include <cassert>

int count_vowel_permutation(int n) {
    static const int MOD = 1000000007;
    long long a = 1, e = 1, i = 1, o = 1, u = 1;

    for (int step = 2; step <= n; ++step) {
        long long next_a = (e + i + u) % MOD;
        long long next_e = (a + i) % MOD;
        long long next_i = (e + o) % MOD;
        long long next_o = i % MOD;
        long long next_u = (i + o) % MOD;

        a = next_a; e = next_e; i = next_i; o = next_o; u = next_u;
    }
    return (a + e + i + o + u) % MOD;
}

int main() {
    assert(count_vowel_permutation(1) == 5);
    assert(count_vowel_permutation(2) == 10);
    assert(count_vowel_permutation(5) == 68);
    return 0;
}
