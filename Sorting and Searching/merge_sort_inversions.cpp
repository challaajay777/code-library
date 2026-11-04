#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Merge Sort with Inversion Counting
// Purpose: Counts total pairs (i, j) such that i < j and a[i] > a[j] while sorting the array in O(N log N).
// Time Complexity: O(N log N) time
// Space Complexity: O(N) auxiliary space
// Preconditions: Comparable array elements.

class InversionCountingMergeSort {
private:
    static long long merge(std::vector<int>& a, std::vector<int>& temp, int left, int mid, int right) {
        int i = left;
        int j = mid + 1;
        int k = left;
        long long inv_count = 0;

        while (i <= mid && j <= right) {
            if (a[i] <= a[j]) {
                temp[k++] = a[i++];
            } else {
                temp[k++] = a[j++];
                inv_count += (mid - i + 1);
            }
        }

        while (i <= mid) temp[k++] = a[i++];
        while (j <= right) temp[k++] = a[j++];

        for (i = left; i <= right; ++i) {
            a[i] = temp[i];
        }
        return inv_count;
    }

    static long long sort_and_count(std::vector<int>& a, std::vector<int>& temp, int left, int right) {
        long long inv_count = 0;
        if (left < right) {
            int mid = left + (right - left) / 2;
            inv_count += sort_and_count(a, temp, left, mid);
            inv_count += sort_and_count(a, temp, mid + 1, right);
            inv_count += merge(a, temp, left, mid, right);
        }
        return inv_count;
    }

public:
    static long long count_inversions(std::vector<int>& a) {
        if (a.size() <= 1) return 0;
        std::vector<int> temp(a.size());
        return sort_and_count(a, temp, 0, (int)a.size() - 1);
    }
};

int main() {
    std::vector<int> a = {8, 4, 2, 1};
    // (8,4), (8,2), (8,1), (4,2), (4,1), (2,1) -> 6 inversions
    assert(InversionCountingMergeSort::count_inversions(a) == 6);

    std::vector<int> b = {1, 20, 6, 4, 5};
    // (20,6), (20,4), (20,5), (6,4), (6,5) -> 5 inversions
    assert(InversionCountingMergeSort::count_inversions(b) == 5);

    std::cout << "merge_sort_inversions tests passed successfully.\n";
    return 0;
}
