#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>

// Algorithm: Largest Number Concatenation
// Purpose: Arranges a list of non-negative integers such that their concatenation forms the largest possible number in O(N log N).
// Time Complexity: O(N log N * L) time where L is average number of digits
// Space Complexity: O(N * L) space
// Preconditions: Array of non-negative integers.

class LargestNumber {
public:
    static std::string form_largest(std::vector<int>& nums) {
        std::vector<std::string> str_nums;
        for (int x : nums) str_nums.push_back(std::to_string(x));

        std::sort(str_nums.begin(), str_nums.end(), [](const std::string& a, const std::string& b) {
            return (a + b) > (b + a);
        });

        if (str_nums[0] == "0") return "0";

        std::string result = "";
        for (const auto& s : str_nums) result += s;
        return result;
    }
};

int main() {
    std::vector<int> nums = {10, 2};
    assert(LargestNumber::form_largest(nums) == "210");

    std::vector<int> nums2 = {3, 30, 34, 5, 9};
    assert(LargestNumber::form_largest(nums2) == "9534330");

    std::cout << "largest_number_custom_comparator tests passed successfully.\n";
    return 0;
}
