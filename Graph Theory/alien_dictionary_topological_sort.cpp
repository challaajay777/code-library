// Algorithm: Alien Dictionary Character Order via Topo Sort
// Purpose: Reconstructs the lexicographical order of characters from a sorted list of foreign words.
// Time Complexity: O(TotalCharacters + Sigma)
// Space Complexity: O(Sigma)
// Preconditions: Sorted word list over lowercase Latin characters.

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <cassert>

std::string alien_order(const std::vector<std::string>& words) {
    std::unordered_map<char, std::unordered_set<char>> adj;
    std::unordered_map<char, int> in_deg;

    for (const auto& w : words) {
        for (char c : w) in_deg[c] = 0;
    }

    for (size_t i = 0; i < words.size() - 1; ++i) {
        const std::string& w1 = words[i];
        const std::string& w2 = words[i + 1];
        if (w1.size() > w2.size() && w1.substr(0, w2.size()) == w2) return "";

        for (size_t j = 0; j < std::min(w1.size(), w2.size()); ++j) {
            if (w1[j] != w2[j]) {
                if (!adj[w1[j]].count(w2[j])) {
                    adj[w1[j]].insert(w2[j]);
                    in_deg[w2[j]]++;
                }
                break;
            }
        }
    }

    std::queue<char> q;
    for (auto [c, deg] : in_deg) {
        if (deg == 0) q.push(c);
    }

    std::string order;
    while (!q.empty()) {
        char c = q.front();
        q.pop();
        order.push_back(c);
        for (char neighbor : adj[c]) {
            if (--in_deg[neighbor] == 0) q.push(neighbor);
        }
    }
    if (order.size() != in_deg.size()) return "";
    return order;
}

int main() {
    std::vector<std::string> words = {"wrt", "wrf", "er", "ett", "rftt"};
    std::string order = alien_order(words);
    assert(order == "wertf");
    return 0;
}
