#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>
#include <cassert>

// Algorithm: Tug of War (Equal-Size Partition with Minimum Difference)
// Purpose: Partitions an array into two subsets of size floor(N/2) and ceil(N/2) minimizing the absolute sum difference.
// Time Complexity: O(2^N) with branch-and-bound pruning
// Space Complexity: O(N) auxiliary space
// Preconditions: Array length >= 2.

class TugOfWar {
private:
    static void dfs(int idx, int chosen_count, long long current_sum,
                    const std::vector<long long>& a, int required,
                    long long total_sum, long long& min_diff, std::vector<bool>& cur_sol,
                    std::vector<bool>& best_sol) {
        if (chosen_count == required) {
            long long other_sum = total_sum - current_sum;
            long long diff = std::abs(current_sum - other_sum);
            if (diff < min_diff) {
                min_diff = diff;
                best_sol = cur_sol;
            }
            return;
        }
        if (idx == (int)a.size()) return;

        // Choice 1: include a[idx]
        cur_sol[idx] = true;
        dfs(idx + 1, chosen_count + 1, current_sum + a[idx], a, required, total_sum, min_diff, cur_sol, best_sol);
        cur_sol[idx] = false;

        // Choice 2: exclude a[idx] (if remaining elements are enough)
        if ((int)a.size() - (idx + 1) >= required - chosen_count) {
            dfs(idx + 1, chosen_count, current_sum, a, required, total_sum, min_diff, cur_sol, best_sol);
        }
    }

public:
    static long long find_min_difference(const std::vector<long long>& a) {
        int n = a.size();
        long long total_sum = std::accumulate(a.begin(), a.end(), 0LL);
        long long min_diff = 2e18;

        std::vector<bool> cur_sol(n, false), best_sol(n, false);
        dfs(0, 0, 0, a, n / 2, total_sum, min_diff, cur_sol, best_sol);
        return min_diff;
    }
};

int main() {
    std::vector<long long> a = {3, 4, 5, -3, 100, 1, 89, 54, 23, 20};
    long long diff = TugOfWar::find_min_difference(a);
    assert(diff == 0); // Sets sum to 98 and 98

    std::cout << "tug_of_war_partition tests passed successfully.\n";
    return 0;
}
