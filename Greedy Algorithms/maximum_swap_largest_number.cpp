#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Maximum Swap (Largest Number Single Swap)
// Purpose: Finds the maximum integer achievable by swapping two digits at most once in O(digits) time.
// Time Complexity: O(digits) time
// Space Complexity: O(1) space
// Preconditions: Integer num >= 0.

class MaximumSwap {
public:
    static int maximum_swap(int num) {
        std::string s = std::to_string(num);
        std::vector<int> last(10, -1);
        for (int i = 0; i < (int)s.size(); ++i) {
            last[s[i] - '0'] = i;
        }

        for (int i = 0; i < (int)s.size(); ++i) {
            for (int d = 9; d > s[i] - '0'; --d) {
                if (last[d] > i) {
                    std::swap(s[i], s[last[d]]);
                    return std::stoi(s);
                }
            }
        }
        return num;
    }
};

int main() {
    assert(MaximumSwap::maximum_swap(2736) == 7236);
    assert(MaximumSwap::maximum_swap(9973) == 9973);

    std::cout << "maximum_swap_largest_number tests passed successfully.\n";
    return 0;
}
