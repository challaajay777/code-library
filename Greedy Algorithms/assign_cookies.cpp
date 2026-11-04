#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Assign Cookies (Greedy Child Satisfaction)
// Purpose: Maximizes the number of children whose greed factors are satisfied by available cookie sizes.
// Time Complexity: O(N log N + M log M) time
// Space Complexity: O(1) auxiliary space beyond sort
// Preconditions: Greed factors and cookie sizes positive.

class AssignCookies {
public:
    static int find_content_children(std::vector<int>& g, std::vector<int>& s) {
        std::sort(g.begin(), g.end());
        std::sort(s.begin(), s.end());

        int child = 0, cookie = 0;
        while (child < (int)g.size() && cookie < (int)s.size()) {
            if (s[cookie] >= g[child]) {
                child++;
            }
            cookie++;
        }
        return child;
    }
};

int main() {
    std::vector<int> g = {1, 2, 3};
    std::vector<int> s = {1, 1};
    assert(AssignCookies::find_content_children(g, s) == 1);

    std::vector<int> g2 = {1, 2};
    std::vector<int> s2 = {1, 2, 3};
    assert(AssignCookies::find_content_children(g2, s2) == 2);

    std::cout << "assign_cookies tests passed successfully.\n";
    return 0;
}
