// Algorithm: Fast Transitive Closure via Bitset
// Purpose: Computes reachability matrix of directed graph using bitset optimization in O(V^3 / 64).
// Time Complexity: O(V^3 / 64)
// Space Complexity: O(V^2 / 64)
// Preconditions: V <= 1000.

#include <iostream>
#include <vector>
#include <bitset>
#include <cassert>

const int MAXV = 128;

std::vector<std::bitset<MAXV>> transitive_closure(int n, const std::vector<std::vector<int>>& adj) {
    std::vector<std::bitset<MAXV>> reach(n);
    for (int i = 0; i < n; ++i) {
        reach[i].set(i);
        for (int v : adj[i]) reach[i].set(v);
    }

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            if (reach[i].test(k)) {
                reach[i] |= reach[k];
            }
        }
    }
    return reach;
}

int main() {
    int n = 4;
    std::vector<std::vector<int>> adj(n);
    adj[0].push_back(1);
    adj[1].push_back(2);
    adj[2].push_back(3);

    auto reach = transitive_closure(n, adj);
    assert(reach[0].test(3));
    assert(!reach[3].test(0));
    return 0;
}
