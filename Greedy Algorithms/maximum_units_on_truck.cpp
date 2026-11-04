#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Maximum Units on a Truck
// Purpose: Maximizes total units loaded onto a truck of box capacity B in O(N log N).
// Time Complexity: O(N log N) time
// Space Complexity: O(1) auxiliary space beyond sort
// Preconditions: Box types formatted as [number_of_boxes, units_per_box].

class MaximumUnitsOnTruck {
public:
    static int maximum_units(std::vector<std::pair<int, int>>& box_types, int truck_size) {
        std::sort(box_types.begin(), box_types.end(), [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
            return a.second > b.second;
        });

        int units = 0;
        for (const auto& b : box_types) {
            int take = std::min(truck_size, b.first);
            units += take * b.second;
            truck_size -= take;
            if (truck_size == 0) break;
        }
        return units;
    }
};

int main() {
    std::vector<std::pair<int, int>> boxes = {{1, 3}, {2, 2}, {3, 1}};
    assert(MaximumUnitsOnTruck::maximum_units(boxes, 4) == 8);

    std::cout << "maximum_units_on_truck tests passed successfully.\n";
    return 0;
}
