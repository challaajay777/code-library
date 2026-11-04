#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Task Scheduler with Cooldown
// Purpose: Computes the minimum total CPU intervals required to complete all tasks given a mandatory cooldown period N.
// Time Complexity: O(Tasks) time
// Space Complexity: O(26) space
// Preconditions: Tasks represented as uppercase characters; cooldown N >= 0.

class TaskScheduler {
public:
    static int least_interval(const std::vector<char>& tasks, int n) {
        std::vector<int> counts(26, 0);
        for (char c : tasks) counts[c - 'A']++;

        int max_freq = *std::max_element(counts.begin(), counts.end());
        int max_count = 0;
        for (int f : counts) {
            if (f == max_freq) max_count++;
        }

        int empty_slots = (max_freq - 1) * (n - (max_count - 1));
        int available_tasks = tasks.size() - max_freq * max_count;
        int idles = std::max(0, empty_slots - available_tasks);

        return tasks.size() + idles;
    }
};

int main() {
    std::vector<char> tasks = {'A', 'A', 'A', 'B', 'B', 'B'};
    assert(TaskScheduler::least_interval(tasks, 2) == 8); // A -> B -> idle -> A -> B -> idle -> A -> B

    assert(TaskScheduler::least_interval(tasks, 0) == 6);

    std::cout << "task_scheduler_cooldown tests passed successfully.\n";
    return 0;
}
