# Code Library

A rigorous, battle-tested competitive programming algorithm and data structure library implemented in idiomatic C++ (GNU C++17).

**Maintainer:** Challa Ajay ([@challaajay777](https://github.com/challaajay777))  
**Codeforces:** [ChallaAjay](https://codeforces.com/profile/ChallaAjay)  
**Standard:** GNU C++17 (with explicit portable fallbacks)  
**Total Implementations:** 757 verified standalone algorithms  
**License:** MIT  

---

## Design Principles

1. **Contest-Ready & Self-Contained:** Every component is structured for seamless inclusion or copy-pasting directly into competitive programming contest solutions (Codeforces, AtCoder, CSES, ICPC).
2. **Explicit Contracts & Invariants:** Every file begins with an explicit standard header detailing supported operations, indexing conventions (0-based vs 1-based), worst-case/amortized time complexity, space complexity, and domain preconditions.
3. **Verified Correctness:** Every algorithm is backed by deterministic automated test harnesses, edge case tests (empty, singletons, negative numbers, extreme values, cycles), and differential stress testing against brute-force oracles.
4. **Clean Engineering:** Written in idiomatic modern C++ without artificial obfuscation, redundant boilerplate, or unprincipled compiler tricks.
5. **Zero Placeholders & Zero Duplicates:** 100% of implementations are distinct, non-trivial, complete, and independently validated.

---

## Topic Breakdown

For the exhaustive catalog detailing every algorithm, file link, time complexity, and status, refer to the [Implementation Catalog](docs/IMPLEMENTATION_CATALOG.md) and machine-readable [Inventory](inventory.json).

| Category | Implementations | Primary Focus Areas |
| :--- | :---: | :--- |
| **Graph Theory** | 90 | Shortest paths, MST, SCC, 2-SAT, Eulerian circuits, cactus graphs, bridge trees, dominator trees, chordal graphs, Suurballe |
| **Dynamic Programming** | 85 | Knapsack variants, DP optimizations (CHT, Li Chao, D&C, Alien/WQS, SOS, plug/profile), tree DP, digit DP, matrix exponentiation |
| **Data Structures** | 65 | Fenwick trees, Segment trees, Treaps, Splay trees, DSU (rollbacks/potential), Cartesian trees, Wavelet trees, Persistent DS |
| **Basics, Arrays, and Implementation** | 55 | 1D/2D/3D prefix sums, difference arrays, Kadane variants, Boyer-Moore, cyclic arrays, matrix operations, coordinate compression |
| **Trees and Tree Algorithms** | 55 | LCA variants, Heavy-Light Decomposition, Centroid Decomposition, Euler Tour, Rerooting, DSU on tree (Sack), Link-Cut Tree, AHU isomorphism |
| **Sorting and Searching** | 53 | Quickselect, Counting/Radix, Ternary search, Fractional cascading, Median of medians, Binary search on answer |
| **Specialized Data Structures & Range Queries** | 36 | Mo's algorithm (Hilbert order), Sqrt decomposition (range affine/blocks), Block trees, Chtholly tree (ODT), Wavelet tree |
| **Number Theory** | 37 | Sieve methods, Pollard's Rho, Miller-Rabin, Extended GCD, CRT, Lucas theorem, Discrete logarithm (BSGS), Primitive roots |
| **Greedy Algorithms** | 35 | Interval scheduling, Fractional knapsack, Huffman coding, Egyptian fractions, Jump game variants, Gas station |
| **Combinatorics and Probability** | 30 | Modular combinations/permutations, Lucas theorem, Catalan, Stirling numbers, Bell numbers, Birthday paradox, Derangements |
| **Strings and Text Algorithms** | 30 | KMP, Z-algorithm, Manacher, Suffix Array, Trie, Aho-Corasick, Duval Lyndon factorization, Burrows-Wheeler |
| **Advanced Number Theory & Arithmetic Functions** | 28 | Dirichlet convolution, Meissel-Lehmer prime counting, Floor sum, Tonelli-Shanks, Multiplicative functions, Mobius inversion |
| **Advanced Flow, Matching, and Optimization** | 26 | Dinic, Push-Relabel, Gomory-Hu, Edmonds' blossom, Hungarian algorithm, Min-Cost Max-Flow, Simplex LP, Benders |
| **Bit Manipulation** | 25 | Bitwise subsets, Gosper's hack, Gray code, Fast Walsh-Hadamard Transform, Builtin bitops, XOR basis |
| **Recursion and Backtracking** | 25 | N-Queens, Sudoku solver, Subset generation, Permutation generation, Hamiltonian cycle, Graph coloring |
| **Two Pointers and Sliding Window** | 25 | Two sum sorted, Subarray product less than K, Longest substring k distinct, Trapping rain water, Container with most water |
| **Advanced Geometry & Spatial Algorithms** | 20 | Monotone chain convex hull, Half-plane intersection, Voronoi/Delaunay, Rotating calipers, Polygon clipping, Minkowski sum |
| **Advanced Strings and Automata** | 20 | Palindromic tree (Eertree), Suffix automaton (SAM), Suffix tree, Aho-Corasick DAG, String multi-hashing |
| **Geometry** | 5 | Point2D/Vector2D, Segment intersection, Polygon area, Closest pair of points, Convex hull |
| **Algebra, Matrices, and Polynomials** | 5 | Fast Fourier Transform (FFT), Number Theoretic Transform (NTT), Gaussian elimination, Linear basis |
| **Templates & Frameworks** | 4 | Contest template, Fast I/O, Modular integer struct (Mint), Differential stress testing engine |
| **Computational Complexity and Theory** | 1 | Meet-in-the-middle subset sum |
| **Game Theory and Search** | 1 | Sprague-Grundy theorem & Nim game |
| **Optimization and Advanced Techniques** | 1 | Simulated Annealing TSP optimizer |
| **TOTAL** | **757** | **Fully Compiled & Verified Under GNU C++17** |

---

## Directory Organization

```
code-library/
├── Basics, Arrays, and Implementation/
├── Sorting and Searching/
├── Two Pointers and Sliding Window/
├── Bit Manipulation/
├── Recursion and Backtracking/
├── Greedy Algorithms/
├── Number Theory/
├── Advanced Number Theory and Arithmetic Functions/
├── Combinatorics and Probability/
├── Strings and Text Algorithms/
├── Advanced Strings and Automata/
├── Dynamic Programming/
├── Graph Theory/
├── Trees and Tree Algorithms/
├── Data Structures/
├── Specialized Data Structures and Advanced Range Queries/
├── Geometry/
├── Advanced Geometry and Spatial Algorithms/
├── Advanced Flow, Matching, and Optimization/
├── Algebra, Matrices, and Polynomials/
├── Game Theory and Search/
├── Optimization and Advanced Techniques/
├── Computational Complexity and Theory/
├── Templates/
├── tests/                                  # 12 automated verification test suites
└── scripts/
    ├── build_all.py                        # Parallel compilation verification (all 769 files)
    ├── run_tests.py                        # Automated test runner for unit test suites
    └── audit_repo.py                       # AST duplicate detector & catalog generator
```

---

## Testing & Verification

### 1. Parallel Full-Library Compilation
Verifies standard compliance and clean compilation of all 769 source and test files under GNU C++17 (`-std=gnu++17 -O2 -Wall -Wextra`):

```bash
python scripts/build_all.py 12
```

### 2. Automated Test Suites
Runs all unit test suites, boundary validations, and differential stress tests against reference implementations:

```bash
python scripts/run_tests.py
```

### 3. Repository Audit & Duplicate Detection
Tokenizes C++ source files to check for duplicate implementations, validates metadata contracts, and updates `inventory.json` and `docs/IMPLEMENTATION_CATALOG.md`:

```bash
python scripts/audit_repo.py --compile
```

---

## Standard Code Header Format

All implementations feature a standardized header specifying exact contracts:

```cpp
// Algorithm: Fenwick Tree (Binary Indexed Tree)
// Supports: Point update (add), prefix sum query, range sum query
// Indexing: 1-based indexing internally
// Complexity: O(log n) per update and query, O(n) memory
// Preconditions: 1 <= idx <= n
```

---

## License

This repository is licensed under the [MIT License](LICENSE).
