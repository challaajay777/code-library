// Algorithm: Mo's Algorithm for Range Distinct Count
// Purpose: Answers offline range queries counting distinct elements in O((N + Q) sqrt(N)) time.
// Time Complexity: O((N + Q) sqrt(N))
// Space Complexity: O(N + Q)
// Preconditions: 0-indexed array, offline queries.

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cassert>

struct MoQuery {
    int l, r, id, block;
    bool operator<(const MoQuery& o) const {
        if (block != o.block) return block < o.block;
        return (block & 1) ? (r < o.r) : (r > o.r);
    }
};

std::vector<int> mo_distinct_elements(const std::vector<int>& a, const std::vector<std::pair<int, int>>& queries) {
    int n = a.size(), q = queries.size();
    int block_sz = std::max(1, (int)std::sqrt(n));

    std::vector<MoQuery> qs(q);
    for (int i = 0; i < q; ++i) {
        qs[i] = {queries[i].first, queries[i].second, i, queries[i].first / block_sz};
    }
    std::sort(qs.begin(), qs.end());

    std::vector<int> freq(1000005, 0);
    int distinct = 0;
    int cur_l = 0, cur_r = -1;

    auto add = [&](int idx) {
        if (++freq[a[idx]] == 1) distinct++;
    };

    auto remove = [&](int idx) {
        if (--freq[a[idx]] == 0) distinct--;
    };

    std::vector<int> ans(q);
    for (const auto& query : qs) {
        while (cur_l > query.l) add(--cur_l);
        while (cur_r < query.r) add(++cur_r);
        while (cur_l < query.l) remove(cur_l++);
        while (cur_r > query.r) remove(cur_r--);
        ans[query.id] = distinct;
    }
    return ans;
}

int main() {
    std::vector<int> a = {1, 2, 1, 3, 4, 2, 3};
    std::vector<std::pair<int, int>> queries = {{0, 3}, {1, 4}, {0, 6}};
    auto ans = mo_distinct_elements(a, queries);
    // [0, 3] is {1, 2, 1, 3} -> 3 distinct
    assert(ans[0] == 3);
    // [0, 6] is {1, 2, 1, 3, 4, 2, 3} -> 4 distinct
    assert(ans[2] == 4);
    return 0;
}
