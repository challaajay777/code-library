// Algorithm: Decode Ways DP (Letter Mappings)
// Purpose: Calculates number of ways to decode a digit string into characters 'A'-'Z'.
// Time Complexity: O(N)
// Space Complexity: O(1)
// Preconditions: Digit string s containing characters '0'-'9'.

#include <iostream>
#include <string>
#include <cassert>

int num_decodings(const std::string& s) {
    if (s.empty() || s[0] == '0') return 0;
    int n = s.size();
    int prev2 = 1, prev1 = 1;

    for (int i = 1; i < n; ++i) {
        int cur = 0;
        if (s[i] != '0') cur += prev1;
        int two_digit = (s[i - 1] - '0') * 10 + (s[i] - '0');
        if (two_digit >= 10 && two_digit <= 26) cur += prev2;
        prev2 = prev1;
        prev1 = cur;
    }
    return prev1;
}

int main() {
    assert(num_decodings("12") == 2); // "AB" (1 2) or "L" (12)
    assert(num_decodings("226") == 3); // "BZ", "VF", "BBF"
    assert(num_decodings("06") == 0);
    return 0;
}
