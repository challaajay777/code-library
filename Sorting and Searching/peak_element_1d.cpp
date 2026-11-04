#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: 1D Peak Element Finder
// Purpose: Finds a peak element (strictly greater than its immediate neighbors) in an array in O(log N) time.
// Time Complexity: O(log N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: a[-1] = a[n] = -infinity.

class PeakElement1D {
public:
    static int find_peak_index(const std::vector<int>& a) {
        int low = 0, high = (int)a.size() - 1;

        while (low < high) {
            int mid = low + (high - low) / 2;
            if (a[mid] < a[mid + 1]) {
                low = mid + 1;
            } else {
                high = mid;
            }
        }
        return low;
    }
};

int main() {
    std::vector<int> a = {1, 2, 3, 1};
    int peak_idx = PeakElement1D::find_peak_index(a);
    assert(peak_idx == 2 && a[peak_idx] == 3);

    std::vector<int> b = {1, 2, 1, 3, 5, 6, 4};
    int p2 = PeakElement1D::find_peak_index(b);
    assert(p2 == 1 || p2 == 5);

    std::cout << "peak_element_1d tests passed successfully.\n";
    return 0;
}
