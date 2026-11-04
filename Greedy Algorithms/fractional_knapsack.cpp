#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cassert>

// Algorithm: Fractional Knapsack
// Purpose: Maximizes total value achievable in knapsack of capacity W allowing fractional quantities of items.
// Time Complexity: O(N log N) time
// Space Complexity: O(1) auxiliary space beyond sort
// Preconditions: Values and weights non-negative; capacity >= 0.

struct KnapsackItem {
    double value;
    double weight;
};

class FractionalKnapsack {
public:
    static double get_max_value(double capacity, std::vector<KnapsackItem>& items) {
        std::sort(items.begin(), items.end(), [](const KnapsackItem& a, const KnapsackItem& b) {
            return (a.value / a.weight) > (b.value / b.weight);
        });

        double total_val = 0.0;
        double rem_cap = capacity;

        for (const auto& item : items) {
            if (rem_cap <= 0.0) break;
            if (item.weight <= rem_cap) {
                total_val += item.value;
                rem_cap -= item.weight;
            } else {
                total_val += item.value * (rem_cap / item.weight);
                rem_cap = 0.0;
            }
        }
        return total_val;
    }
};

int main() {
    std::vector<KnapsackItem> items = {{60, 10}, {100, 20}, {120, 30}};
    double val = FractionalKnapsack::get_max_value(50, items);
    // Takes item 1 (60), item 2 (100), and 2/3 of item 3 (80) -> 240
    assert(std::abs(val - 240.0) < 1e-6);

    std::cout << "fractional_knapsack tests passed successfully.\n";
    return 0;
}
