#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Partition Labels
// Purpose: Partitions a string into as many parts as possible so that each letter appears in at most one part in O(N).
// Time Complexity: O(N) time
// Space Complexity: O(26) space
// Preconditions: String of lowercase English letters.

class PartitionLabels {
public:
    static std::vector<int> partition_labels(const std::string& s) {
        std::vector<int> last(26, 0);
        for (int i = 0; i < (int)s.size(); ++i) {
            last[s[i] - 'a'] = i;
        }

        std::vector<int> partitions;
        int anchor = 0, end = 0;

        for (int i = 0; i < (int)s.size(); ++i) {
            end = std::max(end, last[s[i] - 'a']);
            if (i == end) {
                partitions.push_back(i - anchor + 1);
                anchor = i + 1;
            }
        }
        return partitions;
    }
};

int main() {
    std::string s = "ababcbacadefegdehijhklij";
    auto parts = PartitionLabels::partition_labels(s);
    std::vector<int> expected = {9, 7, 8};
    assert(parts == expected);

    std::cout << "partition_labels tests passed successfully.\n";
    return 0;
}
