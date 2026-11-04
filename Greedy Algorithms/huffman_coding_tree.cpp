#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <map>
#include <cassert>

// Algorithm: Huffman Coding Tree
// Purpose: Constructs optimal prefix-free variable length binary codes for character frequencies using min-heap in O(N log N).
// Time Complexity: O(N log N) time
// Space Complexity: O(N) tree node storage
// Preconditions: Frequencies positive; alphabet size N >= 1.

struct HuffmanNode {
    char ch;
    int freq;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
    HuffmanNode(int f, HuffmanNode* l, HuffmanNode* r) : ch('$'), freq(f), left(l), right(r) {}
};

struct CompareNode {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->freq > b->freq;
    }
};

class HuffmanCoding {
private:
    static void generate_codes(HuffmanNode* root, const std::string& prefix, std::map<char, std::string>& codes) {
        if (!root) return;
        if (!root->left && !root->right) {
            codes[root->ch] = prefix.empty() ? "0" : prefix;
            return;
        }
        generate_codes(root->left, prefix + "0", codes);
        generate_codes(root->right, prefix + "1", codes);
    }

    static void free_tree(HuffmanNode* root) {
        if (!root) return;
        free_tree(root->left);
        free_tree(root->right);
        delete root;
    }

public:
    static std::map<char, std::string> build_codes(const std::vector<std::pair<char, int>>& freqs) {
        std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, CompareNode> pq;
        for (const auto& p : freqs) {
            pq.push(new HuffmanNode(p.first, p.second));
        }

        while (pq.size() > 1) {
            HuffmanNode* l = pq.top(); pq.pop();
            HuffmanNode* r = pq.top(); pq.pop();
            HuffmanNode* parent = new HuffmanNode(l->freq + r->freq, l, r);
            pq.push(parent);
        }

        HuffmanNode* root = pq.top();
        std::map<char, std::string> codes;
        generate_codes(root, "", codes);
        free_tree(root);
        return codes;
    }
};

int main() {
    std::vector<std::pair<char, int>> freqs = {{'a', 5}, {'b', 9}, {'c', 12}, {'d', 13}, {'e', 16}, {'f', 45}};
    auto codes = HuffmanCoding::build_codes(freqs);
    assert(codes.size() == 6);
    // 'f' has highest frequency, so code length must be minimal
    assert(codes['f'].size() == 1 || codes['f'].size() == 2);

    std::cout << "huffman_coding_tree tests passed successfully.\n";
    return 0;
}
