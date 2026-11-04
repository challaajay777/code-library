#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Product of Array Except Self
// Purpose: Computes an array where output[i] is the product of all elements in array except a[i] in O(N) without division.
// Time Complexity: O(N) time
// Space Complexity: O(1) auxiliary space beyond the output array
// Preconditions: 64-bit integer calculations.

class ProductExceptSelf {
public:
    static std::vector<long long> calculate(const std::vector<long long>& a) {
        int n = a.size();
        std::vector<long long> res(n, 1);

        long long left_prod = 1;
        for (int i = 0; i < n; ++i) {
            res[i] = left_prod;
            left_prod *= a[i];
        }

        long long right_prod = 1;
        for (int i = n - 1; i >= 0; --i) {
            res[i] *= right_prod;
            right_prod *= a[i];
        }

        return res;
    }
};

int main() {
    std::vector<long long> a = {1, 2, 3, 4};
    auto p = ProductExceptSelf::calculate(a);
    std::vector<long long> expected = {24, 12, 8, 6};
    assert(p == expected);

    std::vector<long long> b = {-1, 1, 0, -3, 3};
    auto p2 = ProductExceptSelf::calculate(b);
    std::vector<long long> expected2 = {0, 0, 9, 0, 0};
    assert(p2 == expected2);

    std::cout << "product_of_array_except_self tests passed successfully.\n";
    return 0;
}
