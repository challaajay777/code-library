#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

// Algorithm: Minimum Cost of Connecting Ropes
// Purpose: Finds minimum cost to connect N ropes where the cost of connecting two ropes is the sum of their lengths in O(N log N).
// Time Complexity: O(N log N) time
// Space Complexity: O(N) space for min-heap
// Preconditions: Rope lengths positive.

class ConnectRopesMinCost {
public:
    static long long min_cost(const std::vector<long long>& ropes) {
        if (ropes.size() <= 1) return 0;
        std::priority_queue<long long, std::vector<long long>, std::greater<long long>> pq(ropes.begin(), ropes.end());
        long long total = 0;

        while (pq.size() > 1) {
            long long a = pq.top(); pq.pop();
            long long b = pq.top(); pq.pop();
            long long cost = a + b;
            total += cost;
            pq.push(cost);
        }
        return total;
    }
};

int main() {
    std::vector<long long> r = {4, 3, 2, 6};
    // 2+3=5 (cost 5), 4+5=9 (cost 9), 6+9=15 (cost 15) -> total = 29
    assert(ConnectRopesMinCost::min_cost(r) == 29);

    std::cout << "minimum_cost_ropes_connect tests passed successfully.\n";
    return 0;
}
