#include <iostream>
#include <string>
#include <vector>
#include <cassert>

// Algorithm: Restore IP Addresses
// Purpose: Restores all possible valid IPv4 address strings by placing dots into a raw digit string.
// Time Complexity: O(3^4) = O(1) bounded time
// Space Complexity: O(1) auxiliary space
// Preconditions: String of digits.

class RestoreIPAddresses {
private:
    static bool is_valid_part(const std::string& s) {
        if (s.empty() || s.size() > 3) return false;
        if (s.size() > 1 && s[0] == '0') return false;
        int val = std::stoi(s);
        return val >= 0 && val <= 255;
    }

    static void dfs(int idx, int parts, const std::string& s, std::string cur,
                    std::vector<std::string>& res) {
        if (parts == 4) {
            if (idx == (int)s.size()) res.push_back(cur);
            return;
        }

        for (int len = 1; len <= 3 && idx + len <= (int)s.size(); ++len) {
            std::string sub = s.substr(idx, len);
            if (is_valid_part(sub)) {
                dfs(idx + len, parts + 1, s, cur + (parts == 0 ? "" : ".") + sub, res);
            }
        }
    }

public:
    static std::vector<std::string> restore_ip(const std::string& s) {
        std::vector<std::string> res;
        dfs(0, 0, s, "", res);
        return res;
    }
};

int main() {
    auto res = RestoreIPAddresses::restore_ip("25525511135");
    assert(res.size() == 2);
    assert(res[0] == "255.255.11.135");
    assert(res[1] == "255.255.111.35");

    std::cout << "restore_ip_addresses tests passed successfully.\n";
    return 0;
}
