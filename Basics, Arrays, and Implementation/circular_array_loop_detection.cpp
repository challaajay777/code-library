#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Circular Array Loop Detection
// Purpose: Determines if a cycle exists in a circular array where index transitions are given by (i + a[i]) % n.
// Time Complexity: O(N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Cycle length must be > 1 and unidirectional.

class CircularArrayLoop {
public:
    static bool circular_array_loop(std::vector<int>& nums) {
        int n = nums.size();
        auto next_idx = [&](int i) {
            return ((i + nums[i]) % n + n) % n;
        };

        for (int i = 0; i < n; ++i) {
            if (nums[i] == 0) continue;
            int slow = i, fast = i;

            while (nums[slow] * nums[next_idx(slow)] > 0 &&
                   nums[fast] * nums[next_idx(fast)] > 0 &&
                   nums[fast] * nums[next_idx(next_idx(fast))] > 0) {
                slow = next_idx(slow);
                fast = next_idx(next_idx(fast));

                if (slow == fast) {
                    if (slow == next_idx(slow)) {
                        break; // Cycle of length 1 is invalid
                    }
                    return true;
                }
            }

            // Mark visited path as 0
            int cur = i;
            int val = nums[i];
            while (nums[cur] * val > 0) {
                int nxt = next_idx(cur);
                nums[cur] = 0;
                cur = nxt;
            }
        }
        return false;
    }
};

int main() {
    std::vector<int> a = {2, -1, 1, 2, 2};
    assert(CircularArrayLoop::circular_array_loop(a) == true);

    std::vector<int> b = {-1, 2};
    assert(CircularArrayLoop::circular_array_loop(b) == false);

    std::cout << "circular_array_loop_detection tests passed successfully.\n";
    return 0;
}
