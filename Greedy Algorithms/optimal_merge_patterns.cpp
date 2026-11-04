#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

// Algorithm: Optimal Merge Patterns
// Purpose: Finds the minimum total cost to merge N files into one file using a min-heap in O(N log N).
// Time Complexity: O(N log N) time
// Space Complexity: O(N) space for priority queue
// Preconditions: File sizes are positive integers.

class OptimalMergePatterns {
public:
    static long long min_computation_cost(const std::vector<long long>& files) {
        if (files.size() <= 1) return 0;
        std::priority_queue<long long, std::vector<long long>, std::greater<long long>> pq(files.begin(), files.end());
        long long total_cost = 0;

        while (pq.size() > 1) {
            long long a = pq.top(); pq.pop();
            long long b = pq.top(); pq.pop();
            long long sum = a + b;
            total_cost += sum;
            pq.push(sum);
        }
        return total_cost;
    }
};

int main() {
    std::vector<long long> files = {2, 3, 4, 5, 6, 7};
    // Merges: 2+3=5, 4+5=9, 5+6=11, 7+9=16, 11+16=27 -> total cost = 5 + 9 + 11 + 16 + 27 = 68
    assert(OptimalMergePatterns::min_computation_cost(files) == 68);

    std::cout << "optimal_merge_patterns tests passed successfully.\n";
    return 0;
}
