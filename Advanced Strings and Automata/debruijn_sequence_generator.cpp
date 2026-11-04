// Algorithm: De Bruijn Sequence Generator via Lyndon Words
// Purpose: Generates the minimal cyclic sequence of order n containing all k^n substrings exactly once.
// Time Complexity: O(k^n)
// Space Complexity: O(k^n)
// Preconditions: k >= 1, n >= 1.

#include <iostream>
#include <vector>
#include <string>
#include <cassert>

class DeBruijn {
    int k, n;
    std::vector<int> a;
    std::vector<int> sequence;

    void db(int t, int p) {
        if (t > n) {
            if (n % p == 0) {
                for (int i = 1; i <= p; ++i) {
                    sequence.push_back(a[i]);
                }
            }
        } else {
            a[t] = a[t - p];
            db(t + 1, p);
            for (int j = a[t - p] + 1; j < k; ++j) {
                a[t] = j;
                db(t + 1, t);
            }
        }
    }

public:
    DeBruijn(int alphabet_size, int order) : k(alphabet_size), n(order) {
        a.assign(k * n + 1, 0);
    }

    std::vector<int> generate() {
        sequence.clear();
        db(1, 1);
        return sequence;
    }
};

int main() {
    // For alphabet {0, 1} and order 3: sequence length should be 2^3 = 8
    DeBruijn db(2, 3);
    auto seq = db.generate();
    assert((int)seq.size() == 8);

    // Verify all 8 length-3 bit strings appear cyclically
    std::vector<bool> seen(8, false);
    for (int i = 0; i < 8; ++i) {
        int val = (seq[i] << 2) | (seq[(i + 1) % 8] << 1) | seq[(i + 2) % 8];
        seen[val] = true;
    }
    for (bool b : seen) assert(b);

    return 0;
}
