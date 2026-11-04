// Algorithm: Fleury Eulerian Trail Construction
// Purpose: Finds an Eulerian trail by checking bridge edges with reachability count before traversing.
// Time Complexity: O(E^2)
// Space Complexity: O(V + E)
// Preconditions: Connected undirected graph where all or all-except-two vertices have even degrees.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

struct FleurySolver {
    int n;
    std::vector<std::vector<int>> adj;

    FleurySolver(int n) : n(n), adj(n) {}

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void remove_edge(int u, int v) {
        auto it1 = std::find(adj[u].begin(), adj[u].end(), v);
        if (it1 != adj[u].end()) adj[u].erase(it1);
        auto it2 = std::find(adj[v].begin(), adj[v].end(), u);
        if (it2 != adj[v].end()) adj[v].erase(it2);
    }

    int dfs_count(int u, std::vector<bool>& vis) {
        vis[u] = true;
        int count = 1;
        for (int v : adj[u]) {
            if (!vis[v]) count += dfs_count(v, vis);
        }
        return count;
    }

    bool is_valid_next(int u, int v) {
        if (adj[u].size() == 1) return true;
        std::vector<bool> vis1(n, false);
        int c1 = dfs_count(u, vis1);

        remove_edge(u, v);
        std::vector<bool> vis2(n, false);
        int c2 = dfs_count(u, vis2);
        add_edge(u, v);

        return c1 <= c2;
    }

    void get_trail(int u, std::vector<int>& trail) {
        trail.push_back(u);
        for (int i = 0; i < (int)adj[u].size(); ++i) {
            int v = adj[u][i];
            if (is_valid_next(u, v)) {
                remove_edge(u, v);
                get_trail(v, trail);
                break;
            }
        }
    }
};

int main() {
    FleurySolver fs(3);
    fs.add_edge(0, 1);
    fs.add_edge(1, 2);
    fs.add_edge(2, 0);

    std::vector<int> trail;
    fs.get_trail(0, trail);
    assert(trail.size() >= 3);
    return 0;
}
