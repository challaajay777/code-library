#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

// Algorithm: Minimum Refueling Stops
// Purpose: Finds minimum fuel stops to reach target distance using greedy max-heap choice of passed fuel stations.
// Time Complexity: O(N log N) time
// Space Complexity: O(N) space for priority queue
// Preconditions: Stations sorted by position; start_fuel >= 0.

class MinRefuelingStops {
public:
    static int min_refuel_stops(int target, int start_fuel, const std::vector<std::vector<int>>& stations) {
        std::priority_queue<int> max_heap;
        long long cur_fuel = start_fuel;
        int stops = 0;
        size_t i = 0;

        while (cur_fuel < target) {
            while (i < stations.size() && stations[i][0] <= cur_fuel) {
                max_heap.push(stations[i][1]);
                i++;
            }
            if (max_heap.empty()) return -1;
            cur_fuel += max_heap.top();
            max_heap.pop();
            stops++;
        }
        return stops;
    }
};

int main() {
    std::vector<std::vector<int>> stations = {{10, 60}, {20, 30}, {30, 30}, {60, 40}};
    assert(MinRefuelingStops::min_refuel_stops(100, 10, stations) == 2);

    assert(MinRefuelingStops::min_refuel_stops(100, 1, {}) == -1);

    std::cout << "minimum_number_of_refueling_stops tests passed successfully.\n";
    return 0;
}
