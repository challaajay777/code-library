#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

// Algorithm: K-th Largest Element in a Stream
// Purpose: Maintains the k-th largest element seen so far in a continuous stream of numbers using a min-heap in O(log K).
// Time Complexity: O(log K) per added element
// Space Complexity: O(K) space
// Preconditions: K >= 1.

class KthLargestStream {
private:
    int k;
    std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap;

public:
    KthLargestStream(int k_val, const std::vector<int>& nums) : k(k_val) {
        for (int x : nums) {
            add(x);
        }
    }

    int add(int val) {
        if ((int)min_heap.size() < k) {
            min_heap.push(val);
        } else if (val > min_heap.top()) {
            min_heap.pop();
            min_heap.push(val);
        }
        return min_heap.top();
    }
};

int main() {
    KthLargestStream stream(3, {4, 5, 8, 2});
    assert(stream.add(3) == 4);
    assert(stream.add(5) == 5);
    assert(stream.add(10) == 5);
    assert(stream.add(9) == 8);
    assert(stream.add(4) == 8);

    std::cout << "kth_largest_element_stream tests passed successfully.\n";
    return 0;
}
