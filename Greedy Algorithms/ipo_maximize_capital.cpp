#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cassert>

// Algorithm: IPO (Maximize Capital with K Projects)
// Purpose: Maximizes capital after selecting up to K distinct investment projects using min-heap for capital and max-heap for profit.
// Time Complexity: O(N log N + K log N) time
// Space Complexity: O(N) space
// Preconditions: Profits and capital requirements non-negative.

class IPOCapitalMaximizer {
public:
    static int find_maximized_capital(int k, int w, const std::vector<int>& profits, const std::vector<int>& capital) {
        int n = profits.size();
        std::vector<std::pair<int, int>> projects(n);
        for (int i = 0; i < n; ++i) {
            projects[i] = {capital[i], profits[i]};
        }
        std::sort(projects.begin(), projects.end());

        std::priority_queue<int> max_profits;
        int idx = 0;

        for (int step = 0; step < k; ++step) {
            while (idx < n && projects[idx].first <= w) {
                max_profits.push(projects[idx].second);
                idx++;
            }
            if (max_profits.empty()) break;
            w += max_profits.top();
            max_profits.pop();
        }
        return w;
    }
};

int main() {
    std::vector<int> prof = {1, 2, 3};
    std::vector<int> cap = {0, 1, 1};
    assert(IPOCapitalMaximizer::find_maximized_capital(2, 0, prof, cap) == 4);

    std::cout << "ipo_maximize_capital tests passed successfully.\n";
    return 0;
}
