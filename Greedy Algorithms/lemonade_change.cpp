#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Lemonade Change
// Purpose: Determines whether correct change ($5, $10) can be provided to every customer paying with $5, $10, or $20.
// Time Complexity: O(N) time single pass
// Space Complexity: O(1) space
// Preconditions: Bills in {5, 10, 20}.

class LemonadeChange {
public:
    static bool lemonade_change(const std::vector<int>& bills) {
        int five = 0, ten = 0;

        for (int bill : bills) {
            if (bill == 5) {
                five++;
            } else if (bill == 10) {
                if (five == 0) return false;
                five--;
                ten++;
            } else { // bill == 20
                if (ten > 0 && five > 0) {
                    ten--;
                    five--;
                } else if (five >= 3) {
                    five -= 3;
                } else {
                    return false;
                }
            }
        }
        return true;
    }
};

int main() {
    assert(LemonadeChange::lemonade_change({5, 5, 5, 10, 20}) == true);
    assert(LemonadeChange::lemonade_change({5, 5, 10, 10, 20}) == false);

    std::cout << "lemonade_change tests passed successfully.\n";
    return 0;
}
