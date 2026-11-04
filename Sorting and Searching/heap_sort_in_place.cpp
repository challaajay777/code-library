#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: In-Place Heap Sort
// Purpose: Sorts an array in-place using a binary max-heap with zero dynamic memory allocation.
// Time Complexity: O(N log N) guaranteed time
// Space Complexity: O(1) auxiliary space
// Preconditions: Comparable array elements.

class HeapSort {
private:
    static void sift_down(std::vector<int>& a, int n, int i) {
        while (2 * i + 1 < n) {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int largest = i;

            if (left < n && a[left] > a[largest]) largest = left;
            if (right < n && a[right] > a[largest]) largest = right;

            if (largest == i) break;
            std::swap(a[i], a[largest]);
            i = largest;
        }
    }

public:
    static void sort(std::vector<int>& a) {
        int n = a.size();
        if (n <= 1) return;

        // Build max-heap bottom-up in O(N)
        for (int i = n / 2 - 1; i >= 0; --i) {
            sift_down(a, n, i);
        }

        // Extract elements from heap one by one
        for (int i = n - 1; i > 0; --i) {
            std::swap(a[0], a[i]);
            sift_down(a, i, 0);
        }
    }
};

int main() {
    std::vector<int> a = {12, 11, 13, 5, 6, 7};
    HeapSort::sort(a);
    std::vector<int> expected = {5, 6, 7, 11, 12, 13};
    assert(a == expected);

    std::cout << "heap_sort_in_place tests passed successfully.\n";
    return 0;
}
