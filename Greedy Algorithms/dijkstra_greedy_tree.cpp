#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cassert>

// Algorithm: Greedy Maximum Bottleneck Path
// Purpose: Finds path between source and target that maximizes the minimum edge capacity (widest path) using modified Dijkstra in O(M log N).
// Time Complexity: O(M log N) time
// Space Complexity: O(N + M) space
// Preconditions: Edge capacities non-negative.

struct BottleneckEdge {
    int to;
    long long cap;
};

class WidestPathDijkstra {
public:
    static long long max_bottleneck(int n, const std::vector<std::vector<BottleneckEdge>>& adj, int s, int t) {
        std::vector<long long> max_cap(n, 0);
        max_cap[s] = 2e18;

        std::priority_queue<std::pair<long long, int>> pq;
        pq.push({max_cap[s], s});

        while (!pq.empty()) {
            auto [cap, u] = pq.top(); pq.pop();
            if (cap < max_cap[u]) continue;
            if (u == t) return cap;

            for (const auto& edge : adj[u]) {
                long long bottleneck = std::min(cap, edge.cap);
                if (bottleneck > max_cap[edge.to]) {
                    max_cap[edge.to] = bottleneck;
                    pq.push({bottleneck, edge.to});
                }
            }
        }
        return max_cap[t];
    }
};

int main() {
    int n = 4;
    std::vector<std::vector<BottleneckEdge>> adj(n);
    adj[0].push_back({1, 10});
    adj[1].push_back({3, 10});
    adj[0].push_back({2, 5});
    adj[2].push_back({3, 100});

    // Path 0->1->3 has bottleneck 10; Path 0->2->3 has bottleneck 5. Max bottleneck = 10
    assert(WidestPathDijkstra::max_bottleneck(n, adj, 0, 3) == 10);

    std::cout << "dijkstra_greedy_tree tests passed successfully.\n";
    return 0;
}
