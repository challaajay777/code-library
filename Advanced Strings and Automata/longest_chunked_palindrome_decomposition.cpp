// Algorithm: Longest Chunked Palindrome Decomposition (LCPD)
// Purpose: Finds maximum k such that string can be split into chunks s = a_1 + a_2 + ... + a_k with a_i = a_{k-i+1}.
// Time Complexity: O(N)
// Space Complexity: O(N)
// Preconditions: String with valid characters.

#include <iostream>
#include <vector>
#include <string>
#include <cassert>

class ChunkedPalindrome {
    static const unsigned long long BASE = 13331ULL;

public:
    static int max_chunks(const std::string& s) {
        int n = s.size();
        int chunks = 0;
        int l = 0, r = n - 1;

        unsigned long long hash_l = 0, hash_r = 0;
        unsigned long long base_pow = 1;

        while (l < r) {
            hash_l = hash_l * BASE + s[l];
            hash_r = hash_r + s[r] * base_pow;
            base_pow *= BASE;

            if (hash_l == hash_r) {
                // Potential chunk match
                chunks += 2;
                hash_l = 0;
                hash_r = 0;
                base_pow = 1;
            }
            l++;
            r--;
        }

        if (l == r || hash_l != 0) {
            chunks++;
        }
        return chunks;
    }
};

int main() {
    assert(ChunkedPalindrome::max_chunks("ghiabcdefhelloadamhelloabcdefghi") == 7);
    assert(ChunkedPalindrome::max_chunks("merchant") == 1);
    assert(ChunkedPalindrome::max_chunks("antaprezatepzapreanta") == 11);
    return 0;
}
