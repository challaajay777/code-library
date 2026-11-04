#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Submask Enumeration
// Purpose: Iterates over all submasks of a bitmask in descending order; enumerates all submasks of all masks in O(3^N).
// Time Complexity: O(2^k) for a mask with k set bits; O(3^N) for all masks up to N bits
// Space Complexity: O(1) auxiliary space
// Preconditions: 0 <= mask < 2^63.

class SubmaskEnumeration {
public:
    static std::vector<long long> get_submasks(long long mask) {
        std::vector<long long> submasks;
        for (long long s = mask; s > 0; s = (s - 1) & mask) {
            submasks.push_back(s);
        }
        submasks.push_back(0); // empty mask
        return submasks;
    }
};

int main() {
    long long mask = 5; // binary 101: submasks are 5 (101), 4 (100), 1 (001), 0 (000)
    auto res = SubmaskEnumeration::get_submasks(mask);
    std::vector<long long> expected = {5, 4, 1, 0};
    assert(res == expected);

    std::cout << "submask_enumeration tests passed successfully.\n";
    return 0;
}
