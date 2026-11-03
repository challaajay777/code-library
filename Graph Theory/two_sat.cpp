// Algorithm: 2-SAT Solver
// Supports: Satisfiability check and model extraction for 2-CNF boolean formulas
// Indexing: 0-based variable indices [0, n - 1]; positive literal u, negated literal ~u
// Complexity: O(V + E) time, O(V + E) memory
// Preconditions: 0 <= u, v < n

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

struct TwoSat {
    int n; // number of boolean variables
    vector<vector<int>> adj;
    vector<int> dfn, low, comp;
    vector<bool> in_stack;
    vector<int> st;
    int timer = 0, comp_count = 0;

    explicit TwoSat(int n)
        : n(n), adj(2 * n), dfn(2 * n, -1), low(2 * n, -1), comp(2 * n, -1), in_stack(2 * n, false) {}

    // Variable mapping: literal u is 2*u if positive, 2*u + 1 if negated
    inline int lit(int var, bool is_true) {
        assert(0 <= var && var < n);
        return 2 * var + (is_true ? 0 : 1);
    }

    inline int negate_lit(int l) {
        return l ^ 1;
    }

    // Adds clause (lit_u OR lit_v)
    void add_clause(int var_u, bool val_u, int var_v, bool val_v) {
        int u = lit(var_u, val_u);
        int v = lit(var_v, val_v);
        // ~u => v
        adj[negate_lit(u)].push_back(v);
        // ~v => u
        adj[negate_lit(v)].push_back(u);
    }

private:
    void dfs(int u) {
        dfn[u] = low[u] = ++timer;
        st.push_back(u);
        in_stack[u] = true;

        for (int v : adj[u]) {
            if (dfn[v] == -1) {
                dfs(v);
                low[u] = min(low[u], low[v]);
            } else if (in_stack[v]) {
                low[u] = min(low[u], dfn[v]);
            }
        }

        if (low[u] == dfn[u]) {
            while (true) {
                int node = st.back();
                st.pop_back();
                in_stack[node] = false;
                comp[node] = comp_count;
                if (node == u) break;
            }
            comp_count++;
        }
    }

public:
    // Solves 2-SAT. Returns pair {is_satisfiable, boolean_assignment}.
    pair<bool, vector<bool>> solve() {
        fill(dfn.begin(), dfn.end(), -1);
        fill(low.begin(), low.end(), -1);
        fill(comp.begin(), comp.end(), -1);
        fill(in_stack.begin(), in_stack.end(), false);
        st.clear();
        timer = 0;
        comp_count = 0;

        for (int i = 0; i < 2 * n; ++i) {
            if (dfn[i] == -1) dfs(i);
        }

        vector<bool> assignment(n, false);
        for (int i = 0; i < n; ++i) {
            if (comp[2 * i] == comp[2 * i + 1]) {
                return {false, {}}; // Contradiction: x and ~x in same SCC
            }
            // In topological condensation order, earlier component ID means higher reachability
            assignment[i] = (comp[2 * i] < comp[2 * i + 1]);
        }
        return {true, assignment};
    }
};
