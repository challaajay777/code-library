#!/usr/bin/env python3
"""
Batch 2 Generator: Sorting, Searching and Binary Search (40 implementations)
Target Directory: Sorting and Searching
"""

import os
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent.parent
TARGET_DIR = REPO_ROOT / "Sorting and Searching"

FILES = [
    {
        "filename": "quicksort_lomuto.cpp",
        "algorithm": "Quick Sort (Lomuto Partition)",
        "purpose": "Sorts an array using recursive quicksort with Lomuto's single-pointer partition scheme.",
        "time_complexity": "O(N log N) average, O(N^2) worst case",
        "space_complexity": "O(log N) recursion stack",
        "preconditions": "Randomized pivot recommended for worst-case defense.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Quick Sort (Lomuto Partition)
// Purpose: Sorts an array using recursive quicksort with Lomuto's single-pointer partition scheme.
// Time Complexity: O(N log N) average, O(N^2) worst case
// Space Complexity: O(log N) recursion stack
// Preconditions: Randomized pivot recommended for worst-case defense.

class QuickSortLomuto {
private:
    static int partition(std::vector<int>& a, int low, int high) {
        int pivot = a[high];
        int i = low - 1;
        for (int j = low; j < high; ++j) {
            if (a[j] <= pivot) {
                i++;
                std::swap(a[i], a[j]);
            }
        }
        std::swap(a[i + 1], a[high]);
        return i + 1;
    }

    static void sort_helper(std::vector<int>& a, int low, int high) {
        if (low < high) {
            int p = partition(a, low, high);
            sort_helper(a, low, p - 1);
            sort_helper(a, p + 1, high);
        }
    }

public:
    static void sort(std::vector<int>& a) {
        if (!a.empty()) {
            sort_helper(a, 0, (int)a.size() - 1);
        }
    }
};

int main() {
    std::vector<int> a = {10, 7, 8, 9, 1, 5};
    QuickSortLomuto::sort(a);
    std::vector<int> expected = {1, 5, 7, 8, 9, 10};
    assert(a == expected);

    std::cout << "quicksort_lomuto tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "quicksort_hoare.cpp",
        "algorithm": "Quick Sort (Hoare Partition)",
        "purpose": "Sorts array using Hoare's two-pointer bidirectional partition scheme, doing roughly 3x fewer swaps than Lomuto.",
        "time_complexity": "O(N log N) average, O(N^2) worst case",
        "space_complexity": "O(log N) recursion stack",
        "preconditions": "Handles duplicates efficiently.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Quick Sort (Hoare Partition)
// Purpose: Sorts array using Hoare's two-pointer bidirectional partition scheme, doing roughly 3x fewer swaps than Lomuto.
// Time Complexity: O(N log N) average, O(N^2) worst case
// Space Complexity: O(log N) recursion stack
// Preconditions: Handles duplicates efficiently.

class QuickSortHoare {
private:
    static int partition(std::vector<int>& a, int low, int high) {
        int pivot = a[low + (high - low) / 2];
        int i = low - 1;
        int j = high + 1;
        while (true) {
            do { i++; } while (a[i] < pivot);
            do { j--; } while (a[j] > pivot);
            if (i >= j) return j;
            std::swap(a[i], a[j]);
        }
    }

    static void sort_helper(std::vector<int>& a, int low, int high) {
        if (low < high) {
            int p = partition(a, low, high);
            sort_helper(a, low, p);
            sort_helper(a, p + 1, high);
        }
    }

public:
    static void sort(std::vector<int>& a) {
        if (!a.empty()) {
            sort_helper(a, 0, (int)a.size() - 1);
        }
    }
};

int main() {
    std::vector<int> a = {19, 22, 63, 105, 2, 46};
    QuickSortHoare::sort(a);
    std::vector<int> expected = {2, 19, 22, 46, 63, 105};
    assert(a == expected);

    std::cout << "quicksort_hoare tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "quicksort_3way_dutch_flag.cpp",
        "algorithm": "3-Way Quick Sort (Fat Partition)",
        "purpose": "Partitions array into elements less than, equal to, and greater than pivot to achieve O(N) time on many duplicate keys.",
        "time_complexity": "O(N log N) average, O(N) when duplicate elements dominate",
        "space_complexity": "O(log N) auxiliary recursion space",
        "preconditions": "Arbitrary array elements.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <cassert>

// Algorithm: 3-Way Quick Sort (Fat Partition)
// Purpose: Partitions array into elements less than, equal to, and greater than pivot to achieve O(N) time on many duplicate keys.
// Time Complexity: O(N log N) average, O(N) when duplicate elements dominate
// Space Complexity: O(log N) auxiliary recursion space
// Preconditions: Arbitrary array elements.

class QuickSort3Way {
private:
    static void sort_helper(std::vector<int>& a, int low, int high) {
        if (low >= high) return;

        // Choose random pivot
        int p_idx = low + std::rand() % (high - low + 1);
        std::swap(a[low], a[p_idx]);
        int pivot = a[low];

        int lt = low;     // a[low..lt-1] < pivot
        int gt = high;    // a[gt+1..high] > pivot
        int i = low + 1;  // a[lt..i-1] == pivot

        while (i <= gt) {
            if (a[i] < pivot) {
                std::swap(a[lt++], a[i++]);
            } else if (a[i] > pivot) {
                std::swap(a[i], a[gt--]);
            } else {
                i++;
            }
        }

        sort_helper(a, low, lt - 1);
        sort_helper(a, gt + 1, high);
    }

public:
    static void sort(std::vector<int>& a) {
        if (!a.empty()) {
            sort_helper(a, 0, (int)a.size() - 1);
        }
    }
};

int main() {
    std::vector<int> a = {4, 2, 2, 8, 3, 3, 1};
    QuickSort3Way::sort(a);
    std::vector<int> expected = {1, 2, 2, 3, 3, 4, 8};
    assert(a == expected);

    std::cout << "quicksort_3way_dutch_flag tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "randomized_quickselect.cpp",
        "algorithm": "Randomized Quickselect",
        "purpose": "Finds the k-th smallest element (0-indexed) in an unsorted array in expected linear time.",
        "time_complexity": "O(N) expected time, O(N^2) worst case",
        "space_complexity": "O(1) auxiliary space iterative",
        "preconditions": "0 <= k < N.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <cassert>

// Algorithm: Randomized Quickselect
// Purpose: Finds the k-th smallest element (0-indexed) in an unsorted array in expected linear time.
// Time Complexity: O(N) expected time, O(N^2) worst case
// Space Complexity: O(1) auxiliary space iterative
// Preconditions: 0 <= k < N.

class Quickselect {
public:
    static int select(std::vector<int>& a, int k) {
        int n = a.size();
        assert(k >= 0 && k < n);
        int low = 0, high = n - 1;

        std::mt19937 rng(1337);

        while (low <= high) {
            int p_idx = low + rng() % (high - low + 1);
            std::swap(a[p_idx], a[high]);
            int pivot = a[high];

            int i = low;
            for (int j = low; j < high; ++j) {
                if (a[j] <= pivot) {
                    std::swap(a[i++], a[j]);
                }
            }
            std::swap(a[i], a[high]);

            if (i == k) {
                return a[i];
            } else if (i < k) {
                low = i + 1;
            } else {
                high = i - 1;
            }
        }
        return -1;
    }
};

int main() {
    std::vector<int> a = {7, 10, 4, 3, 20, 15};
    // Sorted: 3, 4, 7, 10, 15, 20
    assert(Quickselect::select(a, 0) == 3);
    assert(Quickselect::select(a, 2) == 7);
    assert(Quickselect::select(a, 5) == 20);

    std::cout << "randomized_quickselect tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "heap_sort_in_place.cpp",
        "algorithm": "In-Place Heap Sort",
        "purpose": "Sorts an array in-place using a binary max-heap with zero dynamic memory allocation.",
        "time_complexity": "O(N log N) guaranteed time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "Comparable array elements.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: In-Place Heap Sort
// Purpose: Sorts an array in-place using a binary max-heap with zero dynamic memory allocation.
// Time Complexity: O(N log N) guaranteed time
// Space Complexity: O(1) auxiliary space
// Preconditions: Comparable array elements.

class HeapSort {
private:
    static void sift_down(std::vector<int>& a, int n, int i) {
        while (2 * i + 1 < n) {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int largest = i;

            if (left < n && a[left] > a[largest]) largest = left;
            if (right < n && a[right] > a[largest]) largest = right;

            if (largest == i) break;
            std::swap(a[i], a[largest]);
            i = largest;
        }
    }

public:
    static void sort(std::vector<int>& a) {
        int n = a.size();
        if (n <= 1) return;

        // Build max-heap bottom-up in O(N)
        for (int i = n / 2 - 1; i >= 0; --i) {
            sift_down(a, n, i);
        }

        // Extract elements from heap one by one
        for (int i = n - 1; i > 0; --i) {
            std::swap(a[0], a[i]);
            sift_down(a, i, 0);
        }
    }
};

int main() {
    std::vector<int> a = {12, 11, 13, 5, 6, 7};
    HeapSort::sort(a);
    std::vector<int> expected = {5, 6, 7, 11, 12, 13};
    assert(a == expected);

    std::cout << "heap_sort_in_place tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "counting_sort_signed.cpp",
        "algorithm": "Counting Sort for Signed Integers",
        "purpose": "Sorts integer array in linear time over any range [min_val, max_val] maintaining stability.",
        "time_complexity": "O(N + K) where K = max_val - min_val + 1",
        "space_complexity": "O(N + K) space",
        "preconditions": "Range K is reasonably bounded.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Counting Sort for Signed Integers
// Purpose: Sorts integer array in linear time over any range [min_val, max_val] maintaining stability.
// Time Complexity: O(N + K) where K = max_val - min_val + 1
// Space Complexity: O(N + K) space
// Preconditions: Range K is reasonably bounded.

class CountingSortSigned {
public:
    static void sort(std::vector<int>& a) {
        if (a.empty()) return;
        int min_val = *std::min_element(a.begin(), a.end());
        int max_val = *std::max_element(a.begin(), a.end());
        int range = max_val - min_val + 1;

        std::vector<int> count(range, 0);
        for (int x : a) {
            count[x - min_val]++;
        }

        for (int i = 1; i < range; ++i) {
            count[i] += count[i - 1];
        }

        std::vector<int> output(a.size());
        for (int i = (int)a.size() - 1; i >= 0; --i) {
            output[count[a[i] - min_val] - 1] = a[i];
            count[a[i] - min_val]--;
        }
        a = std::move(output);
    }
};

int main() {
    std::vector<int> a = {-5, -10, 0, -3, 8, 5, -1, 10};
    CountingSortSigned::sort(a);
    std::vector<int> expected = {-10, -5, -3, -1, 0, 5, 8, 10};
    assert(a == expected);

    std::cout << "counting_sort_signed tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "radix_sort_base256.cpp",
        "algorithm": "Base-256 Radix Sort (32-bit Unsigned)",
        "purpose": "Sorts 32-bit unsigned integers in linear time using 4 passes of 8-bit counting sort.",
        "time_complexity": "O(4 * (N + 256)) = O(N) time",
        "space_complexity": "O(N) auxiliary space",
        "preconditions": "Unsigned 32-bit integers.",
        "code": r"""#include <iostream>
#include <vector>
#include <cstdint>
#include <cassert>

// Algorithm: Base-256 Radix Sort (32-bit Unsigned)
// Purpose: Sorts 32-bit unsigned integers in linear time using 4 passes of 8-bit counting sort.
// Time Complexity: O(4 * (N + 256)) = O(N) time
// Space Complexity: O(N) auxiliary space
// Preconditions: Unsigned 32-bit integers.

class RadixSortBase256 {
public:
    static void sort(std::vector<uint32_t>& a) {
        int n = a.size();
        if (n <= 1) return;

        std::vector<uint32_t> buffer(n);
        for (int shift = 0; shift < 32; shift += 8) {
            int count[256] = {0};
            for (int i = 0; i < n; ++i) {
                uint8_t byte = (a[i] >> shift) & 0xFF;
                count[byte]++;
            }
            int offset[256];
            offset[0] = 0;
            for (int i = 1; i < 256; ++i) {
                offset[i] = offset[i - 1] + count[i - 1];
            }
            for (int i = 0; i < n; ++i) {
                uint8_t byte = (a[i] >> shift) & 0xFF;
                buffer[offset[byte]++] = a[i];
            }
            a = buffer;
        }
    }
};

int main() {
    std::vector<uint32_t> a = {170, 45, 75, 90, 802, 24, 2, 66};
    RadixSortBase256::sort(a);
    std::vector<uint32_t> expected = {2, 24, 45, 66, 75, 90, 170, 802};
    assert(a == expected);

    std::cout << "radix_sort_base256 tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "radix_sort_signed.cpp",
        "algorithm": "Signed 32-bit Radix Sort",
        "purpose": "Sorts 32-bit signed integers in O(N) by flipping the sign bit and running 4-pass base-256 radix sort.",
        "time_complexity": "O(N) time",
        "space_complexity": "O(N) auxiliary space",
        "preconditions": "Signed 32-bit integers.",
        "code": r"""#include <iostream>
#include <vector>
#include <cstdint>
#include <cassert>

// Algorithm: Signed 32-bit Radix Sort
// Purpose: Sorts 32-bit signed integers in O(N) by flipping the sign bit and running 4-pass base-256 radix sort.
// Time Complexity: O(N) time
// Space Complexity: O(N) auxiliary space
// Preconditions: Signed 32-bit integers.

class RadixSortSigned {
public:
    static void sort(std::vector<int32_t>& a) {
        int n = a.size();
        if (n <= 1) return;

        // Invert sign bit so negative numbers map below positive numbers
        for (int i = 0; i < n; ++i) {
            a[i] ^= (1U << 31);
        }

        std::vector<int32_t> buffer(n);
        for (int shift = 0; shift < 32; shift += 8) {
            int count[256] = {0};
            for (int i = 0; i < n; ++i) {
                uint8_t byte = ((uint32_t)a[i] >> shift) & 0xFF;
                count[byte]++;
            }
            int offset[256];
            offset[0] = 0;
            for (int i = 1; i < 256; ++i) {
                offset[i] = offset[i - 1] + count[i - 1];
            }
            for (int i = 0; i < n; ++i) {
                uint8_t byte = ((uint32_t)a[i] >> shift) & 0xFF;
                buffer[offset[byte]++] = a[i];
            }
            a = buffer;
        }

        // Restore sign bit
        for (int i = 0; i < n; ++i) {
            a[i] ^= (1U << 31);
        }
    }
};

int main() {
    std::vector<int32_t> a = {-10, 5, -200, 100, 0, -1, 35};
    RadixSortSigned::sort(a);
    std::vector<int32_t> expected = {-200, -10, -1, 0, 5, 35, 100};
    assert(a == expected);

    std::cout << "radix_sort_signed tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "bucket_sort_floating.cpp",
        "algorithm": "Bucket Sort for Uniform Floating-Point Numbers",
        "purpose": "Sorts uniformly distributed floating-point numbers in range [0, 1) in linear expected time.",
        "time_complexity": "O(N) expected time, O(N^2) worst case",
        "space_complexity": "O(N) space",
        "preconditions": "All elements 0.0 <= x < 1.0.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Bucket Sort for Uniform Floating-Point Numbers
// Purpose: Sorts uniformly distributed floating-point numbers in range [0, 1) in linear expected time.
// Time Complexity: O(N) expected time, O(N^2) worst case
// Space Complexity: O(N) space
// Preconditions: All elements 0.0 <= x < 1.0.

class BucketSortFloating {
public:
    static void sort(std::vector<double>& a) {
        int n = a.size();
        if (n <= 1) return;

        std::vector<std::vector<double>> buckets(n);
        for (double x : a) {
            assert(x >= 0.0 && x < 1.0);
            int idx = static_cast<int>(n * x);
            buckets[idx].push_back(x);
        }

        for (int i = 0; i < n; ++i) {
            std::sort(buckets[i].begin(), buckets[i].end());
        }

        int cur = 0;
        for (int i = 0; i < n; ++i) {
            for (double x : buckets[i]) {
                a[cur++] = x;
            }
        }
    }
};

int main() {
    std::vector<double> a = {0.897, 0.565, 0.656, 0.1234, 0.665, 0.3434};
    BucketSortFloating::sort(a);
    for (size_t i = 1; i < a.size(); ++i) {
        assert(a[i] >= a[i - 1]);
    }

    std::cout << "bucket_sort_floating tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "merge_sort_inversions.cpp",
        "algorithm": "Merge Sort with Inversion Counting",
        "purpose": "Counts total pairs (i, j) such that i < j and a[i] > a[j] while sorting the array in O(N log N).",
        "time_complexity": "O(N log N) time",
        "space_complexity": "O(N) auxiliary space",
        "preconditions": "Comparable array elements.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Merge Sort with Inversion Counting
// Purpose: Counts total pairs (i, j) such that i < j and a[i] > a[j] while sorting the array in O(N log N).
// Time Complexity: O(N log N) time
// Space Complexity: O(N) auxiliary space
// Preconditions: Comparable array elements.

class InversionCountingMergeSort {
private:
    static long long merge(std::vector<int>& a, std::vector<int>& temp, int left, int mid, int right) {
        int i = left;
        int j = mid + 1;
        int k = left;
        long long inv_count = 0;

        while (i <= mid && j <= right) {
            if (a[i] <= a[j]) {
                temp[k++] = a[i++];
            } else {
                temp[k++] = a[j++];
                inv_count += (mid - i + 1);
            }
        }

        while (i <= mid) temp[k++] = a[i++];
        while (j <= right) temp[k++] = a[j++];

        for (i = left; i <= right; ++i) {
            a[i] = temp[i];
        }
        return inv_count;
    }

    static long long sort_and_count(std::vector<int>& a, std::vector<int>& temp, int left, int right) {
        long long inv_count = 0;
        if (left < right) {
            int mid = left + (right - left) / 2;
            inv_count += sort_and_count(a, temp, left, mid);
            inv_count += sort_and_count(a, temp, mid + 1, right);
            inv_count += merge(a, temp, left, mid, right);
        }
        return inv_count;
    }

public:
    static long long count_inversions(std::vector<int>& a) {
        if (a.size() <= 1) return 0;
        std::vector<int> temp(a.size());
        return sort_and_count(a, temp, 0, (int)a.size() - 1);
    }
};

int main() {
    std::vector<int> a = {8, 4, 2, 1};
    // (8,4), (8,2), (8,1), (4,2), (4,1), (2,1) -> 6 inversions
    assert(InversionCountingMergeSort::count_inversions(a) == 6);

    std::vector<int> b = {1, 20, 6, 4, 5};
    // (20,6), (20,4), (20,5), (6,4), (6,5) -> 5 inversions
    assert(InversionCountingMergeSort::count_inversions(b) == 5);

    std::cout << "merge_sort_inversions tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "inversion_count_fenwick.cpp",
        "algorithm": "Inversion Counting via Fenwick Tree",
        "purpose": "Calculates total inversions in O(N log N) using coordinate compression and a Fenwick tree (Binary Indexed Tree).",
        "time_complexity": "O(N log N) time",
        "space_complexity": "O(N) space",
        "preconditions": "Arbitrary integer array.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Inversion Counting via Fenwick Tree
// Purpose: Calculates total inversions in O(N log N) using coordinate compression and a Fenwick tree (Binary Indexed Tree).
// Time Complexity: O(N log N) time
// Space Complexity: O(N) space
// Preconditions: Arbitrary integer array.

class FenwickInversions {
private:
    int n;
    std::vector<int> tree;

    void update(int i, int delta) {
        for (; i <= n; i += i & -i) tree[i] += delta;
    }

    int query(int i) const {
        int sum = 0;
        for (; i > 0; i -= i & -i) sum += tree[i];
        return sum;
    }

public:
    explicit FenwickInversions(int sz) : n(sz), tree(sz + 1, 0) {}

    static long long count(const std::vector<long long>& a) {
        int n = a.size();
        if (n <= 1) return 0;

        // Coordinate compression
        std::vector<long long> sorted_unique = a;
        std::sort(sorted_unique.begin(), sorted_unique.end());
        sorted_unique.erase(std::unique(sorted_unique.begin(), sorted_unique.end()), sorted_unique.end());

        FenwickInversions ft(sorted_unique.size());
        long long inv_count = 0;

        for (int i = n - 1; i >= 0; --i) {
            int rank = std::lower_bound(sorted_unique.begin(), sorted_unique.end(), a[i]) - sorted_unique.begin() + 1;
            inv_count += ft.query(rank - 1);
            ft.update(rank, 1);
        }
        return inv_count;
    }
};

int main() {
    std::vector<long long> a = {2, 4, 1, 3, 5};
    // (2,1), (4,1), (4,3) -> 3 inversions
    assert(FenwickInversions::count(a) == 3);

    std::vector<long long> b = {5, 4, 3, 2, 1};
    assert(FenwickInversions::count(b) == 10);

    std::cout << "inversion_count_fenwick tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "binary_search_answer_min_max.cpp",
        "algorithm": "Binary Search on Answer (Minimize Maximum)",
        "purpose": "Solves partitioning / allocation problems (e.g. painter partition, split array largest sum) by binary searching the threshold.",
        "time_complexity": "O(N log(sum - max)) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "Partition count K >= 1, all array values non-negative.",
        "code": r"""#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cassert>

// Algorithm: Binary Search on Answer (Minimize Maximum)
// Purpose: Solves partitioning / allocation problems (e.g. painter partition, split array largest sum) by binary searching the threshold.",
// Time Complexity: O(N log(sum - max)) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Partition count K >= 1, all array values non-negative.

class BinarySearchMinimizeMax {
private:
    static bool can_partition(const std::vector<long long>& a, int k, long long max_sum_allowed) {
        int count = 1;
        long long current_sum = 0;
        for (long long x : a) {
            if (x > max_sum_allowed) return false;
            if (current_sum + x > max_sum_allowed) {
                count++;
                current_sum = x;
            } else {
                current_sum += x;
            }
        }
        return count <= k;
    }

public:
    static long long split_array_largest_sum(const std::vector<long long>& a, int k) {
        long long low = *std::max_element(a.begin(), a.end());
        long long high = std::accumulate(a.begin(), a.end(), 0LL);
        long long ans = high;

        while (low <= high) {
            long long mid = low + (high - low) / 2;
            if (can_partition(a, k, mid)) {
                ans = mid;
                high = mid - 1; // Try smaller maximum sum
            } else {
                low = mid + 1;
            }
        }
        return ans;
    }
};

int main() {
    std::vector<long long> a = {7, 2, 5, 10, 8};
    // k = 2: best split is [7, 2, 5] and [10, 8] with sums 14 and 18 -> max is 18
    assert(BinarySearchMinimizeMax::split_array_largest_sum(a, 2) == 18);

    std::vector<long long> b = {1, 2, 3, 4, 5};
    assert(BinarySearchMinimizeMax::split_array_largest_sum(b, 2) == 9); // [1,2,3],[4,5]

    std::cout << "binary_search_answer_min_max tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "binary_search_answer_max_min.cpp",
        "algorithm": "Binary Search on Answer (Maximize Minimum Distance)",
        "purpose": "Places K items into stalls/positions to maximize the minimum distance between any two adjacent chosen items (Aggressive Cows).",
        "time_complexity": "O(N log(max_pos - min_pos)) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "Positions sorted; K >= 2.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Binary Search on Answer (Maximize Minimum Distance)
// Purpose: Places K items into stalls/positions to maximize the minimum distance between any two adjacent chosen items (Aggressive Cows).
// Time Complexity: O(N log(max_pos - min_pos)) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Positions sorted; K >= 2.

class BinarySearchMaximizeMin {
private:
    static bool can_place(const std::vector<long long>& pos, int k, long long dist) {
        int placed = 1;
        long long last_pos = pos[0];

        for (size_t i = 1; i < pos.size(); ++i) {
            if (pos[i] - last_pos >= dist) {
                placed++;
                last_pos = pos[i];
                if (placed >= k) return true;
            }
        }
        return placed >= k;
    }

public:
    static long long max_min_distance(std::vector<long long>& positions, int k) {
        std::sort(positions.begin(), positions.end());
        long long low = 1;
        long long high = positions.back() - positions.front();
        long long ans = 0;

        while (low <= high) {
            long long mid = low + (high - low) / 2;
            if (can_place(positions, k, mid)) {
                ans = mid;
                low = mid + 1; // Try larger distance
            } else {
                high = mid - 1;
            }
        }
        return ans;
    }
};

int main() {
    std::vector<long long> stalls = {1, 2, 8, 4, 9};
    // For k=3 cows: stalls sorted {1, 2, 4, 8, 9}. Best positions: 1, 4, 8 or 9 (min dist = 3)
    assert(BinarySearchMaximizeMin::max_min_distance(stalls, 3) == 3);

    std::cout << "binary_search_answer_max_min tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "search_rotated_sorted_array.cpp",
        "algorithm": "Search in Rotated Sorted Array (Distinct Elements)",
        "purpose": "Finds index of target element in a circularly rotated sorted array with distinct values in O(log N).",
        "time_complexity": "O(log N) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "Elements in array are unique.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Search in Rotated Sorted Array (Distinct Elements)
// Purpose: Finds index of target element in a circularly rotated sorted array with distinct values in O(log N).
// Time Complexity: O(log N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Elements in array are unique.

class SearchRotatedSortedArray {
public:
    static int search(const std::vector<int>& a, int target) {
        int low = 0, high = (int)a.size() - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (a[mid] == target) return mid;

            // Check if left half is sorted
            if (a[low] <= a[mid]) {
                if (a[low] <= target && target < a[mid]) {
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            } else { // Right half is sorted
                if (a[mid] < target && target <= a[high]) {
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }
        }
        return -1;
    }
};

int main() {
    std::vector<int> a = {4, 5, 6, 7, 0, 1, 2};
    assert(SearchRotatedSortedArray::search(a, 0) == 4);
    assert(SearchRotatedSortedArray::search(a, 3) == -1);

    std::vector<int> b = {1};
    assert(SearchRotatedSortedArray::search(b, 0) == -1);

    std::cout << "search_rotated_sorted_array tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "search_rotated_sorted_array_duplicates.cpp",
        "algorithm": "Search in Rotated Sorted Array with Duplicates",
        "purpose": "Determines whether target exists in a rotated sorted array containing duplicate values in O(log N) average, O(N) worst case.",
        "time_complexity": "O(log N) average, O(N) worst case",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "Rotated sorted array possibly with duplicates.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Search in Rotated Sorted Array with Duplicates
// Purpose: Determines whether target exists in a rotated sorted array containing duplicate values in O(log N) average, O(N) worst case.
// Time Complexity: O(log N) average, O(N) worst case
// Space Complexity: O(1) auxiliary space
// Preconditions: Rotated sorted array possibly with duplicates.

class SearchRotatedWithDuplicates {
public:
    static bool search(const std::vector<int>& a, int target) {
        int low = 0, high = (int)a.size() - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (a[mid] == target) return true;

            if (a[low] == a[mid] && a[mid] == a[high]) {
                low++;
                high--;
            } else if (a[low] <= a[mid]) {
                if (a[low] <= target && target < a[mid]) {
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            } else {
                if (a[mid] < target && target <= a[high]) {
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }
        }
        return false;
    }
};

int main() {
    std::vector<int> a = {2, 5, 6, 0, 0, 1, 2};
    assert(SearchRotatedWithDuplicates::search(a, 0) == true);
    assert(SearchRotatedWithDuplicates::search(a, 3) == false);

    std::vector<int> b = {1, 0, 1, 1, 1};
    assert(SearchRotatedWithDuplicates::search(b, 0) == true);

    std::cout << "search_rotated_sorted_array_duplicates tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "find_minimum_rotated_sorted.cpp",
        "algorithm": "Find Minimum in Rotated Sorted Array",
        "purpose": "Finds the minimum element in a rotated sorted array of distinct elements in O(log N) time.",
        "time_complexity": "O(log N) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "Array length >= 1, all elements unique.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Find Minimum in Rotated Sorted Array
// Purpose: Finds the minimum element in a rotated sorted array of distinct elements in O(log N) time.
// Time Complexity: O(log N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Array length >= 1, all elements unique.

class FindMinRotatedSorted {
public:
    static int find_min(const std::vector<int>& a) {
        assert(!a.empty());
        int low = 0, high = (int)a.size() - 1;

        while (low < high) {
            int mid = low + (high - low) / 2;
            if (a[mid] > a[high]) {
                low = mid + 1;
            } else {
                high = mid;
            }
        }
        return a[low];
    }
};

int main() {
    std::vector<int> a = {3, 4, 5, 1, 2};
    assert(FindMinRotatedSorted::find_min(a) == 1);

    std::vector<int> b = {4, 5, 6, 7, 0, 1, 2};
    assert(FindMinRotatedSorted::find_min(b) == 0);

    std::vector<int> c = {11, 13, 15, 17};
    assert(FindMinRotatedSorted::find_min(c) == 11);

    std::cout << "find_minimum_rotated_sorted tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "peak_element_1d.cpp",
        "algorithm": "1D Peak Element Finder",
        "purpose": "Finds a peak element (strictly greater than its immediate neighbors) in an array in O(log N) time.",
        "time_complexity": "O(log N) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "a[-1] = a[n] = -infinity.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: 1D Peak Element Finder
// Purpose: Finds a peak element (strictly greater than its immediate neighbors) in an array in O(log N) time.
// Time Complexity: O(log N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: a[-1] = a[n] = -infinity.

class PeakElement1D {
public:
    static int find_peak_index(const std::vector<int>& a) {
        int low = 0, high = (int)a.size() - 1;

        while (low < high) {
            int mid = low + (high - low) / 2;
            if (a[mid] < a[mid + 1]) {
                low = mid + 1;
            } else {
                high = mid;
            }
        }
        return low;
    }
};

int main() {
    std::vector<int> a = {1, 2, 3, 1};
    int peak_idx = PeakElement1D::find_peak_index(a);
    assert(peak_idx == 2 && a[peak_idx] == 3);

    std::vector<int> b = {1, 2, 1, 3, 5, 6, 4};
    int p2 = PeakElement1D::find_peak_index(b);
    assert(p2 == 1 || p2 == 5);

    std::cout << "peak_element_1d tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "peak_element_2d.cpp",
        "algorithm": "2D Matrix Peak Finder",
        "purpose": "Finds a peak element in an N x M matrix (strictly greater than up, down, left, right neighbors) in O(N log M) time.",
        "time_complexity": "O(N log M) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "Matrix dimensions >= 1.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: 2D Matrix Peak Finder
// Purpose: Finds a peak element in an N x M matrix (strictly greater than up, down, left, right neighbors) in O(N log M) time.
// Time Complexity: O(N log M) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Matrix dimensions >= 1.

class PeakElement2D {
public:
    static std::pair<int, int> find_peak(const std::vector<std::vector<int>>& mat) {
        int r = mat.size();
        int c = mat[0].size();
        int low_col = 0, high_col = c - 1;

        while (low_col <= high_col) {
            int mid_col = low_col + (high_col - low_col) / 2;

            // Find row index with maximum element in mid_col
            int max_row = 0;
            for (int i = 1; i < r; ++i) {
                if (mat[i][mid_col] > mat[max_row][mid_col]) {
                    max_row = i;
                }
            }

            int left_val = (mid_col > 0 ? mat[max_row][mid_col - 1] : -1e9);
            int right_val = (mid_col < c - 1 ? mat[max_row][mid_col + 1] : -1e9);
            int cur_val = mat[max_row][mid_col];

            if (cur_val > left_val && cur_val > right_val) {
                return {max_row, mid_col};
            } else if (right_val > cur_val) {
                low_col = mid_col + 1;
            } else {
                high_col = mid_col - 1;
            }
        }
        return {0, 0};
    }
};

int main() {
    std::vector<std::vector<int>> mat = {
        {1, 4, 3},
        {6, 7, 2},
        {5, 3, 1}
    };
    auto [row, col] = PeakElement2D::find_peak(mat);
    assert(row == 1 && col == 1); // 7 is greater than 4, 3, 6, 2

    std::cout << "peak_element_2d tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "search_2d_matrix_sorted.cpp",
        "algorithm": "Search in 2D Sorted Matrix (Staircase Search)",
        "purpose": "Searches for target in an R x C matrix where each row and column is sorted in ascending order in O(R + C).",
        "time_complexity": "O(R + C) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "Rows and columns independently sorted in non-decreasing order.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Search in 2D Sorted Matrix (Staircase Search)
// Purpose: Searches for target in an R x C matrix where each row and column is sorted in ascending order in O(R + C).
// Time Complexity: O(R + C) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Rows and columns independently sorted in non-decreasing order.

class StaircaseSearch2D {
public:
    static bool search(const std::vector<std::vector<int>>& mat, int target) {
        if (mat.empty() || mat[0].empty()) return false;
        int r = mat.size();
        int c = mat[0].size();

        // Start from top-right corner
        int row = 0;
        int col = c - 1;

        while (row < r && col >= 0) {
            if (mat[row][col] == target) {
                return true;
            } else if (mat[row][col] > target) {
                col--;
            } else {
                row++;
            }
        }
        return false;
    }
};

int main() {
    std::vector<std::vector<int>> mat = {
        {1, 4, 7, 11, 15},
        {2, 5, 8, 12, 19},
        {3, 6, 9, 16, 22},
        {10, 13, 14, 17, 24},
        {18, 21, 23, 26, 30}
    };
    assert(StaircaseSearch2D::search(mat, 5) == true);
    assert(StaircaseSearch2D::search(mat, 20) == false);

    std::cout << "search_2d_matrix_sorted tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "search_2d_matrix_row_major.cpp",
        "algorithm": "Search 2D Row-Major Sorted Matrix",
        "purpose": "Searches for target in an R x C matrix where each row is sorted and the first integer of each row is greater than the last of the previous row.",
        "time_complexity": "O(log(R * C)) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "Strict row-major sorted matrix.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Search 2D Row-Major Sorted Matrix
// Purpose: Searches for target in an R x C matrix where each row is sorted and the first integer of each row is greater than the last of the previous row.
// Time Complexity: O(log(R * C)) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Strict row-major sorted matrix.

class SearchRowMajor2D {
public:
    static bool search(const std::vector<std::vector<int>>& mat, int target) {
        if (mat.empty() || mat[0].empty()) return false;
        int r = mat.size();
        int c = mat[0].size();
        int low = 0, high = r * c - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            int mid_val = mat[mid / c][mid % c];

            if (mid_val == target) {
                return true;
            } else if (mid_val < target) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return false;
    }
};

int main() {
    std::vector<std::vector<int>> mat = {
        {1, 3, 5, 7},
        {10, 11, 16, 20},
        {23, 30, 34, 60}
    };
    assert(SearchRowMajor2D::search(mat, 3) == true);
    assert(SearchRowMajor2D::search(mat, 13) == false);

    std::cout << "search_2d_matrix_row_major tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "median_of_two_sorted_arrays.cpp",
        "algorithm": "Median of Two Sorted Arrays",
        "purpose": "Finds the median value of two sorted arrays of lengths M and N in O(log(min(M, N))) time.",
        "time_complexity": "O(log(min(M, N))) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "Both arrays sorted in non-decreasing order.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Median of Two Sorted Arrays
// Purpose: Finds the median value of two sorted arrays of lengths M and N in O(log(min(M, N))) time.
// Time Complexity: O(log(min(M, N))) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Both arrays sorted in non-decreasing order.

class MedianTwoSortedArrays {
public:
    static double find_median(const std::vector<int>& a, const std::vector<int>& b) {
        if (a.size() > b.size()) return find_median(b, a);

        int m = a.size(), n = b.size();
        int low = 0, high = m;

        while (low <= high) {
            int partition_a = (low + high) / 2;
            int partition_b = (m + n + 1) / 2 - partition_a;

            int max_left_a = (partition_a == 0) ? -2e9 : a[partition_a - 1];
            int min_right_a = (partition_a == m) ? 2e9 : a[partition_a];

            int max_left_b = (partition_b == 0) ? -2e9 : b[partition_b - 1];
            int min_right_b = (partition_b == n) ? 2e9 : b[partition_b];

            if (max_left_a <= min_right_b && max_left_b <= min_right_a) {
                if ((m + n) % 2 == 0) {
                    return (std::max(max_left_a, max_left_b) + std::min(min_right_a, min_right_b)) / 2.0;
                } else {
                    return std::max(max_left_a, max_left_b);
                }
            } else if (max_left_a > min_right_b) {
                high = partition_a - 1;
            } else {
                low = partition_a + 1;
            }
        }
        return 0.0;
    }
};

int main() {
    std::vector<int> a = {1, 3};
    std::vector<int> b = {2};
    assert(MedianTwoSortedArrays::find_median(a, b) == 2.0);

    std::vector<int> c = {1, 2};
    std::vector<int> d = {3, 4};
    assert(MedianTwoSortedArrays::find_median(c, d) == 2.5);

    std::cout << "median_of_two_sorted_arrays tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "kth_element_of_two_sorted_arrays.cpp",
        "algorithm": "K-th Element of Two Sorted Arrays",
        "purpose": "Finds the k-th smallest element (1-indexed) in the merged representation of two sorted arrays in logarithmic time.",
        "time_complexity": "O(log(min(M, N))) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "1 <= k <= M + N; both arrays sorted.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: K-th Element of Two Sorted Arrays
// Purpose: Finds the k-th smallest element (1-indexed) in the merged representation of two sorted arrays in logarithmic time.
// Time Complexity: O(log(min(M, N))) time
// Space Complexity: O(1) auxiliary space
// Preconditions: 1 <= k <= M + N; both arrays sorted.

class KthElementTwoSortedArrays {
public:
    static int find_kth(const std::vector<int>& a, const std::vector<int>& b, int k) {
        if (a.size() > b.size()) return find_kth(b, a, k);

        int m = a.size(), n = b.size();
        int low = std::max(0, k - n);
        int high = std::min(m, k);

        while (low <= high) {
            int cut_a = (low + high) / 2;
            int cut_b = k - cut_a;

            int left_a = (cut_a == 0) ? -2e9 : a[cut_a - 1];
            int right_a = (cut_a == m) ? 2e9 : a[cut_a];

            int left_b = (cut_b == 0) ? -2e9 : b[cut_b - 1];
            int right_b = (cut_b == n) ? 2e9 : b[cut_b];

            if (left_a <= right_b && left_b <= right_a) {
                return std::max(left_a, left_b);
            } else if (left_a > right_b) {
                high = cut_a - 1;
            } else {
                low = cut_a + 1;
            }
        }
        return -1;
    }
};

int main() {
    std::vector<int> a = {2, 3, 6, 7, 9};
    std::vector<int> b = {1, 4, 8, 10};
    // Merged: 1, 2, 3, 4, 6, 7, 8, 9, 10
    assert(KthElementTwoSortedArrays::find_kth(a, b, 5) == 6);
    assert(KthElementTwoSortedArrays::find_kth(a, b, 1) == 1);
    assert(KthElementTwoSortedArrays::find_kth(a, b, 9) == 10);

    std::cout << "kth_element_of_two_sorted_arrays tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "exponential_search.cpp",
        "algorithm": "Exponential (Galloping) Search",
        "purpose": "Finds a target in a sorted unbounded or large array by doubling range boundaries in O(log i) time.",
        "time_complexity": "O(log i) where i is the target index position",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "Sorted array.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Exponential (Galloping) Search
// Purpose: Finds a target in a sorted unbounded or large array by doubling range boundaries in O(log i) time.
// Time Complexity: O(log i) where i is the target index position
// Space Complexity: O(1) auxiliary space
// Preconditions: Sorted array.

class ExponentialSearch {
public:
    static int search(const std::vector<int>& a, int target) {
        int n = a.size();
        if (n == 0) return -1;
        if (a[0] == target) return 0;

        int bound = 1;
        while (bound < n && a[bound] < target) {
            bound *= 2;
        }

        int low = bound / 2;
        int high = std::min(bound, n - 1);

        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (a[mid] == target) {
                return mid;
            } else if (a[mid] < target) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return -1;
    }
};

int main() {
    std::vector<int> a = {2, 3, 4, 10, 40, 50, 60, 70, 80, 90, 100};
    assert(ExponentialSearch::search(a, 10) == 3);
    assert(ExponentialSearch::search(a, 90) == 9);
    assert(ExponentialSearch::search(a, 25) == -1);

    std::cout << "exponential_search tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "interpolation_search.cpp",
        "algorithm": "Interpolation Search",
        "purpose": "Searches for a key in uniformly distributed sorted numeric arrays in O(log log N) average time.",
        "time_complexity": "O(log log N) average, O(N) worst case",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "Sorted array with approximately uniform value distribution.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Interpolation Search
// Purpose: Searches for a key in uniformly distributed sorted numeric arrays in O(log log N) average time.
// Time Complexity: O(log log N) average, O(N) worst case
// Space Complexity: O(1) auxiliary space
// Preconditions: Sorted array with approximately uniform value distribution.

class InterpolationSearch {
public:
    static int search(const std::vector<int>& a, int target) {
        int low = 0;
        int high = (int)a.size() - 1;

        while (low <= high && target >= a[low] && target <= a[high]) {
            if (low == high) {
                if (a[low] == target) return low;
                return -1;
            }

            // Estimate probe position using linear interpolation
            long long pos = low + ((long long)(target - a[low]) * (high - low)) / (a[high] - a[low]);

            if (a[pos] == target) {
                return pos;
            } else if (a[pos] < target) {
                low = pos + 1;
            } else {
                high = pos - 1;
            }
        }
        return -1;
    }
};

int main() {
    std::vector<int> a = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    assert(InterpolationSearch::search(a, 40) == 3);
    assert(InterpolationSearch::search(a, 70) == 6);
    assert(InterpolationSearch::search(a, 35) == -1);

    std::cout << "interpolation_search tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "ternary_search_unimodal.cpp",
        "algorithm": "Ternary Search on Unimodal Real Function",
        "purpose": "Finds the global maximum or minimum of a continuous unimodal function over [L, R] up to epsilon precision.",
        "time_complexity": "O(log((R - L) / eps)) time (typically ~80 to 100 iterations)",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "Function strictly unimodal on [L, R].",
        "code": r"""#include <iostream>
#include <functional>
#include <cmath>
#include <cassert>

// Algorithm: Ternary Search on Unimodal Real Function
// Purpose: Finds the global maximum or minimum of a continuous unimodal function over [L, R] up to epsilon precision.
// Time Complexity: O(log((R - L) / eps)) time (typically ~80 to 100 iterations)
// Space Complexity: O(1) auxiliary space
// Preconditions: Function strictly unimodal on [L, R].

class TernarySearchUnimodal {
public:
    static double find_maximum(double left, double right, const std::function<double(double)>& f, int iterations = 100) {
        for (int i = 0; i < iterations; ++i) {
            double m1 = left + (right - left) / 3.0;
            double m2 = right - (right - left) / 3.0;

            if (f(m1) < f(m2)) {
                left = m1;
            } else {
                right = m2;
            }
        }
        return (left + right) / 2.0;
    }
};

int main() {
    // Parabola f(x) = -(x - 3)^2 + 10, max at x = 3
    auto f = [](double x) { return -(x - 3.0) * (x - 3.0) + 10.0; };
    double opt_x = TernarySearchUnimodal::find_maximum(-10.0, 10.0, f);
    assert(std::abs(opt_x - 3.0) < 1e-6);

    std::cout << "ternary_search_unimodal tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "ternary_search_discrete.cpp",
        "algorithm": "Discrete Ternary Search on Unimodal Array",
        "purpose": "Finds maximum value in a discrete array that strictly increases then strictly decreases in O(log N).",
        "time_complexity": "O(log N) evaluations",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "Array elements strictly unimodal (increasing to peak then decreasing).",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Discrete Ternary Search on Unimodal Array
// Purpose: Finds maximum value in a discrete array that strictly increases then strictly decreases in O(log N).
// Time Complexity: O(log N) evaluations
// Space Complexity: O(1) auxiliary space
// Preconditions: Array elements strictly unimodal (increasing to peak then decreasing).

class DiscreteTernarySearch {
public:
    static int find_max_index(const std::vector<int>& a) {
        int low = 0, high = (int)a.size() - 1;

        while (high - low >= 3) {
            int m1 = low + (high - low) / 3;
            int m2 = high - (high - low) / 3;

            if (a[m1] < a[m2]) {
                low = m1;
            } else {
                high = m2;
            }
        }

        int best_idx = low;
        for (int i = low + 1; i <= high; ++i) {
            if (a[i] > a[best_idx]) {
                best_idx = i;
            }
        }
        return best_idx;
    }
};

int main() {
    std::vector<int> a = {1, 3, 8, 12, 17, 14, 9, 2};
    assert(DiscreteTernarySearch::find_max_index(a) == 4); // peak = 17

    std::vector<int> b = {10, 8, 5, 2}; // strictly decreasing
    assert(DiscreteTernarySearch::find_max_index(b) == 0);

    std::cout << "ternary_search_discrete tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "stable_selection_sort.cpp",
        "algorithm": "Stable Selection Sort",
        "purpose": "Sorts array by moving min element to position via shifting instead of swapping, preserving relative order of equals.",
        "time_complexity": "O(N^2) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "Comparable elements.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Stable Selection Sort
// Purpose: Sorts array by moving min element to position via shifting instead of swapping, preserving relative order of equals.
// Time Complexity: O(N^2) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Comparable elements.

class StableSelectionSort {
public:
    struct Item {
        int key;
        int original_idx;
        bool operator<(const Item& other) const { return key < other.key; }
    };

    static void sort(std::vector<Item>& a) {
        int n = a.size();
        for (int i = 0; i < n - 1; ++i) {
            int min_idx = i;
            for (int j = i + 1; j < n; ++j) {
                if (a[j] < a[min_idx]) {
                    min_idx = j;
                }
            }
            Item min_item = a[min_idx];
            // Shift elements right to insert min_item stably
            for (int k = min_idx; k > i; --k) {
                a[k] = a[k - 1];
            }
            a[i] = min_item;
        }
    }
};

int main() {
    std::vector<StableSelectionSort::Item> a = {{4, 0}, {5, 1}, {3, 2}, {2, 3}, {4, 4}, {1, 5}};
    StableSelectionSort::sort(a);

    // Verify sorted keys
    for (size_t i = 1; i < a.size(); ++i) {
        assert(a[i].key >= a[i - 1].key);
    }
    // Verify stability for duplicate key 4
    assert(a[3].key == 4 && a[3].original_idx == 0);
    assert(a[4].key == 4 && a[4].original_idx == 4);

    std::cout << "stable_selection_sort tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "cocktail_shaker_sort.cpp",
        "algorithm": "Cocktail Shaker Sort",
        "purpose": "Bidirectional variation of bubble sort that traverses both forward and backward, resolving turtles faster.",
        "time_complexity": "O(N^2) worst case, O(N) best case",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "Comparable array elements.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Cocktail Shaker Sort
// Purpose: Bidirectional variation of bubble sort that traverses both forward and backward, resolving turtles faster.
// Time Complexity: O(N^2) worst case, O(N) best case
// Space Complexity: O(1) auxiliary space
// Preconditions: Comparable array elements.

class CocktailShakerSort {
public:
    static void sort(std::vector<int>& a) {
        bool swapped = true;
        int start = 0;
        int end = (int)a.size() - 1;

        while (swapped) {
            swapped = false;
            for (int i = start; i < end; ++i) {
                if (a[i] > a[i + 1]) {
                    std::swap(a[i], a[i + 1]);
                    swapped = true;
                }
            }
            if (!swapped) break;
            swapped = false;
            end--;

            for (int i = end - 1; i >= start; --i) {
                if (a[i] > a[i + 1]) {
                    std::swap(a[i], a[i + 1]);
                    swapped = true;
                }
            }
            start++;
        }
    }
};

int main() {
    std::vector<int> a = {5, 1, 4, 2, 8, 0, 2};
    CocktailShakerSort::sort(a);
    std::vector<int> expected = {0, 1, 2, 2, 4, 5, 8};
    assert(a == expected);

    std::cout << "cocktail_shaker_sort tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "comb_sort.cpp",
        "algorithm": "Comb Sort",
        "purpose": "Improves bubble sort by eliminating turtles using gap sequence with shrink factor 1.3.",
        "time_complexity": "O(N^2) worst case, O(N log N) typical competitive programming performance",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "Comparable array elements.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Comb Sort
// Purpose: Improves bubble sort by eliminating turtles using gap sequence with shrink factor 1.3.
// Time Complexity: O(N^2) worst case, O(N log N) typical competitive programming performance
// Space Complexity: O(1) auxiliary space
// Preconditions: Comparable array elements.

class CombSort {
public:
    static void sort(std::vector<int>& a) {
        int n = a.size();
        int gap = n;
        const double shrink = 1.3;
        bool sorted = false;

        while (!sorted) {
            gap = static_cast<int>(gap / shrink);
            if (gap <= 1) {
                gap = 1;
                sorted = true; // tentative: confirm no swaps occurred
            }
            for (int i = 0; i + gap < n; ++i) {
                if (a[i] > a[i + gap]) {
                    std::swap(a[i], a[i + gap]);
                    sorted = false;
                }
            }
        }
    }
};

int main() {
    std::vector<int> a = {8, 4, 1, 56, 3, -44, 23, -6, 28, 0};
    CombSort::sort(a);
    for (size_t i = 1; i < a.size(); ++i) {
        assert(a[i] >= a[i - 1]);
    }

    std::cout << "comb_sort tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "shell_sort_ciura.cpp",
        "algorithm": "Shell Sort (Ciura Sequence)",
        "purpose": "In-place comparison sort using Ciura's empirically optimal gap sequence {1, 4, 10, 23, 57, 132, 301, 701, 1750}.",
        "time_complexity": "O(N^(4/3)) empirical time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "Comparable array elements.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Shell Sort (Ciura Sequence)
// Purpose: In-place comparison sort using Ciura's empirically optimal gap sequence {1, 4, 10, 23, 57, 132, 301, 701, 1750}.
// Time Complexity: O(N^(4/3)) empirical time
// Space Complexity: O(1) auxiliary space
// Preconditions: Comparable array elements.

class ShellSortCiura {
public:
    static void sort(std::vector<int>& a) {
        int n = a.size();
        const std::vector<int> gaps = {1750, 701, 301, 132, 57, 23, 10, 4, 1};

        for (int gap : gaps) {
            if (gap >= n) continue;
            for (int i = gap; i < n; ++i) {
                int temp = a[i];
                int j = i;
                while (j >= gap && a[j - gap] > temp) {
                    a[j] = a[j - gap];
                    j -= gap;
                }
                a[j] = temp;
            }
        }
    }
};

int main() {
    std::vector<int> a = {12, 34, 54, 2, 3};
    ShellSortCiura::sort(a);
    std::vector<int> expected = {2, 3, 12, 34, 54};
    assert(a == expected);

    std::cout << "shell_sort_ciura tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "pancake_sorting.cpp",
        "algorithm": "Pancake Sorting",
        "purpose": "Sorts an array using only prefix reversal operations in at most 2*N flips.",
        "time_complexity": "O(N^2) time with at most 2*N flip operations",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "Array length >= 1.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Pancake Sorting
// Purpose: Sorts an array using only prefix reversal operations in at most 2*N flips.
// Time Complexity: O(N^2) time with at most 2*N flip operations
// Space Complexity: O(1) auxiliary space
// Preconditions: Array length >= 1.

class PancakeSort {
public:
    // Returns sequence of k values representing prefix reversals of a[0..k-1]
    static std::vector<int> sort(std::vector<int>& a) {
        int n = a.size();
        std::vector<int> flips;

        for (int cur_size = n; cur_size > 1; --cur_size) {
            int max_idx = std::max_element(a.begin(), a.begin() + cur_size) - a.begin();

            if (max_idx != cur_size - 1) {
                if (max_idx != 0) {
                    flips.push_back(max_idx + 1);
                    std::reverse(a.begin(), a.begin() + max_idx + 1);
                }
                flips.push_back(cur_size);
                std::reverse(a.begin(), a.begin() + cur_size);
            }
        }
        return flips;
    }
};

int main() {
    std::vector<int> a = {3, 2, 4, 1};
    auto flips = PancakeSort::sort(a);
    assert(std::is_sorted(a.begin(), a.end()));
    assert((int)flips.size() <= 2 * 4);

    std::cout << "pancake_sorting tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "bitonic_sort.cpp",
        "algorithm": "Bitonic Sort Network",
        "purpose": "Parallel sorting algorithm building bitonic sequences and recursively merging them in O(log^2 N) depth.",
        "time_complexity": "O(N log^2 N) sequential time, O(log^2 N) parallel depth",
        "space_complexity": "O(log N) recursion depth",
        "preconditions": "Size N must be a power of two.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Bitonic Sort Network
// Purpose: Parallel sorting algorithm building bitonic sequences and recursively merging them in O(log^2 N) depth.
// Time Complexity: O(N log^2 N) sequential time, O(log^2 N) parallel depth
// Space Complexity: O(log N) recursion depth
// Preconditions: Size N must be a power of two.

class BitonicSort {
private:
    static void bitonic_merge(std::vector<int>& a, int low, int cnt, bool dir) {
        if (cnt > 1) {
            int k = cnt / 2;
            for (int i = low; i < low + k; ++i) {
                if ((a[i] > a[i + k]) == dir) {
                    std::swap(a[i], a[i + k]);
                }
            }
            bitonic_merge(a, low, k, dir);
            bitonic_merge(a, low + k, k, dir);
        }
    }

    static void bitonic_sort_rec(std::vector<int>& a, int low, int cnt, bool dir) {
        if (cnt > 1) {
            int k = cnt / 2;
            bitonic_sort_rec(a, low, k, true);        // Ascending
            bitonic_sort_rec(a, low + k, k, false);   // Descending
            bitonic_merge(a, low, cnt, dir);
        }
    }

public:
    static void sort(std::vector<int>& a) {
        int n = a.size();
        assert((n & (n - 1)) == 0 && n > 0); // Check power of two
        bitonic_sort_rec(a, 0, n, true);
    }
};

int main() {
    std::vector<int> a = {3, 7, 4, 8, 6, 2, 1, 5};
    BitonicSort::sort(a);
    std::vector<int> expected = {1, 2, 3, 4, 5, 6, 7, 8};
    assert(a == expected);

    std::cout << "bitonic_sort tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "wiggle_sort.cpp",
        "algorithm": "Wiggle Sort (Odd-Even Peak Rearrangement)",
        "purpose": "Rearranges an array such that nums[0] <= nums[1] >= nums[2] <= nums[3]... in O(N) time and O(1) space.",
        "time_complexity": "O(N) time with a single pass",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "General array of elements.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Wiggle Sort (Odd-Even Peak Rearrangement)
// Purpose: Rearranges an array such that nums[0] <= nums[1] >= nums[2] <= nums[3]... in O(N) time and O(1) space.
// Time Complexity: O(N) time with a single pass
// Space Complexity: O(1) auxiliary space
// Preconditions: General array of elements.

class WiggleSort {
public:
    static void wiggle_sort(std::vector<int>& a) {
        for (size_t i = 0; i + 1 < a.size(); ++i) {
            if ((i % 2 == 0 && a[i] > a[i + 1]) || (i % 2 == 1 && a[i] < a[i + 1])) {
                std::swap(a[i], a[i + 1]);
            }
        }
    }
};

int main() {
    std::vector<int> a = {3, 5, 2, 1, 6, 4};
    WiggleSort::wiggle_sort(a);
    for (size_t i = 0; i + 1 < a.size(); ++i) {
        if (i % 2 == 0) assert(a[i] <= a[i + 1]);
        else assert(a[i] >= a[i + 1]);
    }

    std::cout << "wiggle_sort tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "sorted_matrix_kth_smallest.cpp",
        "algorithm": "K-th Smallest Element in Row-and-Column Sorted Matrix",
        "purpose": "Finds the k-th smallest element in an N x N matrix sorted along both rows and columns using binary search on answer.",
        "time_complexity": "O(N log(max_val - min_val)) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "Matrix sorted along both dimensions; 1 <= k <= N*N.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: K-th Smallest Element in Row-and-Column Sorted Matrix
// Purpose: Finds the k-th smallest element in an N x N matrix sorted along both rows and columns using binary search on answer.
// Time Complexity: O(N log(max_val - min_val)) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Matrix sorted along both dimensions; 1 <= k <= N*N.

class SortedMatrixKthSmallest {
private:
    static int count_less_or_equal(const std::vector<std::vector<int>>& mat, int mid) {
        int n = mat.size();
        int count = 0;
        int row = n - 1;
        int col = 0;

        while (row >= 0 && col < n) {
            if (mat[row][col] <= mid) {
                count += (row + 1);
                col++;
            } else {
                row--;
            }
        }
        return count;
    }

public:
    static int kth_smallest(const std::vector<std::vector<int>>& mat, int k) {
        int n = mat.size();
        int low = mat[0][0];
        int high = mat[n - 1][n - 1];
        int ans = low;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (count_less_or_equal(mat, mid) >= k) {
                ans = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        return ans;
    }
};

int main() {
    std::vector<std::vector<int>> mat = {
        {1, 5, 9},
        {10, 11, 13},
        {12, 13, 15}
    };
    // 8th smallest element is 13
    assert(SortedMatrixKthSmallest::kth_smallest(mat, 8) == 13);
    assert(SortedMatrixKthSmallest::kth_smallest(mat, 1) == 1);

    std::cout << "sorted_matrix_kth_smallest tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "find_first_and_last_position.cpp",
        "algorithm": "First and Last Position in Sorted Array",
        "purpose": "Finds the first and last occurrence indices of a target in a sorted array in O(log N) time.",
        "time_complexity": "O(log N) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "Sorted array in non-decreasing order.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: First and Last Position in Sorted Array
// Purpose: Finds the first and last occurrence indices of a target in a sorted array in O(log N) time.
// Time Complexity: O(log N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Sorted array in non-decreasing order.

class FirstLastPosition {
private:
    static int find_bound(const std::vector<int>& a, int target, bool is_first) {
        int low = 0, high = (int)a.size() - 1;
        int ans = -1;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (a[mid] == target) {
                ans = mid;
                if (is_first) {
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            } else if (a[mid] < target) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return ans;
    }

public:
    static std::pair<int, int> search_range(const std::vector<int>& a, int target) {
        int first = find_bound(a, target, true);
        if (first == -1) return {-1, -1};
        int last = find_bound(a, target, false);
        return {first, last};
    }
};

int main() {
    std::vector<int> a = {5, 7, 7, 8, 8, 10};
    auto [f, l] = FirstLastPosition::search_range(a, 8);
    assert(f == 3 && l == 4);

    auto [f2, l2] = FirstLastPosition::search_range(a, 6);
    assert(f2 == -1 && l2 == -1);

    std::cout << "find_first_and_last_position tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "find_smallest_letter_greater_than_target.cpp",
        "algorithm": "Circular Next Greater Character",
        "purpose": "Finds the smallest character in a sorted circular list that is strictly greater than target.",
        "time_complexity": "O(log N) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "Non-empty sorted vector of characters.",
        "code": r"""#include <iostream>
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
"""
    },
    {
        "filename": "missing_number_binary_search.cpp",
        "algorithm": "Missing Number in Sorted Arithmetic Progression",
        "purpose": "Finds the single missing number in a strictly increasing arithmetic progression in O(log N) time.",
        "time_complexity": "O(log N) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "Array length >= 2; exactly one missing element.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Missing Number in Sorted Arithmetic Progression
// Purpose: Finds the single missing number in a strictly increasing arithmetic progression in O(log N) time.
// Time Complexity: O(log N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Array length >= 2; exactly one missing element.

class MissingNumberAP {
public:
    static int find_missing(const std::vector<int>& arr) {
        int n = arr.size();
        assert(n >= 2);
        int diff = (arr.back() - arr.front()) / n;

        int low = 0, high = n - 1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            int expected = arr[0] + mid * diff;

            if (arr[mid] == expected) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return arr[0] + low * diff;
    }
};

int main() {
    std::vector<int> a = {2, 4, 8, 10, 12, 14};
    assert(MissingNumberAP::find_missing(a) == 6);

    std::vector<int> b = {1, 6, 11, 16, 21, 31};
    assert(MissingNumberAP::find_missing(b) == 26);

    std::cout << "missing_number_binary_search tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "square_root_binary_search.cpp",
        "algorithm": "Integer and Real Square Root via Binary Search",
        "purpose": "Computes floor(sqrt(X)) and high-precision sqrt(X) using binary search without standard floating-point functions.",
        "time_complexity": "O(log X) integer sqrt, O(iterations) floating-point sqrt",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "X >= 0.",
        "code": r"""#include <iostream>
#include <cmath>
#include <cassert>

// Algorithm: Integer and Real Square Root via Binary Search
// Purpose: Computes floor(sqrt(X)) and high-precision sqrt(X) using binary search without standard floating-point functions.
// Time Complexity: O(log X) integer sqrt, O(iterations) floating-point sqrt
// Space Complexity: O(1) auxiliary space
// Preconditions: X >= 0.

class SqrtBinarySearch {
public:
    static long long isqrt(long long x) {
        assert(x >= 0);
        if (x <= 1) return x;

        long long low = 1, high = x / 2;
        long long ans = 1;

        while (low <= high) {
            long long mid = low + (high - low) / 2;
            if (mid <= x / mid) {
                ans = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return ans;
    }

    static double fsqrt(double x, int iterations = 80) {
        assert(x >= 0.0);
        if (x == 0.0) return 0.0;
        double low = (x < 1.0) ? x : 1.0;
        double high = (x < 1.0) ? 1.0 : x;

        for (int i = 0; i < iterations; ++i) {
            double mid = low + (high - low) / 2.0;
            if (mid * mid <= x) {
                low = mid;
            } else {
                high = mid;
            }
        }
        return (low + high) / 2.0;
    }
};

int main() {
    assert(SqrtBinarySearch::isqrt(16) == 4);
    assert(SqrtBinarySearch::isqrt(8) == 2);
    assert(SqrtBinarySearch::isqrt(2147395599LL) == 46339LL);

    assert(std::abs(SqrtBinarySearch::fsqrt(2.0) - 1.41421356) < 1e-6);

    std::cout << "square_root_binary_search tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "nth_root_binary_search.cpp",
        "algorithm": "Integer N-th Root via Binary Search",
        "purpose": "Computes floor(X^(1/N)) for large integers safely preventing integer overflow.",
        "time_complexity": "O(N * log X) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "X >= 0, N >= 1.",
        "code": r"""#include <iostream>
#include <cassert>

// Algorithm: Integer N-th Root via Binary Search
// Purpose: Computes floor(X^(1/N)) for large integers safely preventing integer overflow.
// Time Complexity: O(N * log X) time
// Space Complexity: O(1) auxiliary space
// Preconditions: X >= 0, N >= 1.

class NthRootBinarySearch {
private:
    // Returns 1 if mid^n == m, 2 if mid^n > m, 0 if mid^n < m
    static int check_power(long long mid, int n, long long m) {
        long long ans = 1;
        for (int i = 1; i <= n; ++i) {
            if (m / mid < ans) return 2; // Overflow or exceeded m
            ans *= mid;
        }
        if (ans == m) return 1;
        return 0;
    }

public:
    static long long nth_root_exact(int n, long long m) {
        long long low = 1, high = m;
        while (low <= high) {
            long long mid = low + (high - low) / 2;
            int status = check_power(mid, n, m);
            if (status == 1) return mid;
            if (status == 0) low = mid + 1;
            else high = mid - 1;
        }
        return -1; // No exact integer root
    }
};

int main() {
    assert(NthRootBinarySearch::nth_root_exact(3, 27) == 3);
    assert(NthRootBinarySearch::nth_root_exact(4, 69) == -1);
    assert(NthRootBinarySearch::nth_root_exact(2, 9) == 3);

    std::cout << "nth_root_binary_search tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "index_equals_value_search.cpp",
        "algorithm": "Magic Index (A[i] == i) Finder",
        "purpose": "Finds an index i such that a[i] == i in a sorted array in O(log N) for distinct or recursive divide-and-conquer for duplicates.",
        "time_complexity": "O(log N) for distinct elements",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "Sorted integer array.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Magic Index (A[i] == i) Finder
// Purpose: Finds an index i such that a[i] == i in a sorted array in O(log N) for distinct or recursive divide-and-conquer for duplicates.
// Time Complexity: O(log N) for distinct elements
// Space Complexity: O(1) auxiliary space
// Preconditions: Sorted integer array.

class MagicIndex {
public:
    static int find_magic_index_distinct(const std::vector<int>& a) {
        int low = 0, high = (int)a.size() - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (a[mid] == mid) {
                return mid;
            } else if (a[mid] < mid) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return -1;
    }
};

int main() {
    std::vector<int> a = {-10, -5, 0, 3, 7};
    // a[3] == 3
    assert(MagicIndex::find_magic_index_distinct(a) == 3);

    std::vector<int> b = {1, 2, 3, 4};
    assert(MagicIndex::find_magic_index_distinct(b) == -1);

    std::cout << "index_equals_value_search tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "pigeonhole_sort.cpp",
        "algorithm": "Pigeonhole Sort",
        "purpose": "Sorts an array of integers when range of keys is approximately equal to number of elements.",
        "time_complexity": "O(N + Range) time",
        "space_complexity": "O(Range) auxiliary space",
        "preconditions": "Range = max_val - min_val + 1 is modest.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Pigeonhole Sort
// Purpose: Sorts an array of integers when range of keys is approximately equal to number of elements.
// Time Complexity: O(N + Range) time
// Space Complexity: O(Range) auxiliary space
// Preconditions: Range = max_val - min_val + 1 is modest.

class PigeonholeSort {
public:
    static void sort(std::vector<int>& a) {
        if (a.empty()) return;
        int min_val = *std::min_element(a.begin(), a.end());
        int max_val = *std::max_element(a.begin(), a.end());
        int range = max_val - min_val + 1;

        std::vector<std::vector<int>> holes(range);
        for (int x : a) {
            holes[x - min_val].push_back(x);
        }

        int idx = 0;
        for (int i = 0; i < range; ++i) {
            for (int x : holes[i]) {
                a[idx++] = x;
            }
        }
    }
};

int main() {
    std::vector<int> a = {8, 3, 2, 7, 4, 6, 8};
    PigeonholeSort::sort(a);
    std::vector<int> expected = {2, 3, 4, 6, 7, 8, 8};
    assert(a == expected);

    std::cout << "pigeonhole_sort tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "strand_sort.cpp",
        "algorithm": "Strand Sort",
        "purpose": "Sorts a linked list or array by repeatedly pulling sorted sublists (strands) and merging them.",
        "time_complexity": "O(N log N) best case, O(N^2) worst case",
        "space_complexity": "O(N) auxiliary space",
        "preconditions": "Comparable elements.",
        "code": r"""#include <iostream>
#include <vector>
#include <list>
#include <cassert>

// Algorithm: Strand Sort
// Purpose: Sorts a linked list or array by repeatedly pulling sorted sublists (strands) and merging them.
// Time Complexity: O(N log N) best case, O(N^2) worst case
// Space Complexity: O(N) auxiliary space
// Preconditions: Comparable elements.

class StrandSort {
public:
    static void sort(std::list<int>& ip) {
        std::list<int> op;
        std::list<int> sublist;

        while (!ip.empty()) {
            sublist.push_back(ip.front());
            ip.pop_front();

            for (auto it = ip.begin(); it != ip.end();) {
                if (*it >= sublist.back()) {
                    sublist.push_back(*it);
                    it = ip.erase(it);
                } else {
                    ++it;
                }
            }
            op.merge(sublist);
        }
        ip = std::move(op);
    }
};

int main() {
    std::list<int> a = {10, 5, 30, 40, 2, 4, 9};
    StrandSort::sort(a);
    std::vector<int> res(a.begin(), a.end());
    std::vector<int> expected = {2, 4, 5, 9, 10, 30, 40};
    assert(res == expected);

    std::cout << "strand_sort tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "stooge_sort.cpp",
        "algorithm": "Stooge Sort",
        "purpose": "Recursive sorting algorithm sorting first 2/3, last 2/3, then first 2/3 again.",
        "time_complexity": "O(N^(log 3 / log 1.5)) = O(N^2.7095) time",
        "space_complexity": "O(log N) recursion stack",
        "preconditions": "Educational baseline.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Stooge Sort
// Purpose: Recursive sorting algorithm sorting first 2/3, last 2/3, then first 2/3 again.
// Time Complexity: O(N^(log 3 / log 1.5)) = O(N^2.7095) time
// Space Complexity: O(log N) recursion stack
// Preconditions: Educational baseline.

class StoogeSort {
private:
    static void sort_rec(std::vector<int>& a, int l, int h) {
        if (l >= h) return;
        if (a[l] > a[h]) {
            std::swap(a[l], a[h]);
        }
        if (h - l + 1 > 2) {
            int t = (h - l + 1) / 3;
            sort_rec(a, l, h - t);
            sort_rec(a, l + t, h);
            sort_rec(a, l, h - t);
        }
    }

public:
    static void sort(std::vector<int>& a) {
        if (!a.empty()) {
            sort_rec(a, 0, (int)a.size() - 1);
        }
    }
};

int main() {
    std::vector<int> a = {2, 4, 5, 3, 1};
    StoogeSort::sort(a);
    std::vector<int> expected = {1, 2, 3, 4, 5};
    assert(a == expected);

    std::cout << "stooge_sort tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "cycle_sort.cpp",
        "algorithm": "Cycle Sort",
        "purpose": "In-place, unstable comparison sort that minimizes the total number of memory writes to the original array.",
        "time_complexity": "O(N^2) time with at most N - 1 writes",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "Comparable elements.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Cycle Sort
// Purpose: In-place, unstable comparison sort that minimizes the total number of memory writes to the original array.
// Time Complexity: O(N^2) time with at most N - 1 writes
// Space Complexity: O(1) auxiliary space
// Preconditions: Comparable elements.

class CycleSort {
public:
    static int sort(std::vector<int>& a) {
        int n = a.size();
        int writes = 0;

        for (int cycle_start = 0; cycle_start <= n - 2; ++cycle_start) {
            int item = a[cycle_start];
            int pos = cycle_start;

            for (int i = cycle_start + 1; i < n; ++i) {
                if (a[i] < item) pos++;
            }
            if (pos == cycle_start) continue;

            while (item == a[pos]) pos++;
            if (pos != cycle_start) {
                std::swap(item, a[pos]);
                writes++;
            }

            while (pos != cycle_start) {
                pos = cycle_start;
                for (int i = cycle_start + 1; i < n; ++i) {
                    if (a[i] < item) pos++;
                }
                while (item == a[pos]) pos++;
                if (item != a[pos]) {
                    std::swap(item, a[pos]);
                    writes++;
                }
            }
        }
        return writes;
    }
};

int main() {
    std::vector<int> a = {1, 8, 3, 9, 10, 10, 2, 4};
    CycleSort::sort(a);
    for (size_t i = 1; i < a.size(); ++i) {
        assert(a[i] >= a[i - 1]);
    }

    std::cout << "cycle_sort tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "three_sum_binary_search.cpp",
        "algorithm": "3-Sum via Binary Search",
        "purpose": "Finds all unique triplets [a, b, c] such that a + b + c = 0 in O(N^2 log N) using binary search.",
        "time_complexity": "O(N^2 log N) time",
        "space_complexity": "O(1) auxiliary space beyond output",
        "preconditions": "64-bit integer values.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: 3-Sum via Binary Search
// Purpose: Finds all unique triplets [a, b, c] such that a + b + c = 0 in O(N^2 log N) using binary search.
// Time Complexity: O(N^2 log N) time
// Space Complexity: O(1) auxiliary space beyond output
// Preconditions: 64-bit integer values.

class ThreeSumBinarySearch {
public:
    static std::vector<std::vector<int>> three_sum(std::vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        int n = nums.size();
        std::vector<std::vector<int>> triplets;

        for (int i = 0; i < n - 2; ++i) {
            if (i > 0 && nums[i] == nums[i - 1]) continue;
            for (int j = i + 1; j < n - 1; ++j) {
                if (j > i + 1 && nums[j] == nums[j - 1]) continue;

                int target = -(nums[i] + nums[j]);
                if (std::binary_search(nums.begin() + j + 1, nums.end(), target)) {
                    triplets.push_back({nums[i], nums[j], target});
                }
            }
        }
        return triplets;
    }
};

int main() {
    std::vector<int> a = {-1, 0, 1, 2, -1, -4};
    auto trips = ThreeSumBinarySearch::three_sum(a);
    // Unique triplets: [-1, -1, 2], [-1, 0, 1]
    assert(trips.size() == 2);

    std::cout << "three_sum_binary_search tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "four_sum_binary_search.cpp",
        "algorithm": "4-Sum via Pair Sums and Binary Search",
        "purpose": "Finds unique quadruplets that sum to target value using sorted pair sums and binary search in O(N^2 log N).",
        "time_complexity": "O(N^2 log N) time",
        "space_complexity": "O(N^2) auxiliary space for pair structures",
        "preconditions": "Arbitrary integer array.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: 4-Sum via Pair Sums and Binary Search
// Purpose: Finds unique quadruplets that sum to target value using sorted pair sums and binary search in O(N^2 log N).
// Time Complexity: O(N^2 log N) time
// Space Complexity: O(N^2) auxiliary space for pair structures
// Preconditions: Arbitrary integer array.

class FourSumBinarySearch {
public:
    static std::vector<std::vector<int>> four_sum(std::vector<int>& nums, long long target) {
        std::sort(nums.begin(), nums.end());
        int n = nums.size();
        std::vector<std::vector<int>> res;

        for (int i = 0; i < n - 3; ++i) {
            if (i > 0 && nums[i] == nums[i - 1]) continue;
            for (int j = i + 1; j < n - 2; ++j) {
                if (j > i + 1 && nums[j] == nums[j - 1]) continue;

                int left = j + 1, right = n - 1;
                while (left < right) {
                    long long sum = (long long)nums[i] + nums[j] + nums[left] + nums[right];
                    if (sum == target) {
                        res.push_back({nums[i], nums[j], nums[left], nums[right]});
                        while (left < right && nums[left] == nums[left + 1]) left++;
                        while (left < right && nums[right] == nums[right - 1]) right--;
                        left++;
                        right--;
                    } else if (sum < target) {
                        left++;
                    } else {
                        right--;
                    }
                }
            }
        }
        return res;
    }
};

int main() {
    std::vector<int> a = {1, 0, -1, 0, -2, 2};
    auto quad = FourSumBinarySearch::four_sum(a, 0);
    // [-2, -1, 1, 2], [-2, 0, 0, 2], [-1, 0, 0, 1] -> 3 quadruplets
    assert(quad.size() == 3);

    std::cout << "four_sum_binary_search tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "search_nearly_sorted_array.cpp",
        "algorithm": "Search in K-Nearly Sorted Array",
        "purpose": "Finds target in an array where each element is at most K positions away from its sorted index in O(log N).",
        "time_complexity": "O(log N) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "Element is at most K away from sorted location (here K = 1).",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Search in K-Nearly Sorted Array
// Purpose: Finds target in an array where each element is at most K positions away from its sorted index in O(log N).
// Time Complexity: O(log N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Element is at most K away from sorted location (here K = 1).

class NearlySortedSearch {
public:
    static int search(const std::vector<int>& a, int target) {
        int low = 0, high = (int)a.size() - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (a[mid] == target) return mid;
            if (mid > low && a[mid - 1] == target) return mid - 1;
            if (mid < high && a[mid + 1] == target) return mid + 1;

            if (a[mid] > target) {
                high = mid - 2;
            } else {
                low = mid + 2;
            }
        }
        return -1;
    }
};

int main() {
    std::vector<int> a = {10, 3, 40, 20, 50, 80, 70};
    assert(NearlySortedSearch::search(a, 40) == 2);
    assert(NearlySortedSearch::search(a, 20) == 3);
    assert(NearlySortedSearch::search(a, 90) == -1);

    std::cout << "search_nearly_sorted_array tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "find_frequency_sorted_array.cpp",
        "algorithm": "Count Frequency in Sorted Array",
        "purpose": "Calculates the total frequency of target in sorted array in O(log N) via upper_bound - lower_bound.",
        "time_complexity": "O(log N) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "Sorted array.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Count Frequency in Sorted Array
// Purpose: Calculates the total frequency of target in sorted array in O(log N) via upper_bound - lower_bound.
// Time Complexity: O(log N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Sorted array.

class FrequencyInSortedArray {
public:
    static int count(const std::vector<int>& a, int target) {
        auto it1 = std::lower_bound(a.begin(), a.end(), target);
        auto it2 = std::upper_bound(a.begin(), a.end(), target);
        return std::distance(it1, it2);
    }
};

int main() {
    std::vector<int> a = {1, 1, 2, 2, 2, 2, 3};
    assert(FrequencyInSortedArray::count(a, 2) == 4);
    assert(FrequencyInSortedArray::count(a, 1) == 2);
    assert(FrequencyInSortedArray::count(a, 4) == 0);

    std::cout << "find_frequency_sorted_array tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "majority_element_binary_search.cpp",
        "algorithm": "Majority Element in Sorted Array",
        "purpose": "Checks if a candidate is a majority element (frequency > N/2) in a sorted array in O(1) after lower_bound.",
        "time_complexity": "O(log N) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "Sorted array.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Majority Element in Sorted Array
// Purpose: Checks if a candidate is a majority element (frequency > N/2) in a sorted array in O(1) after lower_bound.
// Time Complexity: O(log N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Sorted array.

class MajorityElementSorted {
public:
    static bool is_majority(const std::vector<int>& a, int candidate) {
        int n = a.size();
        auto it = std::lower_bound(a.begin(), a.end(), candidate);
        if (it == a.end() || *it != candidate) return false;

        int first_idx = it - a.begin();
        int check_idx = first_idx + n / 2;

        return check_idx < n && a[check_idx] == candidate;
    }
};

int main() {
    std::vector<int> a = {1, 2, 3, 3, 3, 3, 10};
    assert(MajorityElementSorted::is_majority(a, 3) == true);
    assert(MajorityElementSorted::is_majority(a, 2) == false);

    std::cout << "majority_element_binary_search tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "find_single_non_duplicate.cpp",
        "algorithm": "Single Element in a Sorted Array",
        "purpose": "Finds the unique single non-duplicate element in a sorted array where all other elements appear twice in O(log N).",
        "time_complexity": "O(log N) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "Array length is odd; all elements except one appear exactly twice.",
        "code": r"""#include <iostream>
#include <vector>
#include <cassert>

// Algorithm: Single Element in a Sorted Array
// Purpose: Finds the unique single non-duplicate element in a sorted array where all other elements appear twice in O(log N).
// Time Complexity: O(log N) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Array length is odd; all elements except one appear exactly twice.

class SingleNonDuplicate {
public:
    static int single_non_duplicate(const std::vector<int>& a) {
        int low = 0, high = (int)a.size() - 1;

        while (low < high) {
            int mid = low + (high - low) / 2;
            if (mid % 2 == 1) mid--; // Ensure mid is even

            if (a[mid] == a[mid + 1]) {
                low = mid + 2;
            } else {
                high = mid;
            }
        }
        return a[low];
    }
};

int main() {
    std::vector<int> a = {1, 1, 2, 3, 3, 4, 4, 8, 8};
    assert(SingleNonDuplicate::single_non_duplicate(a) == 2);

    std::vector<int> b = {3, 3, 7, 7, 10, 11, 11};
    assert(SingleNonDuplicate::single_non_duplicate(b) == 10);

    std::cout << "find_single_non_duplicate tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "kth_smallest_difference_pairs.cpp",
        "algorithm": "K-th Smallest Absolute Pair Distance",
        "purpose": "Finds the k-th smallest distance |a[i] - a[j]| among all pairs in array in O(N log(max_dist)) using two pointers.",
        "time_complexity": "O(N log(max_dist)) time",
        "space_complexity": "O(1) auxiliary space beyond sorting",
        "preconditions": "1 <= k <= N*(N-1)/2.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: K-th Smallest Absolute Pair Distance
// Purpose: Finds the k-th smallest distance |a[i] - a[j]| among all pairs in array in O(N log(max_dist)) using two pointers.
// Time Complexity: O(N log(max_dist)) time
// Space Complexity: O(1) auxiliary space beyond sorting
// Preconditions: 1 <= k <= N*(N-1)/2.

class KthSmallestPairDistance {
private:
    static int count_pairs(const std::vector<int>& a, int dist) {
        int n = a.size();
        int count = 0;
        int left = 0;
        for (int right = 0; right < n; ++right) {
            while (a[right] - a[left] > dist) {
                left++;
            }
            count += (right - left);
        }
        return count;
    }

public:
    static int smallest_distance_pair(std::vector<int>& a, int k) {
        std::sort(a.begin(), a.end());
        int low = 0;
        int high = a.back() - a.front();
        int ans = high;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (count_pairs(a, mid) >= k) {
                ans = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        return ans;
    }
};

int main() {
    std::vector<int> a = {1, 3, 1};
    // Pairs: (1,3) diff=2, (1,1) diff=0, (3,1) diff=2. Sorted: 0, 2, 2. k=1 -> 0
    assert(KthSmallestPairDistance::smallest_distance_pair(a, 1) == 0);

    std::vector<int> b = {1, 6, 1};
    assert(KthSmallestPairDistance::smallest_distance_pair(b, 3) == 5);

    std::cout << "kth_smallest_difference_pairs tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "minimize_max_distance_to_gas_station.cpp",
        "algorithm": "Minimize Maximum Distance to Gas Station",
        "purpose": "Adds K new gas stations on a highway to minimize the maximum distance between adjacent gas stations via binary search on answer.",
        "time_complexity": "O(N * log(max_gap / eps)) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "Stations array sorted; K >= 1.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cassert>

// Algorithm: Minimize Maximum Distance to Gas Station
// Purpose: Adds K new gas stations on a highway to minimize the maximum distance between adjacent gas stations via binary search on answer.
// Time Complexity: O(N * log(max_gap / eps)) time
// Space Complexity: O(1) auxiliary space
// Preconditions: Stations array sorted; K >= 1.

class GasStationMinMaxDistance {
private:
    static bool possible(const std::vector<double>& stations, int k, double d) {
        int added = 0;
        for (size_t i = 1; i < stations.size(); ++i) {
            added += static_cast<int>((stations[i] - stations[i - 1]) / d);
        }
        return added <= k;
    }

public:
    static double minmax_gas_dist(const std::vector<double>& stations, int k, int iterations = 100) {
        double low = 0.0;
        double high = stations.back() - stations.front();

        for (int i = 0; i < iterations; ++i) {
            double mid = low + (high - low) / 2.0;
            if (possible(stations, k, mid)) {
                high = mid;
            } else {
                low = mid;
            }
        }
        return (low + high) / 2.0;
    }
};

int main() {
    std::vector<double> stations = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    double ans = GasStationMinMaxDistance::minmax_gas_dist(stations, 9);
    assert(std::abs(ans - 0.5) < 1e-3);

    std::cout << "minimize_max_distance_to_gas_station tests passed successfully.\n";
    return 0;
}
"""
    },
    {
        "filename": "median_sorted_matrix.cpp",
        "algorithm": "Median in a Row-Wise Sorted Matrix",
        "purpose": "Finds median element of an R x C matrix where each row is sorted in O(32 * R * log C) time without allocating extra memory.",
        "time_complexity": "O(32 * R * log C) time",
        "space_complexity": "O(1) auxiliary space",
        "preconditions": "R * C is odd.",
        "code": r"""#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Algorithm: Median in a Row-Wise Sorted Matrix
// Purpose: Finds median element of an R x C matrix where each row is sorted in O(32 * R * log C) time without allocating extra memory.
// Time Complexity: O(32 * R * log C) time
// Space Complexity: O(1) auxiliary space
// Preconditions: R * C is odd.

class RowWiseSortedMatrixMedian {
public:
    static int find_median(const std::vector<std::vector<int>>& mat) {
        int r = mat.size();
        int c = mat[0].size();
        int low = 1e9, high = -1e9;

        for (int i = 0; i < r; ++i) {
            low = std::min(low, mat[i][0]);
            high = std::max(high, mat[i][c - 1]);
        }

        int desired = (r * c + 1) / 2;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            int count = 0;

            for (int i = 0; i < r; ++i) {
                count += std::upper_bound(mat[i].begin(), mat[i].end(), mid) - mat[i].begin();
            }

            if (count < desired) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return low;
    }
};

int main() {
    std::vector<std::vector<int>> mat = {
        {1, 3, 5},
        {2, 6, 9},
        {3, 6, 9}
    };
    // Elements: 1, 2, 3, 3, 5, 6, 6, 9, 9 -> median is 5
    assert(RowWiseSortedMatrixMedian::find_median(mat) == 5);

    std::cout << "median_sorted_matrix tests passed successfully.\n";
    return 0;
}
"""
    }
]

def main():
    TARGET_DIR.mkdir(parents=True, exist_ok=True)
    count = 0
    for item in FILES:
        path = TARGET_DIR / item["filename"]
        path.write_text(item["code"].strip() + "\n", encoding="utf-8")
        count += 1
        print(f"Wrote [{count}/{len(FILES)}]: {item['filename']}")
    print(f"\nBatch 2 completed: {count} implementations written to {TARGET_DIR.name}")

if __name__ == "__main__":
    main()
