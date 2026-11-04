#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Activity Selection (Interval Scheduling)
// Purpose: Selects maximum number of mutually non-overlapping activities by sorting by finish time in O(N log N).
// Time Complexity: O(N log N) time
// Space Complexity: O(1) auxiliary space beyond sort
// Preconditions: Start and finish times valid (start <= finish).

struct Activity {
    int start;
    int finish;
    bool operator<(const Activity& other) const {
        return finish < other.finish;
    }
};

class ActivitySelection {
public:
    static int max_activities(std::vector<Activity>& acts) {
        if (acts.empty()) return 0;
        std::sort(acts.begin(), acts.end());
        int count = 1;
        int last_finish = acts[0].finish;

        for (size_t i = 1; i < acts.size(); ++i) {
            if (acts[i].start >= last_finish) {
                count++;
                last_finish = acts[i].finish;
            }
        }
        return count;
    }
};

int main() {
    std::vector<Activity> acts = {{1, 4}, {3, 5}, {0, 6}, {5, 7}, {3, 9}, {5, 9}, {6, 10}, {8, 11}, {8, 12}, {2, 14}, {12, 16}};
    assert(ActivitySelection::max_activities(acts) == 4);

    std::cout << "activity_selection tests passed successfully.\n";
    return 0;
}
