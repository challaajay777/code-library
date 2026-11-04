// Algorithm: MCMF with Dijkstra and Johnson Potentials
// Purpose: Accelerates successive shortest paths using Dijkstra with reduced costs via node potentials in O(F * E log V).
// Time Complexity: O(F * E log V)
// Space Complexity: O(V + E)
// Preconditions: No negative cycles initially.

#include <iostream>
#include <vector>
#include <queue>
#include <cassert>
#include <climits>

struct MCMFPotentials {
    struct Edge {
        int to, cap, flow, cost, rev;
    };
    int n, s, t;
    std::vector<std::vector<Edge>> adj;
    std::vector<int> pot;

    MCMFPotentials(int n, int s, int t) : n(n), s(s), t(t), adj(n), pot(n, 0) {}

    void add_edge(int from, int to, int cap, int cost) {
        adj[from].push_back({to, cap, 0, cost, (int)adj[to].size()});
        adj[to].push_back({from, 0, 0, -cost, (int)adj[from].size() - 1});
    }

    std::pair<int, int> solve() {
        int flow = 0, cost = 0;
        const int INF = 1e9;

        while (true) {
            std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;
            std::vector<int> dist(n, INF), parent_node(n, -1), parent_edge(n, -1);

            dist[s] = 0;
            pq.push({0, s});

            while (!pq.empty()) {
                auto [d, u] = pq.top();
                pq.pop();
                if (d > dist[u]) continue;

                for (size_t i = 0; i < adj[u].size(); ++i) {
                    const auto& e = adj[u][i];
                    int red_cost = e.cost + pot[u] - pot[e.to];
                    if (e.cap - e.flow > 0 && dist[u] + red_cost < dist[e.to]) {
                        dist[e.to] = dist[u] + red_cost;
                        parent_node[e.to] = u;
                        parent_edge[e.to] = i;
                        pq.push({dist[e.to], e.to});
                    }
                }
            }

            if (dist[t] == INF) break;

            for (int i = 0; i < n; ++i) {
                if (dist[i] < INF) pot[i] += dist[i];
            }

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
    MCMFPotentials mcmf(3, 0, 2);
    mcmf.add_edge(0, 1, 2, 4);
    mcmf.add_edge(1, 2, 2, 2);
    mcmf.add_edge(0, 2, 1, 10);

    auto [f, c] = mcmf.solve();
    assert(f == 3);
    assert(c == 2 * 6 + 10); // 22
    return 0;
}
