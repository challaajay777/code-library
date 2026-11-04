// Algorithm: Link-Cut Tree (Dynamic Tree Path Aggregates)
// Purpose: Maintains forest of trees supporting link, cut, and path sum queries in O(log N) amortized time.
// Time Complexity: O(log N) amortized per operation
// Space Complexity: O(N)
// Preconditions: Forest of rooted/unrooted trees.

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

struct LinkCutTree {
    struct Node {
        int ch[2] = {0, 0};
        int p = 0;
        long long val = 0, sum = 0;
        bool rev = false;
    };
    std::vector<Node> tree;

    LinkCutTree(int n) : tree(n + 1) {}

    bool is_root(int x) {
        return tree[tree[x].p].ch[0] != x && tree[tree[x].p].ch[1] != x;
    }

    void push_up(int x) {
        tree[x].sum = tree[x].val + tree[tree[x].ch[0]].sum + tree[tree[x].ch[1]].sum;
    }

    void push_down(int x) {
        if (tree[x].rev) {
            std::swap(tree[x].ch[0], tree[x].ch[1]);
            if (tree[x].ch[0]) tree[tree[x].ch[0]].rev ^= 1;
            if (tree[x].ch[1]) tree[tree[x].ch[1]].rev ^= 1;
            tree[x].rev = false;
        }
    }

    void rotate(int x) {
        int y = tree[x].p, z = tree[y].p;
        int k = (tree[y].ch[1] == x);
        if (!is_root(y)) tree[z].ch[tree[z].ch[1] == y] = x;
        tree[x].p = z;
        tree[y].ch[k] = tree[x].ch[k ^ 1];
        if (tree[x].ch[k ^ 1]) tree[tree[x].ch[k ^ 1]].p = y;
        tree[x].ch[k ^ 1] = y;
        tree[y].p = x;
        push_up(y);
        push_up(x);
    }

    void splay(int x) {
        std::vector<int> st = {x};
        for (int i = x; !is_root(i); i = tree[i].p) st.push_back(tree[i].p);
        while (!st.empty()) {
            push_down(st.back());
            st.pop_back();
        }

        while (!is_root(x)) {
            int y = tree[x].p, z = tree[y].p;
            if (!is_root(y)) {
                if ((tree[y].ch[1] == x) ^ (tree[z].ch[1] == y)) rotate(x);
                else rotate(y);
            }
            rotate(x);
        }
    }

    void access(int x) {
        for (int t = 0; x; t = x, x = tree[x].p) {
            splay(x);
            tree[x].ch[1] = t;
            push_up(x);
        }
    }

    void make_root(int x) {
        access(x);
        splay(x);
        tree[x].rev ^= 1;
    }

    void link(int x, int y) {
        make_root(x);
        tree[x].p = y;
    }

    void cut(int x, int y) {
        make_root(x);
        access(y);
        splay(y);
        if (tree[y].ch[0] == x && !tree[x].ch[1]) {
            tree[y].ch[0] = 0;
            tree[x].p = 0;
            push_up(y);
        }
    }

    long long query_path(int x, int y) {
        make_root(x);
        access(y);
        splay(y);
        return tree[y].sum;
    }
};

int main() {
    LinkCutTree lct(3);
    lct.tree[1].val = lct.tree[1].sum = 10;
    lct.tree[2].val = lct.tree[2].sum = 20;
    lct.tree[3].val = lct.tree[3].sum = 30;

    lct.link(1, 2);
    lct.link(2, 3);
    assert(lct.query_path(1, 3) == 60);

    lct.cut(1, 2);
    assert(lct.query_path(2, 3) == 50);
    return 0;
}
