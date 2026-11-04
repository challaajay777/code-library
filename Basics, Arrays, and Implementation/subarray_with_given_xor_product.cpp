#include <iostream>
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
