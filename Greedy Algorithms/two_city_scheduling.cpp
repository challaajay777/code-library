#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Two City Scheduling
// Purpose: Finds minimum travel cost to send exactly N people to city A and N to city B in O(2N log 2N).
// Time Complexity: O(N log N) time
// Space Complexity: O(1) auxiliary space beyond sort
// Preconditions: Costs vector has even length 2*N.

class TwoCityScheduling {
public:
    static int two_city_sched_cost(std::vector<std::vector<int>>& costs) {
        // Sort by the refund / gain of sending to city A vs B (costA - costB)
        std::sort(costs.begin(), costs.end(), [](const std::vector<int>& a, const std::vector<int>& b) {
            return (a[0] - a[1]) < (b[0] - b[1]);
        });

        int total = 0;
        int n = costs.size() / 2;
        for (int i = 0; i < n; ++i) {
            total += costs[i][0]; // Send first n to city A
        }
        for (int i = n; i < 2 * n; ++i) {
            total += costs[i][1]; // Send remaining n to city B
        }
        return total;
    }
};

int main() {
    std::vector<std::vector<int>> costs = {{10, 20}, {30, 200}, {400, 50}, {30, 20}};
    assert(TwoCityScheduling::two_city_sched_cost(costs) == 110);

    std::cout << "two_city_scheduling tests passed successfully.\n";
    return 0;
}
