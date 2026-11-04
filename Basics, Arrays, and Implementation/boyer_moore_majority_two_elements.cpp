#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Boyer-Moore Majority Vote (Extended to N/3 Frequency)
// Purpose: Finds all elements appearing strictly more than floor(N/3) times (at most two elements) in linear time and O(1) space.
// Time Complexity: O(N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: General array of elements.

class MajorityVoteNThirds {
public:
    template <typename T>
    static std::vector<T> find_majority(const std::vector<T>& a) {
        int n = a.size();
        if (n == 0) return {};

        T cand1 = a[0], cand2 = a[0];
        int count1 = 0, count2 = 0;

        for (const auto& x : a) {
            if (count1 > 0 && x == cand1) {
                count1++;
            } else if (count2 > 0 && x == cand2) {
                count2++;
            } else if (count1 == 0) {
                cand1 = x;
                count1 = 1;
            } else if (count2 == 0) {
                cand2 = x;
                count2 = 1;
            } else {
                count1--;
                count2--;
            }
        }

        // Verification step
        int actual1 = 0, actual2 = 0;
        for (const auto& x : a) {
            if (count1 > 0 && x == cand1) actual1++;
            else if (count2 > 0 && x == cand2) actual2++;
        }

        std::vector<T> res;
        if (actual1 > n / 3) res.push_back(cand1);
        if (actual2 > n / 3) res.push_back(cand2);
        return res;
    }
};

int main() {
    std::vector<int> a = {3, 2, 3};
    auto res = MajorityVoteNThirds::find_majority(a);
    assert(res.size() == 1 && res[0] == 3);

    std::vector<int> b = {1, 1, 1, 3, 3, 2, 2, 2};
    auto res2 = MajorityVoteNThirds::find_majority(b);
    assert(res2.size() == 2); // 1 and 2 appear 3 times (> 8/3 = 2)

    std::cout << "boyer_moore_majority_two_elements tests passed successfully.\n";
    return 0;
}
