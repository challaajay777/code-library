# Contributing to Code Library

Thank you for your interest in contributing to **Code Library**. This repository aims to maintain a rigorous, battle-tested standard library of competitive programming algorithms and data structures implemented in idiomatic GNU C++17.

---

## 1. Quality Standards

Every contributed algorithm must meet the following criteria:

- **Language Standard:** GNU C++17.
- **Independence:** Self-contained and easily copy-pastable into contest solutions (Codeforces, AtCoder, CSES, ICPC).
- **Correctness & Verification:** Accompanied by automated unit tests or differential tests against a brute-force oracle.
- **No Redundant Duplication:** Genuinely distinct algorithms or material algorithmic variants only. Renaming variables or slight cosmetic restructuring of an existing algorithm does not count.
- **Safety & Precision:** Explicit edge-case handling (empty sets, singletons, negative numbers, extreme constraints, overflow avoidance with `long long` or `__int128`).

---

## 2. Standard Header Specification

Every source file must begin with a standardized metadata header:

```cpp
// Algorithm: Exact Algorithm Name
// Purpose: Concise description of what the implementation solves
// Time Complexity: Worst-case / amortized time complexity (e.g., O(n log n))
// Space Complexity: Auxiliary space complexity (e.g., O(n))
// Preconditions: Explicit domain assumptions (e.g., 0 <= u, v < n, nonnegative weights)
// Distinctness Notes: Specific differences from related variants (optional)
```

---

## 3. Contribution Workflow

1. **Check Existing Catalog:** Review [`docs/IMPLEMENTATION_CATALOG.md`](docs/IMPLEMENTATION_CATALOG.md) to ensure the algorithm is not already present.
2. **Implement:** Place the implementation in the appropriate topic directory using snake_case (e.g., `convex_hull_trick.cpp`).
3. **Add Tests:** Add unit tests to the corresponding test suite in `tests/` covering:
   - Typical cases
   - Boundary inputs (minimum/maximum sizes, empty/singleton)
   - Edge cases (duplicates, sorted, reverse-sorted, negative numbers, disconnected graphs)
   - Differential stress testing against a brute-force oracle
4. **Audit & Build:**
   ```bash
   python scripts/build_all.py
   python scripts/run_tests.py
   python scripts/audit_repo.py --compile
   ```
5. **Submit PR:** Submit a concise Pull Request with a clear description of the technique and problem types it targets.
