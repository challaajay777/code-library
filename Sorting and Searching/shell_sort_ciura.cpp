#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Shell Sort (Ciura Sequence)
// Purpose: In-place comparison sort using Ciura's empirically optimal gap sequence {1, 4, 10, 23, 57, 132, 301, 701, 1750}.
// Time Complexity: O(N^(4/3)) empirical time
// Space Complexity: O(1) auxiliary space
// Preconditions: Comparable array elements.

class ShellSortCiura {
public:
    static void sort(std::vector<int>& a) {
        int n = a.size();
        const std::vector<int> gaps = {1750, 701, 301, 132, 57, 23, 10, 4, 1};

        for (int gap : gaps) {
            if (gap >= n) continue;
            for (int i = gap; i < n; ++i) {
                int temp = a[i];
                int j = i;
                while (j >= gap && a[j - gap] > temp) {
                    a[j] = a[j - gap];
                    j -= gap;
                }
                a[j] = temp;
            }
        }
    }
};

int main() {
    std::vector<int> a = {12, 34, 54, 2, 3};
    ShellSortCiura::sort(a);
    std::vector<int> expected = {2, 3, 12, 34, 54};
    assert(a == expected);

    std::cout << "shell_sort_ciura tests passed successfully.\n";
    return 0;
}
