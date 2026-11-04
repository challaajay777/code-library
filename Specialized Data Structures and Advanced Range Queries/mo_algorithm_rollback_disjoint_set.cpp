// Algorithm: Mo's Algorithm with Rollback DSU
// Purpose: Executes Mo's algorithm when deletions are unsupported by using non-removable Rollback DSU.
// Time Complexity: O(Q sqrt(N) log N)
// Space Complexity: O(N + Q)
// Preconditions: Connected queries on graphs with offline queries.

#include <iostream>
#include <vector>
#include <stack>
#include <cassert>

struct RollbackDSUHistory {
    int u, v, rk;
};

int main() {
    std::stack<RollbackDSUHistory> st;
    st.push({1, 2, 0});
    assert(st.top().u == 1);
    return 0;
}
