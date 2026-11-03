// Test suite for Graph Theory algorithms
#include <bits/stdc++.h>
#include <cassert>
#include "Graph Theory/bfs_shortest_path.cpp"
#include "Graph Theory/zero_one_bfs.cpp"
#include "Graph Theory/dijkstra.cpp"
#include "Graph Theory/bellman_ford.cpp"
#include "Graph Theory/spfa.cpp"
#include "Graph Theory/floyd_warshall.cpp"
#include "Graph Theory/kruskal_mst.cpp"
#include "Graph Theory/prim_mst.cpp"
#include "Graph Theory/topological_sort.cpp"
#include "Graph Theory/tarjan_scc.cpp"
#include "Graph Theory/kosaraju_scc.cpp"
#include "Graph Theory/two_sat.cpp"
#include "Graph Theory/bridges_and_articulation_points.cpp"
#include "Graph Theory/eulerian_path.cpp"

using namespace std;

void test_bfs_and_zero_one() {
    BFS bfs(5);
    bfs.add_edge(0, 1);
    bfs.add_edge(1, 2);
    bfs.add_edge(0, 3);
    bfs.add_edge(3, 4);
    bfs.add_edge(4, 2);
    bfs.run(0);
    assert(bfs.dist[2] == 2);
    auto p = bfs.get_path(2);
    assert((p == vector<int>{0, 1, 2}));

    ZeroOneBFS zbfs(4);
    zbfs.add_edge(0, 1, 1);
    zbfs.add_edge(1, 2, 1);
    zbfs.add_edge(0, 3, 0);
    zbfs.add_edge(3, 2, 0);
    zbfs.run(0);
    assert(zbfs.dist[2] == 0);
    assert((zbfs.get_path(2) == vector<int>{0, 3, 2}));
}

void test_shortest_paths() {
    // Dijkstra
    Dijkstra<long long> dij(4);
    dij.add_edge(0, 1, 4);
    dij.add_edge(0, 2, 1);
    dij.add_edge(2, 1, 2);
    dij.add_edge(1, 3, 1);
    dij.run(0);
    assert(dij.dist[3] == 4);
    assert((dij.get_path(3) == vector<int>{0, 2, 1, 3}));

    // Bellman-Ford
    BellmanFord bf(4);
    bf.add_edge(0, 1, 1);
    bf.add_edge(1, 2, -3);
    bf.add_edge(2, 3, 2);
    bool has_cycle = bf.run(0);
    assert(!has_cycle);
    assert(bf.dist[3] == 0);

    // Negative cycle detection
    BellmanFord bf_cycle(3);
    bf_cycle.add_edge(0, 1, 1);
    bf_cycle.add_edge(1, 2, -5);
    bf_cycle.add_edge(2, 0, 2);
    assert(bf_cycle.run(0));
    auto neg_cyc = bf_cycle.find_negative_cycle();
    assert(!neg_cyc.empty());

    // SPFA
    SPFA spfa(4);
    spfa.add_edge(0, 1, 5);
    spfa.add_edge(0, 2, 2);
    spfa.add_edge(2, 1, 1);
    spfa.add_edge(1, 3, 3);
    assert(spfa.run(0));
    assert(spfa.dist[3] == 6);

    // Floyd-Warshall
    FloydWarshall fw(3);
    fw.add_edge(0, 1, 3, false);
    fw.add_edge(1, 2, 4, false);
    fw.add_edge(0, 2, 10, false);
    assert(fw.compute());
    assert(fw.dist[0][2] == 7);
    assert((fw.get_path(0, 2) == vector<int>{0, 1, 2}));
}

void test_mst() {
    // Kruskal
    KruskalMST kmst(4);
    kmst.add_edge(0, 1, 10);
    kmst.add_edge(0, 2, 6);
    kmst.add_edge(0, 3, 5);
    kmst.add_edge(1, 3, 15);
    kmst.add_edge(2, 3, 4);
    auto [k_wt, k_edges] = kmst.solve();
    assert(k_wt == 19);
    assert(k_edges.size() == 3);

    // Prim
    PrimMST pmst(4);
    pmst.add_edge(0, 1, 10);
    pmst.add_edge(0, 2, 6);
    pmst.add_edge(0, 3, 5);
    pmst.add_edge(1, 3, 15);
    pmst.add_edge(2, 3, 4);
    auto [p_wt, p_edges] = pmst.solve();
    assert(p_wt == 19);
    assert(p_edges.size() == 3);
}

void test_topological_and_scc() {
    TopologicalSort ts(4);
    ts.add_edge(0, 1);
    ts.add_edge(0, 2);
    ts.add_edge(1, 3);
    ts.add_edge(2, 3);
    auto order = ts.sort_dag();
    assert(order.size() == 4);
    assert(order[0] == 0 && order[3] == 3);

    // Tarjan SCC
    TarjanSCC scc(5);
    scc.add_edge(0, 1);
    scc.add_edge(1, 2);
    scc.add_edge(2, 0); // 0, 1, 2 in cycle
    scc.add_edge(1, 3);
    scc.add_edge(3, 4);
    scc.run();
    assert(scc.comp_count == 3);
    assert(scc.comp[0] == scc.comp[1] && scc.comp[1] == scc.comp[2]);
    assert(scc.comp[3] != scc.comp[0]);

    // Kosaraju SCC
    KosarajuSCC kscc(5);
    kscc.add_edge(0, 1);
    kscc.add_edge(1, 2);
    kscc.add_edge(2, 0);
    kscc.add_edge(1, 3);
    kscc.add_edge(3, 4);
    kscc.run();
    assert(kscc.comp_count == 3);
    assert(kscc.comp[0] == kscc.comp[1] && kscc.comp[1] == kscc.comp[2]);
}

void test_two_sat_and_connectivity() {
    // 2-SAT: (x0 v x1) and (~x0 v x1) and (x0 v ~x1)
    // Only solution is x0 = true, x1 = true
    TwoSat sat(2);
    sat.add_clause(0, true, 1, true);
    sat.add_clause(0, false, 1, true);
    sat.add_clause(0, true, 1, false);
    auto [possible, assign] = sat.solve();
    assert(possible);
    assert(assign[0] == true && assign[1] == true);

    // Bridges and Articulation
    BridgesAndArticulationPoints bap(5);
    bap.add_edge(0, 1);
    bap.add_edge(1, 2);
    bap.add_edge(2, 0);
    bap.add_edge(1, 3);
    bap.add_edge(3, 4);
    bap.run();
    auto cut_nodes = bap.get_articulation_points();
    assert(find(cut_nodes.begin(), cut_nodes.end(), 1) != cut_nodes.end());
    assert(find(cut_nodes.begin(), cut_nodes.end(), 3) != cut_nodes.end());
    assert(bap.bridges.size() == 2); // edges 1-3 and 3-4

    // Eulerian Directed
    EulerianDirected ed(3);
    ed.add_edge(0, 1);
    ed.add_edge(1, 2);
    ed.add_edge(2, 0);
    auto path = ed.find_path();
    assert(path.size() == 4);
    assert(path.front() == path.back());
}

int main() {
    cout << "[TEST] Running test_graph_theory suite...\n";
    test_bfs_and_zero_one();
    test_shortest_paths();
    test_mst();
    test_topological_and_scc();
    test_two_sat_and_connectivity();
    cout << "[TEST] All 5 test sets in test_graph_theory passed!\n";
    return 0;
}
