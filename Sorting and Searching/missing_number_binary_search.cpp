#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Missing Number in Sorted Arithmetic Progression
// Purpose: Finds the single missing number in a strictly increasing arithmetic progression in O(log N) time.
// Time Complexity: O(log N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Array length >= 2; exactly one missing element.

class MissingNumberAP {
public:
    static int find_missing(const std::vector<int>& arr) {
        int n = arr.size();
        assert(n >= 2);
        int diff = (arr.back() - arr.front()) / n;

        int low = 0, high = n - 1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            int expected = arr[0] + mid * diff;

            if (arr[mid] == expected) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return arr[0] + low * diff;
    }
};

int main() {
    std::vector<int> a = {2, 4, 8, 10, 12, 14};
    assert(MissingNumberAP::find_missing(a) == 6);

    std::vector<int> b = {1, 6, 11, 16, 21, 31};
    assert(MissingNumberAP::find_missing(b) == 26);

    std::cout << "missing_number_binary_search tests passed successfully.\n";
    return 0;
}
