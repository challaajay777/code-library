#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Queue Reconstruction by Height
// Purpose: Reconstructs queue of people [h, k] where h is height and k is number of people taller or equal in front in O(N^2).
// Time Complexity: O(N^2) time
// Space Complexity: O(N) space
// Preconditions: Valid people descriptions with h >= 0, k >= 0.

class QueueReconstruction {
public:
    static std::vector<std::pair<int, int>> reconstruct_queue(std::vector<std::pair<int, int>>& people) {
        // Sort descending by height; if equal height, sort ascending by k
        std::sort(people.begin(), people.end(), [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
            if (a.first != b.first) return a.first > b.first;
            return a.second < b.second;
        });

        std::vector<std::pair<int, int>> queue;
        for (const auto& p : people) {
            queue.insert(queue.begin() + p.second, p);
        }
        return queue;
    }
};

int main() {
    std::vector<std::pair<int, int>> people = {{7, 0}, {4, 4}, {7, 1}, {5, 0}, {6, 1}, {5, 2}};
    auto res = QueueReconstruction::reconstruct_queue(people);
    std::vector<std::pair<int, int>> expected = {{5, 0}, {7, 0}, {5, 2}, {6, 1}, {4, 4}, {7, 1}};
    assert(res == expected);

    std::cout << "queue_reconstruction_by_height tests passed successfully.\n";
    return 0;
}
