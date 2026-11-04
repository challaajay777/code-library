// Algorithm: Space-Efficient Bloom Filter
// Purpose: Probabilistic membership check with zero false negatives and low bounded false positives.
// Time Complexity: O(K) hash evaluations
// Space Complexity: O(M) bits
// Preconditions: String elements.

#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <cassert>

class BloomFilter {
    static const int M = 10007;
    std::bitset<M> bits;

    size_t hash1(const std::string& s) const {
        size_t h = 5381;
        for (char c : s) h = ((h << 5) + h) + c;
        return h % M;
    }

    size_t hash2(const std::string& s) const {
        size_t h = 0;
        for (char c : s) h = c + (h << 6) + (h << 16) - h;
        return h % M;
    }

    size_t hash3(const std::string& s) const {
        size_t h = 0;
        for (char c : s) { h = (h * 131) + c; }
        return h % M;
    }

public:
    void add(const std::string& s) {
        bits.set(hash1(s));
        bits.set(hash2(s));
        bits.set(hash3(s));
    }

    bool possibly_contains(const std::string& s) const {
        return bits.test(hash1(s)) && bits.test(hash2(s)) && bits.test(hash3(s));
    }
};

int main() {
    BloomFilter bf;
    bf.add("apple");
    bf.add("banana");
    assert(bf.possibly_contains("apple"));
    assert(bf.possibly_contains("banana"));
    assert(!bf.possibly_contains("strawberry"));
    return 0;
}
