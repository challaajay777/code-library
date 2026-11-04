#include <iostream>
#include <vector>
#include <stack>
#include <cassert>

// Algorithm: Next Greater Element in Circular Array
// Purpose: Finds the first greater element for each index in a circular array in O(N) time using a monotonic stack.
// Time Complexity: O(N) time
// Space Complexity: O(N) auxiliary space
// Preconditions: Returns -1 if no greater element exists in circular array.

class CircularNextGreaterElement {
public:
    static std::vector<int> next_greater(const std::vector<int>& a) {
        int n = a.size();
        std::vector<int> res(n, -1);
        std::stack<int> st;

        for (int i = 0; i < 2 * n; ++i) {
            int cur = a[i % n];
            while (!st.empty() && a[st.top()] < cur) {
                res[st.top()] = cur;
                st.pop();
            }
            if (i < n) {
                st.push(i);
            }
        }
        return res;
    }
};

int main() {
    std::vector<int> a = {1, 2, 1};
    auto res = CircularNextGreaterElement::next_greater(a);
    std::vector<int> expected = {2, -1, 2};
    assert(res == expected);

    std::vector<int> b = {1, 2, 3, 4, 3};
    auto res2 = CircularNextGreaterElement::next_greater(b);
    std::vector<int> expected2 = {2, 3, 4, -1, 4};
    assert(res2 == expected2);

    std::cout << "next_greater_element_circular tests passed successfully.\n";
    return 0;
}
