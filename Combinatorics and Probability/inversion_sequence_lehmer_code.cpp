#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Lehmer Code and Factoradic Permutation Rank
// Purpose: Converts permutation to its unique Lehmer code (factoradic representation) and rank in O(N log N).
// Time Complexity: O(N log N) time using Fenwick tree
// Space Complexity: O(N) space
// Preconditions: Permutation of numbers 1..N.

class LehmerCode {
private:
    struct Fenwick {
        int n;
        std::vector<int> tree;
        explicit Fenwick(int sz) : n(sz), tree(sz + 1, 0) {}
        void update(int i, int delta) {
            for (; i <= n; i += i & -i) tree[i] += delta;
        }
        int query(int i) const {
            int s = 0;
            for (; i > 0; i -= i & -i) s += tree[i];
            return s;
        }
    };

public:
    static std::vector<int> get_lehmer_code(const std::vector<int>& p) {
        int n = p.size();
        Fenwick ft(n);
        std::vector<int> code(n);

        for (int i = 0; i < n; ++i) {
            int smaller_seen = ft.query(p[i]);
            code[i] = (p[i] - 1) - smaller_seen;
            ft.update(p[i], 1);
        }
        return code;
    }
};

int main() {
    std::vector<int> p = {3, 1, 4, 2};
    auto code = LehmerCode::get_lehmer_code(p);
    // 3: 2 smaller (1, 2) to the right
    // 1: 0 smaller to the right
    // 4: 1 smaller (2) to the right
    // 2: 0 smaller
    // Code: [2, 0, 1, 0]
    std::vector<int> expected = {2, 0, 1, 0};
    assert(code == expected);

    std::cout << "inversion_sequence_lehmer_code tests passed successfully.\n";
    return 0;
}
