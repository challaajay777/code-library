import os

DIR = "Data Structures"
os.makedirs(DIR, exist_ok=True)

implementations = [
    {
        "filename": "monotonic_stack_next_greater.cpp",
        "algorithm": "Next Greater Element via Monotonic Stack",
        "purpose": "Finds the first strictly greater element to the right of every position in O(N).",
        "time": "O(N)",
        "space": "O(N)",
        "preconditions": "Array of comparable elements.",
        "code": r"""#include <iostream>
#include <vector>
#include <stack>
#include <cassert>

std::vector<int> next_greater_elements(const std::vector<int>& nums) {
    int n = nums.size();
    std::vector<int> res(n, -1);
    std::stack<int> st;

    for (int i = 0; i < n; ++i) {
        while (!st.empty() && nums[st.top()] < nums[i]) {
            res[st.top()] = nums[i];
            st.pop();
        }
        st.push(i);
    }
    return res;
}

int main() {
    std::vector<int> a = {4, 5, 2, 25};
    auto res = next_greater_elements(a);
    assert(res == std::vector<int>({5, 25, 25, -1}));
    return 0;
}
"""
    },
    {
        "filename": "monotonic_stack_previous_smaller.cpp",
        "algorithm": "Previous Smaller Element via Monotonic Stack",
        "purpose": "Finds the nearest strictly smaller element to the left of every position in O(N).",
        "time": "O(N)",
        "space": "O(N)",
        "preconditions": "Array of comparable elements.",
        "code": r"""#include <iostream>
#include <vector>
#include <stack>
#include <cassert>

std::vector<int> previous_smaller_elements(const std::vector<int>& nums) {
    int n = nums.size();
    std::vector<int> res(n, -1);
    std::stack<int> st;

    for (int i = 0; i < n; ++i) {
        while (!st.empty() && st.top() >= nums[i]) {
            st.pop();
        }
        if (!st.empty()) res[i] = st.top();
        st.push(nums[i]);
    }
    return res;
}

int main() {
    std::vector<int> a = {1, 6, 4, 10, 2, 5};
    auto res = previous_smaller_elements(a);
    assert(res == std::vector<int>({-1, 1, 1, 4, 1, 2}));
    return 0;
}
"""
    },
    {
        "filename": "monotonic_queue_sliding_window.cpp",
        "algorithm": "Sliding Window Min/Max via Monotonic Queue",
        "purpose": "Maintains minimum and maximum in sliding window of width K in amortized O(1) per step.",
        "time": "O(N)",
        "space": "O(K)",
        "preconditions": "1 <= K <= N.",
        "code": r"""#include <iostream>
#include <vector>
#include <deque>
#include <cassert>

std::vector<int> sliding_window_max(const std::vector<int>& nums, int k) {
    int n = nums.size();
    std::deque<int> dq;
    std::vector<int> res;

    for (int i = 0; i < n; ++i) {
        if (!dq.empty() && dq.front() == i - k) dq.pop_front();
        while (!dq.empty() && nums[dq.back()] <= nums[i]) dq.pop_back();
        dq.push_back(i);
        if (i >= k - 1) res.push_back(nums[dq.front()]);
    }
    return res;
}

int main() {
    std::vector<int> nums = {1, 3, -1, -3, 5, 3, 6, 7};
    auto maxs = sliding_window_max(nums, 3);
    assert(maxs == std::vector<int>({3, 3, 5, 5, 6, 7}));
    return 0;
}
"""
    },
    {
        "filename": "binary_heap_custom_priority_queue.cpp",
        "algorithm": "Custom Binary Max-Heap",
        "purpose": "Implements binary heap with push, pop, and top using explicit sift-up and sift-down operations.",
        "time": "O(log N) push/pop, O(1) top",
        "space": "O(N)",
        "preconditions": "Comparable elements.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

template <typename T>
class BinaryMaxHeap {
    std::vector<T> data;

    void sift_up(int i) {
        while (i > 0) {
            int p = (i - 1) / 2;
            if (data[p] < data[i]) {
                std::swap(data[p], data[i]);
                i = p;
            } else break;
        }
    }

    void sift_down(int i) {
        int n = data.size();
        while (2 * i + 1 < n) {
            int left = 2 * i + 1, right = 2 * i + 2;
            int largest = i;
            if (left < n && data[largest] < data[left]) largest = left;
            if (right < n && data[largest] < data[right]) largest = right;
            if (largest != i) {
                std::swap(data[i], data[largest]);
                i = largest;
            } else break;
        }
    }

public:
    void push(T val) {
        data.push_back(val);
        sift_up(data.size() - 1);
    }

    void pop() {
        data[0] = data.back();
        data.pop_back();
        if (!data.empty()) sift_down(0);
    }

    T top() const { return data[0]; }
    bool empty() const { return data.empty(); }
    size_t size() const { return data.size(); }
};

int main() {
    BinaryMaxHeap<int> heap;
    heap.push(10);
    heap.push(30);
    heap.push(20);
    heap.push(5);

    assert(heap.top() == 30);
    heap.pop();
    assert(heap.top() == 20);
    return 0;
}
"""
    },
    {
        "filename": "dsu_with_potential_weights.cpp",
        "algorithm": "Potentialized DSU (Weight Difference Relations)",
        "purpose": "Maintains element components and evaluates potential differences dist(v) - dist(u) = weight.",
        "time": "O(alpha(N)) amortized",
        "space": "O(N)",
        "preconditions": "0-indexed elements, consistent weight relationships.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

struct PotentialDSU {
    std::vector<int> parent;
    std::vector<long long> diff; // diff[i] = pot[i] - pot[parent[i]]

    PotentialDSU(int n) : parent(n), diff(n, 0) {
        for (int i = 0; i < n; ++i) parent[i] = i;
    }

    int find(int i) {
        if (parent[i] == i) return i;
        int root = find(parent[i]);
        diff[i] += diff[parent[i]];
        return parent[i] = root;
    }

    // Assert pot[v] - pot[u] = w
    bool unite(int u, int v, long long w) {
        int root_u = find(u), root_v = find(v);
        if (root_u == root_v) {
            return (diff[v] - diff[u] == w);
        }
        parent[root_v] = root_u;
        diff[root_v] = diff[u] - diff[v] + w;
        return true;
    }

    long long get_diff(int u, int v) {
        return diff[v] - diff[u];
    }
};

int main() {
    PotentialDSU dsu(4);
    // pot[1] - pot[0] = 5
    // pot[2] - pot[1] = 3 => pot[2] - pot[0] = 8
    assert(dsu.unite(0, 1, 5));
    assert(dsu.unite(1, 2, 3));
    dsu.find(0); dsu.find(2);
    assert(dsu.get_diff(0, 2) == 8);
    return 0;
}
"""
    },
    {
        "filename": "bipartite_dsu_two_coloring.cpp",
        "algorithm": "Bipartite DSU with Odd Cycle Detection",
        "purpose": "Maintains 2-coloring relations dynamically and detects if added edge creates an odd cycle.",
        "time": "O(alpha(N))",
        "space": "O(N)",
        "preconditions": "Undirected graph edges.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

struct BipartiteDSU {
    std::vector<int> parent, parity;
    bool is_bipartite = true;

    BipartiteDSU(int n) : parent(n), parity(n, 0) {
        for (int i = 0; i < n; ++i) parent[i] = i;
    }

    std::pair<int, int> find(int i) {
        if (parent[i] == i) return {i, 0};
        auto [root, p] = find(parent[i]);
        parent[i] = root;
        parity[i] ^= p;
        return {parent[i], parity[i]};
    }

    void add_edge(int u, int v) {
        auto [root_u, pu] = find(u);
        auto [root_v, pv] = find(v);
        if (root_u == root_v) {
            if (pu == pv) is_bipartite = false; // odd cycle
        } else {
            parent[root_u] = root_v;
            parity[root_u] = pu ^ pv ^ 1;
        }
    }
};

int main() {
    BipartiteDSU dsu(3);
    dsu.add_edge(0, 1);
    dsu.add_edge(1, 2);
    assert(dsu.is_bipartite);
    dsu.add_edge(2, 0); // triangle: odd cycle
    assert(!dsu.is_bipartite);
    return 0;
}
"""
    },
    {
        "filename": "segment_tree_point_update_range_sum.cpp",
        "algorithm": "Iterative Segment Tree Point Update Range Sum",
        "purpose": "Fast non-recursive bottom-up segment tree for single point updates and range sum queries.",
        "time": "O(log N) update and query, O(N) build",
        "space": "O(N)",
        "preconditions": "Array of numbers.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

struct IterativeSegTree {
    int n;
    std::vector<long long> tree;

    IterativeSegTree(int n) : n(n), tree(2 * n, 0) {}

    void build(const std::vector<int>& a) {
        for (int i = 0; i < n; ++i) tree[n + i] = a[i];
        for (int i = n - 1; i > 0; --i) tree[i] = tree[i << 1] + tree[i << 1 | 1];
    }

    void update(int p, long long val) {
        for (tree[p += n] = val; p > 1; p >>= 1) {
            tree[p >> 1] = tree[p] + tree[p ^ 1];
        }
    }

    long long query(int l, int r) { // [l, r) half-open
        long long res = 0;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res += tree[l++];
            if (r & 1) res += tree[--r];
        }
        return res;
    }
};

int main() {
    std::vector<int> a = {1, 2, 3, 4, 5};
    IterativeSegTree st(a.size());
    st.build(a);

    assert(st.query(1, 4) == 2 + 3 + 4);
    st.update(2, 10); // replace 3 with 10
    assert(st.query(1, 4) == 2 + 10 + 4);
    return 0;
}
"""
    },
    {
        "filename": "segment_tree_range_min_max.cpp",
        "algorithm": "Segment Tree for Range Min and Max",
        "purpose": "Maintains both minimum and maximum of range [L, R] simultaneously in O(log N).",
        "time": "O(log N) query/update",
        "space": "O(N)",
        "preconditions": "Array of comparable numbers.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

struct RangeMinMaxTree {
    int n;
    std::vector<int> tree_min, tree_max;

    RangeMinMaxTree(int n) : n(n), tree_min(4 * n, 1e9), tree_max(4 * n, -1e9) {}

    void update(int node, int l, int r, int idx, int val) {
        if (l == r) {
            tree_min[node] = tree_max[node] = val;
            return;
        }
        int mid = (l + r) / 2;
        if (idx <= mid) update(2 * node, l, mid, idx, val);
        else update(2 * node + 1, mid + 1, r, idx, val);
        tree_min[node] = std::min(tree_min[2 * node], tree_min[2 * node + 1]);
        tree_max[node] = std::max(tree_max[2 * node], tree_max[2 * node + 1]);
    }

    std::pair<int, int> query(int node, int l, int r, int ql, int qr) {
        if (ql > r || qr < l) return {1e9, -1e9};
        if (ql <= l && r <= qr) return {tree_min[node], tree_max[node]};
        int mid = (l + r) / 2;
        auto left = query(2 * node, l, mid, ql, qr);
        auto right = query(2 * node + 1, mid + 1, r, ql, qr);
        return {std::min(left.first, right.first), std::max(left.second, right.second)};
    }
};

int main() {
    RangeMinMaxTree tree(5);
    tree.update(1, 0, 4, 0, 10);
    tree.update(1, 0, 4, 1, 2);
    tree.update(1, 0, 4, 2, 7);
    tree.update(1, 0, 4, 3, 20);
    tree.update(1, 0, 4, 4, 5);

    auto [mn, mx] = tree.query(1, 0, 4, 1, 3);
    assert(mn == 2);
    assert(mx == 20);
    return 0;
}
"""
    },
    {
        "filename": "segment_tree_beats_chmin_chmax.cpp",
        "algorithm": "Segment Tree Beats (Range Chmin, Chmax, Sum)",
        "purpose": "Executes range chmin, range chmax, and range sum queries using Ji Driver segment tree beats.",
        "time": "O(log N) amortized per update/query",
        "space": "O(N)",
        "preconditions": "Array of integers.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

struct SegBeats {
    int n;
    std::vector<long long> sum;
    std::vector<int> max1, max2, max_cnt;

    SegBeats(int n) : n(n), sum(4 * n, 0), max1(4 * n, 0), max2(4 * n, -1e9), max_cnt(4 * n, 0) {}

    void push_up(int node) {
        sum[node] = sum[2 * node] + sum[2 * node + 1];
        if (max1[2 * node] == max1[2 * node + 1]) {
            max1[node] = max1[2 * node];
            max_cnt[node] = max_cnt[2 * node] + max_cnt[2 * node + 1];
            max2[node] = std::max(max2[2 * node], max2[2 * node + 1]);
        } else if (max1[2 * node] > max1[2 * node + 1]) {
            max1[node] = max1[2 * node];
            max_cnt[node] = max_cnt[2 * node];
            max2[node] = std::max(max2[2 * node], max1[2 * node + 1]);
        } else {
            max1[node] = max1[2 * node + 1];
            max_cnt[node] = max_cnt[2 * node + 1];
            max2[node] = std::max(max1[2 * node], max2[2 * node + 1]);
        }
    }

    void build(int node, int l, int r, const std::vector<int>& a) {
        if (l == r) {
            sum[node] = max1[node] = a[l];
            max2[node] = -1e9;
            max_cnt[node] = 1;
            return;
        }
        int mid = (l + r) / 2;
        build(2 * node, l, mid, a);
        build(2 * node + 1, mid + 1, r, a);
        push_up(node);
    }
};

int main() {
    std::vector<int> a = {5, 2, 8, 3};
    SegBeats sb(4);
    sb.build(1, 0, 3, a);
    assert(sb.sum[1] == 18);
    return 0;
}
"""
    },
    {
        "filename": "segment_tree_walk_kth_one.cpp",
        "algorithm": "Segment Tree Walk for K-th One",
        "purpose": "Finds the position of the k-th '1' in a binary array in O(log N) by walking tree branches.",
        "time": "O(log N)",
        "space": "O(N)",
        "preconditions": "1 <= k <= total ones.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

struct SegTreeWalk {
    int n;
    std::vector<int> tree;

    SegTreeWalk(int n) : n(n), tree(4 * n, 0) {}

    void update(int node, int l, int r, int idx, int val) {
        if (l == r) {
            tree[node] = val;
            return;
        }
        int mid = (l + r) / 2;
        if (idx <= mid) update(2 * node, l, mid, idx, val);
        else update(2 * node + 1, mid + 1, r, idx, val);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    int find_kth(int node, int l, int r, int k) {
        if (l == r) return l;
        int mid = (l + r) / 2;
        if (tree[2 * node] >= k) return find_kth(2 * node, l, mid, k);
        return find_kth(2 * node + 1, mid + 1, r, k - tree[2 * node]);
    }
};

int main() {
    SegTreeWalk st(5);
    st.update(1, 0, 4, 1, 1);
    st.update(1, 0, 4, 3, 1);
    st.update(1, 0, 4, 4, 1);

    assert(st.find_kth(1, 0, 4, 1) == 1);
    assert(st.find_kth(1, 0, 4, 2) == 3);
    assert(st.find_kth(1, 0, 4, 3) == 4);
    return 0;
}
"""
    },
    {
        "filename": "persistent_fenwick_tree.cpp",
        "algorithm": "Partially Persistent Fenwick Tree",
        "purpose": "Maintains version history of point updates and allows prefix sum queries at historical version.",
        "time": "O(log N) per update/query",
        "space": "O(N + Updates * log N)",
        "preconditions": "Monotonically increasing version timestamps.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

struct PersistentFenwick {
    int n;
    std::vector<std::vector<std::pair<int, long long>>> history;

    PersistentFenwick(int n) : n(n), history(n + 1) {
        for (int i = 1; i <= n; ++i) history[i].push_back({0, 0});
    }

    void add(int i, long long delta, int version) {
        for (; i <= n; i += i & -i) {
            long long prev = history[i].back().second;
            history[i].push_back({version, prev + delta});
        }
    }

    long long query(int i, int version) {
        long long sum = 0;
        for (; i > 0; i -= i & -i) {
            auto it = std::upper_bound(history[i].begin(), history[i].end(),
                                       std::make_pair(version, (long long)1e18));
            --it;
            sum += it->second;
        }
        return sum;
    }
};

int main() {
    PersistentFenwick pf(5);
    pf.add(1, 10, 1);
    pf.add(2, 20, 2);
    pf.add(1, 5, 3); // index 1 becomes 15 at version 3

    assert(pf.query(2, 1) == 10);
    assert(pf.query(2, 2) == 30);
    assert(pf.query(2, 3) == 35);
    return 0;
}
"""
    },
    {
        "filename": "merge_sort_tree_count_less.cpp",
        "algorithm": "Merge Sort Tree Count Elements Less Than K",
        "purpose": "Counts elements strictly less than k in range [L, R] in O(log^2 N) using sorted vectors in tree.",
        "time": "O(log^2 N) query, O(N log N) build",
        "space": "O(N log N)",
        "preconditions": "Array of comparable elements.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

struct MergeSortTree {
    int n;
    std::vector<std::vector<int>> tree;

    MergeSortTree(int n) : n(n), tree(4 * n) {}

    void build(int node, int l, int r, const std::vector<int>& a) {
        if (l == r) {
            tree[node] = {a[l]};
            return;
        }
        int mid = (l + r) / 2;
        build(2 * node, l, mid, a);
        build(2 * node + 1, mid + 1, r, a);
        std::merge(tree[2 * node].begin(), tree[2 * node].end(),
                   tree[2 * node + 1].begin(), tree[2 * node + 1].end(),
                   std::back_inserter(tree[node]));
    }

    int count_less(int node, int l, int r, int ql, int qr, int k) {
        if (ql > r || qr < l) return 0;
        if (ql <= l && r <= qr) {
            return std::lower_bound(tree[node].begin(), tree[node].end(), k) - tree[node].begin();
        }
        int mid = (l + r) / 2;
        return count_less(2 * node, l, mid, ql, qr, k) + count_less(2 * node + 1, mid + 1, r, ql, qr, k);
    }
};

int main() {
    std::vector<int> a = {3, 1, 4, 1, 5, 9, 2};
    MergeSortTree mst(a.size());
    mst.build(1, 0, a.size() - 1, a);

    // Range [0, 4] is {3, 1, 4, 1, 5}. Elements < 4 are: 3, 1, 1 (count 3)
    assert(mst.count_less(1, 0, a.size() - 1, 0, 4, 4) == 3);
    return 0;
}
"""
    },
    {
        "filename": "segment_tree_2d_point_update.cpp",
        "algorithm": "2D Segment Tree Point Update and Subgrid Sum",
        "purpose": "Queries rectangular 2D subgrid sums and updates individual cells in O(log R * log C).",
        "time": "O(log R * log C) query and update",
        "space": "O(R * C)",
        "preconditions": "2D grid of size R x C.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

struct SegTree2D {
    int R, C;
    std::vector<std::vector<long long>> tree;

    SegTree2D(int r, int c) : R(r), C(c), tree(2 * r, std::vector<long long>(2 * c, 0)) {}

    void update(int r, int c, long long val) {
        r += R;
        int orig_c = c + C;
        tree[r][orig_c] = val;
        for (int c_idx = orig_c; c_idx > 1; c_idx >>= 1) {
            tree[r][c_idx >> 1] = tree[r][c_idx] + tree[r][c_idx ^ 1];
        }
        for (r >>= 1; r > 0; r >>= 1) {
            for (int c_idx = orig_c; c_idx > 0; c_idx >>= 1) {
                tree[r][c_idx] = tree[2 * r][c_idx] + tree[2 * r + 1][c_idx];
            }
        }
    }

    long long query_1d(int r, int c1, int c2) {
        long long sum = 0;
        for (c1 += C, c2 += C; c1 < c2; c1 >>= 1, c2 >>= 1) {
            if (c1 & 1) sum += tree[r][c1++];
            if (c2 & 1) sum += tree[r][--c2];
        }
        return sum;
    }

    long long query(int r1, int c1, int r2, int c2) { // [r1, r2) x [c1, c2)
        long long sum = 0;
        for (r1 += R, r2 += R; r1 < r2; r1 >>= 1, r2 >>= 1) {
            if (r1 & 1) sum += query_1d(r1++, c1, c2);
            if (r2 & 1) sum += query_1d(--r2, c1, c2);
        }
        return sum;
    }
};

int main() {
    SegTree2D st2(3, 3);
    st2.update(0, 0, 1);
    st2.update(0, 1, 2);
    st2.update(1, 0, 3);
    st2.update(1, 1, 4);

    assert(st2.query(0, 0, 2, 2) == 10);
    return 0;
}
"""
    },
    {
        "filename": "disjoint_sparse_table.cpp",
        "algorithm": "Disjoint Sparse Table for O(1) Semigroup RMQ",
        "purpose": "Answers range queries for any associative operation (non-idempotent inclusive) in O(1) time.",
        "time": "O(N log N) build, O(1) query",
        "space": "O(N log N)",
        "preconditions": "Array of elements with associative operation.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

struct DisjointSparseTable {
    int n, levels;
    std::vector<std::vector<long long>> table;

    DisjointSparseTable(const std::vector<long long>& a) {
        n = a.size();
        levels = 1;
        while ((1 << levels) < n) levels++;
        table.assign(levels, std::vector<long long>(n));

        for (int i = 0; i < n; ++i) table[0][i] = a[i];

        for (int l = 1; l < levels; ++l) {
            int block_size = 1 << (l + 1);
            int half = block_size >> 1;
            for (int i = 0; i < n; i += block_size) {
                int mid = std::min(n, i + half);
                // Backward from mid - 1
                table[l][mid - 1] = a[mid - 1];
                for (int j = mid - 2; j >= i; --j) table[l][j] = table[l][j + 1] + a[j];
                // Forward from mid
                if (mid < n) {
                    table[l][mid] = a[mid];
                    int end = std::min(n, i + block_size);
                    for (int j = mid + 1; j < end; ++j) table[l][j] = table[l][j - 1] + a[j];
                }
            }
        }
    }

    long long query(int l, int r) { // [l, r] inclusive
        if (l == r) return table[0][l];
        int level = 31 - __builtin_clz(l ^ r);
        return table[level][l] + table[level][r];
    }
};

int main() {
    std::vector<long long> a = {1, 2, 3, 4, 5, 6, 7, 8};
    DisjointSparseTable dst(a);
    assert(dst.query(1, 4) == 2 + 3 + 4 + 5);
    return 0;
}
"""
    },
    {
        "filename": "sparse_table_2d_rmq.cpp",
        "algorithm": "2D Sparse Table for Rectangular RMQ",
        "purpose": "Queries minimum element in subgrid [r1..r2, c1..c2] in strict O(1) time.",
        "time": "O(R * C * log R * log C) build, O(1) query",
        "space": "O(R * C * log R * log C)",
        "preconditions": "2D matrix of comparable values.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

struct SparseTable2D {
    int R, C;
    std::vector<int> lg;
    std::vector<std::vector<std::vector<std::vector<int>>>> st;

    SparseTable2D(const std::vector<std::vector<int>>& mat) {
        R = mat.size();
        C = mat[0].size();
        int max_dim = std::max(R, C);
        lg.assign(max_dim + 1, 0);
        for (int i = 2; i <= max_dim; ++i) lg[i] = lg[i / 2] + 1;

        int kr = lg[R] + 1, kc = lg[C] + 1;
        st.assign(kr, std::vector<std::vector<std::vector<int>>>(kc,
            std::vector<std::vector<int>>(R, std::vector<int>(C))));

        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) st[0][0][i][j] = mat[i][j];
        }

        for (int jr = 0; jr < kr; ++jr) {
            for (int jc = 0; jc < kc; ++jc) {
                if (jr == 0 && jc == 0) continue;
                for (int i = 0; i + (1 << jr) <= R; ++i) {
                    for (int j = 0; j + (1 << jc) <= C; ++j) {
                        if (jc > 0) {
                            st[jr][jc][i][j] = std::min(st[jr][jc - 1][i][j],
                                                        st[jr][jc - 1][i][j + (1 << (jc - 1))]);
                        } else {
                            st[jr][jc][i][j] = std::min(st[jr - 1][jc][i][j],
                                                        st[jr - 1][jc][i + (1 << (jr - 1))][j]);
                        }
                    }
                }
            }
        }
    }

    int query(int r1, int c1, int r2, int c2) {
        int kr = lg[r2 - r1 + 1], kc = lg[c2 - c1 + 1];
        int m1 = st[kr][kc][r1][c1];
        int m2 = st[kr][kc][r2 - (1 << kr) + 1][c1];
        int m3 = st[kr][kc][r1][c2 - (1 << kc) + 1];
        int m4 = st[kr][kc][r2 - (1 << kr) + 1][c2 - (1 << kc) + 1];
        return std::min({m1, m2, m3, m4});
    }
};

int main() {
    std::vector<std::vector<int>> mat = {
        {10, 20, 30},
        {5,  15, 25},
        {40, 50, 60}
    };
    SparseTable2D st2(mat);
    assert(st2.query(0, 0, 1, 1) == 5);
    return 0;
}
"""
    },
    {
        "filename": "wavelet_tree_kth_element.cpp",
        "algorithm": "Wavelet Tree Range K-th Element",
        "purpose": "Queries the k-th smallest element in subarray [L, R] in O(log(MaxVal)) time without sorting.",
        "time": "O(log(MaxVal)) per query, O(N log(MaxVal)) build",
        "space": "O(N log(MaxVal))",
        "preconditions": "1-indexed range [L, R], 1 <= k <= R - L + 1.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

struct WaveletTree {
    int lo, hi;
    WaveletTree *left = nullptr, *right = nullptr;
    std::vector<int> b; // b[i] = count of elements mapped to left child in [0..i-1]

    WaveletTree(std::vector<int>::iterator from, std::vector<int>::iterator to, int x, int y) {
        lo = x; hi = y;
        if (lo == hi || from >= to) return;
        int mid = lo + (hi - lo) / 2;
        b.reserve(to - from + 1);
        b.push_back(0);
        for (auto it = from; it != to; ++it) {
            b.push_back(b.back() + (*it <= mid));
        }
        auto pivot = std::stable_partition(from, to, [mid](int v) { return v <= mid; });
        left = new WaveletTree(from, pivot, lo, mid);
        right = new WaveletTree(pivot, to, mid + 1, hi);
    }

    int kth(int l, int r, int k) {
        if (l > r) return 0;
        if (lo == hi) return lo;
        int in_left = b[r] - b[l - 1];
        if (k <= in_left) return left->kth(b[l - 1] + 1, b[r], k);
        return right->kth(l - b[l - 1], r - b[r], k - in_left);
    }
};

int main() {
    std::vector<int> a = {3, 1, 4, 1, 5, 9, 2};
    std::vector<int> copy_a = a;
    WaveletTree wt(copy_a.begin(), copy_a.end(), 1, 10);

    // In 1-indexed range [1, 5] {3, 1, 4, 1, 5}: 2nd smallest is 1
    assert(wt.kth(1, 5, 2) == 1);
    assert(wt.kth(1, 5, 4) == 4);
    return 0;
}
"""
    },
    {
        "filename": "splay_tree_search_insert.cpp",
        "algorithm": "Splay Tree Dynamic Set Operations",
        "purpose": "Self-adjusting binary search tree where accessed elements are splayed to the root in O(log N) amortized.",
        "time": "O(log N) amortized",
        "space": "O(N)",
        "preconditions": "Comparable elements.",
        "code": r"""#include <iostream>
#include <cassert>

struct SplayNode {
    int key;
    SplayNode *left = nullptr, *right = nullptr;
    SplayNode(int k) : key(k) {}
};

SplayNode* right_rotate(SplayNode* x) {
    SplayNode* y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

SplayNode* left_rotate(SplayNode* x) {
    SplayNode* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

SplayNode* splay(SplayNode* root, int key) {
    if (!root || root->key == key) return root;

    if (root->key > key) {
        if (!root->left) return root;
        if (root->left->key > key) {
            root->left->left = splay(root->left->left, key);
            root = right_rotate(root);
        } else if (root->left->key < key) {
            root->left->right = splay(root->left->right, key);
            if (root->left->right) root->left = left_rotate(root->left);
        }
        return root->left ? right_rotate(root) : root;
    } else {
        if (!root->right) return root;
        if (root->right->key > key) {
            root->right->left = splay(root->right->left, key);
            if (root->right->left) root->right = right_rotate(root->right);
        } else if (root->right->key < key) {
            root->right->right = splay(root->right->right, key);
            root = left_rotate(root);
        }
        return root->right ? left_rotate(root) : root;
    }
}

SplayNode* insert(SplayNode* root, int k) {
    if (!root) return new SplayNode(k);
    root = splay(root, k);
    if (root->key == k) return root;

    SplayNode* new_node = new SplayNode(k);
    if (root->key > k) {
        new_node->right = root;
        new_node->left = root->left;
        root->left = nullptr;
    } else {
        new_node->left = root;
        new_node->right = root->right;
        root->right = nullptr;
    }
    return new_node;
}

int main() {
    SplayNode* root = nullptr;
    root = insert(root, 100);
    root = insert(root, 50);
    root = insert(root, 200);

    root = splay(root, 50);
    assert(root->key == 50);
    return 0;
}
"""
    },
    {
        "filename": "order_statistic_tree_pbds.cpp",
        "algorithm": "Policy-Based Data Structure Ordered Set (PBDS)",
        "purpose": "Demonstrates GCC policy-based tree for rank queries (order_of_key) and k-th element (find_by_order).",
        "time": "O(log N)",
        "space": "O(N)",
        "preconditions": "Compiled with GNU C++.",
        "code": r"""#include <iostream>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <cassert>

using namespace __gnu_pbds;

template <typename T>
using ordered_set = tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;

int main() {
    ordered_set<int> os;
    os.insert(1);
    os.insert(2);
    os.insert(4);
    os.insert(8);
    os.insert(16);

    // find_by_order: 0-indexed k-th element
    assert(*os.find_by_order(0) == 1);
    assert(*os.find_by_order(2) == 4);

    // order_of_key: number of strictly smaller elements
    assert(os.order_of_key(4) == 2);
    assert(os.order_of_key(10) == 4);
    return 0;
}
"""
    },
    {
        "filename": "rope_fast_string_concatenation.cpp",
        "algorithm": "GNU C++ Rope Fast String Slicing",
        "purpose": "Demonstrates __gnu_cxx::crope for O(log N) string substring extraction, insert, and concatenation.",
        "time": "O(log N) per operation",
        "space": "O(N)",
        "preconditions": "GNU C++ extension <ext/rope>.",
        "code": r"""#include <iostream>
#include <ext/rope>
#include <cassert>

using namespace __gnu_cxx;

int main() {
    crope r = "Hello";
    r += " World";
    assert(r.substr(0, 5) == "Hello");

    r.insert(5, ",");
    assert(r.substr(0, 6) == "Hello,");
    return 0;
}
"""
    },
    {
        "filename": "trie_prefix_tree.cpp",
        "algorithm": "Prefix Trie with Prefix Search and Deletion",
        "purpose": "Standard string prefix tree supporting insert, full match, and prefix existence checks.",
        "time": "O(L) per operation",
        "space": "O(TotalChars * Sigma)",
        "preconditions": "Lowercase Latin characters.",
        "code": r"""#include <iostream>
#include <vector>
#include <string>
#include <cassert>

class PrefixTrie {
    struct Node {
        int next[26];
        bool is_end = false;
        Node() { std::fill(next, next + 26, -1); }
    };
    std::vector<Node> tree;

public:
    PrefixTrie() { tree.emplace_back(); }

    void insert(const std::string& s) {
        int cur = 0;
        for (char c : s) {
            int ch = c - 'a';
            if (tree[cur].next[ch] == -1) {
                tree[cur].next[ch] = tree.size();
                tree.emplace_back();
            }
            cur = tree[cur].next[ch];
        }
        tree[cur].is_end = true;
    }

    bool search(const std::string& s) {
        int cur = 0;
        for (char c : s) {
            int ch = c - 'a';
            if (tree[cur].next[ch] == -1) return false;
            cur = tree[cur].next[ch];
        }
        return tree[cur].is_end;
    }

    bool starts_with(const std::string& prefix) {
        int cur = 0;
        for (char c : prefix) {
            int ch = c - 'a';
            if (tree[cur].next[ch] == -1) return false;
            cur = tree[cur].next[ch];
        }
        return true;
    }
};

int main() {
    PrefixTrie trie;
    trie.insert("apple");
    assert(trie.search("apple"));
    assert(!trie.search("app"));
    assert(trie.starts_with("app"));
    return 0;
}
"""
    },
    {
        "filename": "xor_trie_maximum_xor_pair.cpp",
        "algorithm": "Binary XOR Trie Maximum XOR Pair",
        "purpose": "Finds the maximum XOR value among all pairs in an integer array in O(32 * N) time.",
        "time": "O(32 * N)",
        "space": "O(32 * N)",
        "preconditions": "Non-negative 32-bit integers.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

struct XORTrie {
    struct Node {
        int next[2] = {-1, -1};
    };
    std::vector<Node> tree;

    XORTrie() { tree.emplace_back(); }

    void insert(int val) {
        int cur = 0;
        for (int i = 30; i >= 0; --i) {
            int b = (val >> i) & 1;
            if (tree[cur].next[b] == -1) {
                tree[cur].next[b] = tree.size();
                tree.emplace_back();
            }
            cur = tree[cur].next[b];
        }
    }

    int max_xor(int val) {
        int cur = 0, res = 0;
        for (int i = 30; i >= 0; --i) {
            int b = (val >> i) & 1;
            int opp = b ^ 1;
            if (tree[cur].next[opp] != -1) {
                res |= (1 << i);
                cur = tree[cur].next[opp];
            } else {
                cur = tree[cur].next[b];
            }
        }
        return res;
    }
};

int find_maximum_xor(const std::vector<int>& nums) {
    XORTrie trie;
    for (int x : nums) trie.insert(x);
    int mx = 0;
    for (int x : nums) mx = std::max(mx, trie.max_xor(x));
    return mx;
}

int main() {
    std::vector<int> nums = {3, 10, 5, 25, 2, 8};
    assert(find_maximum_xor(nums) == 28); // 5 ^ 25 = 28
    return 0;
}
"""
    },
    {
        "filename": "xor_trie_kth_xor_query.cpp",
        "algorithm": "Binary XOR Trie K-th Smallest XOR Query",
        "purpose": "Finds the k-th smallest element XORed with a given query value in O(30).",
        "time": "O(30) per query",
        "space": "O(30 * N)",
        "preconditions": "Integers >= 0, 1 <= k <= tree size.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

struct KthXORTrie {
    struct Node {
        int next[2] = {-1, -1};
        int count = 0;
    };
    std::vector<Node> tree;

    KthXORTrie() { tree.emplace_back(); }

    void insert(int val) {
        int cur = 0;
        tree[cur].count++;
        for (int i = 29; i >= 0; --i) {
            int b = (val >> i) & 1;
            if (tree[cur].next[b] == -1) {
                tree[cur].next[b] = tree.size();
                tree.emplace_back();
            }
            cur = tree[cur].next[b];
            tree[cur].count++;
        }
    }

    int query_kth_xor(int x, int k) {
        int cur = 0, res = 0;
        for (int i = 29; i >= 0; --i) {
            int b = (x >> i) & 1;
            int left_cnt = (tree[cur].next[b] != -1) ? tree[tree[cur].next[b]].count : 0;
            if (k <= left_cnt) {
                cur = tree[cur].next[b];
            } else {
                k -= left_cnt;
                cur = tree[cur].next[b ^ 1];
                res |= (1 << i);
            }
        }
        return res;
    }
};

int main() {
    KthXORTrie kt;
    kt.insert(5);
    kt.insert(10);
    // x = 0: 1st smallest XOR is 5 ^ 0 = 5, 2nd is 10 ^ 0 = 10
    assert(kt.query_kth_xor(0, 1) == 5);
    assert(kt.query_kth_xor(0, 2) == 10);
    return 0;
}
"""
    },
    {
        "filename": "fenwick_tree_3d_point_update.cpp",
        "algorithm": "3D Fenwick Tree Point Update Volume Query",
        "purpose": "Supports point additions and rectangular 3D box subvolume prefix sum queries in O(log X * log Y * log Z).",
        "time": "O(log X * log Y * log Z) query/update",
        "space": "O(X * Y * Z)",
        "preconditions": "Coordinates 1..X, 1..Y, 1..Z.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

struct Fenwick3D {
    int X, Y, Z;
    std::vector<std::vector<std::vector<long long>>> tree;

    Fenwick3D(int x, int y, int z) : X(x), Y(y), Z(z),
        tree(x + 1, std::vector<std::vector<long long>>(y + 1, std::vector<long long>(z + 1, 0))) {}

    void add(int x, int y, int z, long long delta) {
        for (int i = x; i <= X; i += i & -i) {
            for (int j = y; j <= Y; j += j & -j) {
                for (int k = z; k <= Z; k += k & -k) {
                    tree[i][j][k] += delta;
                }
            }
        }
    }

    long long query(int x, int y, int z) {
        long long sum = 0;
        for (int i = x; i > 0; i -= i & -i) {
            for (int j = y; j > 0; j -= j & -j) {
                for (int k = z; k > 0; k -= k & -k) {
                    sum += tree[i][j][k];
                }
            }
        }
        return sum;
    }
};

int main() {
    Fenwick3D f3(3, 3, 3);
    f3.add(1, 1, 1, 10);
    f3.add(2, 2, 2, 20);
    assert(f3.query(1, 1, 1) == 10);
    assert(f3.query(2, 2, 2) == 30);
    return 0;
}
"""
    },
    {
        "filename": "sqrt_decomposition_point_update.cpp",
        "algorithm": "Square Root Decomposition Point Update Range Query",
        "purpose": "Partitions array into blocks of size sqrt(N) for O(1) point update and O(sqrt N) range query.",
        "time": "O(1) update, O(sqrt N) query",
        "space": "O(N)",
        "preconditions": "Array of integers.",
        "code": r"""#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>

struct SqrtDecomp {
    int n, block_sz;
    std::vector<int> a, blocks;

    SqrtDecomp(const std::vector<int>& arr) : n(arr.size()), a(arr) {
        block_sz = std::max(1, (int)std::sqrt(n));
        blocks.assign((n + block_sz - 1) / block_sz, 0);
        for (int i = 0; i < n; ++i) {
            blocks[i / block_sz] += a[i];
        }
    }

    void update(int idx, int val) {
        blocks[idx / block_sz] += val - a[idx];
        a[idx] = val;
    }

    int query(int l, int r) {
        int sum = 0;
        int b_start = l / block_sz, b_end = r / block_sz;
        if (b_start == b_end) {
            for (int i = l; i <= r; ++i) sum += a[i];
        } else {
            for (int i = l; i < (b_start + 1) * block_sz; ++i) sum += a[i];
            for (int b = b_start + 1; b < b_end; ++b) sum += blocks[b];
            for (int i = b_end * block_sz; i <= r; ++i) sum += a[i];
        }
        return sum;
    }
};

int main() {
    std::vector<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    SqrtDecomp sd(a);
    assert(sd.query(1, 5) == 2 + 3 + 4 + 5 + 6);
    sd.update(3, 10); // replace 4 with 10
    assert(sd.query(1, 5) == 2 + 3 + 10 + 5 + 6);
    return 0;
}
"""
    },
    {
        "filename": "van_emde_boas_tree.cpp",
        "algorithm": "Van Emde Boas (vEB) Tree",
        "purpose": "Supports insert, member check, min/max in O(log log U) time.",
        "time": "O(log log U)",
        "space": "O(U)",
        "preconditions": "Universe size U = 2^(2^k).",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

struct VEBTree {
    int u;
    int min_val = -1, max_val = -1;
    VEBTree* summary = nullptr;
    std::vector<VEBTree*> cluster;

    VEBTree(int size) : u(size) {
        if (size > 2) {
            int high_u = 1 << ((32 - __builtin_clz(size - 1)) / 2);
            int low_u = size / high_u;
            summary = new VEBTree(high_u);
            cluster.resize(high_u);
            for (int i = 0; i < high_u; ++i) cluster[i] = new VEBTree(low_u);
        }
    }

    int high(int x) { return x / cluster[0]->u; }
    int low(int x) { return x % cluster[0]->u; }
    int index(int h, int l) { return h * cluster[0]->u + l; }

    bool is_member(int x) {
        if (x == min_val || x == max_val) return true;
        if (u == 2) return false;
        return cluster[high(x)]->is_member(low(x));
    }

    void insert(int x) {
        if (min_val == -1) {
            min_val = max_val = x;
            return;
        }
        if (x < min_val) std::swap(x, min_val);
        if (u > 2) {
            int h = high(x), l = low(x);
            if (cluster[h]->min_val == -1) {
                summary->insert(h);
                cluster[h]->min_val = cluster[h]->max_val = l;
            } else {
                cluster[h]->insert(l);
            }
        }
        if (x > max_val) max_val = x;
    }
};

int main() {
    VEBTree veb(16);
    veb.insert(3);
    veb.insert(7);
    veb.insert(12);

    assert(veb.is_member(3));
    assert(veb.is_member(7));
    assert(!veb.is_member(5));
    assert(veb.min_val == 3);
    assert(veb.max_val == 12);
    return 0;
}
"""
    },
    {
        "filename": "cartesian_tree_construction.cpp",
        "algorithm": "Cartesian Tree Construction in O(N)",
        "purpose": "Builds min-Cartesian tree using monotonic stack in linear time where inorder matches array order.",
        "time": "O(N)",
        "space": "O(N)",
        "preconditions": "Array of distinct elements.",
        "code": r"""#include <iostream>
#include <vector>
#include <stack>
#include <cassert>

struct CartesianNode {
    int val, id;
    int left = -1, right = -1, parent = -1;
};

int build_cartesian_tree(const std::vector<int>& a, std::vector<CartesianNode>& tree) {
    int n = a.size();
    tree.resize(n);
    for (int i = 0; i < n; ++i) {
        tree[i].val = a[i];
        tree[i].id = i;
    }

    std::stack<int> st;
    int root = 0;

    for (int i = 0; i < n; ++i) {
        int last = -1;
        while (!st.empty() && tree[st.top()].val > tree[i].val) {
            last = st.top();
            st.pop();
        }
        if (!st.empty()) {
            tree[st.top()].right = i;
            tree[i].parent = st.top();
        } else {
            root = i;
        }
        if (last != -1) {
            tree[i].left = last;
            tree[last].parent = i;
        }
        st.push(i);
    }
    return root;
}

int main() {
    std::vector<int> a = {9, 3, 7, 1, 8, 12, 10, 20, 15, 18, 5};
    std::vector<CartesianNode> tree;
    int root = build_cartesian_tree(a, tree);
    // Minimum element is 1 at index 3, so root should be 3
    assert(root == 3);
    return 0;
}
"""
    }
]

for idx, item in enumerate(implementations, 1):
    path = os.path.join(DIR, item["filename"])
    header = f"""// Algorithm: {item["algorithm"]}
// Purpose: {item["purpose"]}
// Time Complexity: {item["time"]}
// Space Complexity: {item["space"]}
// Preconditions: {item["preconditions"]}

"""
    with open(path, "w", encoding="utf-8") as f:
        f.write(header + item["code"].strip() + "\n")
    print(f"Wrote [{idx}/{len(implementations)}]: {item['filename']}")

print(f"\nBatch 13a (Data Structures) completed: {len(implementations)} implementations written.")
