// Test suite for Data Structures
#include <bits/stdc++.h>
#include <cassert>
#include "Data Structures/fenwick_tree.cpp"
#include "Data Structures/fenwick_tree_range_add.cpp"
#include "Data Structures/fenwick_tree_2d.cpp"
#include "Data Structures/segment_tree.cpp"
#include "Data Structures/lazy_segment_tree.cpp"
#include "Data Structures/lazy_segment_tree_assignment.cpp"
#include "Data Structures/dynamic_segment_tree.cpp"
#include "Data Structures/persistent_segment_tree.cpp"
#include "Data Structures/sparse_table.cpp"
#include "Data Structures/disjoint_set_union.cpp"
#include "Data Structures/rollback_dsu.cpp"
#include "Data Structures/treap.cpp"
#include "Data Structures/implicit_treap.cpp"
#include "Data Structures/min_max_stack_queue.cpp"

using namespace std;

void test_fenwick() {
    FenwickTree<long long> ft(10);
    ft.add(3, 5);
    ft.add(7, 2);
    assert(ft.query(2) == 0);
    assert(ft.query(3) == 5);
    assert(ft.query(6) == 5);
    assert(ft.query(7) == 7);
    assert(ft.query(4, 7) == 2);
    assert(ft.query(3, 7) == 7);
}

void test_fenwick_range_add() {
    FenwickTreeRangeAdd<long long> ft(10);
    ft.add_range(2, 5, 3);
    ft.add_range(4, 8, 2);
    // Elements:
    // idx 1: 0
    // idx 2: 3
    // idx 3: 3
    // idx 4: 5
    // idx 5: 5
    // idx 6: 2
    // idx 7: 2
    // idx 8: 2
    // idx 9..10: 0
    assert(ft.query_range(2, 3) == 6);
    assert(ft.query_range(4, 5) == 10);
    assert(ft.query_range(1, 10) == 3 + 3 + 5 + 5 + 2 + 2 + 2);
}

void test_fenwick_2d() {
    FenwickTree2D<int> ft2(4, 4);
    ft2.add(2, 3, 5);
    ft2.add(3, 3, 10);
    assert(ft2.query(2, 3, 3, 3) == 15);
    assert(ft2.query(1, 1, 4, 4) == 15);
    assert(ft2.query(1, 1, 1, 4) == 0);
}

void test_segment_trees() {
    // Point update, range sum
    vector<int> a = {1, 2, 3, 4, 5};
    SegmentTree<int> st(a, 0);
    assert(st.query(0, 4) == 15);
    assert(st.query(1, 3) == 9);
    st.set(2, 10); // a = {1, 2, 10, 4, 5}
    assert(st.query(0, 4) == 22);

    // Lazy Range Add
    LazySegmentTree<long long> lst(a.size());
    lst.add_range(1, 3, 5);
    assert(lst.query_range(0, 4) == 15);
    assert(lst.query_range(2, 2) == 5);
    assert(lst.query_range(0, 0) == 0);

    // Lazy Range Assign Min
    vector<int> vals = {10, 20, 30, 40, 50};
    LazySegmentTreeAssignMin<int> st_min(vals);
    assert(st_min.query_min(0, 4) == 10);
    st_min.assign_range(1, 3, 5); // {10, 5, 5, 5, 50}
    assert(st_min.query_min(0, 4) == 5);
    assert(st_min.query_min(3, 4) == 5);
    assert(st_min.query_min(4, 4) == 50);
}

void test_dynamic_and_persistent() {
    // Dynamic segment tree on huge range [0, 10^9]
    DynamicSegmentTree<long long> dst(0, 1000000000LL);
    dst.add(500000000LL, 42);
    dst.add(100LL, 8);
    assert(dst.query(0, 200LL) == 8);
    assert(dst.query(0, 1000000000LL) == 50);

    // Persistent segment tree
    vector<long long> base = {1, 2, 3, 4};
    PersistentSegmentTree<long long> pst(base);
    int v0 = 0;
    int v1 = pst.add_point(v0, 1, 10); // base[1] += 10 -> {1, 12, 3, 4}
    int v2 = pst.add_point(v1, 3, 5);  // {1, 12, 3, 9}

    assert(pst.query(v0, 0, 3) == 10);
    assert(pst.query(v1, 0, 3) == 20);
    assert(pst.query(v2, 0, 3) == 25);
    assert(pst.query(v0, 1, 1) == 2);
    assert(pst.query(v1, 1, 1) == 12);
}

void test_sparse_table() {
    vector<int> a = {4, 2, 5, 1, 6, 3, 7};
    SparseTable<int> st(a);
    assert(st.query(0, 6) == 1);
    assert(st.query(0, 2) == 2);
    assert(st.query(4, 6) == 3);
}

void test_dsu() {
    DSU dsu(6);
    assert(dsu.count() == 6);
    dsu.unite(1, 2);
    dsu.unite(3, 4);
    assert(dsu.count() == 4);
    assert(dsu.same(1, 2));
    assert(!dsu.same(1, 3));
    dsu.unite(2, 4);
    assert(dsu.same(1, 3));
    assert(dsu.get_size(1) == 4);

    RollbackDSU rdsu(6);
    int s0 = rdsu.snapshot();
    rdsu.unite(1, 2);
    int s1 = rdsu.snapshot();
    rdsu.unite(3, 4);
    assert(rdsu.same(1, 2));
    assert(rdsu.same(3, 4));
    rdsu.rollback(s1);
    assert(rdsu.same(1, 2));
    assert(!rdsu.same(3, 4));
    rdsu.rollback(s0);
    assert(!rdsu.same(1, 2));
}

void test_treaps() {
    Treap<int> tr(1337);
    tr.insert(50);
    tr.insert(20);
    tr.insert(80);
    tr.insert(10);
    tr.insert(30);
    assert(tr.size() == 5);
    assert(tr.contains(20));
    assert(!tr.contains(99));
    assert(tr.find_kth(1) == 10);
    assert(tr.find_kth(3) == 30);
    assert(tr.find_kth(5) == 80);
    tr.erase(20);
    assert(!tr.contains(20));
    assert(tr.size() == 4);

    // Implicit treap
    ImplicitTreap<int> itr(4242);
    for (int i = 1; i <= 6; ++i) itr.push_back(i); // {1, 2, 3, 4, 5, 6}
    itr.reverse_range(1, 4); // reverse {2, 3, 4, 5} -> {1, 5, 4, 3, 2, 6}
    auto d = itr.dump();
    vector<int> exp = {1, 5, 4, 3, 2, 6};
    assert(d == exp);
}

void test_min_stack_queue() {
    MinStack<int> ms;
    ms.push(3);
    ms.push(5);
    assert(ms.get_min() == 3);
    ms.push(2);
    assert(ms.get_min() == 2);
    ms.pop();
    assert(ms.get_min() == 3);

    MinQueue<int> mq;
    mq.push(4);
    mq.push(2);
    mq.push(7);
    assert(mq.get_min() == 2);
    mq.pop(); // pops 4
    assert(mq.get_min() == 2);
    mq.pop(); // pops 2
    assert(mq.get_min() == 7);
}

int main() {
    cout << "[TEST] Running test_data_structures suite...\n";
    test_fenwick();
    test_fenwick_range_add();
    test_fenwick_2d();
    test_segment_trees();
    test_dynamic_and_persistent();
    test_sparse_table();
    test_dsu();
    test_treaps();
    test_min_stack_queue();
    cout << "[TEST] All 9 test sets in test_data_structures passed!\n";
    return 0;
}
