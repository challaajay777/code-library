#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cassert>

// Algorithm: Fruit Into Baskets (Sliding Window At Most 2 Types)
// Purpose: Finds length of the longest contiguous subarray containing at most two distinct values in O(N).
// Time Complexity: O(N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Non-empty vector of tree fruit types.

class FruitIntoBaskets {
public:
    static int total_fruit(const std::vector<int>& fruits) {
        std::unordered_map<int, int> count;
        int left = 0;
        int max_picked = 0;

        for (int right = 0; right < (int)fruits.size(); ++right) {
            count[fruits[right]]++;
            while (count.size() > 2) {
                count[fruits[left]]--;
                if (count[fruits[left]] == 0) {
                    count.erase(fruits[left]);
                }
                left++;
            }
            max_picked = std::max(max_picked, right - left + 1);
        }
        return max_picked;
    }
};

int main() {
    std::vector<int> f1 = {1, 2, 1};
    assert(FruitIntoBaskets::total_fruit(f1) == 3);

    std::vector<int> f2 = {0, 1, 2, 2};
    assert(FruitIntoBaskets::total_fruit(f2) == 3); // [1, 2, 2]

    std::vector<int> f3 = {1, 2, 3, 2, 2};
    assert(FruitIntoBaskets::total_fruit(f3) == 4); // [2, 3, 2, 2]

    std::cout << "fruit_into_baskets tests passed successfully.\n";
    return 0;
}
