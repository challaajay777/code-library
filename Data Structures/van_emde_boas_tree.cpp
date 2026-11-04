// Algorithm: Van Emde Boas (vEB) Tree
// Purpose: Supports insert, member check, min/max in O(log log U) time.
// Time Complexity: O(log log U)
// Space Complexity: O(U)
// Preconditions: Universe size U = 2^(2^k).

#include <iostream>
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
