// Algorithm: Edmonds-Karp Maximum Flow
// Supports: Maximum flow via BFS shortest augmenting paths
// Indexing: 0-based vertex indices [0, n - 1]
// Complexity: O(V * E^2) time, O(V + E) memory
// Preconditions: Capacities >= 0; source != sink

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

struct EdmondsKarp {
    struct Edge {
        int to;
        long long cap;
        long long flow = 0;
        int rev;
    };

    static constexpr long long INF_FLOW = 1e18;

    int n;
    vector<vector<Edge>> adj;

    explicit EdmondsKarp(int n) : n(n), adj(n) {}

    void add_edge(int from, int to, long long cap) {
        assert(0 <= from && from < n && 0 <= to && to < n);
        assert(cap >= 0);
        int a_id = (int)adj[from].size();
        int b_id = (int)adj[to].size();
        adj[from].push_back({to, cap, 0, b_id});
        adj[to].push_back({from, 0, 0, a_id});
    }

    long long max_flow(int s, int t) {
        assert(0 <= s && s < n && 0 <= t && t < n && s != t);
        long long flow = 0;
        vector<pair<int, int>> parent(n); // {parent_node, edge_index}

        while (true) {
            fill(parent.begin(), parent.end(), make_pair(-1, -1));
            queue<pair<int, long long>> q;
            q.push({s, INF_FLOW});

            while (!q.empty()) {
                auto [cur, cur_flow] = q.front();
                q.pop();

                for (size_t i = 0; i < adj[cur].size(); ++i) {
                    const auto& e = adj[cur][i];
                    if (parent[e.to].first == -1 && e.to != s && e.cap - e.flow > 0) {
                        parent[e.to] = {cur, (int)i};
                        long long new_flow = min(cur_flow, e.cap - e.flow);
                        if (e.to == t) {
                            goto found_augmenting_path;
                        }
                        q.push({e.to, new_flow});
                    }
                }
            }
            break; // No more augmenting paths

        found_augmenting_path:
            long long pushed = INF_FLOW;
            for (int cur = t; cur != s; cur = parent[cur].first) {
                int p = parent[cur].first;
                int edge_idx = parent[cur].second;
                pushed = min(pushed, adj[p][edge_idx].cap - adj[p][edge_idx].flow);
            }

            for (int cur = t; cur != s; cur = parent[cur].first) {
                int p = parent[cur].first;
                int edge_idx = parent[cur].second;
                adj[p][edge_idx].flow += pushed;
                adj[cur][adj[p][edge_idx].rev].flow -= pushed;
            }

            flow += pushed;
        }

        return flow;
    }
};
