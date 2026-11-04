#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <cassert>

// Algorithm: 3-Way Quick Sort (Fat Partition)
// Purpose: Partitions array into elements less than, equal to, and greater than pivot to achieve O(N) time on many duplicate keys.
// Time Complexity: O(N log N) average, O(N) when duplicate elements dominate
// Space Complexity: O(log N) auxiliary recursion space
// Preconditions: Arbitrary array elements.

class QuickSort3Way {
private:
    static void sort_helper(std::vector<int>& a, int low, int high) {
        if (low >= high) return;

        // Choose random pivot
        int p_idx = low + std::rand() % (high - low + 1);
        std::swap(a[low], a[p_idx]);
        int pivot = a[low];

        int lt = low;     // a[low..lt-1] < pivot
        int gt = high;    // a[gt+1..high] > pivot
        int i = low + 1;  // a[lt..i-1] == pivot

        while (i <= gt) {
            if (a[i] < pivot) {
                std::swap(a[lt++], a[i++]);
            } else if (a[i] > pivot) {
                std::swap(a[i], a[gt--]);
            } else {
                i++;
            }
        }

        sort_helper(a, low, lt - 1);
        sort_helper(a, gt + 1, high);
    }

public:
    static void sort(std::vector<int>& a) {
        if (!a.empty()) {
            sort_helper(a, 0, (int)a.size() - 1);
        }
    }
};

int main() {
    std::vector<int> a = {4, 2, 2, 8, 3, 3, 1};
    QuickSort3Way::sort(a);
    std::vector<int> expected = {1, 2, 2, 3, 3, 4, 8};
    assert(a == expected);

    std::cout << "quicksort_3way_dutch_flag tests passed successfully.\n";
    return 0;
}
