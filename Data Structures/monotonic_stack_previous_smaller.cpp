// Algorithm: Previous Smaller Element via Monotonic Stack
// Purpose: Finds the nearest strictly smaller element to the left of every position in O(N).
// Time Complexity: O(N)
// Space Complexity: O(N)
// Preconditions: Array of comparable elements.

#include <iostream>
#include <vector>
#include <stack>
#include <cassert>

std::vector<int> previous_smaller_elements(const std::vector<int>& nums) {
    int n = nums.size();
    std::vector<int> res(n, -1);
    std::stack<int> st;

    for (int i = 0; i < n; ++i) {
        while (!st.empty() && st.top() >= nums[i]) {
            st.pop();
        }
        if (!st.empty()) res[i] = st.top();
        st.push(nums[i]);
    }
    return res;
}

int main() {
    std::vector<int> a = {1, 6, 4, 10, 2, 5};
    auto res = previous_smaller_elements(a);
    assert(res == std::vector<int>({-1, 1, 1, 4, 1, 2}));
    return 0;
}
