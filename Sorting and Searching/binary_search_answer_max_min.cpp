#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Binary Search on Answer (Maximize Minimum Distance)
// Purpose: Places K items into stalls/positions to maximize the minimum distance between any two adjacent chosen items (Aggressive Cows).
// Time Complexity: O(N log(max_pos - min_pos)) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Positions sorted; K >= 2.

class BinarySearchMaximizeMin {
private:
    static bool can_place(const std::vector<long long>& pos, int k, long long dist) {
        int placed = 1;
        long long last_pos = pos[0];

        for (size_t i = 1; i < pos.size(); ++i) {
            if (pos[i] - last_pos >= dist) {
                placed++;
                last_pos = pos[i];
                if (placed >= k) return true;
            }
        }
        return placed >= k;
    }

public:
    static long long max_min_distance(std::vector<long long>& positions, int k) {
        std::sort(positions.begin(), positions.end());
        long long low = 1;
        long long high = positions.back() - positions.front();
        long long ans = 0;

        while (low <= high) {
            long long mid = low + (high - low) / 2;
            if (can_place(positions, k, mid)) {
                ans = mid;
                low = mid + 1; // Try larger distance
            } else {
                high = mid - 1;
            }
        }
        return ans;
    }
};

int main() {
    std::vector<long long> stalls = {1, 2, 8, 4, 9};
    // For k=3 cows: stalls sorted {1, 2, 4, 8, 9}. Best positions: 1, 4, 8 or 9 (min dist = 3)
    assert(BinarySearchMaximizeMin::max_min_distance(stalls, 3) == 3);

    std::cout << "binary_search_answer_max_min tests passed successfully.\n";
    return 0;
}
