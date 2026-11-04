// Algorithm: Ukkonen Online Suffix Tree Construction
// Purpose: Builds the complete suffix tree of a string in linear time online.
// Time Complexity: O(N * Sigma)
// Space Complexity: O(N * Sigma)
// Preconditions: String terminated with a unique character or processed fully.

#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>

class SuffixTree {
    struct Node {
        int l, r, parent, link;
        int next[256];
        Node(int l = 0, int r = 0, int parent = -1) : l(l), r(r), parent(parent), link(-1) {
            std::fill(next, next + 256, -1);
        }
        int len() const { return r - l; }
    };

    std::string s;
    std::vector<Node> tree;
    int root, active_node, active_edge, active_len, rem, pos;

public:
    SuffixTree(const std::string& str) : s(str) {
        root = new_node(-1, -1);
        active_node = root;
        active_edge = -1;
        active_len = 0;
        rem = 0;
        pos = 0;
        for (pos = 0; pos < (int)s.size(); ++pos) {
            extend(pos);
        }
    }

private:
    int new_node(int l, int r, int p = -1) {
        tree.emplace_back(l, r, p);
        return tree.size() - 1;
    }

    void extend(int i) {
        rem++;
        int last_created = -1;
        while (rem > 0) {
            if (active_len == 0) active_edge = i;
            unsigned char edge_char = s[active_edge];
            if (tree[active_node].next[edge_char] == -1) {
                int leaf = new_node(i, s.size(), active_node);
                tree[active_node].next[edge_char] = leaf;
                if (last_created != -1) {
                    tree[last_created].link = active_node;
                    last_created = -1;
                }
            } else {
                int next_node = tree[active_node].next[edge_char];
                int edge_len = tree[next_node].len();
                if (active_len >= edge_len) {
                    active_edge += edge_len;
                    active_len -= edge_len;
                    active_node = next_node;
                    continue;
                }
                if (s[tree[next_node].l + active_len] == s[i]) {
                    active_len++;
                    if (last_created != -1) {
                        tree[last_created].link = active_node;
                    }
                    break;
                }
                int split = new_node(tree[next_node].l, tree[next_node].l + active_len, active_node);
                tree[active_node].next[edge_char] = split;
                int leaf = new_node(i, s.size(), split);
                tree[split].next[(unsigned char)s[i]] = leaf;
                tree[next_node].l += active_len;
                tree[next_node].parent = split;
                tree[split].next[(unsigned char)s[tree[next_node].l]] = next_node;

                if (last_created != -1) tree[last_created].link = split;
                last_created = split;
            }
            rem--;
            if (active_node == root && active_len > 0) {
                active_len--;
                active_edge = i - rem + 1;
            } else if (active_node != root) {
                active_node = (tree[active_node].link != -1) ? tree[active_node].link : root;
            }
        }
    }

public:
    bool search(const std::string& pat) {
        int cur = root;
        int i = 0;
        while (i < (int)pat.size()) {
            unsigned char ch = pat[i];
            int nxt = tree[cur].next[ch];
            if (nxt == -1) return false;
            int l = tree[nxt].l, r = tree[nxt].r;
            for (int k = l; k < r && i < (int)pat.size(); ++k, ++i) {
                if (s[k] != pat[i]) return false;
            }
            cur = nxt;
        }
        return true;
    }
};

int main() {
    std::string text = "banana$";
    SuffixTree st(text);
    assert(st.search("nan"));
    assert(st.search("ana"));
    assert(st.search("banana"));
    assert(!st.search("apple"));
    return 0;
}
