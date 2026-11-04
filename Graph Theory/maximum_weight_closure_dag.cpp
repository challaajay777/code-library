// Algorithm: Maximum Weight Closure in DAG
// Purpose: Finds a closed subset of DAG vertices with maximum total weight via min-cut reduction.
// Time Complexity: O(V^2 * E)
// Space Complexity: O(V + E)
// Preconditions: Directed Acyclic Graph with integer vertex weights.

#include <iostream>
#include <vector>
#include <queue>
#include <cassert>
#include <algorithm>

struct DinicClosure {
    struct FlowEdge {
        int to, cap, flow;
    };
    int n, s, t;
    std::vector<FlowEdge> edges;
    std::vector<std::vector<int>> adj;
    std::vector<int> level, ptr;

    DinicClosure(int n, int s, int t) : n(n), s(s), t(t), adj(n), level(n), ptr(n) {}

    void add_edge(int from, int to, int cap) {
        adj[from].push_back(edges.size());
        edges.push_back({to, cap, 0});
        adj[to].push_back(edges.size());
        edges.push_back({from, 0, 0});
    }

    bool bfs() {
        std::fill(level.begin(), level.end(), -1);
        level[s] = 0;
        std::queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int id : adj[v]) {
                if (edges[id].cap - edges[id].flow > 0 && level[edges[id].to] == -1) {
                    level[edges[id].to] = level[v] + 1;
                    q.push(edges[id].to);
                }
            }
        }
        return level[t] != -1;
    }

    int dfs(int v, int pushed) {
        if (pushed == 0 || v == t) return pushed;
        for (int& cid = ptr[v]; cid < (int)adj[v].size(); ++cid) {
            int id = adj[v][cid];
            int trg = edges[id].to;
            if (level[v] + 1 != level[trg] || edges[id].cap - edges[id].flow == 0) continue;
            int tr = dfs(trg, std::min(pushed, edges[id].cap - edges[id].flow));
            if (tr == 0) continue;
            edges[id].flow += tr;
            edges[id ^ 1].flow -= tr;
            return tr;
        }
        return 0;
    }

    int max_flow() {
        int flow = 0;
        while (bfs()) {
            std::fill(ptr.begin(), ptr.end(), 0);
            while (int pushed = dfs(s, 1e9)) flow += pushed;
        }
        return flow;
    }
};

long long max_weight_closure(int n, const std::vector<int>& weights, const std::vector<std::pair<int, int>>& reqs) {
    int src = n, snk = n + 1;
    DinicClosure dinic(n + 2, src, snk);
    const int INF = 1e8;
    long long pos_sum = 0;

    for (int i = 0; i < n; ++i) {
        if (weights[i] > 0) {
            dinic.add_edge(src, i, weights[i]);
            pos_sum += weights[i];
        } else if (weights[i] < 0) {
            dinic.add_edge(i, snk, -weights[i]);
        }
    }

    for (auto [u, v] : reqs) {
        dinic.add_edge(u, v, INF);
    }
    return pos_sum - dinic.max_flow();
}

int main() {
    std::vector<int> weights = {10, -5, 20};
    // 0 requires 1, 2 requires 1
    std::vector<std::pair<int, int>> reqs = {{0, 1}, {2, 1}};
    // Choosing {0, 1, 2}: weight 10 - 5 + 20 = 25
    assert(max_weight_closure(3, weights, reqs) == 25);
    return 0;
}
