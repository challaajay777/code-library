#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: First and Last Position in Sorted Array
// Purpose: Finds the first and last occurrence indices of a target in a sorted array in O(log N) time.
// Time Complexity: O(log N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Sorted array in non-decreasing order.

class FirstLastPosition {
private:
    static int find_bound(const std::vector<int>& a, int target, bool is_first) {
        int low = 0, high = (int)a.size() - 1;
        int ans = -1;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (a[mid] == target) {
                ans = mid;
                if (is_first) {
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            } else if (a[mid] < target) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return ans;
    }

public:
    static std::pair<int, int> search_range(const std::vector<int>& a, int target) {
        int first = find_bound(a, target, true);
        if (first == -1) return {-1, -1};
        int last = find_bound(a, target, false);
        return {first, last};
    }
};

int main() {
    std::vector<int> a = {5, 7, 7, 8, 8, 10};
    auto [f, l] = FirstLastPosition::search_range(a, 8);
    assert(f == 3 && l == 4);

    auto [f2, l2] = FirstLastPosition::search_range(a, 6);
    assert(f2 == -1 && l2 == -1);

    std::cout << "find_first_and_last_position tests passed successfully.\n";
    return 0;
}
