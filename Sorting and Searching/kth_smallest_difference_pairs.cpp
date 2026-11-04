#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: K-th Smallest Absolute Pair Distance
// Purpose: Finds the k-th smallest distance |a[i] - a[j]| among all pairs in array in O(N log(max_dist)) using two pointers.
// Time Complexity: O(N log(max_dist)) time
// Space Complexity: O(1) auxiliary space beyond sorting
// Preconditions: 1 <= k <= N*(N-1)/2.

class KthSmallestPairDistance {
private:
    static int count_pairs(const std::vector<int>& a, int dist) {
        int n = a.size();
        int count = 0;
        int left = 0;
        for (int right = 0; right < n; ++right) {
            while (a[right] - a[left] > dist) {
                left++;
            }
            count += (right - left);
        }
        return count;
    }

public:
    static int smallest_distance_pair(std::vector<int>& a, int k) {
        std::sort(a.begin(), a.end());
        int low = 0;
        int high = a.back() - a.front();
        int ans = high;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (count_pairs(a, mid) >= k) {
                ans = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        return ans;
    }
};

int main() {
    std::vector<int> a = {1, 3, 1};
    // Pairs: (1,3) diff=2, (1,1) diff=0, (3,1) diff=2. Sorted: 0, 2, 2. k=1 -> 0
    assert(KthSmallestPairDistance::smallest_distance_pair(a, 1) == 0);

    std::vector<int> b = {1, 6, 1};
    assert(KthSmallestPairDistance::smallest_distance_pair(b, 3) == 5);

    std::cout << "kth_smallest_difference_pairs tests passed successfully.\n";
    return 0;
}
