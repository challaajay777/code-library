// Algorithm: Centroid Decomposition Distance-K Pair Count
// Purpose: Counts number of node pairs with path distance exactly K using centroid divide and conquer.
// Time Complexity: O(N log N)
// Space Complexity: O(N)
// Preconditions: Connected unweighted tree.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

struct CentroidDistK {
    int n, K;
    long long total_pairs;
    std::vector<std::vector<int>> adj;
    std::vector<int> sz;
    std::vector<bool> removed;

    CentroidDistK(int n, int k, const std::vector<std::vector<int>>& adj)
        : n(n), K(k), total_pairs(0), adj(adj), sz(n, 0), removed(n, false) {
        decompose(0);
    }

    void get_sz(int u, int p) {
        sz[u] = 1;
        for (int v : adj[u]) if (v != p && !removed[v]) { get_sz(v, u); sz[u] += sz[v]; }
    }

    int get_centroid(int u, int p, int total) {
        for (int v : adj[u]) if (v != p && !removed[v] && sz[v] > total / 2) return get_centroid(v, u, total);
        return u;
    }

    void get_dists(int u, int p, int d, std::vector<int>& dists) {
        if (d > K) return;
        dists.push_back(d);
        for (int v : adj[u]) if (v != p && !removed[v]) get_dists(v, u, d + 1, dists);
    }

    void decompose(int entry) {
        get_sz(entry, -1);
        int c = get_centroid(entry, -1, sz[entry]);
        removed[c] = true;

        std::vector<int> count(K + 1, 0);
        count[0] = 1;

        for (int v : adj[c]) {
            if (!removed[v]) {
                std::vector<int> cur_dists;
                get_dists(v, c, 1, cur_dists);
                for (int d : cur_dists) {
                    if (K >= d) total_pairs += count[K - d];
                }
                for (int d : cur_dists) {
                    if (d <= K) count[d]++;
                }
            }
        }

        for (int v : adj[c]) if (!removed[v]) decompose(v);
    }
};

int main() {
    int n = 5;
    std::vector<std::vector<int>> adj(n);
    adj[0] = {1}; adj[1] = {0, 2}; adj[2] = {1, 3}; adj[3] = {2, 4}; adj[4] = {3};

    CentroidDistK cdk(n, 2, adj);
    // Path length 2 pairs: (0,2), (1,3), (2,4) -> 3 pairs
    assert(cdk.total_pairs == 3);
    return 0;
}
