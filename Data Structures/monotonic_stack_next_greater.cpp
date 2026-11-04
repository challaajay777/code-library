// Algorithm: Next Greater Element via Monotonic Stack
// Purpose: Finds the first strictly greater element to the right of every position in O(N).
// Time Complexity: O(N)
// Space Complexity: O(N)
// Preconditions: Array of comparable elements.

#include <iostream>
#include <vector>
#include <stack>
#include <cassert>

std::vector<int> next_greater_elements(const std::vector<int>& nums) {
    int n = nums.size();
    std::vector<int> res(n, -1);
    std::stack<int> st;

    for (int i = 0; i < n; ++i) {
        while (!st.empty() && nums[st.top()] < nums[i]) {
            res[st.top()] = nums[i];
            st.pop();
        }
        st.push(i);
    }
    return res;
}

int main() {
    std::vector<int> a = {4, 5, 2, 25};
    auto res = next_greater_elements(a);
    assert(res == std::vector<int>({5, 25, 25, -1}));
    return 0;
}
