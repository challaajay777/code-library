// Algorithm: Burstsort String Sorting
// Purpose: High-performance cache-efficient string sorting using trie node bursts into bucket arrays.
// Time Complexity: O(N * L)
// Space Complexity: O(N * L)
// Preconditions: Vector of strings to be sorted lexicographically.

#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>

class BurstSort {
    static const int THRESHOLD = 16;
    struct Node {
        std::vector<std::string> bucket;
        std::vector<Node*> children;
        bool is_trie;
        Node() : is_trie(false) {}
    };

    Node* root;

    void insert(Node* node, const std::string& s, size_t depth) {
        if (!node->is_trie) {
            node->bucket.push_back(s);
            if (node->bucket.size() > THRESHOLD && depth < 20) {
                burst(node, depth);
            }
        } else {
            if (depth == s.size()) {
                node->bucket.push_back(s);
            } else {
                unsigned char ch = s[depth];
                if (!node->children[ch]) node->children[ch] = new Node();
                insert(node->children[ch], s, depth + 1);
            }
        }
    }

    void burst(Node* node, size_t depth) {
        node->is_trie = true;
        node->children.assign(256, nullptr);
        std::vector<std::string> old = std::move(node->bucket);
        for (const auto& str : old) {
            if (depth == str.size()) {
                node->bucket.push_back(str);
            } else {
                unsigned char ch = str[depth];
                if (!node->children[ch]) node->children[ch] = new Node();
                insert(node->children[ch], str, depth + 1);
            }
        }
    }

    void collect(Node* node, std::vector<std::string>& out) {
        if (!node) return;
        if (!node->is_trie) {
            std::sort(node->bucket.begin(), node->bucket.end());
            for (const auto& s : node->bucket) out.push_back(s);
        } else {
            for (const auto& s : node->bucket) out.push_back(s);
            for (int c = 0; c < 256; ++c) {
                collect(node->children[c], out);
            }
        }
    }

public:
    BurstSort() {
        root = new Node();
    }

    std::vector<std::string> sort(const std::vector<std::string>& input) {
        for (const auto& s : input) insert(root, s, 0);
        std::vector<std::string> result;
        collect(root, result);
        return result;
    }
};

int main() {
    std::vector<std::string> arr = {"banana", "apple", "app", "band", "bandana", "cat"};
    BurstSort bs;
    auto sorted = bs.sort(arr);
    std::vector<std::string> expected = arr;
    std::sort(expected.begin(), expected.end());
    assert(sorted == expected);
    return 0;
}
