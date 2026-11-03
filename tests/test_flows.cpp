// Test suite for Advanced Flow, Matching, and Optimization
#include <bits/stdc++.h>
#include <cassert>
#include "Advanced Flow, Matching, and Optimization/dinic_max_flow.cpp"
#include "Advanced Flow, Matching, and Optimization/edmonds_karp_max_flow.cpp"
#include "Advanced Flow, Matching, and Optimization/hopcroft_karp_bipartite_matching.cpp"
#include "Advanced Flow, Matching, and Optimization/min_cost_max_flow.cpp"

using namespace std;

void test_max_flow_and_cuts() {
    // Graph:
    // 0 -> 1 (cap 10)
    // 0 -> 2 (cap 10)
    // 1 -> 2 (cap 2)
    // 1 -> 3 (cap 4)
    // 1 -> 4 (cap 8)
    // 2 -> 4 (cap 9)
    // 3 -> 5 (cap 10)
    // 4 -> 5 (cap 10)
    Dinic dinic(6);
    dinic.add_edge(0, 1, 10);
    dinic.add_edge(0, 2, 10);
    dinic.add_edge(1, 2, 2);
    dinic.add_edge(1, 3, 4);
    dinic.add_edge(1, 4, 8);
    dinic.add_edge(2, 4, 9);
    dinic.add_edge(3, 5, 10);
    dinic.add_edge(4, 5, 10);

    long long max_f = dinic.max_flow(0, 5);
    assert(max_f == 14);

    // Min-cut source side should contain source 0
    auto cut = dinic.min_cut_source_side();
    assert(cut[0] == true);
    assert(cut[5] == false);

    // Differential check against Edmonds-Karp
    EdmondsKarp ek(6);
    ek.add_edge(0, 1, 10);
    ek.add_edge(0, 2, 10);
    ek.add_edge(1, 2, 2);
    ek.add_edge(1, 3, 4);
    ek.add_edge(1, 4, 8);
    ek.add_edge(2, 4, 9);
    ek.add_edge(3, 5, 10);
    ek.add_edge(4, 5, 10);
    assert(ek.max_flow(0, 5) == 14);
}

void test_hopcroft_karp() {
    // Left: 0, 1, 2, 3
    // Right: 0, 1, 2, 3
    // 0 - 0, 0 - 1
    // 1 - 1, 1 - 2
    // 2 - 2
    // 3 - 2
    HopcroftKarp hk(4, 4);
    hk.add_edge(0, 0);
    hk.add_edge(0, 1);
    hk.add_edge(1, 1);
    hk.add_edge(1, 2);
    hk.add_edge(2, 2);
    hk.add_edge(3, 2);

    int matching = hk.max_matching();
    assert(matching == 3);
    auto pairs = hk.get_matches();
    assert((int)pairs.size() == 3);
}

void test_mcmf() {
    // 0 -> 1 (cap 2, cost 4)
    // 0 -> 2 (cap 2, cost 1)
    // 2 -> 1 (cap 1, cost 2)
    // 1 -> 3 (cap 2, cost 1)
    // 2 -> 3 (cap 1, cost 5)
    MinCostMaxFlow mcmf(4);
    mcmf.add_edge(0, 1, 2, 4);
    mcmf.add_edge(0, 2, 2, 1);
    mcmf.add_edge(2, 1, 1, 2);
    mcmf.add_edge(1, 3, 2, 1);
    mcmf.add_edge(2, 3, 1, 5);

    auto [flow, cost] = mcmf.solve(0, 3);
    // Flow paths:
    // 0 -> 2 -> 1 -> 3: 1 unit, cost 1 + 2 + 1 = 4
    // 0 -> 1 -> 3: 1 unit, cost 4 + 1 = 5
    // 0 -> 2 -> 3: 1 unit, cost 1 + 5 = 6
    // Max flow is 3, total min cost is 4 + 5 + 6 = 15
    assert(flow == 3);
    assert(cost == 15);
}

int main() {
    cout << "[TEST] Running test_flows suite...\n";
    test_max_flow_and_cuts();
    test_hopcroft_karp();
    test_mcmf();
    cout << "[TEST] All 3 test sets in test_flows passed!\n";
    return 0;
}
