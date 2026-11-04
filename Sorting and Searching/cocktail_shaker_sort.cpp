#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Cocktail Shaker Sort
// Purpose: Bidirectional variation of bubble sort that traverses both forward and backward, resolving turtles faster.
// Time Complexity: O(N^2) worst case, O(N) best case
// Space Complexity: O(1) auxiliary space
// Preconditions: Comparable array elements.

class CocktailShakerSort {
public:
    static void sort(std::vector<int>& a) {
        bool swapped = true;
        int start = 0;
        int end = (int)a.size() - 1;

        while (swapped) {
            swapped = false;
            for (int i = start; i < end; ++i) {
                if (a[i] > a[i + 1]) {
                    std::swap(a[i], a[i + 1]);
                    swapped = true;
                }
            }
            if (!swapped) break;
            swapped = false;
            end--;

            for (int i = end - 1; i >= start; --i) {
                if (a[i] > a[i + 1]) {
                    std::swap(a[i], a[i + 1]);
                    swapped = true;
                }
            }
            start++;
        }
    }
};

int main() {
    std::vector<int> a = {5, 1, 4, 2, 8, 0, 2};
    CocktailShakerSort::sort(a);
    std::vector<int> expected = {0, 1, 2, 2, 4, 5, 8};
    assert(a == expected);

    std::cout << "cocktail_shaker_sort tests passed successfully.\n";
    return 0;
}
