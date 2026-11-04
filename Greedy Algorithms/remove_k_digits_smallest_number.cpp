#include <iostream>
#include <string>
#include <vector>
#include <cassert>

// Algorithm: Remove K Digits (Smallest Number Monotonic Stack)
// Purpose: Removes K digits from number string to form the smallest possible numerical value in O(N).
// Time Complexity: O(N) time
// Space Complexity: O(N) auxiliary space
// Preconditions: String num contains digits; 0 <= K <= |num|.

class RemoveKDigits {
public:
    static std::string remove_kdigits(const std::string& num, int k) {
        std::string st = "";
        for (char c : num) {
            while (!st.empty() && k > 0 && st.back() > c) {
                st.pop_back();
                k--;
            }
            st.push_back(c);
        }

        while (k > 0 && !st.empty()) {
            st.pop_back();
            k--;
        }

        // Strip leading zeros
        size_t start = 0;
        while (start < st.size() && st[start] == '0') {
            start++;
        }
        std::string res = st.substr(start);
        return res.empty() ? "0" : res;
    }
};

int main() {
    assert(RemoveKDigits::remove_kdigits("1432219", 3) == "1219");
    assert(RemoveKDigits::remove_kdigits("10200", 1) == "200");
    assert(RemoveKDigits::remove_kdigits("10", 2) == "0");

    std::cout << "remove_k_digits_smallest_number tests passed successfully.\n";
    return 0;
}
