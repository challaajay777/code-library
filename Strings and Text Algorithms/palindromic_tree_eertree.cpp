#include <iostream>
#include <string>
#include <vector>
#include <cassert>

// Algorithm: Palindromic Tree (EERTREE)
// Purpose: Online data structure maintaining all distinct palindromic substrings and their occurrences in O(N) time.
// Time Complexity: O(N) total time for string length N
// Space Complexity: O(N * Sigma) space
// Preconditions: Alphabet consists of lowercase English letters.

class EerTree {
private:
    struct Node {
        int next[26];
        int len;
        int link;
        int count;
        Node(int l = 0, int lnk = 0) : len(l), link(lnk), count(0) {
            for (int i = 0; i < 26; ++i) next[i] = 0;
        }
    };

    std::vector<Node> tree;
    std::string s;
    int last;

    int get_link(int u, int p) {
        while (p - 1 - tree[u].len < 0 || s[p - 1 - tree[u].len] != s[p]) {
            u = tree[u].link;
        }
        return u;
    }

public:
    EerTree() {
        // Node 1: root with len = -1 (odd root)
        // Node 2: root with len = 0 (even root)
        tree.emplace_back(); // 0 dummy
        tree.emplace_back(-1, 1);
        tree.emplace_back(0, 1);
        last = 2;
    }

    void add_char(char c) {
        s.push_back(c);
        int p = s.size() - 1;
        int ch = c - 'a';
        int cur = get_link(last, p);

        if (!tree[cur].next[ch]) {
            int node = tree.size();
            tree.emplace_back(tree[cur].len + 2, tree[get_link(tree[cur].link, p)].next[ch]);
            if (tree.back().link == 0) tree.back().link = 2;
            tree[cur].next[ch] = node;
        }
        last = tree[cur].next[ch];
        tree[last].count++;
    }

    int num_distinct_palindromes() const {
        return tree.size() - 3;
    }
};

int main() {
    EerTree et;
    for (char c : std::string("abacaba")) {
        et.add_char(c);
    }
    // Distinct palindromes in "abacaba": "a", "b", "c", "aba", "aca", "bacab", "abacaba" -> 7
    assert(et.num_distinct_palindromes() == 7);

    std::cout << "palindromic_tree_eertree tests passed successfully.\n";
    return 0;
}
