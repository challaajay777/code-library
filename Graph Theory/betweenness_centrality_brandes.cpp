// Algorithm: Betweenness Centrality (Brandes Algorithm)
// Purpose: Computes betweenness centrality for all vertices by counting shortest paths in O(V * E).
// Time Complexity: O(V * E)
// Space Complexity: O(V + E)
// Preconditions: Connected unweighted graph.

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <cassert>

std::vector<double> betweenness_centrality(int n, const std::vector<std::vector<int>>& adj) {
    std::vector<double> cb(n, 0.0);

    for (int s = 0; s < n; ++s) {
        std::stack<int> st;
        std::vector<std::vector<int>> p(n);
        std::vector<int> sigma(n, 0);
        std::vector<int> d(n, -1);
        std::queue<int> q;

        sigma[s] = 1;
        d[s] = 0;
        q.push(s);

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            st.push(v);

            for (int w : adj[v]) {
                if (d[w] < 0) {
                    q.push(w);
                    d[w] = d[v] + 1;
                }
                if (d[w] == d[v] + 1) {
                    sigma[w] += sigma[v];
                    p[w].push_back(v);
                }
            }
        }

        std::vector<double> delta(n, 0.0);
        while (!st.empty()) {
            int w = st.top();
            st.pop();
            for (int v : p[w]) {
                delta[v] += (double)sigma[v] / sigma[w] * (1.0 + delta[w]);
            }
            if (w != s) cb[w] += delta[w];
        }
    }
    return cb;
}

int main() {
    int n = 3;
    std::vector<std::vector<int>> adj(n);
    adj[0] = {1}; adj[1] = {0, 2}; adj[2] = {1}; // Path 0-1-2
    auto cb = betweenness_centrality(n, adj);
    assert(cb[1] > cb[0] && cb[1] > cb[2]);
    return 0;
}
