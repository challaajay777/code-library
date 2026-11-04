#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Boats to Save People (Two Pointers Greedy)
// Purpose: Finds minimum rescue boats needed where each boat carries at most 2 people and total weight <= limit.
// Time Complexity: O(N log N) time
// Space Complexity: O(1) auxiliary space beyond sort
// Preconditions: People weights <= limit; boat capacity = 2.

class BoatsToSavePeople {
public:
    static int num_rescue_boats(std::vector<int>& people, int limit) {
        std::sort(people.begin(), people.end());
        int left = 0, right = (int)people.size() - 1;
        int boats = 0;

        while (left <= right) {
            if (people[left] + people[right] <= limit) {
                left++;
            }
            right--;
            boats++;
        }
        return boats;
    }
};

int main() {
    std::vector<int> p1 = {1, 2};
    assert(BoatsToSavePeople::num_rescue_boats(p1, 3) == 1);

    std::vector<int> p2 = {3, 2, 2, 1};
    assert(BoatsToSavePeople::num_rescue_boats(p2, 3) == 3);

    std::vector<int> p3 = {3, 5, 3, 4};
    assert(BoatsToSavePeople::num_rescue_boats(p3, 5) == 4);

    std::cout << "boats_to_save_people tests passed successfully.\n";
    return 0;
}
