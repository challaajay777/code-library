#include <iostream>
#include <string>
#include <cassert>

// Algorithm: Monotone Increasing Digits
// Purpose: Finds the largest integer less than or equal to N with monotone non-decreasing digits in O(digits) time.
// Time Complexity: O(digits) time
// Space Complexity: O(digits) space
// Preconditions: N >= 0.

class MonotoneIncreasingDigits {
public:
    static int monotone_digits(int n) {
        std::string s = std::to_string(n);
        int marker = s.size();

        for (int i = (int)s.size() - 1; i > 0; --i) {
            if (s[i - 1] > s[i]) {
                marker = i;
                s[i - 1]--;
            }
        }

        for (size_t i = marker; i < s.size(); ++i) {
            s[i] = '9';
        }
        return std::stoi(s);
    }
};

int main() {
    assert(MonotoneIncreasingDigits::monotone_digits(10) == 9);
    assert(MonotoneIncreasingDigits::monotone_digits(1234) == 1234);
    assert(MonotoneIncreasingDigits::monotone_digits(332) == 299);

    std::cout << "monotone_increasing_digits tests passed successfully.\n";
    return 0;
}
