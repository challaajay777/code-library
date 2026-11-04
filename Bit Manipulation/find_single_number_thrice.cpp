#include <iostream>
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
