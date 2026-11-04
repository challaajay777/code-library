#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Dutch National Flag 3-Way Partitioning
// Purpose: Partitions an array into three segments (< pivot, == pivot, > pivot) in a single linear pass with O(1) space.
// Time Complexity: O(N) time with at most N element swaps
// Space Complexity: O(1) auxiliary space
// Preconditions: Elements comparable with < and == operators.

class DutchNationalFlag {
public:
    // Returns pair of indices [mid_start, mid_end] indicating the range of elements equal to pivot
    template <typename T>
    static std::pair<int, int> partition(std::vector<T>& a, const T& pivot) {
        int low = 0;
        int mid = 0;
        int high = (int)a.size() - 1;

        while (mid <= high) {
            if (a[mid] < pivot) {
                std::swap(a[low++], a[mid++]);
            } else if (pivot < a[mid]) {
                std::swap(a[mid], a[high--]);
            } else {
                mid++;
            }
        }
        return {low, high};
    }
};

int main() {
    std::vector<int> a = {2, 0, 2, 1, 1, 0, 1, 2, 0};
    auto [l, r] = DutchNationalFlag::partition(a, 1);

    for (int i = 0; i < l; ++i) assert(a[i] < 1);
    for (int i = l; i <= r; ++i) assert(a[i] == 1);
    for (int i = r + 1; i < (int)a.size(); ++i) assert(a[i] > 1);

    std::cout << "dutch_national_flag_partition tests passed successfully.\n";
    return 0;
}
