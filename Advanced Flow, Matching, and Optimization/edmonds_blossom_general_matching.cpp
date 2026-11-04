// Algorithm: Edmonds Blossom Maximum Matching on General Graphs
// Purpose: Finds maximum cardinality matching on arbitrary general graphs by contracting odd-length alternating cycles.
// Time Complexity: O(V^3)
// Space Complexity: O(V^2)
// Preconditions: General undirected graph without multi-edges.

#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

class Blossom {
    int n;
    std::vector<std::vector<int>> adj;
    std::vector<int> match, p, base;
    std::vector<bool> used, in_blossom;

    int lca(int a, int b) {
        std::vector<bool> used_lca(n, false);
        while (true) {
            a = base[a];
            used_lca[a] = true;
            if (match[a] == -1) break;
            a = p[match[a]];
        }
        while (true) {
            b = base[b];
            if (used_lca[b]) return b;
            b = p[match[b]];
        }
    }

    void mark_blossom(int l, int u, std::queue<int>& q) {
        while (base[u] != l) {
            int v = match[u];
            in_blossom[base[u]] = in_blossom[base[v]] = true;
            u = p[v];
            if (base[u] != l) p[u] = v;
        }
    }

    void blossom_contraction(int s, int u, int v, std::queue<int>& q) {
        int l = lca(u, v);
        std::fill(in_blossom.begin(), in_blossom.end(), false);
        mark_blossom(l, u, q);
        mark_blossom(l, v, q);
        if (base[u] != l) p[u] = v;
        if (base[v] != l) p[v] = u;
        for (int i = 0; i < n; ++i) {
            if (in_blossom[base[i]]) {
                base[i] = l;
                if (!used[i]) {
                    used[i] = true;
                    q.push(i);
                }
            }
        }
    }

    bool find_path(int s) {
        std::fill(used.begin(), used.end(), false);
        std::fill(p.begin(), p.end(), -1);
        for (int i = 0; i < n; ++i) base[i] = i;

        std::queue<int> q;
        q.push(s);
        used[s] = true;

        while (!q.empty()) {
            int v = q.front();
            q.pop();

            for (int to : adj[v]) {
                if (base[v] == base[to] || match[v] == to) continue;
                if (to == s || (match[to] != -1 && p[match[to]] != -1)) {
                    blossom_contraction(s, v, to, q);
                } else if (p[to] == -1) {
                    p[to] = v;
                    if (match[to] == -1) {
                        for (int cur = to, next_cur; cur != -1; cur = next_cur) {
                            int pv = p[cur];
                            next_cur = match[pv];
                            match[cur] = pv;
                            match[pv] = cur;
                        }
                        return true;
                    }
                    to = match[to];
                    used[to] = true;
                    q.push(to);
                }
            }
        }
        return false;
    }

public:
    Blossom(int n) : n(n), adj(n), match(n, -1), p(n), base(n), used(n), in_blossom(n) {}

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int max_matching() {
        int res = 0;
        for (int i = 0; i < n; ++i) {
            if (match[i] == -1 && find_path(i)) res++;
        }
        return res;
    }
};

int main() {
    Blossom b(4);
    b.add_edge(0, 1);
    b.add_edge(1, 2);
    b.add_edge(2, 0); // triangle
    b.add_edge(2, 3);

    // Max matching is 2 (e.g., 0-1 and 2-3)
    assert(b.max_matching() == 2);
    return 0;
}
