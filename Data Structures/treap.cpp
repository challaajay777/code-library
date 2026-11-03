// Algorithm: Treap (Cartesian Tree)
// Supports: Dynamic balanced binary search tree, insert, erase, split, merge, k-th element, rank query
// Indexing: 1-based order statistics (k-th element)
// Complexity: O(log n) expected per operation, O(n) memory
// Preconditions: Keys are strictly comparable; priorities generated randomly via mt19937

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

template <typename Key>
struct Treap {
    struct Node {
        Key key;
        uint32_t priority;
        int sz;
        Node *l, *r;
        Node(Key k, uint32_t p) : key(k), priority(p), sz(1), l(nullptr), r(nullptr) {}
    };

    Node* root = nullptr;
    mt19937 rng;

    Treap(uint32_t seed = 1337) : rng(seed) {}
    ~Treap() { clear(root); }

private:
    void clear(Node* t) {
        if (!t) return;
        clear(t->l);
        clear(t->r);
        delete t;
    }

    int get_sz(Node* t) const { return t ? t->sz : 0; }
    void update(Node* t) {
        if (t) t->sz = 1 + get_sz(t->l) + get_sz(t->r);
    }

    // Splits treap t into l (keys <= key) and r (keys > key)
    void split(Node* t, Key key, Node*& l, Node*& r) {
        if (!t) {
            l = r = nullptr;
            return;
        }
        if (t->key <= key) {
            split(t->r, key, t->r, r);
            l = t;
        } else {
            split(t->l, key, l, t->l);
            r = t;
        }
        update(t);
    }

    // Merges two treaps l and r assuming all keys in l <= all keys in r
    void merge(Node*& t, Node* l, Node* r) {
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

public:
    int size() const { return get_sz(root); }
    bool empty() const { return root == nullptr; }

    void insert(Key key) {
        Node *l, *r;
        split(root, key, l, r);
        Node* mid = new Node(key, rng());
        merge(l, l, mid);
        merge(root, l, r);
    }

    void erase(Key key) {
        Node *l, *mid, *r;
        split(root, key - 1, l, r);
        split(r, key, mid, r);
        if (mid) {
            Node* old_mid = mid;
            merge(mid, mid->l, mid->r);
            delete old_mid;
        }
        merge(r, mid, r);
        merge(root, l, r);
    }

    bool contains(Key key) {
        Node* cur = root;
        while (cur) {
            if (cur->key == key) return true;
            cur = (key < cur->key) ? cur->l : cur->r;
        }
        return false;
    }

    // 1-based k-th smallest element
    Key find_kth(int k) {
        assert(1 <= k && k <= size());
        Node* cur = root;
        while (cur) {
            int left_sz = get_sz(cur->l);
            if (k == left_sz + 1) return cur->key;
            if (k <= left_sz) {
                cur = cur->l;
            } else {
                k -= left_sz + 1;
                cur = cur->r;
            }
        }
        assert(false);
        return Key();
    }
};
