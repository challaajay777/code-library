#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Two Sum (Sorted Array Two Pointers)
// Purpose: Finds two indices in a 1-indexed sorted array that add up to target in O(N) time and O(1) space.
// Time Complexity: O(N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Array sorted in non-decreasing order.

class TwoSumSorted {
public:
    static std::pair<int, int> two_sum(const std::vector<int>& numbers, int target) {
        int left = 0, right = (int)numbers.size() - 1;

        while (left < right) {
            int sum = numbers[left] + numbers[right];
            if (sum == target) {
                return {left + 1, right + 1}; // 1-based indexing
            } else if (sum < target) {
                left++;
            } else {
                right--;
            }
        }
        return {-1, -1};
    }
};

int main() {
    std::vector<int> a = {2, 7, 11, 15};
    auto [i, j] = TwoSumSorted::two_sum(a, 9);
    assert(i == 1 && j == 2);

    std::vector<int> b = {2, 3, 4};
    auto [i2, j2] = TwoSumSorted::two_sum(b, 6);
    assert(i2 == 1 && j2 == 3);

    std::cout << "two_sum_sorted tests passed successfully.\n";
    return 0;
}
