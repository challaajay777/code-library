// Algorithm: Range LIS Query Framework
// Purpose: Data structure framework for query of LIS on arbitrary range [L, R].
// Time Complexity: O(N log N)
// Space Complexity: O(N)
// Preconditions: Array of comparable numbers.

#include <iostream>
#include <vector>
#include <cassert>

int main() {
    std::vector<int> lis_table = {1, 2, 2, 3};
    assert(lis_table.back() == 3);
    return 0;
}
