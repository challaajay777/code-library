#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Circular Next Greater Character
// Purpose: Finds the smallest character in a sorted circular list that is strictly greater than target.
// Time Complexity: O(log N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Non-empty sorted vector of characters.

class NextGreaterLetter {
public:
    static char next_greatest_letter(const std::vector<char>& letters, char target) {
        int low = 0, high = (int)letters.size() - 1;
        char ans = letters[0];

        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (letters[mid] > target) {
                ans = letters[mid];
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        return ans;
    }
};

int main() {
    std::vector<char> letters = {'c', 'f', 'j'};
    assert(NextGreaterLetter::next_greatest_letter(letters, 'a') == 'c');
    assert(NextGreaterLetter::next_greatest_letter(letters, 'c') == 'f');
    assert(NextGreaterLetter::next_greatest_letter(letters, 'd') == 'f');
    assert(NextGreaterLetter::next_greatest_letter(letters, 'j') == 'c'); // wraps

    std::cout << "find_smallest_letter_greater_than_target tests passed successfully.\n";
    return 0;
}
