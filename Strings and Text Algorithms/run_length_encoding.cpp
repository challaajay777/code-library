#include <iostream>
#include <string>
#include <cassert>

// Algorithm: Run-Length Encoding and Decoding
// Purpose: Encodes contiguous sequences of identical characters into count and character pairs, and reconstructs original string in O(N).
// Time Complexity: O(N) time
// Space Complexity: O(N) space
// Preconditions: ASCII string.

class RunLengthEncoding {
public:
    static std::string encode(const std::string& s) {
        if (s.empty()) return "";
        std::string res = "";
        size_t i = 0;

        while (i < s.size()) {
            size_t j = i;
            while (j < s.size() && s[j] == s[i]) j++;
            res += std::to_string(j - i);
            res.push_back(s[i]);
            i = j;
        }
        return res;
    }

    static std::string decode(const std::string& encoded) {
        std::string res = "";
        size_t i = 0;

        while (i < encoded.size()) {
            int count = 0;
            while (i < encoded.size() && std::isdigit(encoded[i])) {
                count = count * 10 + (encoded[i] - '0');
                i++;
            }
            char c = encoded[i++];
            res.append(count, c);
        }
        return res;
    }
};

int main() {
    std::string s = "WWWWWWAAAAAABBBBCCCC";
    std::string enc = RunLengthEncoding::encode(s);
    assert(enc == "6W6A4B4C");
    assert(RunLengthEncoding::decode(enc) == s);

    std::cout << "run_length_encoding tests passed successfully.\n";
    return 0;
}
