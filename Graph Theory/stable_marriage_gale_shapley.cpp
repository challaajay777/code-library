// Algorithm: Gale-Shapley Stable Marriage Algorithm
// Purpose: Finds a stable matching between two equally-sized sets of elements based on preference lists.
// Time Complexity: O(N^2)
// Space Complexity: O(N^2)
// Preconditions: N men and N women with complete strictly-ordered preferences.

#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

std::vector<int> stable_marriage(int n, const std::vector<std::vector<int>>& men_pref,
                                 const std::vector<std::vector<int>>& women_pref) {
    std::vector<std::vector<int>> women_rank(n, std::vector<int>(n));
    for (int w = 0; w < n; ++w) {
        for (int r = 0; r < n; ++r) {
            women_rank[w][women_pref[w][r]] = r;
        }
    }

    std::vector<int> wife(n, -1);
    std::vector<int> husband(n, -1);
    std::vector<int> next_proposal(n, 0);
    std::queue<int> free_men;
    for (int m = 0; m < n; ++m) free_men.push(m);

    while (!free_men.empty()) {
        int m = free_men.front();
        free_men.pop();
        int w = men_pref[m][next_proposal[m]++];

        if (husband[w] == -1) {
            husband[w] = m;
            wife[m] = w;
        } else {
            int current_m = husband[w];
            if (women_rank[w][m] < women_rank[w][current_m]) {
                husband[w] = m;
                wife[m] = w;
                wife[current_m] = -1;
                free_men.push(current_m);
            } else {
                free_men.push(m);
            }
        }
    }
    return wife;
}

int main() {
    int n = 2;
    std::vector<std::vector<int>> men = {{0, 1}, {0, 1}};
    std::vector<std::vector<int>> women = {{0, 1}, {0, 1}};
    auto match = stable_marriage(n, men, women);
    assert(match[0] == 0);
    assert(match[1] == 1);
    return 0;
}
