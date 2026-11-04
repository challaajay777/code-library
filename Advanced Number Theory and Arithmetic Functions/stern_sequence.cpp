#include <iostream>
#include <cassert>

// Algorithm: Stern's Diatomic Sequence (Fusc Function)
// Purpose: Calculates fusc(N) where fusc(2n) = fusc(n) and fusc(2n+1) = fusc(n) + fusc(n+1) in O(log N) time.
// Time Complexity: O(log N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: N >= 0.

class SternSequence {
public:
    static long long fusc(long long n) {
        long long a = 1, b = 0;
        while (n > 0) {
            if (n & 1) {
                b += a;
            } else {
                a += b;
            }
            n >>= 1;
        }
        return b;
    }
};

int main() {
    // fusc(0)=0, fusc(1)=1, fusc(2)=1, fusc(3)=2, fusc(4)=1, fusc(5)=3
    assert(SternSequence::fusc(0) == 0);
    assert(SternSequence::fusc(1) == 1);
    assert(SternSequence::fusc(5) == 3);

    std::cout << "stern_sequence tests passed successfully.\n";
    return 0;
}
