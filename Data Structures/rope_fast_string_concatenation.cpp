// Algorithm: GNU C++ Rope Fast String Slicing
// Purpose: Demonstrates __gnu_cxx::crope for O(log N) string substring extraction, insert, and concatenation.
// Time Complexity: O(log N) per operation
// Space Complexity: O(N)
// Preconditions: GNU C++ extension <ext/rope>.

#include <iostream>
#include <ext/rope>
#include <cassert>

using namespace __gnu_cxx;

int main() {
    crope r = "Hello";
    r += " World";
    assert(r.substr(0, 5) == crope("Hello"));

    r.insert(5, ",");
    assert(r.substr(0, 6) == crope("Hello,"));
    return 0;
}
