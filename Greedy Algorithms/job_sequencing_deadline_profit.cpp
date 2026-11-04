#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cassert>

// Algorithm: Job Sequencing with Deadlines and Profits (DSU)
// Purpose: Schedules unit-time jobs to maximize total profit within deadlines in O(N log N) using Disjoint Set Union.
// Time Complexity: O(N log N + N * alpha(max_deadline)) time
// Space Complexity: O(max_deadline) space for DSU
// Preconditions: Deadlines >= 1; profits >= 0.

struct Job {
    int id;
    int deadline;
    int profit;
};

class JobSequencingDSU {
private:
    struct DSU {
        std::vector<int> parent;
        explicit DSU(int n) : parent(n + 1) {
            std::iota(parent.begin(), parent.end(), 0);
        }
        int find(int i) {
            return parent[i] == i ? i : (parent[i] = find(parent[i]));
        }
        void unite(int u, int v) {
            parent[u] = v;
        }
    };

public:
    static std::pair<int, int> schedule(std::vector<Job>& jobs) {
        std::sort(jobs.begin(), jobs.end(), [](const Job& a, const Job& b) {
            return a.profit > b.profit;
        });

        int max_deadline = 0;
        for (const auto& j : jobs) max_deadline = std::max(max_deadline, j.deadline);

        DSU dsu(max_deadline);
        int job_count = 0;
        int total_profit = 0;

        for (const auto& j : jobs) {
            int available_slot = dsu.find(j.deadline);
            if (available_slot > 0) {
                job_count++;
                total_profit += j.profit;
                dsu.unite(available_slot, dsu.find(available_slot - 1));
            }
        }
        return {job_count, total_profit};
    }
};

int main() {
    std::vector<Job> jobs = {{1, 4, 20}, {2, 1, 10}, {3, 1, 40}, {4, 1, 30}};
    auto [cnt, prof] = JobSequencingDSU::schedule(jobs);
    assert(cnt == 2 && prof == 60); // Job 3 (profit 40) + Job 1 (profit 20)

    std::cout << "job_sequencing_deadline_profit tests passed successfully.\n";
    return 0;
}
