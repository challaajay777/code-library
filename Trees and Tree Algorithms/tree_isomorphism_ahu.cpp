// Algorithm: AHU Rooted Tree Isomorphism Algorithm
// Purpose: Encodes rooted trees into canonical string brackets to test exact tree isomorphism.
// Time Complexity: O(N log N)
// Space Complexity: O(N)
// Preconditions: Rooted tree.

#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>

std::string ahu_encode(int u, int p, const std::vector<std::vector<int>>& adj) {
    std::vector<std::string> child_codes;
    for (int v : adj[u]) {
        if (v != p) {
            child_codes.push_back(ahu_encode(v, u, adj));
        }
    }
    std::sort(child_codes.begin(), child_codes.end());

    std::string res = "(";
    for (const auto& s : child_codes) res += s;
    res += ")";
    return res;
}

int main() {
    int n = 3;
    std::vector<std::vector<int>> t1(n), t2(n);
    t1[0] = {1, 2}; t1[1] = {0}; t1[2] = {0};
    t2[0] = {2, 1}; t2[1] = {0}; t2[2] = {0};

    assert(ahu_encode(0, -1, t1) == ahu_encode(0, -1, t2));
    return 0;
}
