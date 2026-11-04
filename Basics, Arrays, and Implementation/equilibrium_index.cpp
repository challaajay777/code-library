#include <iostream>
#include <vector>
#include <numeric>
#include <cassert>

// Algorithm: Equilibrium Index Finder
// Purpose: Finds all indices in an array where the sum of lower indices equals the sum of higher indices in O(N).
// Time Complexity: O(N) time
// Space Complexity: O(1) auxiliary space beyond input
// Preconditions: 64-bit integers prevent sum overflow.

class EquilibriumIndexFinder {
public:
    static std::vector<int> find_all(const std::vector<long long>& a) {
        long long total_sum = std::accumulate(a.begin(), a.end(), 0LL);
        long long left_sum = 0;
        std::vector<int> result;

        for (int i = 0; i < (int)a.size(); ++i) {
            long long right_sum = total_sum - left_sum - a[i];
            if (left_sum == right_sum) {
                result.push_back(i);
            }
            left_sum += a[i];
        }
        return result;
    }

    static int find_first(const std::vector<long long>& a) {
        auto all = find_all(a);
        return all.empty() ? -1 : all.front();
    }
};

int main() {
    std::vector<long long> a = {-7, 1, 5, 2, -4, 3, 0};
    auto eq = EquilibriumIndexFinder::find_all(a);
    // Index 3: left = -7+1+5 = -1, right = -4+3+0 = -1
    // Index 6: left = -7+1+5+2-4+3 = 0, right = 0
    assert(eq.size() == 2);
    assert(eq[0] == 3);
    assert(eq[1] == 6);

    std::vector<long long> b = {1, 2, 3};
    assert(EquilibriumIndexFinder::find_first(b) == -1);

    std::cout << "equilibrium_index tests passed successfully.\n";
    return 0;
}
