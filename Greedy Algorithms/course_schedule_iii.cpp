#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cassert>

// Algorithm: Course Schedule III (Max Courses via Max-Heap)
// Purpose: Finds the maximum number of courses that can be completed given [duration, lastDay] for each course in O(N log N).
// Time Complexity: O(N log N) time
// Space Complexity: O(N) space for max-heap
// Preconditions: Course durations and deadlines positive.

class CourseScheduleIII {
public:
    static int schedule_course(std::vector<std::vector<int>>& courses) {
        std::sort(courses.begin(), courses.end(), [](const std::vector<int>& a, const std::vector<int>& b) {
            return a[1] < b[1];
        });

        std::priority_queue<int> max_heap;
        int current_time = 0;

        for (const auto& c : courses) {
            int duration = c[0];
            int last_day = c[1];

            if (current_time + duration <= last_day) {
                current_time += duration;
                max_heap.push(duration);
            } else if (!max_heap.empty() && max_heap.top() > duration) {
                current_time -= max_heap.top();
                max_heap.pop();
                current_time += duration;
                max_heap.push(duration);
            }
        }
        return max_heap.size();
    }
};

int main() {
    std::vector<std::vector<int>> c = {{100, 200}, {200, 1300}, {1000, 1250}, {2000, 3200}};
    assert(CourseScheduleIII::schedule_course(c) == 3);

    std::cout << "course_schedule_iii tests passed successfully.\n";
    return 0;
}
