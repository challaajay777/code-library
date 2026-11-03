// Algorithm: Mo's Algorithm with Hilbert Curve Ordering
// Supports: Offline range queries in O(N sqrt(Q)) with minimal pointer travel distance
// Indexing: 0-based range queries [l, r]
// Complexity: O(N * sqrt(Q)) time, O(Q) memory
// Preconditions: Range updates can be added/removed in O(1) amortized time

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

struct MoHilbert {
    struct Query {
        int l, r, id;
        long long ord;

        bool operator<(const Query& o) const {
            return ord < o.ord;
        }
    };

    // Computes Hilbert curve coordinate mapping for (x, y) with pow = 2^k
    static long long hilbert_order(int x, int y, int pow, int rotate = 0) {
        if (pow == 0) return 0;
        int hpow = 1 << (pow - 1);
        int seg = (x < hpow) ? ((y < hpow) ? 0 : 3) : ((y < hpow) ? 1 : 2);
        seg = (seg + rotate) & 3;
        const int rotate_delta[4] = {3, 0, 0, 1};
        int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
        int nrot = (rotate + rotate_delta[seg]) & 3;
        long long sub_square_size = 1LL << (2 * pow - 2);
        long long ans = seg * sub_square_size;
        long long add = hilbert_order(nx, ny, pow - 1, nrot);
        ans += (seg == 1 || seg == 2) ? add : (sub_square_size - add - 1);
        return ans;
    }

    int n;
    int K; // 2^K >= n
    vector<Query> queries;

    explicit MoHilbert(int n) : n(n) {
        K = 1;
        while ((1 << K) < n) K++;
    }

    void add_query(int l, int r, int id) {
        assert(0 <= l && l <= r && r < n);
        queries.push_back({l, r, id, hilbert_order(l, r, K + 1)});
    }

    template <typename AddFunc, typename RemoveFunc, typename ReportFunc>
    void solve(AddFunc add, RemoveFunc remove, ReportFunc report) {
        sort(queries.begin(), queries.end());

        int cur_l = 0, cur_r = -1;
        for (const auto& q : queries) {
            while (cur_l > q.l) add(--cur_l);
            while (cur_r < q.r) add(++cur_r);
            while (cur_l < q.l) remove(cur_l++);
            while (cur_r > q.r) remove(cur_r--);
            report(q.id);
        }
    }
};
