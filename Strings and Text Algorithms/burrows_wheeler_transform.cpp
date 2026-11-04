#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Burrows-Wheeler Transform (BWT)
// Purpose: Reversible permutation of a string grouping identical characters together for block compression in O(N log N).
// Time Complexity: O(N log N) time
// Space Complexity: O(N) space
// Preconditions: String characters printable ASCII.

class BurrowsWheeler {
public:
    static std::string transform(std::string s) {
        s += '$'; // End marker
        int n = s.size();
        std::vector<std::string> rotations(n);

        for (int i = 0; i < n; ++i) {
            rotations[i] = s.substr(i) + s.substr(0, i);
        }
        std::sort(rotations.begin(), rotations.end());

        std::string bwt = "";
        for (int i = 0; i < n; ++i) {
            bwt.push_back(rotations[i].back());
        }
        return bwt;
    }
};

int main() {
    std::string s = "banana";
    std::string bwt = BurrowsWheeler::transform(s);
    assert(bwt == "annb$aa");

    std::cout << "burrows_wheeler_transform tests passed successfully.\n";
    return 0;
}
