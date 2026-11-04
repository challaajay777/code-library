// Algorithm: Dinic Max Flow with Capacity Scaling
// Purpose: Computes max flow by restricting augmenting paths to residual capacity >= Delta.
// Time Complexity: O(V * E * log(MaxCap))
// Space Complexity: O(V + E)
// Preconditions: Directed flow network.

#include <iostream>
#include <vector>
#include <queue>
#include <cassert>
#include <algorithm>

struct DinicScaling {
    struct FlowEdge {
        int to, cap, flow;
    };
    int n, s, t;
    std::vector<FlowEdge> edges;
    std::vector<std::vector<int>> adj;
    std::vector<int> level, ptr;

    DinicScaling(int n, int s, int t) : n(n), s(s), t(t), adj(n), level(n), ptr(n) {}

    void add_edge(int from, int to, int cap) {
        adj[from].push_back(edges.size());
        edges.push_back({to, cap, 0});
        adj[to].push_back(edges.size());
        edges.push_back({from, 0, 0});
    }

    bool bfs(int delta) {
        std::fill(level.begin(), level.end(), -1);
        level[s] = 0;
        std::queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int id : adj[v]) {
                if (edges[id].cap - edges[id].flow >= delta && level[edges[id].to] == -1) {
                    level[edges[id].to] = level[v] + 1;
                    q.push(edges[id].to);
                }
            }
        }
        return level[t] != -1;
    }

    int dfs(int v, int pushed, int delta) {
        if (pushed == 0 || v == t) return pushed;
        for (int& cid = ptr[v]; cid < (int)adj[v].size(); ++cid) {
            int id = adj[v][cid];
            int trg = edges[id].to;
            if (level[v] + 1 != level[trg] || edges[id].cap - edges[id].flow < delta) continue;
            int tr = dfs(trg, std::min(pushed, edges[id].cap - edges[id].flow), delta);
            if (tr == 0) continue;
            edges[id].flow += tr;
            edges[id ^ 1].flow -= tr;
            return tr;
        }
        return 0;
    }

    int max_flow(int max_cap = 1 << 30) {
        int flow = 0;
        for (int delta = max_cap; delta > 0; delta >>= 1) {
            while (bfs(delta)) {
                std::fill(ptr.begin(), ptr.end(), 0);
                while (int pushed = dfs(s, 1e9, delta)) flow += pushed;
            }
        }
        return flow;
    }
};

int main() {
    DinicScaling ds(4, 0, 3);
    ds.add_edge(0, 1, 100);
    ds.add_edge(0, 2, 100);
    ds.add_edge(1, 3, 100);
    ds.add_edge(2, 3, 100);

    assert(ds.max_flow(128) == 200);
    return 0;
}
