#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cassert>

// Algorithm: Minimize Maximum Distance to Gas Station
// Purpose: Adds K new gas stations on a highway to minimize the maximum distance between adjacent gas stations via binary search on answer.
// Time Complexity: O(N * log(max_gap / eps)) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Stations array sorted; K >= 1.

class GasStationMinMaxDistance {
private:
    static bool possible(const std::vector<double>& stations, int k, double d) {
        int added = 0;
        for (size_t i = 1; i < stations.size(); ++i) {
            added += static_cast<int>((stations[i] - stations[i - 1]) / d);
        }
        return added <= k;
    }

public:
    static double minmax_gas_dist(const std::vector<double>& stations, int k, int iterations = 100) {
        double low = 0.0;
        double high = stations.back() - stations.front();

        for (int i = 0; i < iterations; ++i) {
            double mid = low + (high - low) / 2.0;
            if (possible(stations, k, mid)) {
                high = mid;
            } else {
                low = mid;
            }
        }
        return (low + high) / 2.0;
    }
};

int main() {
    std::vector<double> stations = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    double ans = GasStationMinMaxDistance::minmax_gas_dist(stations, 9);
    assert(std::abs(ans - 0.5) < 1e-3);

    std::cout << "minimize_max_distance_to_gas_station tests passed successfully.\n";
    return 0;
}
