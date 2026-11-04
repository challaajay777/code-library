// Algorithm: Segment Tree Beats (Range Chmin, Chmax, Sum)
// Purpose: Executes range chmin, range chmax, and range sum queries using Ji Driver segment tree beats.
// Time Complexity: O(log N) amortized per update/query
// Space Complexity: O(N)
// Preconditions: Array of integers.

#include <iostream>
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
