#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Minimum Railway Platforms Required
// Purpose: Finds minimum number of railway platforms required given train arrival and departure times in O(N log N).
// Time Complexity: O(N log N) time
// Space Complexity: O(1) auxiliary space beyond sort
// Preconditions: Arrival and departure times in consistent time units.

class MinimumPlatforms {
public:
    static int find_platform(std::vector<int>& arr, std::vector<int>& dep) {
        int n = arr.size();
        std::sort(arr.begin(), arr.end());
        std::sort(dep.begin(), dep.end());

        int plat_needed = 1, max_plat = 1;
        int i = 1, j = 0;

        while (i < n && j < n) {
            if (arr[i] <= dep[j]) {
                plat_needed++;
                i++;
            } else {
                plat_needed--;
                j++;
            }
            max_plat = std::max(max_plat, plat_needed);
        }
        return max_plat;
    }
};

int main() {
    std::vector<int> arr = {900, 940, 950, 1100, 1500, 1800};
    std::vector<int> dep = {910, 1200, 1120, 1130, 1900, 2000};
    assert(MinimumPlatforms::find_platform(arr, dep) == 3);

    std::cout << "minimum_platforms_trains tests passed successfully.\n";
    return 0;
}
