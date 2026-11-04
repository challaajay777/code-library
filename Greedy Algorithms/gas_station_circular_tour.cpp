#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Gas Station Circular Tour
// Purpose: Finds unique starting gas station index from which a car can complete a full clockwise circuit in O(N) time and O(1) space.
// Time Complexity: O(N) time single pass
// Space Complexity: O(1) auxiliary space
// Preconditions: Non-negative gas and cost values.

class GasStationTour {
public:
    static int can_complete_circuit(const std::vector<int>& gas, const std::vector<int>& cost) {
        int total_tank = 0;
        int curr_tank = 0;
        int starting_station = 0;

        for (size_t i = 0; i < gas.size(); ++i) {
            int balance = gas[i] - cost[i];
            total_tank += balance;
            curr_tank += balance;

            if (curr_tank < 0) {
                starting_station = i + 1;
                curr_tank = 0;
            }
        }
        return total_tank >= 0 ? starting_station : -1;
    }
};

int main() {
    std::vector<int> gas = {1, 2, 3, 4, 5};
    std::vector<int> cost = {3, 4, 5, 1, 2};
    assert(GasStationTour::can_complete_circuit(gas, cost) == 3);

    std::vector<int> gas2 = {2, 3, 4};
    std::vector<int> cost2 = {3, 4, 3};
    assert(GasStationTour::can_complete_circuit(gas2, cost2) == -1);

    std::cout << "gas_station_circular_tour tests passed successfully.\n";
    return 0;
}
