#include <iostream>
#include <vector>
#include <list>
#include <cassert>

// Algorithm: Strand Sort
// Purpose: Sorts a linked list or array by repeatedly pulling sorted sublists (strands) and merging them.
// Time Complexity: O(N log N) best case, O(N^2) worst case
// Space Complexity: O(N) auxiliary space
// Preconditions: Comparable elements.

class StrandSort {
public:
    static void sort(std::list<int>& ip) {
        std::list<int> op;
        std::list<int> sublist;

        while (!ip.empty()) {
            sublist.push_back(ip.front());
            ip.pop_front();

            for (auto it = ip.begin(); it != ip.end();) {
                if (*it >= sublist.back()) {
                    sublist.push_back(*it);
                    it = ip.erase(it);
                } else {
                    ++it;
                }
            }
            op.merge(sublist);
        }
        ip = std::move(op);
    }
};

int main() {
    std::list<int> a = {10, 5, 30, 40, 2, 4, 9};
    StrandSort::sort(a);
    std::vector<int> res(a.begin(), a.end());
    std::vector<int> expected = {2, 4, 5, 9, 10, 30, 40};
    assert(res == expected);

    std::cout << "strand_sort tests passed successfully.\n";
    return 0;
}
