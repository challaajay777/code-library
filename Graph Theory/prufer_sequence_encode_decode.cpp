// Algorithm: Prufer Sequence Tree Encoding and Decoding
// Purpose: Encodes a labeled tree to its unique Prufer code of length N-2 and reconstructs the tree in O(N log N).
// Time Complexity: O(N log N)
// Space Complexity: O(N)
// Preconditions: Tree of N >= 2 labeled vertices 0..N-1.

#include <iostream>
#include <vector>
#include <set>
#include <cassert>
#include <algorithm>

std::vector<int> encode_prufer(int n, const std::vector<std::vector<int>>& adj) {
    std::vector<int> deg(n);
    std::set<int> leaves;
    for (int i = 0; i < n; ++i) {
        deg[i] = adj[i].size();
        if (deg[i] == 1) leaves.insert(i);
    }

    std::vector<bool> removed(n, false);
    std::vector<int> code;

    for (int step = 0; step < n - 2; ++step) {
        int leaf = *leaves.begin();
        leaves.erase(leaves.begin());
        removed[leaf] = true;

        for (int neighbor : adj[leaf]) {
            if (!removed[neighbor]) {
                code.push_back(neighbor);
                if (--deg[neighbor] == 1) leaves.insert(neighbor);
                break;
            }
        }
    }
    return code;
}

std::vector<std::pair<int, int>> decode_prufer(int n, const std::vector<int>& code) {
    std::vector<int> deg(n, 1);
    for (int x : code) deg[x]++;

    std::set<int> leaves;
    for (int i = 0; i < n; ++i) {
        if (deg[i] == 1) leaves.insert(i);
    }

    std::vector<std::pair<int, int>> edges;
    for (int x : code) {
        int leaf = *leaves.begin();
        leaves.erase(leaves.begin());
        edges.push_back({leaf, x});
        if (--deg[x] == 1) leaves.insert(x);
    }
    int u = *leaves.begin();
    leaves.erase(leaves.begin());
    int v = *leaves.begin();
    edges.push_back({u, v});
    return edges;
}

int main() {
    int n = 4;
    std::vector<std::vector<int>> adj(n);
    adj[0] = {1}; adj[1] = {0, 2, 3}; adj[2] = {1}; adj[3] = {1};

    auto code = encode_prufer(n, adj);
    assert((int)code.size() == 2);
    auto edges = decode_prufer(n, code);
    assert((int)edges.size() == 3);
    return 0;
}
