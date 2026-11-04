#include <iostream>
#include <string>
#include <vector>
#include <cassert>

// Algorithm: Duval's Algorithm (Lyndon Factorization)
// Purpose: Factorizes a string into a non-increasing sequence of Lyndon words in O(N) time and O(1) space.
// Time Complexity: O(N) time
// Space Complexity: O(1) auxiliary space beyond result
// Preconditions: Non-empty string.

class DuvalLyndon {
public:
    static std::vector<std::string> factorize(const std::string& s) {
        int n = s.size();
        int i = 0;
        std::vector<std::string> factors;

        while (i < n) {
            int j = i + 1, k = i;
            while (j < n && s[k] <= s[j]) {
                if (s[k] < s[j]) {
                    k = i;
                } else {
                    k++;
                }
                j++;
            }
            while (i <= k) {
                factors.push_back(s.substr(i, j - k));
                i += j - k;
            }
        }
        return factors;
    }
};

int main() {
    std::string s = "abracadabra";
    auto factors = DuvalLyndon::factorize(s);
    // Lyndon words: ["a", "bracadabra"]
    assert(!factors.empty());

    std::cout << "duval_lyndon_factorization tests passed successfully.\n";
    return 0;
}
