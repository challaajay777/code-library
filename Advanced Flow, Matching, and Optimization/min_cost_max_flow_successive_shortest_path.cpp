// Algorithm: Min-Cost Max-Flow via Successive Shortest Paths
// Purpose: Computes maximum flow at minimum cost using SPFA augmenting shortest paths.
// Time Complexity: O(F * V * E)
// Space Complexity: O(V + E)
// Preconditions: Directed flow network without negative cost cycles.

#include <iostream>
#include <vector>
#include <queue>
#include <cassert>
#include <algorithm>

struct MCMFSPFA {
    struct Edge {
        int to, cap, flow, cost, rev;
    };
    int n, s, t;
    std::vector<std::vector<Edge>> adj;

    MCMFSPFA(int n, int s, int t) : n(n), s(s), t(t), adj(n) {}

    void add_edge(int from, int to, int cap, int cost) {
        adj[from].push_back({to, cap, 0, cost, (int)adj[to].size()});
        adj[to].push_back({from, 0, 0, -cost, (int)adj[from].size() - 1});
    }

    std::pair<int, int> solve() {
        int flow = 0, cost = 0;
        const int INF = 1e9;

        while (true) {
            std::vector<int> dist(n, INF), parent_edge(n, -1), parent_node(n, -1);
            std::vector<bool> in_queue(n, false);
            std::queue<int> q;

            dist[s] = 0;
            q.push(s);
            in_queue[s] = true;

            while (!q.empty()) {
                int u = q.front();
                q.pop();
                in_queue[u] = false;

                for (size_t i = 0; i < adj[u].size(); ++i) {
                    const auto& e = adj[u][i];
                    if (e.cap - e.flow > 0 && dist[u] + e.cost < dist[e.to]) {
                        dist[e.to] = dist[u] + e.cost;
                        parent_node[e.to] = u;
                        parent_edge[e.to] = i;
                        if (!in_queue[e.to]) {
                            q.push(e.to);
                            in_queue[e.to] = true;
                        }
                    }
                }
            }

            if (dist[t] == INF) break;

            int push = INF;
            for (int cur = t; cur != s; cur = parent_node[cur]) {
                int p = parent_node[cur], e_idx = parent_edge[cur];
                push = std::min(push, adj[p][e_idx].cap - adj[p][e_idx].flow);
            }

            for (int cur = t; cur != s; cur = parent_node[cur]) {
                int p = parent_node[cur], e_idx = parent_edge[cur];
                adj[p][e_idx].flow += push;
                adj[cur][adj[p][e_idx].rev].flow -= push;
                cost += push * adj[p][e_idx].cost;
            }
            flow += push;
        }
        return {flow, cost};
    }
};

int main() {
    MCMFSPFA mcmf(4, 0, 3);
    mcmf.add_edge(0, 1, 2, 1);
    mcmf.add_edge(0, 2, 1, 2);
    mcmf.add_edge(1, 2, 1, 1);
    mcmf.add_edge(1, 3, 1, 3);
    mcmf.add_edge(2, 3, 2, 1);

    auto [f, c] = mcmf.solve();
    assert(f == 3);
    assert(c == 8);
    return 0;
}
