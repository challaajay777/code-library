// Algorithm: Implicit Treap (Dynamic Array / Rope with Range Reversal)
// Supports: Dynamic sequence indexing, range reversal lazy tag, split by size, merge
// Indexing: 0-based sequence positions [0, size - 1]
// Complexity: O(log n) expected per range operation, O(n) memory
// Preconditions: Range [l, r] satisfies 0 <= l <= r < size

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

template <typename T>
struct ImplicitTreap {
    struct Node {
        T val;
        uint32_t priority;
        int sz;
        bool rev;
        Node *l, *r;
        Node(T v, uint32_t p) : val(v), priority(p), sz(1), rev(false), l(nullptr), r(nullptr) {}
    };

    Node* root = nullptr;
    mt19937 rng;

    ImplicitTreap(uint32_t seed = 4242) : rng(seed) {}
    ~ImplicitTreap() { clear(root); }

private:
    void clear(Node* t) {
        if (!t) return;
        clear(t->l);
        clear(t->r);
        delete t;
    }

    int get_sz(Node* t) const { return t ? t->sz : 0; }

    void push(Node* t) {
        if (t && t->rev) {
            t->rev = false;
            swap(t->l, t->r);
            if (t->l) t->l->rev ^= true;
            if (t->r) t->r->rev ^= true;
        }
    }

    void update(Node* t) {
        if (t) t->sz = 1 + get_sz(t->l) + get_sz(t->r);
    }

    // Splits t into l (first k elements) and r (remaining elements)
    void split(Node* t, int k, Node*& l, Node*& r) {
        if (!t) {
            l = r = nullptr;
            return;
        }
        push(t);
        int left_sz = get_sz(t->l);
        if (k <= left_sz) {
            split(t->l, k, l, t->l);
            r = t;
        } else {
            split(t->r, k - left_sz - 1, t->r, r);
            l = t;
        }
        update(t);
    }

    void merge(Node*& t, Node* l, Node* r) {
        push(l);
        push(r);
        if (!l || !r) {
            t = l ? l : r;
            return;
        }
        if (l->priority > r->priority) {
            merge(l->r, l->r, r);
            t = l;
        } else {
            merge(r->l, l, r->l);
            t = r;
        }
        update(t);
    }

    void to_vector(Node* t, vector<T>& res) {
        if (!t) return;
        push(t);
        to_vector(t->l, res);
        res.push_back(t->val);
        to_vector(t->r, res);
    }

public:
    int size() const { return get_sz(root); }

    void push_back(T val) {
        Node* n = new Node(val, rng());
        merge(root, root, n);
    }

    // Reverses subsequence [l, r] in O(log n)
    void reverse_range(int l, int r) {
        assert(0 <= l && l <= r && r < size());
        Node *t1, *t2, *t3;
        split(root, l, t1, t2);
        split(t2, r - l + 1, t2, t3);
        if (t2) t2->rev ^= true;
        merge(root, t1, t2);
        merge(root, root, t3);
    }

    vector<T> dump() {
        vector<T> res;
        to_vector(root, res);
        return res;
    }
};
