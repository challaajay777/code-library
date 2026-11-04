#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cassert>

// Algorithm: Binary Search on Answer (Minimize Maximum)
// Purpose: Solves partitioning / allocation problems (e.g. painter partition, split array largest sum) by binary searching the threshold.",
// Time Complexity: O(N log(sum - max)) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Partition count K >= 1, all array values non-negative.

class BinarySearchMinimizeMax {
private:
    static bool can_partition(const std::vector<long long>& a, int k, long long max_sum_allowed) {
        int count = 1;
        long long current_sum = 0;
        for (long long x : a) {
            if (x > max_sum_allowed) return false;
            if (current_sum + x > max_sum_allowed) {
                count++;
                current_sum = x;
            } else {
                current_sum += x;
            }
        }
        return count <= k;
    }

public:
    static long long split_array_largest_sum(const std::vector<long long>& a, int k) {
        long long low = *std::max_element(a.begin(), a.end());
        long long high = std::accumulate(a.begin(), a.end(), 0LL);
        long long ans = high;

        while (low <= high) {
            long long mid = low + (high - low) / 2;
            if (can_partition(a, k, mid)) {
                ans = mid;
                high = mid - 1; // Try smaller maximum sum
            } else {
                low = mid + 1;
            }
        }
        return ans;
    }
};

int main() {
    std::vector<long long> a = {7, 2, 5, 10, 8};
    // k = 2: best split is [7, 2, 5] and [10, 8] with sums 14 and 18 -> max is 18
    assert(BinarySearchMinimizeMax::split_array_largest_sum(a, 2) == 18);

    std::vector<long long> b = {1, 2, 3, 4, 5};
    assert(BinarySearchMinimizeMax::split_array_largest_sum(b, 2) == 9); // [1,2,3],[4,5]

    std::cout << "binary_search_answer_min_max tests passed successfully.\n";
    return 0;
}
