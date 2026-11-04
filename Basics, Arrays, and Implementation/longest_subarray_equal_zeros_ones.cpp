#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cassert>

// Algorithm: Longest Subarray with Equal 0s and 1s
// Purpose: Finds the maximum length of a contiguous binary subarray having equal numbers of 0 and 1 in O(N) time.
// Time Complexity: O(N) time
// Space Complexity: O(N) space
// Preconditions: Binary array (elements are 0 or 1).

class EqualZerosAndOnes {
public:
    static int find_max_length(const std::vector<int>& a) {
        std::unordered_map<int, int> first_seen;
        first_seen[0] = -1;

        int pref = 0;
        int max_len = 0;

        for (int i = 0; i < (int)a.size(); ++i) {
            pref += (a[i] == 1 ? 1 : -1);
            auto it = first_seen.find(pref);
            if (it != first_seen.end()) {
                max_len = std::max(max_len, i - it->second);
            } else {
                first_seen[pref] = i;
            }
        }
        return max_len;
    }
};

int main() {
    std::vector<int> a = {0, 1, 0};
    assert(EqualZerosAndOnes::find_max_length(a) == 2);

    std::vector<int> b = {0, 1, 1, 0, 1, 1, 1, 0};
    assert(EqualZerosAndOnes::find_max_length(b) == 4); // [0, 1, 1, 0]

    std::cout << "longest_subarray_equal_zeros_ones tests passed successfully.\n";
    return 0;
}
