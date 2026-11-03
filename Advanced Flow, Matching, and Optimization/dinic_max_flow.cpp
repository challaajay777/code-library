// Algorithm: Dinic's Maximum Flow
// Supports: Maximum network flow, min-cut partition recovery, unit networks in O(E sqrt(V))
// Indexing: 0-based vertex indices [0, n - 1]
// Complexity: O(V^2 * E) general, O(E * sqrt(V)) unit capacity, O(V + E) memory
// Preconditions: Capacities >= 0; source != sink

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

struct Dinic {
    struct Edge {
        int to;
        long long cap;
        long long flow = 0;
        int rev;
    };

    static constexpr long long INF_FLOW = 1e18;

    int n;
    vector<vector<Edge>> adj;
    vector<int> level, ptr;

    explicit Dinic(int n) : n(n), adj(n), level(n), ptr(n) {}

    void add_edge(int from, int to, long long cap) {
        assert(0 <= from && from < n && 0 <= to && to < n);
        assert(cap >= 0);
        int a_id = (int)adj[from].size();
        int b_id = (int)adj[to].size();
        adj[from].push_back({to, cap, 0, b_id});
        adj[to].push_back({from, 0, 0, a_id}); // Reverse residual edge
    }

private:
    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        level[s] = 0;
        queue<int> q;
        q.push(s);

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (const auto& e : adj[u]) {
                if (e.cap - e.flow > 0 && level[e.to] == -1) {
                    level[e.to] = level[u] + 1;
                    q.push(e.to);
                }
            }
        }
        return level[t] != -1;
    }

    long long dfs(int u, int t, long long pushed) {
        if (pushed == 0 || u == t) return pushed;
        for (int& cid = ptr[u]; cid < (int)adj[u].size(); ++cid) {
            auto& e = adj[u][cid];
            int tr = e.to;
            if (level[u] + 1 != level[tr] || e.cap - e.flow == 0) continue;
            long long push = dfs(tr, t, min(pushed, e.cap - e.flow));
            if (push == 0) continue;
            e.flow += push;
            adj[tr][e.rev].flow -= push;
            return push;
        }
        return 0;
    }

public:
    long long max_flow(int s, int t) {
        assert(0 <= s && s < n && 0 <= t && t < n && s != t);
        long long flow = 0;
        while (bfs(s, t)) {
            fill(ptr.begin(), ptr.end(), 0);
            while (long long pushed = dfs(s, t, INF_FLOW)) {
                flow += pushed;
            }
        }
        return flow;
    }

    // Returns vertices on the source side of the minimum cut (level[u] != -1)
    vector<bool> min_cut_source_side() const {
        vector<bool> in_cut(n, false);
        for (int i = 0; i < n; ++i) {
            if (level[i] != -1) in_cut[i] = true;
        }
        return in_cut;
    }
};
