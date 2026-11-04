#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Container with Most Water
// Purpose: Finds two vertical lines that together with the x-axis form a container holding the maximum water in O(N).
// Time Complexity: O(N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Heights are non-negative.

class ContainerWithMostWater {
public:
    static long long max_area(const std::vector<int>& height) {
        int left = 0, right = (int)height.size() - 1;
        long long max_water = 0;

        while (left < right) {
            long long h = std::min(height[left], height[right]);
            max_water = std::max(max_water, h * (right - left));

            if (height[left] < height[right]) {
                left++;
            } else {
                right--;
            }
        }
        return max_water;
    }
};

int main() {
    std::vector<int> h = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    assert(ContainerWithMostWater::max_area(h) == 49);

    std::vector<int> h2 = {1, 1};
    assert(ContainerWithMostWater::max_area(h2) == 1);

    std::cout << "container_with_most_water tests passed successfully.\n";
    return 0;
}
