// Algorithm: Dynamic / Implicit Segment Tree
// Supports: Point updates and range sum queries on huge coordinate ranges (e.g. [0, 10^9])
// Indexing: 0-based coordinate range [0, MAX_COORD]
// Complexity: O(log MAX_COORD) per update and query, O(Q * log MAX_COORD) total memory
// Preconditions: 0 <= idx <= MAX_COORD

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

template <typename T>
struct DynamicSegmentTree {
    struct Node {
        T sum = 0;
        int left_child = -1;
        int right_child = -1;
    };

    long long range_start, range_end;
    vector<Node> nodes;

    DynamicSegmentTree(long long start, long long end)
        : range_start(start), range_end(end) {
        nodes.reserve(100000);
        create_node(); // root node at index 0
    }

private:
    int create_node() {
        nodes.push_back(Node());
        return (int)nodes.size() - 1;
    }

    void add(int u, long long s, long long e, long long idx, T val) {
        nodes[u].sum += val;
        if (s == e) return;
        long long mid = s + (e - s) / 2;
        if (idx <= mid) {
            if (nodes[u].left_child == -1) {
                int nxt = create_node();
                nodes[u].left_child = nxt;
            }
            add(nodes[u].left_child, s, mid, idx, val);
        } else {
            if (nodes[u].right_child == -1) {
                int nxt = create_node();
                nodes[u].right_child = nxt;
            }
            add(nodes[u].right_child, mid + 1, e, idx, val);
        }
    }

    T query(int u, long long s, long long e, long long l, long long r) const {
        if (u == -1 || r < s || e < l) return 0;
        if (l <= s && e <= r) return nodes[u].sum;
        long long mid = s + (e - s) / 2;
        return query(nodes[u].left_child, s, mid, l, r) +
               query(nodes[u].right_child, mid + 1, e, l, r);
    }

public:
    void add(long long idx, T val) {
        assert(range_start <= idx && idx <= range_end);
        add(0, range_start, range_end, idx, val);
    }

    T query(long long l, long long r) const {
        if (l > r) return 0;
        assert(range_start <= l && r <= range_end);
        return query(0, range_start, range_end, l, r);
    }
};
