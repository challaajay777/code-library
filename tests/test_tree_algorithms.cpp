// Test suite for Trees and Tree Algorithms
#include <bits/stdc++.h>
#include <cassert>
#include "Trees and Tree Algorithms/binary_lifting_lca.cpp"
#include "Trees and Tree Algorithms/heavy_light_decomposition.cpp"
#include "Trees and Tree Algorithms/tree_diameter_and_center.cpp"
#include "Trees and Tree Algorithms/centroid_decomposition.cpp"
#include "Trees and Tree Algorithms/euler_tour_flattening.cpp"
#include "Trees and Tree Algorithms/tree_rerooting_dp.cpp"
#include "Trees and Tree Algorithms/sack_dsu_on_tree.cpp"

using namespace std;

void test_binary_lifting_and_hld() {
    // Tree:
    //         0
    //       /   \
    //      1     2
    //     / \
    //    3   4
    BinaryLiftingLCA bl(5);
    bl.add_edge(0, 1);
    bl.add_edge(0, 2);
    bl.add_edge(1, 3);
    bl.add_edge(1, 4);
    bl.build(0);

    assert(bl.lca(3, 4) == 1);
    assert(bl.lca(3, 2) == 0);
    assert(bl.lca(1, 4) == 1);
    assert(bl.get_kth_ancestor(3, 1) == 1);
    assert(bl.get_kth_ancestor(3, 2) == 0);
    assert(bl.get_kth_ancestor(3, 3) == -1);
    assert(bl.distance(3, 2) == 3);

    // HLD test
    HLD hld(5);
    hld.add_edge(0, 1);
    hld.add_edge(0, 2);
    hld.add_edge(1, 3);
    hld.add_edge(1, 4);
    hld.build(0);
    assert(hld.lca(3, 4) == 1);
    assert(hld.lca(3, 2) == 0);

    int path_nodes_visited = 0;
    hld.process_path(3, 2, [&](int l, int r) {
        path_nodes_visited += (r - l + 1);
    });
    // Path 3 - 1 - 0 - 2 has 4 vertices
    assert(path_nodes_visited == 4);
}

void test_diameter_and_center() {
    // Path: 0 - 1 - 2 - 3 - 4 (length 4, center is 2)
    TreeDiameterCenter tdc(5);
    tdc.add_edge(0, 1);
    tdc.add_edge(1, 2);
    tdc.add_edge(2, 3);
    tdc.add_edge(3, 4);

    auto [u, v, len] = tdc.get_diameter_endpoints();
    assert(len == 4);
    auto centers = tdc.get_centers();
    assert(centers.size() == 1 && centers[0] == 2);
    auto path = tdc.get_diameter_path();
    assert((int)path.size() == 5);
}

void test_centroid_and_euler() {
    // Star graph: 0 connected to 1, 2, 3, 4. Centroid is 0.
    CentroidDecomposition cd(5);
    cd.add_edge(0, 1);
    cd.add_edge(0, 2);
    cd.add_edge(0, 3);
    cd.add_edge(0, 4);
    cd.build();
    assert(cd.root == 0);

    // Euler Tour
    EulerTourTree ett(5);
    ett.add_edge(0, 1);
    ett.add_edge(0, 2);
    ett.add_edge(1, 3);
    ett.add_edge(1, 4);
    ett.build(0);

    assert(ett.is_ancestor(0, 3));
    assert(ett.is_ancestor(1, 3));
    assert(!ett.is_ancestor(2, 3));
    auto sub1 = ett.subtree_interval(1);
    // Subtree of 1 has 3 nodes (1, 3, 4) -> length 3
    assert(sub1.second - sub1.first + 1 == 3);
}

void test_rerooting_and_sack() {
    // Tree: 0 - 1 - 2
    TreeRerooting tr(3);
    tr.add_edge(0, 1);
    tr.add_edge(1, 2);
    auto dists = tr.solve();
    // From 0: d(1)=1, d(2)=2 -> sum = 3
    // From 1: d(0)=1, d(2)=1 -> sum = 2
    // From 2: d(1)=1, d(0)=2 -> sum = 3
    assert(dists[0] == 3);
    assert(dists[1] == 2);
    assert(dists[2] == 3);

    // DSU on tree
    // Tree:
    //      0 (c:1)
    //     / \
    // 1(c:2) 2(c:1)
    vector<int> colors = {1, 2, 1};
    DsuOnTree sack(3, colors);
    sack.add_edge(0, 1);
    sack.add_edge(0, 2);
    auto ans = sack.solve(0);
    // Subtree 1: only color 2 -> 1
    // Subtree 2: only color 1 -> 1
    // Subtree 0: colors 1, 2 -> 2 distinct
    assert(ans[1] == 1);
    assert(ans[2] == 1);
    assert(ans[0] == 2);
}

int main() {
    cout << "[TEST] Running test_tree_algorithms suite...\n";
    test_binary_lifting_and_hld();
    test_diameter_and_center();
    test_centroid_and_euler();
    test_rerooting_and_sack();
    cout << "[TEST] All 4 test sets in test_tree_algorithms passed!\n";
    return 0;
}
