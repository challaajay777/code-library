#include <iostream>
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
