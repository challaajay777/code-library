// Algorithm: Minimum-Cost Maximum-Flow (MCMF - Successive Shortest Path)
// Supports: Maximum flow with minimum total edge cost using SPFA augmenting paths
// Indexing: 0-based vertex indices [0, n - 1]
// Complexity: O(F * V * E) where F is total flow, O(V + E) memory
// Preconditions: No negative cost cycles; capacities >= 0

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

struct MinCostMaxFlow {
    struct Edge {
        int to;
        long long cap;
        long long flow = 0;
        long long cost;
        int rev;
    };

    static constexpr long long INF_FLOW = 1e18;
    static constexpr long long INF_COST = 1e18;

    int n;
    vector<vector<Edge>> adj;

    explicit MinCostMaxFlow(int n) : n(n), adj(n) {}

    void add_edge(int from, int to, long long cap, long long cost) {
        assert(0 <= from && from < n && 0 <= to && to < n);
        assert(cap >= 0);
        int a_id = (int)adj[from].size();
        int b_id = (int)adj[to].size();
        adj[from].push_back({to, cap, 0, cost, b_id});
        adj[to].push_back({from, 0, 0, -cost, a_id});
    }

    // Returns {total_flow, total_min_cost}
    pair<long long, long long> solve(int s, int t) {
        assert(0 <= s && s < n && 0 <= t && t < n && s != t);
        long long flow = 0, cost = 0;
        vector<long long> dist(n);
        vector<int> parent_node(n), parent_edge(n);
        vector<bool> in_queue(n);

        while (true) {
            fill(dist.begin(), dist.end(), INF_COST);
            fill(parent_node.begin(), parent_node.end(), -1);
            fill(in_queue.begin(), in_queue.end(), false);

            deque<int> dq;
            dist[s] = 0;
            dq.push_back(s);
            in_queue[s] = true;

            while (!dq.empty()) {
                int u = dq.front();
                dq.pop_front();
                in_queue[u] = false;

                for (size_t i = 0; i < adj[u].size(); ++i) {
                    const auto& e = adj[u][i];
                    if (e.cap - e.flow > 0 && dist[u] + e.cost < dist[e.to]) {
                        dist[e.to] = dist[u] + e.cost;
                        parent_node[e.to] = u;
                        parent_edge[e.to] = (int)i;
                        if (!in_queue[e.to]) {
                            in_queue[e.to] = true;
                            if (!dq.empty() && dist[e.to] < dist[dq.front()]) {
                                dq.push_front(e.to);
                            } else {
                                dq.push_back(e.to);
                            }
                        }
                    }
                }
            }

            if (dist[t] == INF_COST) break; // No augmenting path

            long long push = INF_FLOW;
            for (int cur = t; cur != s; cur = parent_node[cur]) {
                int p = parent_node[cur];
                int e_idx = parent_edge[cur];
                push = min(push, adj[p][e_idx].cap - adj[p][e_idx].flow);
            }

            for (int cur = t; cur != s; cur = parent_node[cur]) {
                int p = parent_node[cur];
                int e_idx = parent_edge[cur];
                adj[p][e_idx].flow += push;
                adj[cur][adj[p][e_idx].rev].flow -= push;
                cost += push * adj[p][e_idx].cost;
            }

            flow += push;
        }

        return {flow, cost};
    }
};
