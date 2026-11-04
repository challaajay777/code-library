// Algorithm: De Bruijn Graph Eulerian Reconstruction
// Purpose: Constructs De Bruijn graph from k-mer reads and reconstructs original sequence via Eulerian path.
// Time Complexity: O(N * K)
// Space Complexity: O(N * K)
// Preconditions: Collection of k-mer strings of identical length.

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <cassert>
#include <algorithm>

std::string assemble_from_kmers(const std::vector<std::string>& kmers) {
    std::unordered_map<std::string, std::vector<std::string>> adj;
    std::unordered_map<std::string, int> in_deg, out_deg;

    for (const auto& kmer : kmers) {
        std::string u = kmer.substr(0, kmer.size() - 1);
        std::string v = kmer.substr(1);
        adj[u].push_back(v);
        out_deg[u]++;
        in_deg[v]++;
    }

    std::string start = kmers[0].substr(0, kmers[0].size() - 1);
    for (const auto& [u, deg] : out_deg) {
        if (deg - in_deg[u] == 1) {
            start = u;
            break;
        }
    }

    std::vector<std::string> path;
    std::vector<std::string> st = {start};

    while (!st.empty()) {
        std::string u = st.back();
        if (!adj[u].empty()) {
            std::string v = adj[u].back();
            adj[u].pop_back();
            st.push_back(v);
        } else {
            path.push_back(u);
            st.pop_back();
        }
    }
    std::reverse(path.begin(), path.end());

    std::string result = path[0];
    for (size_t i = 1; i < path.size(); ++i) {
        result.push_back(path[i].back());
    }
    return result;
}

int main() {
    std::vector<std::string> kmers = {"ATG", "TGG", "GGC", "GCG", "CGT"};
    std::string genome = assemble_from_kmers(kmers);
    assert(genome == "ATGGCGT");
    return 0;
}
