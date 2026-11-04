#include <iostream>
#include <cassert>

// Algorithm: Stern-Brocot Tree and Farey Sequence
// Purpose: Finds rational fraction approximation p/q in Stern-Brocot tree with denominator bound Q.
// Time Complexity: O(log(Q)) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Target real in (0, 1); max_denom >= 1.

class SternBrocotRationalApprox {
public:
    static std::pair<long long, long long> approximate(double target, long long max_denom) {
        long long l_p = 0, l_q = 1;
        long long r_p = 1, r_q = 1;
        long long best_p = 0, best_q = 1;

        while (true) {
            long long m_p = l_p + r_p;
            long long m_q = l_q + r_q;
            if (m_q > max_denom) break;

            best_p = m_p;
            best_q = m_q;
            double mediant = (double)m_p / m_q;

            if (mediant < target) {
                l_p = m_p;
                l_q = m_q;
            } else {
                r_p = m_p;
                r_q = m_q;
            }
        }
        return {best_p, best_q};
    }
};

int main() {
    // Approximate pi - 3 = 0.1415926535...
    auto [p, q] = SternBrocotRationalApprox::approximate(0.1415926535, 100);
    // Best fraction with denominator <= 100 is 1/7 (0.142857)
    assert(p == 1 && q == 7);

    std::cout << "stern_brocot_farey tests passed successfully.\n";
    return 0;
}
