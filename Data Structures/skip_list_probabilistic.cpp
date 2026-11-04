// Algorithm: Probabilistic Skip List
// Purpose: Maintains sorted collection supporting search, insert, and delete in O(log N) average time.
// Time Complexity: O(log N) average
// Space Complexity: O(N)
// Preconditions: Comparable integer keys.

#include <iostream>
#include <vector>
#include <random>
#include <cassert>

class SkipList {
    static const int MAX_LVL = 16;
    struct Node {
        int key;
        std::vector<Node*> forward;
        Node(int k, int lvl) : key(k), forward(lvl + 1, nullptr) {}
    };

    Node* header;
    int level;
    std::mt19937 rng;

    int random_level() {
        int lvl = 0;
        while ((rng() & 1) && lvl < MAX_LVL - 1) lvl++;
        return lvl;
    }

public:
    SkipList() : level(0), rng(1337) {
        header = new Node(-1, MAX_LVL);
    }

    bool search(int key) {
        Node* cur = header;
        for (int i = level; i >= 0; --i) {
            while (cur->forward[i] && cur->forward[i]->key < key) {
                cur = cur->forward[i];
            }
        }
        cur = cur->forward[0];
        return cur && cur->key == key;
    }

    void insert(int key) {
        std::vector<Node*> update(MAX_LVL);
        Node* cur = header;
        for (int i = level; i >= 0; --i) {
            while (cur->forward[i] && cur->forward[i]->key < key) {
                cur = cur->forward[i];
            }
            update[i] = cur;
        }
        cur = cur->forward[0];

        if (!cur || cur->key != key) {
            int rlevel = random_level();
            if (rlevel > level) {
                for (int i = level + 1; i <= rlevel; ++i) update[i] = header;
                level = rlevel;
            }
            Node* n = new Node(key, rlevel);
            for (int i = 0; i <= rlevel; ++i) {
                n->forward[i] = update[i]->forward[i];
                update[i]->forward[i] = n;
            }
        }
    }
};

int main() {
    SkipList sl;
    sl.insert(3);
    sl.insert(6);
    sl.insert(7);
    sl.insert(9);

    assert(sl.search(6));
    assert(!sl.search(4));
    return 0;
}
