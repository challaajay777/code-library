// Algorithm: Persistent Segment Tree
// Supports: Fully persistent point updates and range sum queries
// Indexing: 0-based indices [0, n - 1]
// Complexity: O(n) initial build, O(log n) time and memory per point update, O(log n) per range query
// Preconditions: Version indices refer to previously created roots

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

template <typename T>
struct PersistentSegmentTree {
    struct Node {
        T sum = 0;
        int left_child = -1;
        int right_child = -1;
    };

    int n;
    vector<Node> nodes;
    vector<int> roots;

    explicit PersistentSegmentTree(int n) : n(n) {
        nodes.reserve(n * 40);
        roots.push_back(build(0, n - 1));
    }

    explicit PersistentSegmentTree(const vector<T>& a) : n((int)a.size()) {
        nodes.reserve(n * 40);
        roots.push_back(build(0, n - 1, &a));
    }

private:
    int create_node(T sum = 0, int lc = -1, int rc = -1) {
        nodes.push_back({sum, lc, rc});
        return (int)nodes.size() - 1;
    }

    int build(int s, int e, const vector<T>* a = nullptr) {
        int u = create_node();
        if (s == e) {
            if (a) nodes[u].sum = (*a)[s];
            return u;
        }
        int mid = s + (e - s) / 2;
        nodes[u].left_child = build(s, mid, a);
        nodes[u].right_child = build(mid + 1, e, a);
        nodes[u].sum = nodes[nodes[u].left_child].sum + nodes[nodes[u].right_child].sum;
        return u;
    }

    int update(int prev_node, int s, int e, int idx, T val) {
        int u = create_node(nodes[prev_node].sum + val,
                            nodes[prev_node].left_child,
                            nodes[prev_node].right_child);
        if (s == e) return u;
        int mid = s + (e - s) / 2;
        if (idx <= mid) {
            nodes[u].left_child = update(nodes[prev_node].left_child, s, mid, idx, val);
        } else {
            nodes[u].right_child = update(nodes[prev_node].right_child, mid + 1, e, idx, val);
        }
        return u;
    }

    T query(int u, int s, int e, int l, int r) const {
        if (u == -1 || r < s || e < l) return 0;
        if (l <= s && e <= r) return nodes[u].sum;
        int mid = s + (e - s) / 2;
        return query(nodes[u].left_child, s, mid, l, r) +
               query(nodes[u].right_child, mid + 1, e, l, r);
    }

public:
    // Creates a new version by adding val to element idx in version prev_ver.
    // Returns index of the newly created version.
    int add_point(int prev_ver, int idx, T val) {
        assert(0 <= prev_ver && prev_ver < (int)roots.size());
        assert(0 <= idx && idx < n);
        int new_root = update(roots[prev_ver], 0, n - 1, idx, val);
        roots.push_back(new_root);
        return (int)roots.size() - 1;
    }

    // Query sum of range [l, r] at specific version
    T query(int version, int l, int r) const {
        if (l > r) return 0;
        assert(0 <= version && version < (int)roots.size());
        assert(0 <= l && r < n);
        return query(roots[version], 0, n - 1, l, r);
    }
};
