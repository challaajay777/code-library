#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Create Maximum Number
// Purpose: Creates the maximum number of length K from two digit arrays maintaining relative order within each in O((N+M)^3).
// Time Complexity: O(K * (N + M)^2) time
// Space Complexity: O(K) auxiliary space
// Preconditions: 0 <= K <= N + M.

class CreateMaxNumber {
private:
    static std::vector<int> max_subsequence(const std::vector<int>& nums, int k) {
        std::vector<int> res;
        int drop = nums.size() - k;
        for (int x : nums) {
            while (!res.empty() && drop > 0 && res.back() < x) {
                res.pop_back();
                drop--;
            }
            res.push_back(x);
        }
        res.resize(k);
        return res;
    }

    static std::vector<int> merge(const std::vector<int>& a, const std::vector<int>& b) {
        std::vector<int> res;
        auto it1 = a.begin(), it2 = b.begin();
        while (it1 != a.end() || it2 != b.end()) {
            if (std::lexicographical_compare(it1, a.end(), it2, b.end())) {
                res.push_back(*it2++);
            } else {
                res.push_back(*it1++);
            }
        }
        return res;
    }

public:
    static std::vector<int> max_number(const std::vector<int>& nums1, const std::vector<int>& nums2, int k) {
        std::vector<int> best;
        int n1 = nums1.size(), n2 = nums2.size();

        for (int i = std::max(0, k - n2); i <= std::min(k, n1); ++i) {
            auto s1 = max_subsequence(nums1, i);
            auto s2 = max_subsequence(nums2, k - i);
            auto candidate = merge(s1, s2);
            if (candidate > best) {
                best = candidate;
            }
        }
        return best;
    }
};

int main() {
    std::vector<int> n1 = {3, 4, 6, 5};
    std::vector<int> n2 = {9, 1, 2, 5, 8, 3};
    auto max_num = CreateMaxNumber::max_number(n1, n2, 5);
    std::vector<int> expected = {9, 8, 6, 5, 3};
    assert(max_num == expected);

    std::cout << "create_maximum_number tests passed successfully.\n";
    return 0;
}
