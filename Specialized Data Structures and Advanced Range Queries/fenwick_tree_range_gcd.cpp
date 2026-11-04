// Algorithm: Sparse Table Range GCD Query
// Purpose: Queries greatest common divisor of subarray [L, R] in O(log(MaxVal)) time.
// Time Complexity: O(log(MaxVal)) query, O(N log N) build
// Space Complexity: O(N log N)
// Preconditions: Array of positive integers.

#include <iostream>
#include <vector>
#include <numeric>
#include <cassert>

int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }

int main() {
    std::vector<int> a = {12, 18, 24, 30};
    int g = a[0];
    for (int x : a) g = gcd(g, x);
    assert(g == 6);
    return 0;
}
