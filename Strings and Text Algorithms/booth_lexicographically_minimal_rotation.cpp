#include <iostream>
#include <string>
#include <vector>
#include <cassert>

// Algorithm: Booth's Algorithm (Minimal String Rotation)
// Purpose: Finds the lexicographically minimal rotation of a string in O(N) time and O(N) auxiliary space.
// Time Complexity: O(N) time
// Space Complexity: O(N) auxiliary space
// Preconditions: Non-empty string.

class BoothMinimalRotation {
public:
    static int min_rotation_index(const std::string& s) {
        std::string s2 = s + s;
        int n = s2.size();
        std::vector<int> f(n, -1);
        int k = 0;

        for (int j = 1; j < n; ++j) {
            char sj = s2[j];
            int i = f[j - k - 1];
            while (i != -1 && sj != s2[k + i + 1]) {
                if (sj < s2[k + i + 1]) {
                    k = j - i - 1;
                }
                i = f[i];
            }
            if (sj != s2[k + i + 1]) {
                if (sj < s2[k]) {
                    k = j;
                }
                f[j - k] = -1;
            } else {
                f[j - k] = i + 1;
            }
        }
        return k;
    }
};

int main() {
    std::string s = "bbaaccaadd";
    int idx = BoothMinimalRotation::min_rotation_index(s);
    // Minimal rotation starts at "aaccaaddbb"
    std::string rot = s.substr(idx) + s.substr(0, idx);
    assert(rot == "aaccaaddbb");

    std::cout << "booth_lexicographically_minimal_rotation tests passed successfully.\n";
    return 0;
}
