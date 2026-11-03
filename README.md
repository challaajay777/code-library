# Code Library

A rigorous, battle-tested competitive programming algorithm and data structure library implemented in idiomatic C++ (GNU C++17).

**Maintainer:** Challa Ajay ([@challaajay777](https://github.com/challaajay777))  
**Codeforces:** [ChallaAjay](https://codeforces.com/profile/ChallaAjay)  
**Standard:** GNU C++17 (with explicit portable fallbacks)  
**License:** MIT  

---

## Design Principles

1. **Contest-Ready & Self-Contained:** Every component is structured for seamless inclusion or copy-pasting directly into competitive programming contest solutions (Codeforces, AtCoder, CSES, ICPC).
2. **Explicit Contracts & Invariants:** Every file begins with an explicit standard header detailing supported operations, indexing conventions (0-based vs 1-based), worst-case/amortized time complexity, space complexity, and domain preconditions.
3. **Verified Correctness:** Every algorithm is backed by deterministic automated test harnesses, edge case tests (empty, singletons, negative numbers, extreme values, cycles), and differential stress testing against brute-force oracles.
4. **Clean Engineering:** Written in idiomatic modern C++ without artificial obfuscation, redundant boilerplate, or unprincipled compiler tricks.

---

## Directory Structure & Implemented Algorithms

```
code-library/
├── Basics, Arrays, and Implementation/
│   ├── prefix_sums_1d.cpp                  # 1D Prefix Sums (O(1) range queries)
│   ├── prefix_sums_2d.cpp                  # 2D Subgrid Prefix Sums (O(1) range queries)
│   ├── difference_array_1d.cpp             # 1D Difference Array (O(1) range adds)
│   ├── difference_array_2d.cpp             # 2D Difference Array (O(1) subgrid adds)
│   ├── coordinate_compression.cpp          # Coordinate Compression & rank lookup
│   ├── sliding_window_min_max.cpp          # Monotone deque sliding window min/max
│   ├── maximum_subarray_sum.cpp            # Kadane's algorithm & circular max subarray
│   ├── binary_search_helpers.cpp           # First-true, last-true, integer sqrt
│   ├── ternary_search.cpp                  # Discrete and continuous ternary search
│   ├── misra_gries_heavy_hitters.cpp       # Boyer-Moore majority & Misra-Gries streaming
│   ├── interval_operations.cpp             # Interval merge, intersection, covered length
│   └── fast_exponentiation.cpp             # Modular power & fast doubling Fibonacci
│
├── Data Structures/
│   ├── fenwick_tree.cpp                    # Binary Indexed Tree (point add, range sum)
│   ├── fenwick_tree_range_add.cpp          # Dual BIT range add & range sum
│   ├── fenwick_tree_2d.cpp                 # 2D Fenwick Tree for 2D subgrid queries
│   ├── segment_tree.cpp                    # Point update, range associative query
│   ├── lazy_segment_tree.cpp               # Range add & range sum with lazy propagation
│   ├── lazy_segment_tree_assignment.cpp    # Range assign & range min with lazy propagation
│   ├── dynamic_segment_tree.cpp            # Implicit dynamic segment tree [0, 10^9]
│   ├── persistent_segment_tree.cpp         # Fully persistent segment tree
│   ├── sparse_table.cpp                    # Static RMQ with O(1) query
│   ├── disjoint_set_union.cpp              # DSU / Union-Find with path compression
│   ├── rollback_dsu.cpp                    # Rollback DSU with history stack
│   ├── treap.cpp                           # Balanced Cartesian Tree (BST + Heap)
│   ├── implicit_treap.cpp                  # Implicit Treap (rope with range reversal)
│   └── min_max_stack_queue.cpp             # O(1) Min Stack & 2-stack Min Queue
│
├── Graph Theory/
│   ├── bfs_shortest_path.cpp               # BFS with parent path reconstruction
│   ├── zero_one_bfs.cpp                    # Deque 0-1 BFS for {0, 1} edge weights
│   ├── dijkstra.cpp                        # Dijkstra's shortest path (nonnegative weights)
│   ├── bellman_ford.cpp                    # Bellman-Ford with negative cycle detection
│   ├── spfa.cpp                            # Shortest Path Faster Algorithm + SLF
│   ├── floyd_warshall.cpp                  # Floyd-Warshall all-pairs shortest paths
│   ├── kruskal_mst.cpp                     # Kruskal's MST using DSU
│   ├── prim_mst.cpp                        # Prim's MST with priority queue
│   ├── topological_sort.cpp                # Kahn's topological sort & cycle detection
│   ├── tarjan_scc.cpp                      # Tarjan's Strongly Connected Components
│   ├── kosaraju_scc.cpp                    # Kosaraju's two-pass SCC
│   ├── two_sat.cpp                         # 2-SAT solver using implication graph
│   ├── bridges_and_articulation_points.cpp # Cut edges and cut vertices
│   └── eulerian_path.cpp                   # Hierholzer's Eulerian trail & circuit
│
├── Trees and Tree Algorithms/
│   ├── binary_lifting_lca.cpp              # Binary lifting LCA & k-th ancestor
│   ├── heavy_light_decomposition.cpp       # Heavy-Light Decomposition path processing
│   ├── tree_diameter_and_center.cpp        # Tree diameter, path, and center(s)
│   ├── centroid_decomposition.cpp          # Centroid tree hierarchy
│   ├── euler_tour_flattening.cpp           # Euler tour subtree interval mapping
│   ├── tree_rerooting_dp.cpp               # 2-pass tree rerooting DP
│   └── sack_dsu_on_tree.cpp                # Small-to-large subtree merging (Sack)
│
├── Dynamic Programming/
│   ├── longest_increasing_subsequence.cpp  # O(n log n) LIS with reconstruction
│   ├── knapsack_01_and_bounded.cpp         # 0-1 & binary-split bounded knapsack
│   ├── unbounded_knapsack.cpp              # Unbounded knapsack
│   ├── convex_hull_trick.cpp               # Dynamic LineContainer for max(kx + m)
│   ├── li_chao_tree.cpp                    # Li Chao segment tree for line min queries
│   ├── divide_and_conquer_dp.cpp           # D&C DP quadrangle inequality optimization
│   ├── sos_dp.cpp                          # Sum Over Subsets (Yates' algorithm)
│   └── digit_dp.cpp                        # Digit DP framework for digit constraints
│
├── Strings and Text Algorithms/
│   ├── string_hashing.cpp                  # Double rolling polynomial hash
│   ├── kmp_prefix_function.cpp             # KMP prefix function & pattern search
│   ├── z_algorithm.cpp                     # Z-algorithm LCP & pattern search
│   ├── manacher_palindromes.cpp            # Manacher's linear palindrome finder
│   ├── trie.cpp                            # Prefix Tree (Trie)
│   ├── binary_trie.cpp                     # Binary XOR Trie for max/min XOR
│   ├── aho_corasick.cpp                    # Multi-pattern Aho-Corasick automaton
│   └── suffix_automaton.cpp                # Suffix Automaton (SAM)
│
├── Number Theory/
│   ├── sieve_of_eratosthenes.cpp           # Sieve of Eratosthenes
│   ├── linear_sieve.cpp                    # Euler's linear sieve with SPF
│   ├── extended_gcd_and_modular_inverse.cpp# Extended GCD & modular inverse
│   ├── chinese_remainder_theorem.cpp       # General non-coprime CRT solver
│   ├── euler_totient.cpp                   # Euler's phi (single value & sieve)
│   ├── miller_rabin_primality.cpp          # Deterministic 64-bit Miller-Rabin test
│   └── pollards_rho.cpp                    # Pollard's rho 64-bit factorization
│
├── Combinatorics and Probability/
│   ├── combinatorics_mod.cpp               # Modular factorials, nCr, nPr, stars & bars
│   ├── lucas_theorem.cpp                   # Lucas' theorem for large nCr mod p
│   ├── catalan_numbers.cpp                 # Catalan numbers C_n
│   ├── derangements.cpp                    # Derangements / subfactorials !n
│   └── birthday_paradox.cpp                # Birthday collision probability & binomial PMF
│
├── Geometry/
│   ├── point2d_and_vector2d.cpp            # Point2D/Vector2D dot, cross, orientation
│   ├── convex_hull_monotone_chain.cpp      # Monotone Chain convex hull
│   ├── segment_intersection.cpp            # Exact segment-segment intersection
│   ├── polygon_area_and_point_in_polygon.cpp# Shoelace formula, Pick's theorem, ray casting
│   └── closest_pair_of_points.cpp          # O(n log n) closest pair of points
│
├── Algebra, Matrices, and Polynomials/
│   ├── matrix_operations.cpp               # Matrix addition, multiplication, exponentiation
│   ├── gaussian_elimination.cpp            # Gaussian elimination over R
│   ├── xor_basis.cpp                       # Linear basis over GF(2)
│   ├── fast_fourier_transform.cpp          # Cooley-Tukey FFT polynomial multiplication
│   └── number_theoretic_transform.cpp      # NTT modulo 998244353
│
├── Advanced Flow, Matching, and Optimization/
│   ├── dinic_max_flow.cpp                  # Dinic's max flow & min-cut recovery
│   ├── edmonds_karp_max_flow.cpp           # Edmonds-Karp max flow
│   ├── hopcroft_karp_bipartite_matching.cpp# Hopcroft-Karp bipartite matching
│   └── min_cost_max_flow.cpp               # Successive Shortest Path MCMF
│
├── Game Theory and Search/
│   └── nim_game_and_grundy.cpp             # Sprague-Grundy theorem & Nim sum
│
├── Optimization and Advanced Techniques/
│   └── simulated_annealing.cpp             # Simulated Annealing TSP optimizer
│
├── Specialized Data Structures and Advanced Range Queries/
│   └── mo_algorithm_with_hilbert.cpp       # Mo's algorithm with Hilbert curve ordering
│
├── Computational Complexity and Theory/
│   └── meet_in_the_middle.cpp              # Meet in the middle subset sum
│
├── Templates/
│   ├── contest_template.cpp                # Standard contest boilerplate
│   ├── fast_io.cpp                         # Fast I/O with 64KB fread/fwrite buffer
│   ├── modular_int.cpp                     # Modular integer struct (Mint)
│   └── stress_framework.cpp                # Differential stress tester engine
│
├── tests/                                  # Comprehensive automated test suites
└── scripts/
    ├── audit_repo.py                       # Audit metadata & duplicate detector
    ├── build_all.py                        # Full syntax and standard check
    └── run_tests.py                        # Automated test runner
```

---

## Testing & Verification

### Running All Test Suites
Every component is accompanied by unit tests, boundary validations, and differential stress tests against reference implementations.

```bash
python scripts/run_tests.py
```

### Full Compilation Check
Verifies standard compliance and clean compilation of all `.cpp` files under GNU C++17 (`-std=gnu++17 -O2 -Wall -Wextra`):

```bash
python scripts/build_all.py
```

### Repository Audit & Metadata Indexing
Parses algorithmic metadata headers, checks for duplication, and generates `inventory.json`:

```bash
python scripts/audit_repo.py
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
