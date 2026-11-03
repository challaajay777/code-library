// Algorithm: Li Chao Tree
// Supports: Adding lines y = m*x + c over [x_min, x_max], querying min(m*x + c) at point x
// Indexing: 0-based coordinate range [0, MAX_X]
// Complexity: O(log MAX_X) per line insertion and point query, O(MAX_X) or dynamic memory
// Preconditions: Coordinate x within designated range

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

struct LiChaoTree {
    struct Line {
        long long m, c;
        long long eval(long long x) const { return m * x + c; }
    };

    static constexpr long long INF_VAL = 2e18;

    int n;
    vector<Line> tree;

    explicit LiChaoTree(int max_x)
        : n(max_x), tree(4 * max_x + 1, {0, INF_VAL}) {}

private:
    void add_line(int node, int l, int r, Line line) {
        int mid = l + (r - l) / 2;
        bool left_better = line.eval(l) < tree[node].eval(l);
        bool mid_better = line.eval(mid) < tree[node].eval(mid);

        if (mid_better) {
            swap(tree[node], line);
        }

        if (l == r) return;

        if (left_better != mid_better) {
            add_line(2 * node, l, mid, line);
        } else {
            add_line(2 * node + 1, mid + 1, r, line);
        }
    }

    long long query(int node, int l, int r, int x) const {
        long long cur = tree[node].eval(x);
        if (l == r) return cur;
        int mid = l + (r - l) / 2;
        if (x <= mid) {
            return min(cur, query(2 * node, l, mid, x));
        } else {
            return min(cur, query(2 * node + 1, mid + 1, r, x));
        }
    }

public:
    void add_line(long long m, long long c) {
        add_line(1, 0, n, {m, c});
    }

    long long query_min(int x) const {
        assert(0 <= x && x <= n);
        return query(1, 0, n, x);
    }
};
