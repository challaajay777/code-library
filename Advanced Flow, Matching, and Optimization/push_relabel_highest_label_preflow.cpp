// Algorithm: Push-Relabel with Highest-Label Pre-flow Push
// Purpose: Calculates maximum network flow in O(V^2 sqrt(E)) using highest active label discharge.
// Time Complexity: O(V^2 sqrt(E))
// Space Complexity: O(V + E)
// Preconditions: Directed graph with capacities, source and sink.

#include <iostream>
#include <vector>
#include <queue>
#include <cassert>
#include <algorithm>

struct PushRelabelHL {
    struct Edge {
        int to, flow, cap, rev;
    };
    int n, s, t;
    std::vector<std::vector<Edge>> adj;
    std::vector<long long> excess;
    std::vector<int> height, count;
    std::vector<std::vector<int>> b;
    int highest;

    PushRelabelHL(int n, int s, int t) : n(n), s(s), t(t), adj(n), excess(n, 0),
        height(n, 0), count(2 * n, 0), b(2 * n), highest(0) {}

    void add_edge(int from, int to, int cap) {
        adj[from].push_back({to, 0, cap, (int)adj[to].size()});
        adj[to].push_back({from, 0, 0, (int)adj[from].size() - 1});
    }

    void push(int u, Edge& e) {
        int tr = std::min(excess[u], (long long)e.cap - e.flow);
        if (height[u] <= height[e.to] || tr == 0) return;
        e.flow += tr;
        adj[e.to][e.rev].flow -= tr;
        excess[u] -= tr;
        excess[e.to] += tr;
        if (e.to != s && e.to != t && excess[e.to] == tr) {
            b[height[e.to]].push_back(e.to);
            highest = std::max(highest, height[e.to]);
        }
    }

    void relabel(int u) {
        int mn = 2 * n;
        for (const auto& e : adj[u]) {
            if (e.cap - e.flow > 0) mn = std::min(mn, height[e.to]);
        }
        if (count[height[u]] == 1) {
            for (int i = 0; i < n; ++i) {
                if (height[i] >= height[u] && i != s && i != t) {
                    count[height[i]]--;
                    height[i] = std::max(height[i], n + 1);
                    count[height[i]]++;
                }
            }
        } else {
            count[height[u]]--;
            height[u] = mn + 1;
            count[height[u]]++;
            highest = std::max(highest, height[u]);
            b[height[u]].push_back(u);
        }
    }

    long long max_flow() {
        height[s] = n;
        count[0] = n - 1;
        count[n] = 1;
        for (auto& e : adj[s]) {
            int tr = e.cap;
            if (tr > 0) {
                e.flow += tr;
                adj[e.to][e.rev].flow -= tr;
                excess[s] -= tr;
                excess[e.to] += tr;
                if (e.to != s && e.to != t) b[0].push_back(e.to);
            }
        }

        while (highest >= 0) {
            if (b[highest].empty()) { highest--; continue; }
            int u = b[highest].back();
            b[highest].pop_back();

            for (auto& e : adj[u]) {
                if (excess[u] == 0) break;
                push(u, e);
            }
            if (excess[u] > 0) relabel(u);
        }
        return excess[t];
    }
};

int main() {
    PushRelabelHL pr(4, 0, 3);
    pr.add_edge(0, 1, 10);
    pr.add_edge(0, 2, 10);
    pr.add_edge(1, 2, 2);
    pr.add_edge(1, 3, 4);
    pr.add_edge(2, 3, 8);

    assert(pr.max_flow() == 12);
    return 0;
}
