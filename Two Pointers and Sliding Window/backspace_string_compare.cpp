#include <iostream>
#include <string>
#include <cassert>

// Algorithm: Backspace String Compare (Two Pointers Reverse)
// Purpose: Compares two typed strings containing backspaces '#' in O(N + M) time and O(1) auxiliary space.
// Time Complexity: O(N + M) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Strings containing lowercase letters and '#'.

class BackspaceStringCompare {
private:
    static int get_next_valid_char_index(const std::string& str, int index) {
        int backspaces = 0;
        while (index >= 0) {
            if (str[index] == '#') {
                backspaces++;
            } else if (backspaces > 0) {
                backspaces--;
            } else {
                break;
            }
            index--;
        }
        return index;
    }

public:
    static bool backspace_compare(const std::string& s, const std::string& t) {
        int i = s.size() - 1;
        int j = t.size() - 1;

        while (i >= 0 || j >= 0) {
            i = get_next_valid_char_index(s, i);
            j = get_next_valid_char_index(t, j);

            if (i >= 0 && j >= 0 && s[i] != t[j]) {
                return false;
            }
            if ((i >= 0) != (j >= 0)) {
                return false;
            }
            i--;
            j--;
        }
        return true;
    }
};

int main() {
    assert(BackspaceStringCompare::backspace_compare("ab#c", "ad#c") == true);
    assert(BackspaceStringCompare::backspace_compare("ab##", "c#d#") == true);
    assert(BackspaceStringCompare::backspace_compare("a#c", "b") == false);

    std::cout << "backspace_string_compare tests passed successfully.\n";
    return 0;
}
