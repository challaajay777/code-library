# Implementation Catalog

**Total Verified Implementations:** 757  
**Total Lines of Code:** 38582  
**Duplicate Implementations Detected:** 0  
**Standard:** GNU C++17  

---

## Topic Summary

| Topic | Count |
| :--- | :---: |
| Advanced Flow, Matching, and Optimization | 26 |
| Advanced Geometry and Spatial Algorithms | 20 |
| Advanced Number Theory and Arithmetic Functions | 28 |
| Advanced Strings and Automata | 20 |
| Algebra, Matrices, and Polynomials | 5 |
| Basics, Arrays, and Implementation | 55 |
| Bit Manipulation | 25 |
| Combinatorics and Probability | 30 |
| Computational Complexity and Theory | 1 |
| Data Structures | 65 |
| Dynamic Programming | 85 |
| Game Theory and Search | 1 |
| Geometry | 5 |
| Graph Theory | 90 |
| Greedy Algorithms | 35 |
| Number Theory | 37 |
| Optimization and Advanced Techniques | 1 |
| Recursion and Backtracking | 25 |
| Sorting and Searching | 53 |
| Specialized Data Structures and Advanced Range Queries | 36 |
| Strings and Text Algorithms | 30 |
| Templates | 4 |
| Trees and Tree Algorithms | 55 |
| Two Pointers and Sliding Window | 25 |

---

## Complete Implementations

### Advanced Flow, Matching, and Optimization (26 implementations)

| ID | Algorithm | File | Complexity | Status |
| :--- | :--- | :--- | :--- | :---: |
| `ALG-0001` | **Benders Decomposition for Mixed-Integer Programs** | [benders_decomposition_mip.cpp](../Advanced%20Flow,%20Matching,%20and%20Optimization/benders_decomposition_mip.cpp) | `Iterative Benders iterations` | `VERIFIED` |
| `ALG-0002` | **Bipartite Edge Coloring with Delta Colors** | [bipartite_edge_coloring_regular.cpp](../Advanced%20Flow,%20Matching,%20and%20Optimization/bipartite_edge_coloring_regular.cpp) | `O(E * Delta)` | `VERIFIED` |
| `ALG-0003` | **Hungarian Algorithm for Bipartite Assignment** | [bipartite_min_cost_perfect_matching_hungarian.cpp](../Advanced%20Flow,%20Matching,%20and%20Optimization/bipartite_min_cost_perfect_matching_hungarian.cpp) | `O(N^3)` | `VERIFIED` |
| `ALG-0004` | **Branch and Bound Exact 0/1 Knapsack** | [branch_and_bound_01_knapsack.cpp](../Advanced%20Flow,%20Matching,%20and%20Optimization/branch_and_bound_01_knapsack.cpp) | `O(2^N) worst-case, fast on typical instances` | `VERIFIED` |
| `ALG-0005` | **Circulation with Lower Bounds and Demands** | [circulation_demands_lower_bounds.cpp](../Advanced%20Flow,%20Matching,%20and%20Optimization/circulation_demands_lower_bounds.cpp) | `O(V^2 * E)` | `VERIFIED` |
| `ALG-0006` | **Dilworth Theorem Maximum Antichain** | [dilworth_theorem_antichain.cpp](../Advanced%20Flow,%20Matching,%20and%20Optimization/dilworth_theorem_antichain.cpp) | `O(V^3)` | `VERIFIED` |
| `ALG-0007` | **Dinic Max Flow with Capacity Scaling** | [dinic_capacity_scaling.cpp](../Advanced%20Flow,%20Matching,%20and%20Optimization/dinic_capacity_scaling.cpp) | `O(V * E * log(MaxCap))` | `VERIFIED` |
| `ALG-0008` | **Dinic's Maximum Flow** | [dinic_max_flow.cpp](../Advanced%20Flow,%20Matching,%20and%20Optimization/dinic_max_flow.cpp) | `O(V^2 * E) general, O(E * sqrt(V)) unit capacity, O(V + E) memory` | `VERIFIED` |
| `ALG-0009` | **Dual Simplex Method for Linear Programming** | [dual_simplex_linear_programming.cpp](../Advanced%20Flow,%20Matching,%20and%20Optimization/dual_simplex_linear_programming.cpp) | `Exponential worst-case, fast in practice` | `VERIFIED` |
| `ALG-0010` | **Edmonds Blossom Maximum Matching on General Graphs** | [edmonds_blossom_general_matching.cpp](../Advanced%20Flow,%20Matching,%20and%20Optimization/edmonds_blossom_general_matching.cpp) | `O(V^3)` | `VERIFIED` |
| `ALG-0011` | **Edmonds-Karp Maximum Flow** | [edmonds_karp_max_flow.cpp](../Advanced%20Flow,%20Matching,%20and%20Optimization/edmonds_karp_max_flow.cpp) | `O(V * E^2) time, O(V + E) memory` | `VERIFIED` |
| `ALG-0012` | **Gomory-Hu Tree for All-Pairs Min Cut** | [gomory_hu_tree_all_pairs_min_cut.cpp](../Advanced%20Flow,%20Matching,%20and%20Optimization/gomory_hu_tree_all_pairs_min_cut.cpp) | `O(V * MaxFlow)` | `VERIFIED` |
| `ALG-0013` | **Hopcroft-Karp Maximum Bipartite Matching** | [hopcroft_karp_bipartite_matching.cpp](../Advanced%20Flow,%20Matching,%20and%20Optimization/hopcroft_karp_bipartite_matching.cpp) | `O(E * sqrt(V)) time, O(V + E) memory` | `VERIFIED` |
| `ALG-0014` | **K-Regular Bipartite Graph Perfect Matching** | [k_regular_bipartite_graph_matching.cpp](../Advanced%20Flow,%20Matching,%20and%20Optimization/k_regular_bipartite_graph_matching.cpp) | `O(E sqrt(V))` | `VERIFIED` |
| `ALG-0015` | **Sinkhorn-Knopp Matrix Scaling** | [matrix_scaling_sinkhorn.cpp](../Advanced%20Flow,%20Matching,%20and%20Optimization/matrix_scaling_sinkhorn.cpp) | `O(Iterations * R * C)` | `VERIFIED` |
| `ALG-0016` | **Goldberg Maximum Density Subgraph** | [maximum_density_subgraph_goldberg.cpp](../Advanced%20Flow,%20Matching,%20and%20Optimization/maximum_density_subgraph_goldberg.cpp) | `O(log(V) * V * E^2)` | `VERIFIED` |
| `ALG-0017` | **Project Selection Problem (Max-Weight Closure)** | [maximum_weight_closure_project_selection.cpp](../Advanced%20Flow,%20Matching,%20and%20Optimization/maximum_weight_closure_project_selection.cpp) | `O(V^2 * E)` | `VERIFIED` |
| `ALG-0018` | **Maximum Weight Matching on General Graphs** | [maximum_weight_matching_blossom.cpp](../Advanced%20Flow,%20Matching,%20and%20Optimization/maximum_weight_matching_blossom.cpp) | `O(V^3)` | `VERIFIED` |
| `ALG-0019` | **Klein Cycle-Canceling Algorithm** | [min_cost_circulation_cycle_canceling.cpp](../Advanced%20Flow,%20Matching,%20and%20Optimization/min_cost_circulation_cycle_canceling.cpp) | `O(E * C * BellmanFord)` | `VERIFIED` |
| `ALG-0020` | **Minimum-Cost Maximum-Flow (MCMF - Successive Shortest Path)** | [min_cost_max_flow.cpp](../Advanced%20Flow,%20Matching,%20and%20Optimization/min_cost_max_flow.cpp) | `O(F * V * E) where F is total flow, O(V + E) memory` | `VERIFIED` |
| `ALG-0021` | **MCMF with Dijkstra and Johnson Potentials** | [min_cost_max_flow_dijkstra_potentials.cpp](../Advanced%20Flow,%20Matching,%20and%20Optimization/min_cost_max_flow_dijkstra_potentials.cpp) | `O(F * E log V)` | `VERIFIED` |
| `ALG-0022` | **Min-Cost Max-Flow via Successive Shortest Paths** | [min_cost_max_flow_successive_shortest_path.cpp](../Advanced%20Flow,%20Matching,%20and%20Optimization/min_cost_max_flow_successive_shortest_path.cpp) | `O(F * V * E)` | `VERIFIED` |
| `ALG-0023` | **Minimum Path Cover in DAG via Bipartite Matching** | [minimum_path_cover_dag.cpp](../Advanced%20Flow,%20Matching,%20and%20Optimization/minimum_path_cover_dag.cpp) | `O(V * E)` | `VERIFIED` |
| `ALG-0024` | **Push-Relabel with Highest-Label Pre-flow Push** | [push_relabel_highest_label_preflow.cpp](../Advanced%20Flow,%20Matching,%20and%20Optimization/push_relabel_highest_label_preflow.cpp) | `O(V^2 sqrt(E))` | `VERIFIED` |
| `ALG-0025` | **Two-Phase Simplex Algorithm for Linear Programs** | [simplex_two_phase_lp_solver.cpp](../Advanced%20Flow,%20Matching,%20and%20Optimization/simplex_two_phase_lp_solver.cpp) | `Exponential worst-case, polynomial average` | `VERIFIED` |
| `ALG-0026` | **Irving Algorithm for Stable Roommates** | [stable_roommates_irving_algorithm.cpp](../Advanced%20Flow,%20Matching,%20and%20Optimization/stable_roommates_irving_algorithm.cpp) | `O(N^2)` | `VERIFIED` |

### Advanced Geometry and Spatial Algorithms (20 implementations)

| ID | Algorithm | File | Complexity | Status |
| :--- | :--- | :--- | :--- | :---: |
| `ALG-0027` | **Circle-Circle Intersection Area** | [circle_circle_intersection_area.cpp](../Advanced%20Geometry%20and%20Spatial%20Algorithms/circle_circle_intersection_area.cpp) | `O(1)` | `VERIFIED` |
| `ALG-0028` | **Circle and Line Intersection Points** | [circle_line_intersection_points.cpp](../Advanced%20Geometry%20and%20Spatial%20Algorithms/circle_line_intersection_points.cpp) | `O(1)` | `VERIFIED` |
| `ALG-0029` | **Circumcircle and Incircle of Triangle** | [circumscribed_and_inscribed_circle.cpp](../Advanced%20Geometry%20and%20Spatial%20Algorithms/circumscribed_and_inscribed_circle.cpp) | `O(1)` | `VERIFIED` |
| `ALG-0030` | **Common Tangents Between Two Circles** | [common_tangents_two_circles.cpp](../Advanced%20Geometry%20and%20Spatial%20Algorithms/common_tangents_two_circles.cpp) | `O(1)` | `VERIFIED` |
| `ALG-0031` | **Convex Polygon Cut by Directed Line** | [convex_polygon_cut_by_line.cpp](../Advanced%20Geometry%20and%20Spatial%20Algorithms/convex_polygon_cut_by_line.cpp) | `O(N)` | `VERIFIED` |
| `ALG-0032` | **2D Delaunay Triangulation Concept** | [delaunay_triangulation_2d.cpp](../Advanced%20Geometry%20and%20Spatial%20Algorithms/delaunay_triangulation_2d.cpp) | `O(N log N)` | `VERIFIED` |
| `ALG-0033` | **Graham Scan Convex Hull** | [graham_scan_convex_hull.cpp](../Advanced%20Geometry%20and%20Spatial%20Algorithms/graham_scan_convex_hull.cpp) | `O(N log N)` | `VERIFIED` |
| `ALG-0034` | **Half-Plane Intersection in O(N log N)** | [halfplane_intersection_nlogn.cpp](../Advanced%20Geometry%20and%20Spatial%20Algorithms/halfplane_intersection_nlogn.cpp) | `O(N log N)` | `VERIFIED` |
| `ALG-0035` | **Maximum Collinear Points via Slope Hashing** | [maximum_collinear_points_slope.cpp](../Advanced%20Geometry%20and%20Spatial%20Algorithms/maximum_collinear_points_slope.cpp) | `O(N^2)` | `VERIFIED` |
| `ALG-0036` | **Minimum Area Bounding Box (Rotating Calipers)** | [minimum_area_bounding_box.cpp](../Advanced%20Geometry%20and%20Spatial%20Algorithms/minimum_area_bounding_box.cpp) | `O(N)` | `VERIFIED` |
| `ALG-0037` | **Minkowski Sum of Two Convex Polygons** | [minkowski_sum_convex_polygons.cpp](../Advanced%20Geometry%20and%20Spatial%20Algorithms/minkowski_sum_convex_polygons.cpp) | `O(N + M)` | `VERIFIED` |
| `ALG-0038` | **Pick's Theorem for Lattice Polygons** | [picks_theorem_lattice_polygon.cpp](../Advanced%20Geometry%20and%20Spatial%20Algorithms/picks_theorem_lattice_polygon.cpp) | `O(N log(MaxCoord))` | `VERIFIED` |
| `ALG-0039` | **Point in Convex Polygon in O(log N)** | [point_in_convex_polygon_log_n.cpp](../Advanced%20Geometry%20and%20Spatial%20Algorithms/point_in_convex_polygon_log_n.cpp) | `O(log N)` | `VERIFIED` |
| `ALG-0040` | **Point to Line Segment Minimum Distance** | [point_to_segment_distance.cpp](../Advanced%20Geometry%20and%20Spatial%20Algorithms/point_to_segment_distance.cpp) | `O(1)` | `VERIFIED` |
| `ALG-0041` | **Polygon Geometric Centroid Calculation** | [polygon_centroid_and_center_of_mass.cpp](../Advanced%20Geometry%20and%20Spatial%20Algorithms/polygon_centroid_and_center_of_mass.cpp) | `O(N)` | `VERIFIED` |
| `ALG-0042` | **Rotating Calipers Convex Polygon Diameter** | [rotating_calipers_polygon_diameter.cpp](../Advanced%20Geometry%20and%20Spatial%20Algorithms/rotating_calipers_polygon_diameter.cpp) | `O(N)` | `VERIFIED` |
| `ALG-0043` | **Rotating Calipers Convex Polygon Minimum Width** | [rotating_calipers_polygon_width.cpp](../Advanced%20Geometry%20and%20Spatial%20Algorithms/rotating_calipers_polygon_width.cpp) | `O(N)` | `VERIFIED` |
| `ALG-0044` | **Tangent Lines from Point to Circle** | [tangent_lines_point_to_circle.cpp](../Advanced%20Geometry%20and%20Spatial%20Algorithms/tangent_lines_point_to_circle.cpp) | `O(1)` | `VERIFIED` |
| `ALG-0045` | **Voronoi Diagram Geometric Dual** | [voronoi_diagram_dual.cpp](../Advanced%20Geometry%20and%20Spatial%20Algorithms/voronoi_diagram_dual.cpp) | `O(N log N)` | `VERIFIED` |
| `ALG-0046` | **Welzl Minimum Enclosing Circle (Randomized O(N))** | [welzl_minimum_enclosing_circle.cpp](../Advanced%20Geometry%20and%20Spatial%20Algorithms/welzl_minimum_enclosing_circle.cpp) | `O(N) expected` | `VERIFIED` |

### Advanced Number Theory and Arithmetic Functions (28 implementations)

| ID | Algorithm | File | Complexity | Status |
| :--- | :--- | :--- | :--- | :---: |
| `ALG-0047` | **Carmichael Lambda Function** | [carmichael_lambda_function.cpp](../Advanced%20Number%20Theory%20and%20Arithmetic%20Functions/carmichael_lambda_function.cpp) | `O(sqrt(N)) time` | `VERIFIED` |
| `ALG-0048` | **Cipolla's Algorithm (Modular Square Root in Field Extension)** | [cipolla_modular_sqrt.cpp](../Advanced%20Number%20Theory%20and%20Arithmetic%20Functions/cipolla_modular_sqrt.cpp) | `O(log p) expected time` | `VERIFIED` |
| `ALG-0049` | **Cornacchia's Algorithm (x^2 + d*y^2 = p)** | [cornacchia_algorithm.cpp](../Advanced%20Number%20Theory%20and%20Arithmetic%20Functions/cornacchia_algorithm.cpp) | `O(log p) time` | `VERIFIED` |
| `ALG-0050` | **Dirichlet Convolution of Arithmetic Functions** | [dirichlet_convolution.cpp](../Advanced%20Number%20Theory%20and%20Arithmetic%20Functions/dirichlet_convolution.cpp) | `O(N log N) time` | `VERIFIED` |
| `ALG-0051` | **Pohlig-Hellman Algorithm (Discrete Logarithm for Smooth Orders)** | [discrete_log_pohlig_hellman.cpp](../Advanced%20Number%20Theory%20and%20Arithmetic%20Functions/discrete_log_pohlig_hellman.cpp) | `O(sum e_i * sqrt(p_i)) time` | `VERIFIED` |
| `ALG-0052` | **Du Sieve for Euler Totient Prefix Sums** | [du_sieve_phi_sum.cpp](../Advanced%20Number%20Theory%20and%20Arithmetic%20Functions/du_sieve_phi_sum.cpp) | `O(N^(2/3)) time` | `VERIFIED` |
| `ALG-0053` | **Eisenstein Integers GCD and Norm** | [eisenstein_integers_gcd.cpp](../Advanced%20Number%20Theory%20and%20Arithmetic%20Functions/eisenstein_integers_gcd.cpp) | `O(log(Norm)) time` | `VERIFIED` |
| `ALG-0054` | **Elliptic Curve Point Addition and Multiplication** | [elliptic_curve_point_addition.cpp](../Advanced%20Number%20Theory%20and%20Arithmetic%20Functions/elliptic_curve_point_addition.cpp) | `O(log k) operations per scalar multiplication k * P` | `VERIFIED` |
| `ALG-0055` | **Lenstra Elliptic Curve Factorization (ECM)** | [factorization_lenstra_ecm.cpp](../Advanced%20Number%20Theory%20and%20Arithmetic%20Functions/factorization_lenstra_ecm.cpp) | `O(exp((1 + o(1)) * sqrt(log p * log log p))) subexponential in smallest prime factor p` | `VERIFIED` |
| `ALG-0056` | **Farey Sequence Neighbor Finding** | [farey_sequence_neighbors.cpp](../Advanced%20Number%20Theory%20and%20Arithmetic%20Functions/farey_sequence_neighbors.cpp) | `O(log n) time` | `VERIFIED` |
| `ALG-0057` | **Fast Doubling Fibonacci** | [fibonacci_matrix_doubling.cpp](../Advanced%20Number%20Theory%20and%20Arithmetic%20Functions/fibonacci_matrix_doubling.cpp) | `O(log N) time` | `VERIFIED` |
| `ALG-0058` | **Gaussian Integers GCD and Norm** | [gaussian_integers_gcd.cpp](../Advanced%20Number%20Theory%20and%20Arithmetic%20Functions/gaussian_integers_gcd.cpp) | `O(log(Norm)) time` | `VERIFIED` |
| `ALG-0059` | **Kronecker Symbol** | [kronecker_symbol.cpp](../Advanced%20Number%20Theory%20and%20Arithmetic%20Functions/kronecker_symbol.cpp) | `O(log(min(|a|, |n|))) time` | `VERIFIED` |
| `ALG-0060` | **Legendre and Jacobi Symbol Computation** | [legendre_symbol_jacobi_symbol.cpp](../Advanced%20Number%20Theory%20and%20Arithmetic%20Functions/legendre_symbol_jacobi_symbol.cpp) | `O(log(min(a, n))) time` | `VERIFIED` |
| `ALG-0061` | **Generalized Lucas Theorem (Prime Powers p^k)** | [lucas_theorem_generalized.cpp](../Advanced%20Number%20Theory%20and%20Arithmetic%20Functions/lucas_theorem_generalized.cpp) | `O(p^k + log_p N) time` | `VERIFIED` |
| `ALG-0062` | **Meissel-Lehmer Prime Counting** | [meissel_lehmer_prime_count.cpp](../Advanced%20Number%20Theory%20and%20Arithmetic%20Functions/meissel_lehmer_prime_count.cpp) | `O(N^(2/3)) time` | `VERIFIED` |
| `ALG-0063` | **Mertens Function (Sublinear Sum of Mobius)** | [mertens_function_sublinear.cpp](../Advanced%20Number%20Theory%20and%20Arithmetic%20Functions/mertens_function_sublinear.cpp) | `O(N^(2/3)) time` | `VERIFIED` |
| `ALG-0064` | **Min25 Sieve (Prime Counting Function pi(N))** | [min25_sieve_prime_counting.cpp](../Advanced%20Number%20Theory%20and%20Arithmetic%20Functions/min25_sieve_prime_counting.cpp) | `O(N^(3/4) / log N) time` | `VERIFIED` |
| `ALG-0065` | **Mobius Inversion Framework** | [mobius_inversion_formula.cpp](../Advanced%20Number%20Theory%20and%20Arithmetic%20Functions/mobius_inversion_formula.cpp) | `O(N log N) time` | `VERIFIED` |
| `ALG-0066` | **Multiplicative Order Modulo M** | [multiplicative_order_modulo_m.cpp](../Advanced%20Number%20Theory%20and%20Arithmetic%20Functions/multiplicative_order_modulo_m.cpp) | `O(sqrt(phi(m))) time` | `VERIFIED` |
| `ALG-0067` | **Padovan and Perrin Sequence Generator** | [padovan_and_perrin_sequence.cpp](../Advanced%20Number%20Theory%20and%20Arithmetic%20Functions/padovan_and_perrin_sequence.cpp) | `O(log N) time` | `VERIFIED` |
| `ALG-0068` | **Pell's Equation Solver (x^2 - D*y^2 = 1)** | [pell_equation_solver.cpp](../Advanced%20Number%20Theory%20and%20Arithmetic%20Functions/pell_equation_solver.cpp) | `O(period * log D) time` | `VERIFIED` |
| `ALG-0069` | **Pisano Period Modulo M** | [pisano_period.cpp](../Advanced%20Number%20Theory%20and%20Arithmetic%20Functions/pisano_period.cpp) | `O(M^2) time` | `VERIFIED` |
| `ALG-0070` | **Berggren's Tree of Primitive Pythagorean Triples** | [primitive_pythagorean_tree.cpp](../Advanced%20Number%20Theory%20and%20Arithmetic%20Functions/primitive_pythagorean_tree.cpp) | `O(3^Depth) time` | `VERIFIED` |
| `ALG-0071` | **Primitive Roots for Composite Moduli** | [primitive_root_composite.cpp](../Advanced%20Number%20Theory%20and%20Arithmetic%20Functions/primitive_root_composite.cpp) | `O(Ans * log^2 M) time` | `VERIFIED` |
| `ALG-0072` | **Euler's Criterion for Quadratic Residues** | [quadratic_residue_check.cpp](../Advanced%20Number%20Theory%20and%20Arithmetic%20Functions/quadratic_residue_check.cpp) | `O(log P) time` | `VERIFIED` |
| `ALG-0073` | **Stern's Diatomic Sequence (Fusc Function)** | [stern_sequence.cpp](../Advanced%20Number%20Theory%20and%20Arithmetic%20Functions/stern_sequence.cpp) | `O(log N) time` | `VERIFIED` |
| `ALG-0074` | **Hensel's Lemma for Polynomial Roots Modulo Prime Powers** | [tonelli_shanks_sqrt_modular.cpp](../Advanced%20Number%20Theory%20and%20Arithmetic%20Functions/tonelli_shanks_sqrt_modular.cpp) | `O(k) steps` | `VERIFIED` |

### Advanced Strings and Automata (20 implementations)

| ID | Algorithm | File | Complexity | Status |
| :--- | :--- | :--- | :--- | :---: |
| `ALG-0075` | **Aho-Corasick DP for Forbidden Words** | [aho_corasick_dp_forbidden.cpp](../Advanced%20Strings%20and%20Automata/aho_corasick_dp_forbidden.cpp) | `O(L * N * Sigma)` | `VERIFIED` |
| `ALG-0076` | **Burstsort String Sorting** | [burst_sort_trie.cpp](../Advanced%20Strings%20and%20Automata/burst_sort_trie.cpp) | `O(N * L)` | `VERIFIED` |
| `ALG-0077` | **FM-Index Count Query via Burrows-Wheeler Transform** | [bwt_fm_index_count.cpp](../Advanced%20Strings%20and%20Automata/bwt_fm_index_count.cpp) | `O(M) per count query, O(N * Sigma) index build` | `VERIFIED` |
| `ALG-0078` | **De Bruijn Sequence Generator via Lyndon Words** | [debruijn_sequence_generator.cpp](../Advanced%20Strings%20and%20Automata/debruijn_sequence_generator.cpp) | `O(k^n)` | `VERIFIED` |
| `ALG-0079` | **Generalized Suffix Automaton for Trie / Set of Strings** | [generalized_suffix_automaton.cpp](../Advanced%20Strings%20and%20Automata/generalized_suffix_automaton.cpp) | `O(Sigma * sum(|Si|))` | `VERIFIED` |
| `ALG-0080` | **Convert KMP Pi Function to Z-Algorithm Array** | [kmp_pi_to_z_algorithm.cpp](../Advanced%20Strings%20and%20Automata/kmp_pi_to_z_algorithm.cpp) | `O(N)` | `VERIFIED` |
| `ALG-0081` | **Longest Common Extension (LCE) via Suffix Array and RMQ** | [lce_longest_common_extension.cpp](../Advanced%20Strings%20and%20Automata/lce_longest_common_extension.cpp) | `O(N log N) precomputation, O(1) per query` | `VERIFIED` |
| `ALG-0082` | **Longest Chunked Palindrome Decomposition (LCPD)** | [longest_chunked_palindrome_decomposition.cpp](../Advanced%20Strings%20and%20Automata/longest_chunked_palindrome_decomposition.cpp) | `O(N)` | `VERIFIED` |
| `ALG-0083` | **Lyndon Word Factorization and Minimal Rotation** | [lyndon_word_min_rotation.cpp](../Advanced%20Strings%20and%20Automata/lyndon_word_min_rotation.cpp) | `O(N)` | `VERIFIED` |
| `ALG-0084` | **Main-Lorentz Repetition Finder** | [main_lorentz_repetitions.cpp](../Advanced%20Strings%20and%20Automata/main_lorentz_repetitions.cpp) | `O(N log N)` | `VERIFIED` |
| `ALG-0085` | **Palindromic Substring Counting via Manacher** | [manacher_palindromic_subsequences.cpp](../Advanced%20Strings%20and%20Automata/manacher_palindromic_subsequences.cpp) | `O(N)` | `VERIFIED` |
| `ALG-0086` | **Shortest Palindromic Prefix & Suffix Cuts** | [minimum_cut_prefix_palindrome.cpp](../Advanced%20Strings%20and%20Automata/minimum_cut_prefix_palindrome.cpp) | `O(N)` | `VERIFIED` |
| `ALG-0087` | **Minimum Palindrome Factorization via Palindromic Tree** | [palindromic_tree_factorization.cpp](../Advanced%20Strings%20and%20Automata/palindromic_tree_factorization.cpp) | `O(N log N)` | `VERIFIED` |
| `ALG-0088` | **2D Polynomial Rolling Hash for Subgrid Matching** | [string_hash_2d_matrix.cpp](../Advanced%20Strings%20and%20Automata/string_hash_2d_matrix.cpp) | `O(R * C) precomputation, O(1) query` | `VERIFIED` |
| `ALG-0089` | **Count and Total Length of Distinct Substrings via SAM** | [suffix_automaton_distinct_substrings.cpp](../Advanced%20Strings%20and%20Automata/suffix_automaton_distinct_substrings.cpp) | `O(N * Sigma)` | `VERIFIED` |
| `ALG-0090` | **K-th Lexicographical Substring via Suffix Automaton** | [suffix_automaton_kth_substring.cpp](../Advanced%20Strings%20and%20Automata/suffix_automaton_kth_substring.cpp) | `O(N * Sigma) to build, O(|result|) per query` | `VERIFIED` |
| `ALG-0091` | **Multiple String LCS via Suffix Automaton** | [suffix_automaton_lcs_multiple.cpp](../Advanced%20Strings%20and%20Automata/suffix_automaton_lcs_multiple.cpp) | `O(N1 * Sigma + sum(Ni))` | `VERIFIED` |
| `ALG-0092` | **Three-Way String Quicksort (Bentley-Sedgewick)** | [three_way_string_quicksort.cpp](../Advanced%20Strings%20and%20Automata/three_way_string_quicksort.cpp) | `O(N * L)` | `VERIFIED` |
| `ALG-0093` | **Ukkonen Online Suffix Tree Construction** | [ukkonen_suffix_tree_online.cpp](../Advanced%20Strings%20and%20Automata/ukkonen_suffix_tree_online.cpp) | `O(N * Sigma)` | `VERIFIED` |
| `ALG-0094` | **Convert Z-Algorithm Array to KMP Pi Function** | [z_algorithm_to_kmp_pi.cpp](../Advanced%20Strings%20and%20Automata/z_algorithm_to_kmp_pi.cpp) | `O(N)` | `VERIFIED` |

### Algebra, Matrices, and Polynomials (5 implementations)

| ID | Algorithm | File | Complexity | Status |
| :--- | :--- | :--- | :--- | :---: |
| `ALG-0095` | **Fast Fourier Transform (FFT)** | [fast_fourier_transform.cpp](../Algebra,%20Matrices,%20and%20Polynomials/fast_fourier_transform.cpp) | `O(N log N) time, O(N) memory` | `VERIFIED` |
| `ALG-0096` | **Gaussian Elimination (System of Linear Equations)** | [gaussian_elimination.cpp](../Algebra,%20Matrices,%20and%20Polynomials/gaussian_elimination.cpp) | `O(min(n, m) * n * m) time, O(n * m) memory` | `VERIFIED` |
| `ALG-0097` | **Matrix Operations & Fast Exponentiation** | [matrix_operations.cpp](../Algebra,%20Matrices,%20and%20Polynomials/matrix_operations.cpp) | `O(n^3) multiplication, O(n^3 log k) exponentiation, O(n^3) determinant` | `VERIFIED` |
| `ALG-0098` | **Number Theoretic Transform (NTT)** | [number_theoretic_transform.cpp](../Algebra,%20Matrices,%20and%20Polynomials/number_theoretic_transform.cpp) | `O(N log N) time, O(N) memory` | `VERIFIED` |
| `ALG-0099` | **Linear Basis / XOR Basis (Gaussian Elimination over GF(2))** | [xor_basis.cpp](../Algebra,%20Matrices,%20and%20Polynomials/xor_basis.cpp) | `O(BITS) per insertion and query, O(BITS) memory` | `VERIFIED` |

### Basics, Arrays, and Implementation (55 implementations)

| ID | Algorithm | File | Complexity | Status |
| :--- | :--- | :--- | :--- | :---: |
| `ALG-0100` | **Dense Array Rank Transform** | [array_rank_transform.cpp](../Basics,%20Arrays,%20and%20Implementation/array_rank_transform.cpp) | `O(N log N) time` | `VERIFIED` |
| `ALG-0101` | **Binary Search Utilities** | [binary_search_helpers.cpp](../Basics,%20Arrays,%20and%20Implementation/binary_search_helpers.cpp) | `O(log(high - low)) predicate evaluations` | `VERIFIED` |
| `ALG-0102` | **Generalized Boyer-Moore Majority Vote (N/K Frequency)** | [boyer_moore_majority_k_elements.cpp](../Basics,%20Arrays,%20and%20Implementation/boyer_moore_majority_k_elements.cpp) | `O(N * K) time` | `VERIFIED` |
| `ALG-0103` | **Boyer-Moore Majority Vote (Extended to N/3 Frequency)** | [boyer_moore_majority_two_elements.cpp](../Basics,%20Arrays,%20and%20Implementation/boyer_moore_majority_two_elements.cpp) | `O(N) time` | `VERIFIED` |
| `ALG-0104` | **Circular Array Loop Detection** | [circular_array_loop_detection.cpp](../Basics,%20Arrays,%20and%20Implementation/circular_array_loop_detection.cpp) | `O(N) time` | `VERIFIED` |
| `ALG-0105` | **Coordinate Compression** | [coordinate_compression.cpp](../Basics,%20Arrays,%20and%20Implementation/coordinate_compression.cpp) | `O(n log n) sorting, O(log n) per value query, O(1) per rank lookup` | `VERIFIED` |
| `ALG-0106` | **Count Subarrays with Bounded Maximum** | [count_subarrays_bounded_maximum.cpp](../Basics,%20Arrays,%20and%20Implementation/count_subarrays_bounded_maximum.cpp) | `O(N) time` | `VERIFIED` |
| `ALG-0107` | **Count Subarrays with Sum at Most K** | [count_subarrays_sum_at_most_k.cpp](../Basics,%20Arrays,%20and%20Implementation/count_subarrays_sum_at_most_k.cpp) | `O(N) time` | `VERIFIED` |
| `ALG-0108` | **Count Subarrays with Sum Equal to K** | [count_subarrays_sum_exact_k.cpp](../Basics,%20Arrays,%20and%20Implementation/count_subarrays_sum_exact_k.cpp) | `O(N) average time` | `VERIFIED` |
| `ALG-0109` | **Array Cyclic Rotations (Reversal and Juggling)** | [cyclic_shifts_and_rotations.cpp](../Basics,%20Arrays,%20and%20Implementation/cyclic_shifts_and_rotations.cpp) | `O(N) time` | `VERIFIED` |
| `ALG-0110` | **Diagonal Matrix Traversal** | [diagonal_matrix_traversal.cpp](../Basics,%20Arrays,%20and%20Implementation/diagonal_matrix_traversal.cpp) | `O(R * C) time` | `VERIFIED` |
| `ALG-0111` | **1D Difference Array** | [difference_array_1d.cpp](../Basics,%20Arrays,%20and%20Implementation/difference_array_1d.cpp) | `O(1) per range add, O(n) prefix sum reconstruction, O(n) space` | `VERIFIED` |
| `ALG-0112` | **2D Difference Array** | [difference_array_2d.cpp](../Basics,%20Arrays,%20and%20Implementation/difference_array_2d.cpp) | `O(1) per subgrid addition, O(R * C) restoration, O(R * C) space` | `VERIFIED` |
| `ALG-0113` | **3D Difference Array** | [difference_array_3d.cpp](../Basics,%20Arrays,%20and%20Implementation/difference_array_3d.cpp) | `O(1) per 3D box update, O(X*Y*Z) prefix reconstruction` | `VERIFIED` |
| `ALG-0114` | **Linear Difference Array (Arithmetic Progression Range Update)** | [difference_array_linear.cpp](../Basics,%20Arrays,%20and%20Implementation/difference_array_linear.cpp) | `O(1) per range addition, O(N) array reconstruction` | `VERIFIED` |
| `ALG-0115` | **Dutch National Flag 3-Way Partitioning** | [dutch_national_flag_partition.cpp](../Basics,%20Arrays,%20and%20Implementation/dutch_national_flag_partition.cpp) | `O(N) time with at most N element swaps` | `VERIFIED` |
| `ALG-0116` | **Equilibrium Index Finder** | [equilibrium_index.cpp](../Basics,%20Arrays,%20and%20Implementation/equilibrium_index.cpp) | `O(N) time` | `VERIFIED` |
| `ALG-0117` | **Fast Exponentiation & Fast Doubling Fibonacci** | [fast_exponentiation.cpp](../Basics,%20Arrays,%20and%20Implementation/fast_exponentiation.cpp) | `O(log n) time, O(1) space` | `VERIFIED` |
| `ALG-0118` | **In-Place Matrix Rotation** | [in_place_matrix_rotation.cpp](../Basics,%20Arrays,%20and%20Implementation/in_place_matrix_rotation.cpp) | `O(N^2) time` | `VERIFIED` |
| `ALG-0119` | **In-Place Matrix Transpose** | [in_place_matrix_transpose.cpp](../Basics,%20Arrays,%20and%20Implementation/in_place_matrix_transpose.cpp) | `O(N^2) time with N*(N-1)/2 swaps` | `VERIFIED` |
| `ALG-0120` | **In-Place Permutation Rearrange A[i] = A[A[i]]** | [in_place_rearrange_elements.cpp](../Basics,%20Arrays,%20and%20Implementation/in_place_rearrange_elements.cpp) | `O(N) time with two passes` | `VERIFIED` |
| `ALG-0121` | **Interval Operations** | [interval_operations.cpp](../Basics,%20Arrays,%20and%20Implementation/interval_operations.cpp) | `O(n log n) sorting, O(n) scan` | `VERIFIED` |
| `ALG-0122` | **Length-Constrained Maximum Subarray Sum** | [kadane_length_constrained.cpp](../Basics,%20Arrays,%20and%20Implementation/kadane_length_constrained.cpp) | `O(N) time` | `VERIFIED` |
| `ALG-0123` | **Two Non-Overlapping Maximum Subarrays** | [kadane_two_non_overlapping.cpp](../Basics,%20Arrays,%20and%20Implementation/kadane_two_non_overlapping.cpp) | `O(N) time` | `VERIFIED` |
| `ALG-0124` | **Longest Consecutive Sequence** | [longest_consecutive_sequence.cpp](../Basics,%20Arrays,%20and%20Implementation/longest_consecutive_sequence.cpp) | `O(N) average time` | `VERIFIED` |
| `ALG-0125` | **Longest Subarray with Sum Divisible by K** | [longest_subarray_divisible_by_k.cpp](../Basics,%20Arrays,%20and%20Implementation/longest_subarray_divisible_by_k.cpp) | `O(N) time` | `VERIFIED` |
| `ALG-0126` | **Longest Subarray with Equal 0s and 1s** | [longest_subarray_equal_zeros_ones.cpp](../Basics,%20Arrays,%20and%20Implementation/longest_subarray_equal_zeros_ones.cpp) | `O(N) time` | `VERIFIED` |
| `ALG-0127` | **Longest Subarray with Sum Equal to K** | [longest_subarray_sum_k.cpp](../Basics,%20Arrays,%20and%20Implementation/longest_subarray_sum_k.cpp) | `O(N) time with hash table` | `VERIFIED` |
| `ALG-0128` | **2D Matrix Prefix XOR** | [matrix_prefix_sum_xor_2d.cpp](../Basics,%20Arrays,%20and%20Implementation/matrix_prefix_sum_xor_2d.cpp) | `O(R * C) preprocessing, O(1) per range query` | `VERIFIED` |
| `ALG-0129` | **Max Consecutive Ones with K Flips** | [max_consecutive_ones_k_flips.cpp](../Basics,%20Arrays,%20and%20Implementation/max_consecutive_ones_k_flips.cpp) | `O(N) time` | `VERIFIED` |
| `ALG-0130` | **Maximum Circular Subarray Sum** | [maximum_circular_subarray_sum.cpp](../Basics,%20Arrays,%20and%20Implementation/maximum_circular_subarray_sum.cpp) | `O(N) time` | `VERIFIED` |
| `ALG-0131` | **Maximum Gap (Bucket Pigeonhole Algorithm)** | [maximum_gap_pigeonhole.cpp](../Basics,%20Arrays,%20and%20Implementation/maximum_gap_pigeonhole.cpp) | `O(N) time` | `VERIFIED` |
| `ALG-0132` | **Maximum Subarray Sum (Kadane's Algorithm)** | [maximum_subarray_sum.cpp](../Basics,%20Arrays,%20and%20Implementation/maximum_subarray_sum.cpp) | `O(n) time, O(1) auxiliary space` | `VERIFIED` |
| `ALG-0133` | **Maximum Subarray Sum After One Operation** | [maximum_subarray_sum_after_one_operation.cpp](../Basics,%20Arrays,%20and%20Implementation/maximum_subarray_sum_after_one_operation.cpp) | `O(N) time` | `VERIFIED` |
| `ALG-0134` | **Minimum Increments to Make Array Unique** | [min_increments_to_make_unique.cpp](../Basics,%20Arrays,%20and%20Implementation/min_increments_to_make_unique.cpp) | `O(N log N) time` | `VERIFIED` |
| `ALG-0135` | **Misra-Gries Heavy Hitters / Boyer-Moore Majority Element** | [misra_gries_heavy_hitters.cpp](../Basics,%20Arrays,%20and%20Implementation/misra_gries_heavy_hitters.cpp) | `O(n * k) time for stream pass, O(n) verification pass, O(k) memory` | `VERIFIED` |
| `ALG-0136` | **Next Greater Element in Circular Array** | [next_greater_element_circular.cpp](../Basics,%20Arrays,%20and%20Implementation/next_greater_element_circular.cpp) | `O(N) time` | `VERIFIED` |
| `ALG-0137` | **Distinct Bitwise OR of Subarrays** | [prefix_bitwise_or_and.cpp](../Basics,%20Arrays,%20and%20Implementation/prefix_bitwise_or_and.cpp) | `O(N * log(max_A)) time` | `VERIFIED` |
| `ALG-0138` | **Prefix Frequency Counts** | [prefix_frequencies.cpp](../Basics,%20Arrays,%20and%20Implementation/prefix_frequencies.cpp) | `O(N * Sigma) preprocessing, O(Sigma) per range query` | `VERIFIED` |
| `ALG-0139` | **Prefix and Suffix GCD** | [prefix_gcd_array.cpp](../Basics,%20Arrays,%20and%20Implementation/prefix_gcd_array.cpp) | `O(N log(max_A)) preprocessing, O(1) query` | `VERIFIED` |
| `ALG-0140` | **Prefix and Suffix Extrema Arrays** | [prefix_maximums_and_minimums.cpp](../Basics,%20Arrays,%20and%20Implementation/prefix_maximums_and_minimums.cpp) | `O(N) preprocessing, O(1) query` | `VERIFIED` |
| `ALG-0141` | **Prefix Products with Zero Counts** | [prefix_product_with_zeros.cpp](../Basics,%20Arrays,%20and%20Implementation/prefix_product_with_zeros.cpp) | `O(N) preprocessing, O(1) query` | `VERIFIED` |
| `ALG-0142` | **1D Prefix Sums** | [prefix_sums_1d.cpp](../Basics,%20Arrays,%20and%20Implementation/prefix_sums_1d.cpp) | `O(n) preprocessing, O(1) per range sum query, O(n) space` | `VERIFIED` |
| `ALG-0143` | **2D Prefix Sums** | [prefix_sums_2d.cpp](../Basics,%20Arrays,%20and%20Implementation/prefix_sums_2d.cpp) | `O(R * C) preprocessing, O(1) per query, O(R * C) space` | `VERIFIED` |
| `ALG-0144` | **3D Prefix Sums** | [prefix_sums_3d.cpp](../Basics,%20Arrays,%20and%20Implementation/prefix_sums_3d.cpp) | `O(X*Y*Z) preprocessing, O(1) per box sum query` | `VERIFIED` |
| `ALG-0145` | **1D Prefix XOR** | [prefix_xor_1d.cpp](../Basics,%20Arrays,%20and%20Implementation/prefix_xor_1d.cpp) | `O(N) preprocessing, O(1) per query` | `VERIFIED` |
| `ALG-0146` | **Product of Array Except Self** | [product_of_array_except_self.cpp](../Basics,%20Arrays,%20and%20Implementation/product_of_array_except_self.cpp) | `O(N) time` | `VERIFIED` |
| `ALG-0147` | **Sliding Window Minimum / Maximum (Monotone Deque)** | [sliding_window_min_max.cpp](../Basics,%20Arrays,%20and%20Implementation/sliding_window_min_max.cpp) | `O(n) total time (each index pushed and popped at most once), O(k) memory` | `VERIFIED` |
| `ALG-0148` | **Spiral Matrix Traversal and Generation** | [spiral_matrix_traversal.cpp](../Basics,%20Arrays,%20and%20Implementation/spiral_matrix_traversal.cpp) | `O(R * C) time` | `VERIFIED` |
| `ALG-0149` | **Subarrays with Sum Divisible by K** | [subarray_sum_divisible_by_k.cpp](../Basics,%20Arrays,%20and%20Implementation/subarray_sum_divisible_by_k.cpp) | `O(N) time` | `VERIFIED` |
| `ALG-0150` | **Subarray Sum Divisible by Array Length (Pigeonhole Subarray)** | [subarray_sum_divisible_by_length.cpp](../Basics,%20Arrays,%20and%20Implementation/subarray_sum_divisible_by_length.cpp) | `O(N) time` | `VERIFIED` |
| `ALG-0151` | **Subarray Zero XOR and Target Product Check** | [subarray_with_given_xor_product.cpp](../Basics,%20Arrays,%20and%20Implementation/subarray_with_given_xor_product.cpp) | `O(N) average time` | `VERIFIED` |
| `ALG-0152` | **Subarrays with XOR Sum Equal to K** | [subarray_xor_equals_k.cpp](../Basics,%20Arrays,%20and%20Implementation/subarray_xor_equals_k.cpp) | `O(N) average time` | `VERIFIED` |
| `ALG-0153` | **Ternary Search** | [ternary_search.cpp](../Basics,%20Arrays,%20and%20Implementation/ternary_search.cpp) | `O(log(range)) function evaluations` | `VERIFIED` |
| `ALG-0154` | **Trapping Rainwater via Prefix & Suffix Extrema** | [trapping_rainwater_prefix_max.cpp](../Basics,%20Arrays,%20and%20Implementation/trapping_rainwater_prefix_max.cpp) | `O(N) time` | `VERIFIED` |

### Bit Manipulation (25 implementations)

| ID | Algorithm | File | Complexity | Status |
| :--- | :--- | :--- | :--- | :---: |
| `ALG-0155` | **Bitset-Accelerated Subset Sum** | [bitset_fast_subset_sum.cpp](../Bit%20Manipulation/bitset_fast_subset_sum.cpp) | `O(N * W / 64) time` | `VERIFIED` |
| `ALG-0156` | **Bitwise Division** | [bitwise_division.cpp](../Bit%20Manipulation/bitwise_division.cpp) | `O(log(dividend)) time` | `VERIFIED` |
| `ALG-0157` | **Russian Peasant Multiplication** | [bitwise_multiplication_russian_peasant.cpp](../Bit%20Manipulation/bitwise_multiplication_russian_peasant.cpp) | `O(log B) time` | `VERIFIED` |
| `ALG-0158` | **Binary Trie with Dynamic Add and Remove** | [bitwise_trie_xor_query.cpp](../Bit%20Manipulation/bitwise_trie_xor_query.cpp) | `O(B) per insertion, deletion, and query where B = 30` | `VERIFIED` |
| `ALG-0159` | **Prefix and Range XOR Sum (1 to N)** | [bitwise_xor_range_1_to_n.cpp](../Bit%20Manipulation/bitwise_xor_range_1_to_n.cpp) | `O(1) time` | `VERIFIED` |
| `ALG-0160` | **Compiler Builtin Bit Operations** | [builtin_bit_operations.cpp](../Bit%20Manipulation/builtin_bit_operations.cpp) | `O(1) CPU instructions` | `VERIFIED` |
| `ALG-0161` | **Count Total Set Bits from 1 to N** | [count_set_bits_1_to_n.cpp](../Bit%20Manipulation/count_set_bits_1_to_n.cpp) | `O(log N) time` | `VERIFIED` |
| `ALG-0162` | **Single Number Among Triplets** | [find_single_number_thrice.cpp](../Bit%20Manipulation/find_single_number_thrice.cpp) | `O(N * 32) time` | `VERIFIED` |
| `ALG-0163` | **Find Two Unique Non-Repeating Elements** | [find_two_non_repeating_elements.cpp](../Bit%20Manipulation/find_two_non_repeating_elements.cpp) | `O(N) time` | `VERIFIED` |
| `ALG-0164` | **Fast Walsh-Hadamard Transform (AND Convolution)** | [fwht_and.cpp](../Bit%20Manipulation/fwht_and.cpp) | `O(N log N) where N = 2^k` | `VERIFIED` |
| `ALG-0165` | **Fast Walsh-Hadamard Transform (OR Convolution)** | [fwht_or.cpp](../Bit%20Manipulation/fwht_or.cpp) | `O(N log N) where N = 2^k` | `VERIFIED` |
| `ALG-0166` | **Fast Walsh-Hadamard Transform (XOR Convolution)** | [fwht_xor.cpp](../Bit%20Manipulation/fwht_xor.cpp) | `O(N log N) where N = 2^k` | `VERIFIED` |
| `ALG-0167` | **Gosper's Hack (K-Element Subsets)** | [gosper_hack_k_subsets.cpp](../Bit%20Manipulation/gosper_hack_k_subsets.cpp) | `O(C(N, K)) time` | `VERIFIED` |
| `ALG-0168` | **Gray Code Generation and Conversion** | [gray_code_generation.cpp](../Bit%20Manipulation/gray_code_generation.cpp) | `O(1) per conversion, O(2^N) for sequence generation` | `VERIFIED` |
| `ALG-0169` | **Most Significant Set Bit (MSB)** | [highest_set_bit.cpp](../Bit%20Manipulation/highest_set_bit.cpp) | `O(1) time` | `VERIFIED` |
| `ALG-0170` | **Lowbit and Bit Clearing Tricks** | [isolate_lowest_set_bit.cpp](../Bit%20Manipulation/isolate_lowest_set_bit.cpp) | `O(1) time` | `VERIFIED` |
| `ALG-0171` | **Maximum XOR of Two Numbers (Binary Trie)** | [maximum_xor_two_numbers_trie.cpp](../Bit%20Manipulation/maximum_xor_two_numbers_trie.cpp) | `O(N * 31) time` | `VERIFIED` |
| `ALG-0172` | **Minimum XOR Pair in Array** | [minimum_xor_pair.cpp](../Bit%20Manipulation/minimum_xor_pair.cpp) | `O(N log N) time` | `VERIFIED` |
| `ALG-0173` | **Power of Four Check** | [power_of_four_check.cpp](../Bit%20Manipulation/power_of_four_check.cpp) | `O(1) time` | `VERIFIED` |
| `ALG-0174` | **Power of Two Utilities** | [power_of_two_utilities.cpp](../Bit%20Manipulation/power_of_two_utilities.cpp) | `O(1) time` | `VERIFIED` |
| `ALG-0175` | **Reverse 32-bit Integer** | [reverse_bits_32.cpp](../Bit%20Manipulation/reverse_bits_32.cpp) | `O(1) time (5 bitwise swap steps)` | `VERIFIED` |
| `ALG-0176` | **Sum Over Subsets (SOS) Dynamic Programming** | [sos_dp_submask_sums.cpp](../Bit%20Manipulation/sos_dp_submask_sums.cpp) | `O(N * 2^N) time` | `VERIFIED` |
| `ALG-0177` | **Submask Enumeration** | [submask_enumeration.cpp](../Bit%20Manipulation/submask_enumeration.cpp) | `O(2^k) for a mask with k set bits; O(3^N) for all masks up to N bits` | `VERIFIED` |
| `ALG-0178` | **Linear Basis for XOR (Gaussian Elimination in GF(2))** | [subset_xor_basis.cpp](../Bit%20Manipulation/subset_xor_basis.cpp) | `O(B) per insertion and max XOR query where B = 60` | `VERIFIED` |
| `ALG-0179` | **Swap Bits at Arbitrary Positions** | [swap_bits_in_integer.cpp](../Bit%20Manipulation/swap_bits_in_integer.cpp) | `O(1) time` | `VERIFIED` |

### Combinatorics and Probability (30 implementations)

| ID | Algorithm | File | Complexity | Status |
| :--- | :--- | :--- | :--- | :---: |
| `ALG-0180` | **Vose's Alias Method (O(1) Discrete Distribution Sampling)** | [alias_method_discrete_distribution.cpp](../Combinatorics%20and%20Probability/alias_method_discrete_distribution.cpp) | `O(N) initialization, O(1) per random sample` | `VERIFIED` |
| `ALG-0181` | **Bell Numbers (Set Partitions Count)** | [bell_numbers.cpp](../Combinatorics%20and%20Probability/bell_numbers.cpp) | `O(N^2) time` | `VERIFIED` |
| `ALG-0182` | **Bernoulli Numbers Modulo P** | [bernoulli_numbers_modular.cpp](../Combinatorics%20and%20Probability/bernoulli_numbers_modular.cpp) | `O(N^2) time` | `VERIFIED` |
| `ALG-0183` | **Birthday Paradox and Probability Utilities** | [birthday_paradox.cpp](../Combinatorics%20and%20Probability/birthday_paradox.cpp) | `O(k) or O(1) approximation` | `VERIFIED` |
| `ALG-0184` | **Birthday Paradox Probability Calculator** | [birthday_paradox_probability.cpp](../Combinatorics%20and%20Probability/birthday_paradox_probability.cpp) | `O(K) time` | `VERIFIED` |
| `ALG-0185` | **Burnside's Lemma (Necklace Counting Under Rotation)** | [burnside_lemma_necklace.cpp](../Combinatorics%20and%20Probability/burnside_lemma_necklace.cpp) | `O(N log N) time` | `VERIFIED` |
| `ALG-0186` | **Catalan Numbers** | [catalan_numbers.cpp](../Combinatorics%20and%20Probability/catalan_numbers.cpp) | `O(N) precomputation, O(1) query, O(N) memory` | `VERIFIED` |
| `ALG-0187` | **Cayley's Formula and Prufer Counting** | [cayley_formula_labeled_trees.cpp](../Combinatorics%20and%20Probability/cayley_formula_labeled_trees.cpp) | `O(N) time` | `VERIFIED` |
| `ALG-0188` | **Modular Combinatorics (Factorials and nCr)** | [combinatorics_mod.cpp](../Combinatorics%20and%20Probability/combinatorics_mod.cpp) | `O(N) precomputation, O(1) per nCr query, O(N) memory` | `VERIFIED` |
| `ALG-0189` | **Coupon Collector's Expected Value and Variance** | [coupon_collector_expected_value.cpp](../Combinatorics%20and%20Probability/coupon_collector_expected_value.cpp) | `O(N) time` | `VERIFIED` |
| `ALG-0190` | **Derangements (Subfactorials)** | [derangements.cpp](../Combinatorics%20and%20Probability/derangements.cpp) | `O(N) precomputation, O(1) query, O(N) memory` | `VERIFIED` |
| `ALG-0191` | **Derangements (Subfactorial !n)** | [derangements_subfactorial.cpp](../Combinatorics%20and%20Probability/derangements_subfactorial.cpp) | `O(N) time` | `VERIFIED` |
| `ALG-0192` | **Eulerian Numbers A(n, m)** | [eulerian_numbers.cpp](../Combinatorics%20and%20Probability/eulerian_numbers.cpp) | `O(N * M) time` | `VERIFIED` |
| `ALG-0193` | **Ordinary Generating Functions (Dice Sum Probability Distribution)** | [generating_functions_dice_sum.cpp](../Combinatorics%20and%20Probability/generating_functions_dice_sum.cpp) | `O(N * D * (N * D)) time` | `VERIFIED` |
| `ALG-0194` | **Inclusion-Exclusion Coprime Counting** | [inclusion_exclusion_coprime_count.cpp](../Combinatorics%20and%20Probability/inclusion_exclusion_coprime_count.cpp) | `O(2^K) time where K is number of distinct prime factors` | `VERIFIED` |
| `ALG-0195` | **Lehmer Code and Factoradic Permutation Rank** | [inversion_sequence_lehmer_code.cpp](../Combinatorics%20and%20Probability/inversion_sequence_lehmer_code.cpp) | `O(N log N) time using Fenwick tree` | `VERIFIED` |
| `ALG-0196` | **Lucas' Theorem for Large Binomial Coefficients** | [lucas_theorem.cpp](../Combinatorics%20and%20Probability/lucas_theorem.cpp) | `O(p) precomputation, O(log_p(n)) per query, O(p) memory` | `VERIFIED` |
| `ALG-0197` | **Absorbing Markov Chain Fundamental Matrix** | [markov_chain_absorbing_states.cpp](../Combinatorics%20and%20Probability/markov_chain_absorbing_states.cpp) | `O(K^3) matrix inversion time` | `VERIFIED` |
| `ALG-0198` | **Montmort Derangements Numbers Modulo M** | [montmort_derangements_modulo.cpp](../Combinatorics%20and%20Probability/montmort_derangements_modulo.cpp) | `O(N) time` | `VERIFIED` |
| `ALG-0199` | **Motzkin Numbers** | [motzkin_numbers.cpp](../Combinatorics%20and%20Probability/motzkin_numbers.cpp) | `O(N) time` | `VERIFIED` |
| `ALG-0200` | **Multinomial Coefficient** | [multinomial_coefficient.cpp](../Combinatorics%20and%20Probability/multinomial_coefficient.cpp) | `O(N) time` | `VERIFIED` |
| `ALG-0201` | **Narayana Numbers** | [narayana_numbers.cpp](../Combinatorics%20and%20Probability/narayana_numbers.cpp) | `O(N) time` | `VERIFIED` |
| `ALG-0202` | **Polya Enumeration Theorem (Bracelet Counting)** | [polya_enumeration_bracelet.cpp](../Combinatorics%20and%20Probability/polya_enumeration_bracelet.cpp) | `O(N log N) time` | `VERIFIED` |
| `ALG-0203` | **xoshiro256** Pseudo-Random Number Generator** | [random_number_generator_xoshiro256.cpp](../Combinatorics%20and%20Probability/random_number_generator_xoshiro256.cpp) | `O(1) time per random 64-bit word` | `VERIFIED` |
| `ALG-0204` | **Fisher-Yates (Knuth) Shuffle** | [random_shuffle_fisher_yates.cpp](../Combinatorics%20and%20Probability/random_shuffle_fisher_yates.cpp) | `O(N) time` | `VERIFIED` |
| `ALG-0205` | **1D Random Walk Absorption (Gambler's Ruin)** | [random_walk_1d_absorption.cpp](../Combinatorics%20and%20Probability/random_walk_1d_absorption.cpp) | `O(log B) time` | `VERIFIED` |
| `ALG-0206` | **Reservoir Sampling (Algorithm R)** | [reservoir_sampling.cpp](../Combinatorics%20and%20Probability/reservoir_sampling.cpp) | `O(N) time single pass` | `VERIFIED` |
| `ALG-0207` | **Stars and Bars Theorem** | [stars_and_bars_non_negative.cpp](../Combinatorics%20and%20Probability/stars_and_bars_non_negative.cpp) | `O(K) time` | `VERIFIED` |
| `ALG-0208` | **Stirling Numbers of the First Kind (Unsigned)** | [stirling_numbers_first_kind.cpp](../Combinatorics%20and%20Probability/stirling_numbers_first_kind.cpp) | `O(N * K) time` | `VERIFIED` |
| `ALG-0209` | **Stirling Numbers of the Second Kind** | [stirling_numbers_second_kind.cpp](../Combinatorics%20and%20Probability/stirling_numbers_second_kind.cpp) | `O(N * K) time` | `VERIFIED` |

### Computational Complexity and Theory (1 implementations)

| ID | Algorithm | File | Complexity | Status |
| :--- | :--- | :--- | :--- | :---: |
| `ALG-0210` | **Meet in the Middle (Subset Sum)** | [meet_in_the_middle.cpp](../Computational%20Complexity%20and%20Theory/meet_in_the_middle.cpp) | `O(n * 2^(n/2)) time, O(2^(n/2)) memory` | `VERIFIED` |

### Data Structures (65 implementations)

| ID | Algorithm | File | Complexity | Status |
| :--- | :--- | :--- | :--- | :---: |
| `ALG-0211` | **AVL Tree Self-Balancing BST** | [avl_tree_balanced_bst.cpp](../Data%20Structures/avl_tree_balanced_bst.cpp) | `O(log N) insert/delete/search` | `VERIFIED` |
| `ALG-0212` | **Custom Binary Max-Heap** | [binary_heap_custom_priority_queue.cpp](../Data%20Structures/binary_heap_custom_priority_queue.cpp) | `O(log N) push/pop, O(1) top` | `VERIFIED` |
| `ALG-0213` | **Binomial Heap Mergeable Priority Queue** | [binomial_heap_merge.cpp](../Data%20Structures/binomial_heap_merge.cpp) | `O(log N) merge, insert, extract-min` | `VERIFIED` |
| `ALG-0214` | **Bipartite DSU with Odd Cycle Detection** | [bipartite_dsu_two_coloring.cpp](../Data%20Structures/bipartite_dsu_two_coloring.cpp) | `O(alpha(N))` | `VERIFIED` |
| `ALG-0215` | **Space-Efficient Bloom Filter** | [bloom_filter_bitset.cpp](../Data%20Structures/bloom_filter_bitset.cpp) | `O(K) hash evaluations` | `VERIFIED` |
| `ALG-0216` | **Cartesian Tree Construction in O(N)** | [cartesian_tree_construction.cpp](../Data%20Structures/cartesian_tree_construction.cpp) | `O(N)` | `VERIFIED` |
| `ALG-0217` | **Count-Min Sketch Frequency Estimator** | [count_min_sketch.cpp](../Data%20Structures/count_min_sketch.cpp) | `O(Depth) per update and query` | `VERIFIED` |
| `ALG-0218` | **Disjoint Set Union (DSU / Union-Find)** | [disjoint_set_union.cpp](../Data%20Structures/disjoint_set_union.cpp) | `O(alpha(n)) amortized per operation, O(n) memory` | `VERIFIED` |
| `ALG-0219` | **Disjoint Sparse Table for O(1) Semigroup RMQ** | [disjoint_sparse_table.cpp](../Data%20Structures/disjoint_sparse_table.cpp) | `O(N log N) build, O(1) query` | `VERIFIED` |
| `ALG-0220` | **Potentialized DSU (Weight Difference Relations)** | [dsu_with_potential_weights.cpp](../Data%20Structures/dsu_with_potential_weights.cpp) | `O(alpha(N)) amortized` | `VERIFIED` |
| `ALG-0221` | **Dynamic / Implicit Segment Tree** | [dynamic_segment_tree.cpp](../Data%20Structures/dynamic_segment_tree.cpp) | `O(log MAX_COORD) per update and query, O(Q * log MAX_COORD) total memory` | `VERIFIED` |
| `ALG-0222` | **Fenwick Tree (Binary Indexed Tree)** | [fenwick_tree.cpp](../Data%20Structures/fenwick_tree.cpp) | `O(log n) per update and query, O(n) memory` | `VERIFIED` |
| `ALG-0223` | **2D Fenwick Tree** | [fenwick_tree_2d.cpp](../Data%20Structures/fenwick_tree_2d.cpp) | `O(log R * log C) per update and query, O(R * C) memory` | `VERIFIED` |
| `ALG-0224` | **3D Fenwick Tree Point Update Volume Query** | [fenwick_tree_3d_point_update.cpp](../Data%20Structures/fenwick_tree_3d_point_update.cpp) | `O(log X * log Y * log Z) query/update` | `VERIFIED` |
| `ALG-0225` | **Inversion Counting via Fenwick Tree** | [fenwick_tree_inversion_count.cpp](../Data%20Structures/fenwick_tree_inversion_count.cpp) | `O(N log N)` | `VERIFIED` |
| `ALG-0226` | **Fenwick Tree with Range Add and Range Sum** | [fenwick_tree_range_add.cpp](../Data%20Structures/fenwick_tree_range_add.cpp) | `O(log n) per range update and query, O(n) memory` | `VERIFIED` |
| `ALG-0227` | **Fenwick Tree Range Update and Range Query** | [fenwick_tree_range_add_range_sum.cpp](../Data%20Structures/fenwick_tree_range_add_range_sum.cpp) | `O(log N) update and query` | `VERIFIED` |
| `ALG-0228` | **Fibonacci Heap Priority Queue** | [fibonacci_heap_decrease_key.cpp](../Data%20Structures/fibonacci_heap_decrease_key.cpp) | `O(1) amortized insert/decrease-key, O(log N) extract-min` | `VERIFIED` |
| `ALG-0229` | **HyperLogLog Distinct Cardinality Estimator** | [hyperloglog_cardinality.cpp](../Data%20Structures/hyperloglog_cardinality.cpp) | `O(1) update, O(M) estimate` | `VERIFIED` |
| `ALG-0230` | **Implicit Treap (Dynamic Array / Rope with Range Reversal)** | [implicit_treap.cpp](../Data%20Structures/implicit_treap.cpp) | `O(log n) expected per range operation, O(n) memory` | `VERIFIED` |
| `ALG-0231` | **Interval Tree Overlapping Interval Search** | [interval_tree_overlap_search.cpp](../Data%20Structures/interval_tree_overlap_search.cpp) | `O(log N) search/insert` | `VERIFIED` |
| `ALG-0232` | **2D K-d Tree Nearest Neighbor Search** | [kd_tree_nearest_neighbor_2d.cpp](../Data%20Structures/kd_tree_nearest_neighbor_2d.cpp) | `O(N log N) build, O(log N) average query` | `VERIFIED` |
| `ALG-0233` | **Lazy Segment Tree (Range Add, Range Sum)** | [lazy_segment_tree.cpp](../Data%20Structures/lazy_segment_tree.cpp) | `O(n) build, O(log n) per range update and query, O(n) memory` | `VERIFIED` |
| `ALG-0234` | **Lazy Segment Tree (Range Assignment, Range Min)** | [lazy_segment_tree_assignment.cpp](../Data%20Structures/lazy_segment_tree_assignment.cpp) | `O(n) build, O(log n) per assignment and query, O(n) memory` | `VERIFIED` |
| `ALG-0235` | **Leftist Heap (Mergeable Priority Queue)** | [leftist_heap_mergeable.cpp](../Data%20Structures/leftist_heap_mergeable.cpp) | `O(log N) merge, insert, and delete-min` | `VERIFIED` |
| `ALG-0236` | **LFU Cache (Least Frequently Used O(1))** | [lfu_cache_frequency_lists.cpp](../Data%20Structures/lfu_cache_frequency_lists.cpp) | `O(1) get and put` | `VERIFIED` |
| `ALG-0237` | **LRU Cache (Hash Map + Doubly Linked List)** | [lru_cache_doubly_linked_list.cpp](../Data%20Structures/lru_cache_doubly_linked_list.cpp) | `O(1) get and put` | `VERIFIED` |
| `ALG-0238` | **Merge Sort Tree Count Elements Less Than K** | [merge_sort_tree_count_less.cpp](../Data%20Structures/merge_sort_tree_count_less.cpp) | `O(log^2 N) query, O(N log N) build` | `VERIFIED` |
| `ALG-0239` | **Min Stack & Min Queue** | [min_max_stack_queue.cpp](../Data%20Structures/min_max_stack_queue.cpp) | `O(1) worst-case for MinStack, O(1) amortized for MinQueue, O(n) memory` | `VERIFIED` |
| `ALG-0240` | **Sliding Window Min/Max via Monotonic Queue** | [monotonic_queue_sliding_window.cpp](../Data%20Structures/monotonic_queue_sliding_window.cpp) | `O(N)` | `VERIFIED` |
| `ALG-0241` | **Next Greater Element via Monotonic Stack** | [monotonic_stack_next_greater.cpp](../Data%20Structures/monotonic_stack_next_greater.cpp) | `O(N)` | `VERIFIED` |
| `ALG-0242` | **Previous Smaller Element via Monotonic Stack** | [monotonic_stack_previous_smaller.cpp](../Data%20Structures/monotonic_stack_previous_smaller.cpp) | `O(N)` | `VERIFIED` |
| `ALG-0243` | **Policy-Based Data Structure Ordered Set (PBDS)** | [order_statistic_tree_pbds.cpp](../Data%20Structures/order_statistic_tree_pbds.cpp) | `O(log N)` | `VERIFIED` |
| `ALG-0244` | **Pairing Heap Priority Queue** | [pairing_heap_priority_queue.cpp](../Data%20Structures/pairing_heap_priority_queue.cpp) | `O(1) insert/merge, O(log N) extract-min` | `VERIFIED` |
| `ALG-0245` | **Partially Persistent Fenwick Tree** | [persistent_fenwick_tree.cpp](../Data%20Structures/persistent_fenwick_tree.cpp) | `O(log N) per update/query` | `VERIFIED` |
| `ALG-0246` | **Fully Persistent Functional Queue** | [persistent_queue_functional.cpp](../Data%20Structures/persistent_queue_functional.cpp) | `O(1) amortized` | `VERIFIED` |
| `ALG-0247` | **Persistent Segment Tree** | [persistent_segment_tree.cpp](../Data%20Structures/persistent_segment_tree.cpp) | `O(n) initial build, O(log n) time and memory per point update, O(log n) per range query` | `VERIFIED` |
| `ALG-0248` | **Persistent Stack via Linked Nodes** | [persistent_stack_linked.cpp](../Data%20Structures/persistent_stack_linked.cpp) | `O(1) push and pop` | `VERIFIED` |
| `ALG-0249` | **PATRICIA Radix Trie** | [radix_tree_patricia.cpp](../Data%20Structures/radix_tree_patricia.cpp) | `O(WordLen)` | `VERIFIED` |
| `ALG-0250` | **Red-Black Tree Insertion** | [red_black_tree_insert.cpp](../Data%20Structures/red_black_tree_insert.cpp) | `O(log N)` | `VERIFIED` |
| `ALG-0251` | **Rollback DSU (Undoable Union-Find)** | [rollback_dsu.cpp](../Data%20Structures/rollback_dsu.cpp) | `O(log n) per find/union (no path compression), O(1) rollback step, O(n) memory` | `VERIFIED` |
| `ALG-0252` | **GNU C++ Rope Fast String Slicing** | [rope_fast_string_concatenation.cpp](../Data%20Structures/rope_fast_string_concatenation.cpp) | `O(log N) per operation` | `VERIFIED` |
| `ALG-0253` | **Segment Tree (Point Update, Range Query)** | [segment_tree.cpp](../Data%20Structures/segment_tree.cpp) | `O(n) construction, O(log n) per update and range query, O(n) memory` | `VERIFIED` |
| `ALG-0254` | **2D Segment Tree Point Update and Subgrid Sum** | [segment_tree_2d_point_update.cpp](../Data%20Structures/segment_tree_2d_point_update.cpp) | `O(log R * log C) query and update` | `VERIFIED` |
| `ALG-0255` | **Segment Tree Beats (Range Chmin, Chmax, Sum)** | [segment_tree_beats_chmin_chmax.cpp](../Data%20Structures/segment_tree_beats_chmin_chmax.cpp) | `O(log N) amortized per update/query` | `VERIFIED` |
| `ALG-0256` | **Segment Tree with Combined Lazy Mul and Add** | [segment_tree_lazy_multiplication_addition.cpp](../Data%20Structures/segment_tree_lazy_multiplication_addition.cpp) | `O(log N) update/query` | `VERIFIED` |
| `ALG-0257` | **Segment Tree Longest Consecutive Ones** | [segment_tree_longest_consecutive_ones.cpp](../Data%20Structures/segment_tree_longest_consecutive_ones.cpp) | `O(log N)` | `VERIFIED` |
| `ALG-0258` | **Iterative Segment Tree Point Update Range Sum** | [segment_tree_point_update_range_sum.cpp](../Data%20Structures/segment_tree_point_update_range_sum.cpp) | `O(log N) update and query, O(N) build` | `VERIFIED` |
| `ALG-0259` | **Segment Tree for Range Min and Max** | [segment_tree_range_min_max.cpp](../Data%20Structures/segment_tree_range_min_max.cpp) | `O(log N) query/update` | `VERIFIED` |
| `ALG-0260` | **Segment Tree Walk for K-th One** | [segment_tree_walk_kth_one.cpp](../Data%20Structures/segment_tree_walk_kth_one.cpp) | `O(log N)` | `VERIFIED` |
| `ALG-0261` | **Skew Heap Self-Adjusting Mergeable Heap** | [skew_heap_self_adjusting.cpp](../Data%20Structures/skew_heap_self_adjusting.cpp) | `O(log N) amortized` | `VERIFIED` |
| `ALG-0262` | **Probabilistic Skip List** | [skip_list_probabilistic.cpp](../Data%20Structures/skip_list_probabilistic.cpp) | `O(log N) average` | `VERIFIED` |
| `ALG-0263` | **Sparse Table (RMQ)** | [sparse_table.cpp](../Data%20Structures/sparse_table.cpp) | `O(n log n) preprocessing, O(1) per range query, O(n log n) memory` | `VERIFIED` |
| `ALG-0264` | **2D Sparse Table for Rectangular RMQ** | [sparse_table_2d_rmq.cpp](../Data%20Structures/sparse_table_2d_rmq.cpp) | `O(R * C * log R * log C) build, O(1) query` | `VERIFIED` |
| `ALG-0265` | **Splay Tree Dynamic Set Operations** | [splay_tree_search_insert.cpp](../Data%20Structures/splay_tree_search_insert.cpp) | `O(log N) amortized` | `VERIFIED` |
| `ALG-0266` | **Square Root Decomposition Point Update Range Query** | [sqrt_decomposition_point_update.cpp](../Data%20Structures/sqrt_decomposition_point_update.cpp) | `O(1) update, O(sqrt N) query` | `VERIFIED` |
| `ALG-0267` | **Treap (Cartesian Tree)** | [treap.cpp](../Data%20Structures/treap.cpp) | `O(log n) expected per operation, O(n) memory` | `VERIFIED` |
| `ALG-0268` | **Implicit Treap Range Cyclic Shift** | [treap_implicit_range_cyclic_shift.cpp](../Data%20Structures/treap_implicit_range_cyclic_shift.cpp) | `O(log N)` | `VERIFIED` |
| `ALG-0269` | **Implicit Treap Range Reversal** | [treap_implicit_range_reverse.cpp](../Data%20Structures/treap_implicit_range_reverse.cpp) | `O(log N)` | `VERIFIED` |
| `ALG-0270` | **Trie Auto-Complete with Frequency Ranking** | [trie_autocomplete_top_k.cpp](../Data%20Structures/trie_autocomplete_top_k.cpp) | `O(PrefixLen + K)` | `VERIFIED` |
| `ALG-0271` | **Prefix Trie with Prefix Search and Deletion** | [trie_prefix_tree.cpp](../Data%20Structures/trie_prefix_tree.cpp) | `O(L) per operation` | `VERIFIED` |
| `ALG-0272` | **Van Emde Boas (vEB) Tree** | [van_emde_boas_tree.cpp](../Data%20Structures/van_emde_boas_tree.cpp) | `O(log log U)` | `VERIFIED` |
| `ALG-0273` | **Wavelet Tree Range K-th Element** | [wavelet_tree_kth_element.cpp](../Data%20Structures/wavelet_tree_kth_element.cpp) | `O(log(MaxVal)) per query, O(N log(MaxVal)) build` | `VERIFIED` |
| `ALG-0274` | **Binary XOR Trie K-th Smallest XOR Query** | [xor_trie_kth_xor_query.cpp](../Data%20Structures/xor_trie_kth_xor_query.cpp) | `O(30) per query` | `VERIFIED` |
| `ALG-0275` | **Binary XOR Trie Maximum XOR Pair** | [xor_trie_maximum_xor_pair.cpp](../Data%20Structures/xor_trie_maximum_xor_pair.cpp) | `O(32 * N)` | `VERIFIED` |

### Dynamic Programming (85 implementations)

| ID | Algorithm | File | Complexity | Status |
| :--- | :--- | :--- | :--- | :---: |
| `ALG-0276` | **Aliens Trick (WQS Binary Search on Cost Multiplier)** | [alien_trick_wqs_binary_search.cpp](../Dynamic%20Programming/alien_trick_wqs_binary_search.cpp) | `O(N log(Range))` | `VERIFIED` |
| `ALG-0277` | **Boolean Parenthesization DP** | [boolean_parenthesization.cpp](../Dynamic%20Programming/boolean_parenthesization.cpp) | `O(N^3)` | `VERIFIED` |
| `ALG-0278` | **3D Box Stacking via DAG Dynamic Programming** | [box_stacking_3d_dag.cpp](../Dynamic%20Programming/box_stacking_3d_dag.cpp) | `O(N^2)` | `VERIFIED` |
| `ALG-0279` | **Broken Profile (Plug) DP for Domino Tiling** | [broken_profile_domino_tiling.cpp](../Dynamic%20Programming/broken_profile_domino_tiling.cpp) | `O(N * M * 2^M)` | `VERIFIED` |
| `ALG-0280` | **Building Bridges Problem via LIS** | [building_bridges_problem.cpp](../Dynamic%20Programming/building_bridges_problem.cpp) | `O(N log N)` | `VERIFIED` |
| `ALG-0281` | **Burst Balloons Maximum Coins Interval DP** | [burst_balloons_dp.cpp](../Dynamic%20Programming/burst_balloons_dp.cpp) | `O(N^3)` | `VERIFIED` |
| `ALG-0282` | **Cherry Pickup Dual Synchronous Path DP** | [cherry_pickup_two_paths.cpp](../Dynamic%20Programming/cherry_pickup_two_paths.cpp) | `O(N^3)` | `VERIFIED` |
| `ALG-0283` | **Coin Change Minimum Coins with Combination Reconstruction** | [coin_change_minimum_coins.cpp](../Dynamic%20Programming/coin_change_minimum_coins.cpp) | `O(N * V)` | `VERIFIED` |
| `ALG-0284` | **Coin Change Total Combinations DP** | [coin_change_total_ways.cpp](../Dynamic%20Programming/coin_change_total_ways.cpp) | `O(N * V)` | `VERIFIED` |
| `ALG-0285` | **Convex Hull Trick (Dynamic Line Container)** | [convex_hull_trick.cpp](../Dynamic%20Programming/convex_hull_trick.cpp) | `O(log n) amortized per line insertion, O(log n) per query, O(n) memory` | `VERIFIED` |
| `ALG-0286` | **Count Derangements DP** | [count_derangements_dp.cpp](../Dynamic%20Programming/count_derangements_dp.cpp) | `O(N)` | `VERIFIED` |
| `ALG-0287` | **Count Distinct Palindromic Subsequences Modulo 10^9+7** | [count_palindromic_subsequences_modulo.cpp](../Dynamic%20Programming/count_palindromic_subsequences_modulo.cpp) | `O(N^2)` | `VERIFIED` |
| `ALG-0288` | **Count Square Submatrices with All Ones DP** | [count_square_submatrices_all_ones.cpp](../Dynamic%20Programming/count_square_submatrices_all_ones.cpp) | `O(R * C)` | `VERIFIED` |
| `ALG-0289` | **Unique BST Count via Catalan DP** | [count_unique_bst_catalan_dp.cpp](../Dynamic%20Programming/count_unique_bst_catalan_dp.cpp) | `O(N^2)` | `VERIFIED` |
| `ALG-0290` | **Count Vowel Permutation Graph DP** | [count_vowel_permutation_graph_dp.cpp](../Dynamic%20Programming/count_vowel_permutation_graph_dp.cpp) | `O(N)` | `VERIFIED` |
| `ALG-0291` | **Decode Ways DP (Letter Mappings)** | [decode_ways_dp.cpp](../Dynamic%20Programming/decode_ways_dp.cpp) | `O(N)` | `VERIFIED` |
| `ALG-0292` | **Dice Roll Simulation with Consecutive Face Limits DP** | [dice_roll_simulation_consecutive_limit.cpp](../Dynamic%20Programming/dice_roll_simulation_consecutive_limit.cpp) | `O(N * 6 * MaxRoll)` | `VERIFIED` |
| `ALG-0293` | **Digit DP** | [digit_dp.cpp](../Dynamic%20Programming/digit_dp.cpp) | `O(len(N) * states) time, O(len(N) * states) memory` | `VERIFIED` |
| `ALG-0294` | **Distinct Subsequences Matching Count DP** | [distinct_subsequences_count.cpp](../Dynamic%20Programming/distinct_subsequences_count.cpp) | `O(N * M)` | `VERIFIED` |
| `ALG-0295` | **Divide and Conquer DP Optimization** | [divide_and_conquer_dp.cpp](../Dynamic%20Programming/divide_and_conquer_dp.cpp) | `O(k * n log n) time, O(k * n) space (or O(n) space rolling)` | `VERIFIED` |
| `ALG-0296` | **Dungeon Game Reverse DP** | [dungeon_game_reverse_dp.cpp](../Dynamic%20Programming/dungeon_game_reverse_dp.cpp) | `O(R * C)` | `VERIFIED` |
| `ALG-0297` | **Levenshtein Edit Distance with Operation Alignment Trace** | [edit_distance_levenshtein.cpp](../Dynamic%20Programming/edit_distance_levenshtein.cpp) | `O(N * M)` | `VERIFIED` |
| `ALG-0298` | **Egg Dropping Puzzle DP with Binary Search** | [egg_dropping_puzzle.cpp](../Dynamic%20Programming/egg_dropping_puzzle.cpp) | `O(K * N)` | `VERIFIED` |
| `ALG-0299` | **Frog Jump with K Steps DP** | [frog_jump_k_steps.cpp](../Dynamic%20Programming/frog_jump_k_steps.cpp) | `O(N * K)` | `VERIFIED` |
| `ALG-0300` | **Hamiltonian Path Check and Extraction via Bitmask DP** | [hamiltonian_path_bitmask.cpp](../Dynamic%20Programming/hamiltonian_path_bitmask.cpp) | `O(2^N * N^2)` | `VERIFIED` |
| `ALG-0301` | **House Robber on Binary Tree DP** | [house_robber_binary_tree.cpp](../Dynamic%20Programming/house_robber_binary_tree.cpp) | `O(N)` | `VERIFIED` |
| `ALG-0302` | **House Robber Circular Street DP** | [house_robber_circular_dp.cpp](../Dynamic%20Programming/house_robber_circular_dp.cpp) | `O(N)` | `VERIFIED` |
| `ALG-0303` | **Integer Break Product Maximization DP** | [integer_break_product_maximization.cpp](../Dynamic%20Programming/integer_break_product_maximization.cpp) | `O(N^2)` | `VERIFIED` |
| `ALG-0304` | **Interleaving String DP Check** | [interleaving_string_dp.cpp](../Dynamic%20Programming/interleaving_string_dp.cpp) | `O(N * M)` | `VERIFIED` |
| `ALG-0305` | **Jump Game Minimum Jumps DP/Greedy** | [jump_game_min_jumps.cpp](../Dynamic%20Programming/jump_game_min_jumps.cpp) | `O(N)` | `VERIFIED` |
| `ALG-0306` | **0-1 and Bounded Knapsack** | [knapsack_01_and_bounded.cpp](../Dynamic%20Programming/knapsack_01_and_bounded.cpp) | `O(n * W) for 0-1 knapsack, O(W * sum(log count_i)) for bounded knapsack` | `VERIFIED` |
| `ALG-0307` | **Knight Dialer Distinct Numbers DP** | [knight_dialer_phone_keypad.cpp](../Dynamic%20Programming/knight_dialer_phone_keypad.cpp) | `O(N)` | `VERIFIED` |
| `ALG-0308` | **Knuth Optimization for Interval DP** | [knuth_optimization_dp.cpp](../Dynamic%20Programming/knuth_optimization_dp.cpp) | `O(N^2)` | `VERIFIED` |
| `ALG-0309` | **Longest Common Subsequence with Full Reconstruction** | [lcs_full_reconstruction.cpp](../Dynamic%20Programming/lcs_full_reconstruction.cpp) | `O(N * M)` | `VERIFIED` |
| `ALG-0310` | **Li Chao Tree** | [li_chao_tree.cpp](../Dynamic%20Programming/li_chao_tree.cpp) | `O(log MAX_X) per line insertion and point query, O(MAX_X) or dynamic memory` | `VERIFIED` |
| `ALG-0311` | **Longest Alternating Subsequence DP** | [longest_alternating_subsequence.cpp](../Dynamic%20Programming/longest_alternating_subsequence.cpp) | `O(N)` | `VERIFIED` |
| `ALG-0312` | **Longest Arithmetic Subsequence DP** | [longest_arithmetic_subsequence.cpp](../Dynamic%20Programming/longest_arithmetic_subsequence.cpp) | `O(N^2)` | `VERIFIED` |
| `ALG-0313` | **Longest Arithmetic Subsequence with Fixed Difference** | [longest_arithmetic_subsequence_given_diff.cpp](../Dynamic%20Programming/longest_arithmetic_subsequence_given_diff.cpp) | `O(N)` | `VERIFIED` |
| `ALG-0314` | **Longest Common Increasing Subsequence (LCIS)** | [longest_common_increasing_subsequence.cpp](../Dynamic%20Programming/longest_common_increasing_subsequence.cpp) | `O(N * M)` | `VERIFIED` |
| `ALG-0315` | **Longest Increasing Subsequence (LIS)** | [longest_increasing_subsequence.cpp](../Dynamic%20Programming/longest_increasing_subsequence.cpp) | `O(n log n) time, O(n) memory` | `VERIFIED` |
| `ALG-0316` | **Longest Palindromic Subsequence DP with Reconstruction** | [longest_palindromic_subsequence_dp.cpp](../Dynamic%20Programming/longest_palindromic_subsequence_dp.cpp) | `O(N^2)` | `VERIFIED` |
| `ALG-0317` | **Longest Path in DAG via Topological Order DP** | [longest_path_dag_dp.cpp](../Dynamic%20Programming/longest_path_dag_dp.cpp) | `O(V + E)` | `VERIFIED` |
| `ALG-0318` | **Longest Repeating Subsequence DP** | [longest_repeating_subsequence.cpp](../Dynamic%20Programming/longest_repeating_subsequence.cpp) | `O(N^2)` | `VERIFIED` |
| `ALG-0319` | **Longest Valid Parentheses Substring DP** | [longest_valid_parentheses_dp.cpp](../Dynamic%20Programming/longest_valid_parentheses_dp.cpp) | `O(N)` | `VERIFIED` |
| `ALG-0320` | **Matchsticks to Square Bitmask DP** | [matchsticks_to_square_bitmask.cpp](../Dynamic%20Programming/matchsticks_to_square_bitmask.cpp) | `O(2^N)` | `VERIFIED` |
| `ALG-0321` | **Matrix Chain Multiplication with Optimal Parenthesization** | [matrix_chain_multiplication.cpp](../Dynamic%20Programming/matrix_chain_multiplication.cpp) | `O(N^3)` | `VERIFIED` |
| `ALG-0322` | **Maximal Rectangle in Binary Matrix via Histogram DP** | [maximal_rectangle_histogram_dp.cpp](../Dynamic%20Programming/maximal_rectangle_histogram_dp.cpp) | `O(R * C)` | `VERIFIED` |
| `ALG-0323` | **Maximal Square in Binary Matrix DP** | [maximal_square_dp.cpp](../Dynamic%20Programming/maximal_square_dp.cpp) | `O(R * C)` | `VERIFIED` |
| `ALG-0324` | **Maximum Length Chain of Pairs DP** | [maximum_length_chain_of_pairs.cpp](../Dynamic%20Programming/maximum_length_chain_of_pairs.cpp) | `O(N log N)` | `VERIFIED` |
| `ALG-0325` | **Maximum Students Taking Exam Profile DP** | [maximum_students_taking_exam.cpp](../Dynamic%20Programming/maximum_students_taking_exam.cpp) | `O(R * 2^C * 2^C)` | `VERIFIED` |
| `ALG-0326` | **Maximum Sum Increasing Subsequence (MSIS) DP** | [maximum_sum_increasing_subsequence.cpp](../Dynamic%20Programming/maximum_sum_increasing_subsequence.cpp) | `O(N^2)` | `VERIFIED` |
| `ALG-0327` | **Max Weight Independent Set on Path Graph** | [maximum_weight_independent_set_path.cpp](../Dynamic%20Programming/maximum_weight_independent_set_path.cpp) | `O(N)` | `VERIFIED` |
| `ALG-0328` | **Min-Cost Bipartite Matching via Bitmask DP** | [minimum_cost_bipartite_matching_bitmask.cpp](../Dynamic%20Programming/minimum_cost_bipartite_matching_bitmask.cpp) | `O(2^N * N)` | `VERIFIED` |
| `ALG-0329` | **Minimum Path Sum in Grid DP** | [minimum_path_sum_grid.cpp](../Dynamic%20Programming/minimum_path_sum_grid.cpp) | `O(R * C)` | `VERIFIED` |
| `ALG-0330` | **Monotonic Queue 1D DP Optimization** | [monotonic_queue_dp_optimization.cpp](../Dynamic%20Programming/monotonic_queue_dp_optimization.cpp) | `O(N)` | `VERIFIED` |
| `ALG-0331` | **Count Paths of Exact Length K in DAG DP** | [number_of_paths_exact_k_steps_dag.cpp](../Dynamic%20Programming/number_of_paths_exact_k_steps_dag.cpp) | `O(K * (V + E))` | `VERIFIED` |
| `ALG-0332` | **Optimal Binary Search Tree Interval DP** | [optimal_binary_search_tree.cpp](../Dynamic%20Programming/optimal_binary_search_tree.cpp) | `O(N^3)` | `VERIFIED` |
| `ALG-0333` | **Paint Fence DP (At Most Two Adjacent Same)** | [paint_fence_dp.cpp](../Dynamic%20Programming/paint_fence_dp.cpp) | `O(N)` | `VERIFIED` |
| `ALG-0334` | **Paint House with K Colors DP** | [paint_house_colors_dp.cpp](../Dynamic%20Programming/paint_house_colors_dp.cpp) | `O(N * K)` | `VERIFIED` |
| `ALG-0335` | **Palindrome Partitioning Minimum Cuts DP** | [palindrome_partitioning_min_cuts.cpp](../Dynamic%20Programming/palindrome_partitioning_min_cuts.cpp) | `O(N^2)` | `VERIFIED` |
| `ALG-0336` | **Partition Equal Subset Sum DP** | [partition_equal_subset_sum.cpp](../Dynamic%20Programming/partition_equal_subset_sum.cpp) | `O(N * Sum)` | `VERIFIED` |
| `ALG-0337` | **Partition Array into K Subsets of Equal Sum DP** | [partition_k_subsets_equal_sum.cpp](../Dynamic%20Programming/partition_k_subsets_equal_sum.cpp) | `O(K * 2^N)` | `VERIFIED` |
| `ALG-0338` | **Minimum Perfect Squares Sum DP** | [perfect_squares_sum_dp.cpp](../Dynamic%20Programming/perfect_squares_sum_dp.cpp) | `O(N * sqrt(N))` | `VERIFIED` |
| `ALG-0339` | **Regular Expression Matching NFA DP** | [regular_expression_matching_nfa_dp.cpp](../Dynamic%20Programming/regular_expression_matching_nfa_dp.cpp) | `O(N * M)` | `VERIFIED` |
| `ALG-0340` | **Rod Cutting Profit Maximization DP** | [rod_cutting_maximization.cpp](../Dynamic%20Programming/rod_cutting_maximization.cpp) | `O(N^2)` | `VERIFIED` |
| `ALG-0341` | **Russian Doll Envelopes 2D LIS** | [russian_doll_envelopes.cpp](../Dynamic%20Programming/russian_doll_envelopes.cpp) | `O(N log N)` | `VERIFIED` |
| `ALG-0342` | **Shortest Common Supersequence with Reconstruction** | [shortest_common_supersequence.cpp](../Dynamic%20Programming/shortest_common_supersequence.cpp) | `O(N * M)` | `VERIFIED` |
| `ALG-0343` | **Metric TSP Shortest Hamiltonian Cycle DP** | [shortest_hamiltonian_cycle_metric.cpp](../Dynamic%20Programming/shortest_hamiltonian_cycle_metric.cpp) | `O(N^2 * 2^N)` | `VERIFIED` |
| `ALG-0344` | **Slope Trick for Piecewise Linear Convex Optimization** | [slope_trick_convex_dp.cpp](../Dynamic%20Programming/slope_trick_convex_dp.cpp) | `O(N log N)` | `VERIFIED` |
| `ALG-0345` | **Sum Over Subsets (SOS DP / Yates' Algorithm)** | [sos_dp.cpp](../Dynamic%20Programming/sos_dp.cpp) | `O(N * 2^N) time, O(2^N) memory` | `VERIFIED` |
| `ALG-0346` | **Stone Game Interval DP (Minimax Game Theory)** | [stone_game_minimax_interval.cpp](../Dynamic%20Programming/stone_game_minimax_interval.cpp) | `O(N^2)` | `VERIFIED` |
| `ALG-0347` | **Subset Sum Decision and Subset Reconstruction** | [subset_sum_decision_and_reconstruct.cpp](../Dynamic%20Programming/subset_sum_decision_and_reconstruct.cpp) | `O(N * S)` | `VERIFIED` |
| `ALG-0348` | **Super Ugly Numbers Multi-Prime DP** | [super_ugly_numbers_primes_dp.cpp](../Dynamic%20Programming/super_ugly_numbers_primes_dp.cpp) | `O(N * K)` | `VERIFIED` |
| `ALG-0349` | **Target Sum Ways via Subset Sum Reduction** | [target_sum_ways.cpp](../Dynamic%20Programming/target_sum_ways.cpp) | `O(N * Sum)` | `VERIFIED` |
| `ALG-0350` | **Domino and Tromino Tiling 2xN DP** | [tiling_trominoes_dp.cpp](../Dynamic%20Programming/tiling_trominoes_dp.cpp) | `O(N)` | `VERIFIED` |
| `ALG-0351` | **3xN Domino Tiling DP** | [tiling_with_dominoes_3xn.cpp](../Dynamic%20Programming/tiling_with_dominoes_3xn.cpp) | `O(N)` | `VERIFIED` |
| `ALG-0352` | **Traveling Salesperson Problem via Held-Karp Bitmask DP** | [traveling_salesperson_bitmask.cpp](../Dynamic%20Programming/traveling_salesperson_bitmask.cpp) | `O(2^N * N^2)` | `VERIFIED` |
| `ALG-0353` | **Minimum Dominating Set on Trees DP** | [tree_dominating_set.cpp](../Dynamic%20Programming/tree_dominating_set.cpp) | `O(N)` | `VERIFIED` |
| `ALG-0354` | **Tree Knapsack Subtree-Bounded DP** | [tree_knapsack_subtree_dp.cpp](../Dynamic%20Programming/tree_knapsack_subtree_dp.cpp) | `O(N * W)` | `VERIFIED` |
| `ALG-0355` | **Maximum Independent Set on Trees via Post-Order DP** | [tree_max_independent_set.cpp](../Dynamic%20Programming/tree_max_independent_set.cpp) | `O(N)` | `VERIFIED` |
| `ALG-0356` | **Minimum Vertex Cover on Trees DP** | [tree_vertex_cover.cpp](../Dynamic%20Programming/tree_vertex_cover.cpp) | `O(N)` | `VERIFIED` |
| `ALG-0357` | **N-th Ugly Number Three-Pointer DP** | [ugly_numbers_ii_three_pointers.cpp](../Dynamic%20Programming/ugly_numbers_ii_three_pointers.cpp) | `O(N)` | `VERIFIED` |
| `ALG-0358` | **Unbounded Knapsack** | [unbounded_knapsack.cpp](../Dynamic%20Programming/unbounded_knapsack.cpp) | `O(n * W) time, O(W) memory` | `VERIFIED` |
| `ALG-0359` | **Wildcard Pattern Matching 2D DP** | [wildcard_matching_2d_dp.cpp](../Dynamic%20Programming/wildcard_matching_2d_dp.cpp) | `O(N * M)` | `VERIFIED` |
| `ALG-0360` | **Word Break Problem DP** | [word_break_dp.cpp](../Dynamic%20Programming/word_break_dp.cpp) | `O(N^2)` | `VERIFIED` |

### Game Theory and Search (1 implementations)

| ID | Algorithm | File | Complexity | Status |
| :--- | :--- | :--- | :--- | :---: |
| `ALG-0361` | **Sprague-Grundy Theorem & Nim Sum** | [nim_game_and_grundy.cpp](../Game%20Theory%20and%20Search/nim_game_and_grundy.cpp) | `O(states * transitions) for Grundy values, O(piles) for Nim sum` | `VERIFIED` |

### Geometry (5 implementations)

| ID | Algorithm | File | Complexity | Status |
| :--- | :--- | :--- | :--- | :---: |
| `ALG-0362` | **Closest Pair of Points (Divide and Conquer)** | [closest_pair_of_points.cpp](../Geometry/closest_pair_of_points.cpp) | `O(n log n) time, O(n) memory` | `VERIFIED` |
| `ALG-0363` | **Convex Hull (Andrew's Monotone Chain)** | [convex_hull_monotone_chain.cpp](../Geometry/convex_hull_monotone_chain.cpp) | `O(n log n) sorting, O(n) scan, O(n) memory` | `VERIFIED` |
| `ALG-0364` | **Point2D and Vector2D** | [point2d_and_vector2d.cpp](../Geometry/point2d_and_vector2d.cpp) | `O(1) per operation, exact 64-bit/128-bit integer precision` | `VERIFIED` |
| `ALG-0365` | **Polygon Area and Point-in-Polygon (Ray Casting)** | [polygon_area_and_point_in_polygon.cpp](../Geometry/polygon_area_and_point_in_polygon.cpp) | `O(n) time, O(1) space` | `VERIFIED` |
| `ALG-0366` | **Segment-Segment Intersection** | [segment_intersection.cpp](../Geometry/segment_intersection.cpp) | `O(1) time, exact arithmetic using __int128 to prevent overflow` | `VERIFIED` |

### Graph Theory (90 implementations)

| ID | Algorithm | File | Complexity | Status |
| :--- | :--- | :--- | :--- | :---: |
| `ALG-0367` | **A* Heuristic Path Search on 2D Grid** | [a_star_heuristic_search.cpp](../Graph%20Theory/a_star_heuristic_search.cpp) | `O(E)` | `VERIFIED` |
| `ALG-0368` | **Alien Dictionary Character Order via Topo Sort** | [alien_dictionary_topological_sort.cpp](../Graph%20Theory/alien_dictionary_topological_sort.cpp) | `O(TotalCharacters + Sigma)` | `VERIFIED` |
| `ALG-0369` | **All Simple Paths Enumeration DFS** | [all_simple_paths_dfs.cpp](../Graph%20Theory/all_simple_paths_dfs.cpp) | `O(V * Paths)` | `VERIFIED` |
| `ALG-0370` | **Edmonds / Chu-Liu Minimum Spanning Arborescence** | [arborescence_edmonds_chu_liu.cpp](../Graph%20Theory/arborescence_edmonds_chu_liu.cpp) | `O(V * E)` | `VERIFIED` |
| `ALG-0371` | **Bellman-Ford Algorithm** | [bellman_ford.cpp](../Graph%20Theory/bellman_ford.cpp) | `O(V * E) time, O(V + E) memory` | `VERIFIED` |
| `ALG-0372` | **BEST Theorem for Number of Eulerian Circuits** | [best_theorem_eulerian_tours.cpp](../Graph%20Theory/best_theorem_eulerian_tours.cpp) | `O(V^3)` | `VERIFIED` |
| `ALG-0373` | **Betweenness Centrality (Brandes Algorithm)** | [betweenness_centrality_brandes.cpp](../Graph%20Theory/betweenness_centrality_brandes.cpp) | `O(V * E)` | `VERIFIED` |
| `ALG-0374` | **Breadth-First Search (BFS) Shortest Path** | [bfs_shortest_path.cpp](../Graph%20Theory/bfs_shortest_path.cpp) | `O(V + E) time, O(V) memory` | `VERIFIED` |
| `ALG-0375` | **Biconnected Components (Hopcroft-Tarjan)** | [biconnected_components_hopcroft_tarjan.cpp](../Graph%20Theory/biconnected_components_hopcroft_tarjan.cpp) | `O(V + E)` | `VERIFIED` |
| `ALG-0376` | **Bidirectional Breadth-First Search** | [bidirectional_bfs.cpp](../Graph%20Theory/bidirectional_bfs.cpp) | `O(b^(d/2))` | `VERIFIED` |
| `ALG-0377` | **Bidirectional Dijkstra Search** | [bidirectional_dijkstra.cpp](../Graph%20Theory/bidirectional_dijkstra.cpp) | `O(b^(d/2)) average search space` | `VERIFIED` |
| `ALG-0378` | **Bipartite Graph 2-Coloring Check** | [bipartite_graph_two_coloring.cpp](../Graph%20Theory/bipartite_graph_two_coloring.cpp) | `O(V + E)` | `VERIFIED` |
| `ALG-0379` | **Hungarian Algorithm for Min Weight Perfect Matching** | [bipartite_matching_minimum_weight_perfect.cpp](../Graph%20Theory/bipartite_matching_minimum_weight_perfect.cpp) | `O(N^3)` | `VERIFIED` |
| `ALG-0380` | **Block-Cut Tree Construction** | [block_cut_tree_construction.cpp](../Graph%20Theory/block_cut_tree_construction.cpp) | `O(V + E)` | `VERIFIED` |
| `ALG-0381` | **Boruvka Minimum Spanning Tree Algorithm** | [boruvka_mst_algorithm.cpp](../Graph%20Theory/boruvka_mst_algorithm.cpp) | `O(E log V)` | `VERIFIED` |
| `ALG-0382` | **2-Edge Connected Components and Bridge Tree** | [bridge_tree_2_edge_connected.cpp](../Graph%20Theory/bridge_tree_2_edge_connected.cpp) | `O(V + E)` | `VERIFIED` |
| `ALG-0383` | **Bridges and Articulation Points (Cut Vertices & Edges)** | [bridges_and_articulation_points.cpp](../Graph%20Theory/bridges_and_articulation_points.cpp) | `O(V + E) time, O(V + E) memory` | `VERIFIED` |
| `ALG-0384` | **Bron-Kerbosch Maximal Cliques with Pivoting** | [bron_kerbosch_maximal_cliques.cpp](../Graph%20Theory/bron_kerbosch_maximal_cliques.cpp) | `O(3^(V/3))` | `VERIFIED` |
| `ALG-0385` | **Chinese Postman Problem Undirected Graph** | [chinese_postman_undirected.cpp](../Graph%20Theory/chinese_postman_undirected.cpp) | `O(V^3 + 2^K * K^2)` | `VERIFIED` |
| `ALG-0386` | **Chordal Graph Recognition via MCS** | [chordal_graph_mcs.cpp](../Graph%20Theory/chordal_graph_mcs.cpp) | `O(V + E)` | `VERIFIED` |
| `ALG-0387` | **Closeness Centrality for All Vertices** | [closeness_centrality_all_vertices.cpp](../Graph%20Theory/closeness_centrality_all_vertices.cpp) | `O(V * (V + E))` | `VERIFIED` |
| `ALG-0388` | **Condensation Graph Construction via Tarjan** | [condensation_graph_dag.cpp](../Graph%20Theory/condensation_graph_dag.cpp) | `O(V + E)` | `VERIFIED` |
| `ALG-0389` | **Connected Components via BFS** | [connected_components_bfs.cpp](../Graph%20Theory/connected_components_bfs.cpp) | `O(V + E)` | `VERIFIED` |
| `ALG-0390` | **Connected Components via DFS** | [connected_components_dfs.cpp](../Graph%20Theory/connected_components_dfs.cpp) | `O(V + E)` | `VERIFIED` |
| `ALG-0391` | **Kirchhoff Matrix Tree Theorem** | [count_spanning_trees_kirchhoff.cpp](../Graph%20Theory/count_spanning_trees_kirchhoff.cpp) | `O(V^3)` | `VERIFIED` |
| `ALG-0392` | **Directed Cycle Detection via 3-Color DFS** | [cycle_detection_directed_color.cpp](../Graph%20Theory/cycle_detection_directed_color.cpp) | `O(V + E)` | `VERIFIED` |
| `ALG-0393` | **Undirected Cycle Detection with Path Extraction** | [cycle_detection_undirected_dfs.cpp](../Graph%20Theory/cycle_detection_undirected_dfs.cpp) | `O(V + E)` | `VERIFIED` |
| `ALG-0394` | **De Bruijn Graph Eulerian Reconstruction** | [de_bruijn_graph_construction.cpp](../Graph%20Theory/de_bruijn_graph_construction.cpp) | `O(N * K)` | `VERIFIED` |
| `ALG-0395` | **Dial Algorithm (0-C Shortest Path Bucket Queue)** | [dial_algorithm_0_c_bfs.cpp](../Graph%20Theory/dial_algorithm_0_c_bfs.cpp) | `O(V * C + E)` | `VERIFIED` |
| `ALG-0396` | **Diameter of Directed Acyclic Graph** | [diameter_of_dag.cpp](../Graph%20Theory/diameter_of_dag.cpp) | `O(V + E)` | `VERIFIED` |
| `ALG-0397` | **Dijkstra's Algorithm** | [dijkstra.cpp](../Graph%20Theory/dijkstra.cpp) | `O((V + E) log V) time, O(V + E) memory` | `VERIFIED` |
| `ALG-0398` | **Directed Eulerian Trail via Hierholzer** | [directed_eulerian_trail_hierholzer.cpp](../Graph%20Theory/directed_eulerian_trail_hierholzer.cpp) | `O(V + E)` | `VERIFIED` |
| `ALG-0399` | **Lengauer-Tarjan Dominator Tree** | [dominator_tree_lengauer_tarjan.cpp](../Graph%20Theory/dominator_tree_lengauer_tarjan.cpp) | `O(M log N)` | `VERIFIED` |
| `ALG-0400` | **Ear Decomposition of 2-Connected Graphs** | [ear_decomposition_2_connected.cpp](../Graph%20Theory/ear_decomposition_2_connected.cpp) | `O(V + E)` | `VERIFIED` |
| `ALG-0401` | **Edge Connectivity via Minimum s-t Cuts** | [edge_connectivity_flow.cpp](../Graph%20Theory/edge_connectivity_flow.cpp) | `O(V^2 * E)` | `VERIFIED` |
| `ALG-0402` | **Eulerian Trail / Circuit (Hierholzer's Algorithm)** | [eulerian_path.cpp](../Graph%20Theory/eulerian_path.cpp) | `O(V + E) time, O(V + E) memory` | `VERIFIED` |
| `ALG-0403` | **Directed Eulerian Path with Edge IDs** | [eulerian_path_directed_with_edge_ids.cpp](../Graph%20Theory/eulerian_path_directed_with_edge_ids.cpp) | `O(V + E)` | `VERIFIED` |
| `ALG-0404` | **Feedback Vertex Set in Tournament Graph** | [feedback_vertex_set_tournament.cpp](../Graph%20Theory/feedback_vertex_set_tournament.cpp) | `O(2^K * N)` | `VERIFIED` |
| `ALG-0405` | **Fleury Eulerian Trail Construction** | [fleury_eulerian_trail.cpp](../Graph%20Theory/fleury_eulerian_trail.cpp) | `O(E^2)` | `VERIFIED` |
| `ALG-0406` | **2D Grid Flood Fill via BFS** | [flood_fill_grid_bfs.cpp](../Graph%20Theory/flood_fill_grid_bfs.cpp) | `O(R * C)` | `VERIFIED` |
| `ALG-0407` | **Floyd-Warshall Algorithm** | [floyd_warshall.cpp](../Graph%20Theory/floyd_warshall.cpp) | `O(V^3) time, O(V^2) memory` | `VERIFIED` |
| `ALG-0408` | **Gabow Strongly Connected Components (Two Stacks)** | [gabow_scc_algorithm.cpp](../Graph%20Theory/gabow_scc_algorithm.cpp) | `O(V + E)` | `VERIFIED` |
| `ALG-0409` | **Graph Center and Periphery** | [graph_center_and_periphery.cpp](../Graph%20Theory/graph_center_and_periphery.cpp) | `O(V * (V + E))` | `VERIFIED` |
| `ALG-0410` | **DSatur Graph Vertex Coloring** | [graph_coloring_dsatur.cpp](../Graph%20Theory/graph_coloring_dsatur.cpp) | `O(V^2)` | `VERIFIED` |
| `ALG-0411` | **Welsh-Powell Graph Coloring** | [graph_coloring_welsh_powell.cpp](../Graph%20Theory/graph_coloring_welsh_powell.cpp) | `O(V^2 + E)` | `VERIFIED` |
| `ALG-0412` | **Shortest Cycle (Girth) via BFS** | [graph_girth_bfs.cpp](../Graph%20Theory/graph_girth_bfs.cpp) | `O(V * (V + E))` | `VERIFIED` |
| `ALG-0413` | **Hopcroft-Karp Maximum Bipartite Matching** | [hopcroft_karp_bipartite_matching.cpp](../Graph%20Theory/hopcroft_karp_bipartite_matching.cpp) | `O(E sqrt(V))` | `VERIFIED` |
| `ALG-0414` | **Iterative Deepening A* (IDA*) Grid Search** | [ida_star_search.cpp](../Graph%20Theory/ida_star_search.cpp) | `O(b^d)` | `VERIFIED` |
| `ALG-0415` | **Interval Graph Recognition from Intervals** | [interval_graph_recognition.cpp](../Graph%20Theory/interval_graph_recognition.cpp) | `O(N log N + E)` | `VERIFIED` |
| `ALG-0416` | **Johnson All-Pairs Shortest Paths** | [johnson_all_pairs_shortest_paths.cpp](../Graph%20Theory/johnson_all_pairs_shortest_paths.cpp) | `O(V * E + V^2 log V)` | `VERIFIED` |
| `ALG-0417` | **Yen's Algorithm for K Shortest Loopless Paths** | [k_shortest_paths_yen.cpp](../Graph%20Theory/k_shortest_paths_yen.cpp) | `O(K * V * (E + V log V))` | `VERIFIED` |
| `ALG-0418` | **Kosaraju's Strongly Connected Components** | [kosaraju_scc.cpp](../Graph%20Theory/kosaraju_scc.cpp) | `O(V + E) time, O(V + E) memory` | `VERIFIED` |
| `ALG-0419` | **Kruskal's Minimum Spanning Tree** | [kruskal_mst.cpp](../Graph%20Theory/kruskal_mst.cpp) | `O(E log E) time, O(V + E) memory` | `VERIFIED` |
| `ALG-0420` | **Kuhn's Maximum Bipartite Matching** | [kuhn_bipartite_matching.cpp](../Graph%20Theory/kuhn_bipartite_matching.cpp) | `O(V * E)` | `VERIFIED` |
| `ALG-0421` | **Line Graph Construction** | [line_graph_construction.cpp](../Graph%20Theory/line_graph_construction.cpp) | `O(E + sum(deg^2))` | `VERIFIED` |
| `ALG-0422` | **Tree Diameter and Endpoints via Double BFS** | [longest_path_tree_double_bfs.cpp](../Graph%20Theory/longest_path_tree_double_bfs.cpp) | `O(V + E)` | `VERIFIED` |
| `ALG-0423` | **Maximum Clique Branch and Bound** | [maximum_clique_branch_and_bound.cpp](../Graph%20Theory/maximum_clique_branch_and_bound.cpp) | `O(2^V)` | `VERIFIED` |
| `ALG-0424` | **Maximum Independent Set via Complement Clique** | [maximum_independent_set_general.cpp](../Graph%20Theory/maximum_independent_set_general.cpp) | `O(2^V)` | `VERIFIED` |
| `ALG-0425` | **Maximum Weight Closure in DAG** | [maximum_weight_closure_dag.cpp](../Graph%20Theory/maximum_weight_closure_dag.cpp) | `O(V^2 * E)` | `VERIFIED` |
| `ALG-0426` | **Minimum Bottleneck Spanning Tree (MBST)** | [minimum_bottleneck_spanning_tree.cpp](../Graph%20Theory/minimum_bottleneck_spanning_tree.cpp) | `O(E log V)` | `VERIFIED` |
| `ALG-0427` | **Karger-Stein Randomized Min-Cut** | [minimum_cut_karger_stein.cpp](../Graph%20Theory/minimum_cut_karger_stein.cpp) | `O(V^2 log^3 V)` | `VERIFIED` |
| `ALG-0428` | **Karp Minimum Mean Weight Cycle** | [minimum_mean_weight_cycle_karp.cpp](../Graph%20Theory/minimum_mean_weight_cycle_karp.cpp) | `O(V * E)` | `VERIFIED` |
| `ALG-0429` | **Directed Minimum Spanning Arborescence** | [minimum_spanning_arborescence.cpp](../Graph%20Theory/minimum_spanning_arborescence.cpp) | `O(V * E)` | `VERIFIED` |
| `ALG-0430` | **Multi-Source BFS on 2D Grid** | [multi_source_bfs_grid.cpp](../Graph%20Theory/multi_source_bfs_grid.cpp) | `O(R * C)` | `VERIFIED` |
| `ALG-0431` | **Negative Cycle Detection and Extraction via Bellman-Ford** | [negative_cycle_detection_bellman.cpp](../Graph%20Theory/negative_cycle_detection_bellman.cpp) | `O(V * E)` | `VERIFIED` |
| `ALG-0432` | **PageRank via Power Iteration** | [page_rank_power_iteration.cpp](../Graph%20Theory/page_rank_power_iteration.cpp) | `O(Iterations * (V + E))` | `VERIFIED` |
| `ALG-0433` | **Planar Graph Face Count via Euler Formula** | [planar_graph_euler_formula.cpp](../Graph%20Theory/planar_graph_euler_formula.cpp) | `O(1)` | `VERIFIED` |
| `ALG-0434` | **Prim's Minimum Spanning Tree** | [prim_mst.cpp](../Graph%20Theory/prim_mst.cpp) | `O(E log V) time, O(V + E) memory` | `VERIFIED` |
| `ALG-0435` | **Prufer Sequence Tree Encoding and Decoding** | [prufer_sequence_encode_decode.cpp](../Graph%20Theory/prufer_sequence_encode_decode.cpp) | `O(N log N)` | `VERIFIED` |
| `ALG-0436` | **Random Walk Cover Time Simulation** | [random_walk_cover_time.cpp](../Graph%20Theory/random_walk_cover_time.cpp) | `O(CoverTime)` | `VERIFIED` |
| `ALG-0437` | **Second-Best Minimum Spanning Tree** | [second_best_mst.cpp](../Graph%20Theory/second_best_mst.cpp) | `O(E log V)` | `VERIFIED` |
| `ALG-0438` | **Shortest Cycle Containing Given Edge** | [shortest_cycle_containing_edge.cpp](../Graph%20Theory/shortest_cycle_containing_edge.cpp) | `O(V + E)` | `VERIFIED` |
| `ALG-0439` | **Shortest Path in DAG via Topological Sort** | [shortest_path_dag_topo.cpp](../Graph%20Theory/shortest_path_dag_topo.cpp) | `O(V + E)` | `VERIFIED` |
| `ALG-0440` | **Shortest Path Faster Algorithm (SPFA)** | [spfa.cpp](../Graph%20Theory/spfa.cpp) | `O(E) average time, O(V * E) worst-case, O(V + E) memory` | `VERIFIED` |
| `ALG-0441` | **SPQR Tree Decomposition Representation** | [spqr_tree_triconnected.cpp](../Graph%20Theory/spqr_tree_triconnected.cpp) | `O(V + E)` | `VERIFIED` |
| `ALG-0442` | **Gale-Shapley Stable Marriage Algorithm** | [stable_marriage_gale_shapley.cpp](../Graph%20Theory/stable_marriage_gale_shapley.cpp) | `O(N^2)` | `VERIFIED` |
| `ALG-0443` | **Stoer-Wagner Deterministic Global Min-Cut** | [stoer_wagner_global_min_cut.cpp](../Graph%20Theory/stoer_wagner_global_min_cut.cpp) | `O(V^3)` | `VERIFIED` |
| `ALG-0444` | **Suurballe Algorithm for Minimum Total Length Disjoint Paths** | [suurballe_disjoint_paths.cpp](../Graph%20Theory/suurballe_disjoint_paths.cpp) | `O(E + V log V)` | `VERIFIED` |
| `ALG-0445` | **Tarjan's Strongly Connected Components (SCC)** | [tarjan_scc.cpp](../Graph%20Theory/tarjan_scc.cpp) | `O(V + E) time, O(V + E) memory` | `VERIFIED` |
| `ALG-0446` | **Thorup Component Hierarchy SSSP Simulation** | [thorup_single_source_shortest_path.cpp](../Graph%20Theory/thorup_single_source_shortest_path.cpp) | `O(V + E)` | `VERIFIED` |
| `ALG-0447` | **Topological Sort (Kahn's Algorithm)** | [topological_sort.cpp](../Graph%20Theory/topological_sort.cpp) | `O(V + E) time, O(V + E) memory` | `VERIFIED` |
| `ALG-0448` | **Lexicographically Smallest Topological Sort (Kahn)** | [topological_sort_all_kahn.cpp](../Graph%20Theory/topological_sort_all_kahn.cpp) | `O(V log V + E)` | `VERIFIED` |
| `ALG-0449` | **Hamiltonian Path in Tournament Graph** | [tournament_graph_hamiltonian_path.cpp](../Graph%20Theory/tournament_graph_hamiltonian_path.cpp) | `O(N^2)` | `VERIFIED` |
| `ALG-0450` | **Fast Transitive Closure via Bitset** | [transitive_closure_bitset.cpp](../Graph%20Theory/transitive_closure_bitset.cpp) | `O(V^3 / 64)` | `VERIFIED` |
| `ALG-0451` | **Tree Metric Recognition (Four-Point Condition)** | [tree_metric_recognition.cpp](../Graph%20Theory/tree_metric_recognition.cpp) | `O(N^4)` | `VERIFIED` |
| `ALG-0452` | **2-SAT Solver** | [two_sat.cpp](../Graph%20Theory/two_sat.cpp) | `O(V + E) time, O(V + E) memory` | `VERIFIED` |
| `ALG-0453` | **Undirected Eulerian Circuit Hierholzer** | [undirected_eulerian_circuit.cpp](../Graph%20Theory/undirected_eulerian_circuit.cpp) | `O(V + E)` | `VERIFIED` |
| `ALG-0454` | **Vertex Connectivity via Max Flow** | [vertex_connectivity_flow.cpp](../Graph%20Theory/vertex_connectivity_flow.cpp) | `O(V^3 * E)` | `VERIFIED` |
| `ALG-0455` | **Konig's Theorem Bipartite Minimum Vertex Cover** | [vertex_cover_bipartite_konig.cpp](../Graph%20Theory/vertex_cover_bipartite_konig.cpp) | `O(V * E)` | `VERIFIED` |
| `ALG-0456` | **0-1 BFS** | [zero_one_bfs.cpp](../Graph%20Theory/zero_one_bfs.cpp) | `O(V + E) time, O(V) memory` | `VERIFIED` |

### Greedy Algorithms (35 implementations)

| ID | Algorithm | File | Complexity | Status |
| :--- | :--- | :--- | :--- | :---: |
| `ALG-0457` | **Activity Selection (Interval Scheduling)** | [activity_selection.cpp](../Greedy%20Algorithms/activity_selection.cpp) | `O(N log N) time` | `VERIFIED` |
| `ALG-0458` | **Assign Cookies (Greedy Child Satisfaction)** | [assign_cookies.cpp](../Greedy%20Algorithms/assign_cookies.cpp) | `O(N log N + M log M) time` | `VERIFIED` |
| `ALG-0459` | **Candy Distribution Problem** | [candy_distribution.cpp](../Greedy%20Algorithms/candy_distribution.cpp) | `O(N) time with two passes` | `VERIFIED` |
| `ALG-0460` | **Course Schedule III (Max Courses via Max-Heap)** | [course_schedule_iii.cpp](../Greedy%20Algorithms/course_schedule_iii.cpp) | `O(N log N) time` | `VERIFIED` |
| `ALG-0461` | **Create Maximum Number** | [create_maximum_number.cpp](../Greedy%20Algorithms/create_maximum_number.cpp) | `O(K * (N + M)^2) time` | `VERIFIED` |
| `ALG-0462` | **Greedy Maximum Bottleneck Path** | [dijkstra_greedy_tree.cpp](../Greedy%20Algorithms/dijkstra_greedy_tree.cpp) | `O(M log N) time` | `VERIFIED` |
| `ALG-0463` | **Egyptian Fraction (Greedy Algorithm)** | [egyptian_fraction.cpp](../Greedy%20Algorithms/egyptian_fraction.cpp) | `O(terms) steps` | `VERIFIED` |
| `ALG-0464` | **Fractional Knapsack** | [fractional_knapsack.cpp](../Greedy%20Algorithms/fractional_knapsack.cpp) | `O(N log N) time` | `VERIFIED` |
| `ALG-0465` | **Furthest Building Reachable** | [furthest_building_ladders_bricks.cpp](../Greedy%20Algorithms/furthest_building_ladders_bricks.cpp) | `O(N log ladders) time` | `VERIFIED` |
| `ALG-0466` | **Gas Station Circular Tour** | [gas_station_circular_tour.cpp](../Greedy%20Algorithms/gas_station_circular_tour.cpp) | `O(N) time single pass` | `VERIFIED` |
| `ALG-0467` | **Huffman Coding Tree** | [huffman_coding_tree.cpp](../Greedy%20Algorithms/huffman_coding_tree.cpp) | `O(N log N) time` | `VERIFIED` |
| `ALG-0468` | **IPO (Maximize Capital with K Projects)** | [ipo_maximize_capital.cpp](../Greedy%20Algorithms/ipo_maximize_capital.cpp) | `O(N log N + K log N) time` | `VERIFIED` |
| `ALG-0469` | **Job Sequencing with Deadlines and Profits (DSU)** | [job_sequencing_deadline_profit.cpp](../Greedy%20Algorithms/job_sequencing_deadline_profit.cpp) | `O(N log N + N * alpha(max_deadline)) time` | `VERIFIED` |
| `ALG-0470` | **Jump Game II (Minimum Jumps)** | [jump_game_min_jumps.cpp](../Greedy%20Algorithms/jump_game_min_jumps.cpp) | `O(N) time` | `VERIFIED` |
| `ALG-0471` | **Jump Game (Reachability)** | [jump_game_reachability.cpp](../Greedy%20Algorithms/jump_game_reachability.cpp) | `O(N) time` | `VERIFIED` |
| `ALG-0472` | **K-th Largest Element in a Stream** | [kth_largest_element_stream.cpp](../Greedy%20Algorithms/kth_largest_element_stream.cpp) | `O(log K) per added element` | `VERIFIED` |
| `ALG-0473` | **Largest Number Concatenation** | [largest_number_custom_comparator.cpp](../Greedy%20Algorithms/largest_number_custom_comparator.cpp) | `O(N log N * L) time where L is average number of digits` | `VERIFIED` |
| `ALG-0474` | **Lemonade Change** | [lemonade_change.cpp](../Greedy%20Algorithms/lemonade_change.cpp) | `O(N) time single pass` | `VERIFIED` |
| `ALG-0475` | **Maximum Swap (Largest Number Single Swap)** | [maximum_swap_largest_number.cpp](../Greedy%20Algorithms/maximum_swap_largest_number.cpp) | `O(digits) time` | `VERIFIED` |
| `ALG-0476` | **Maximum Units on a Truck** | [maximum_units_on_truck.cpp](../Greedy%20Algorithms/maximum_units_on_truck.cpp) | `O(N log N) time` | `VERIFIED` |
| `ALG-0477` | **Minimum Arrows to Burst Balloons (Interval Covering)** | [minimum_arrows_burst_balloons.cpp](../Greedy%20Algorithms/minimum_arrows_burst_balloons.cpp) | `O(N log N) time` | `VERIFIED` |
| `ALG-0478` | **Minimum Cost of Connecting Ropes** | [minimum_cost_ropes_connect.cpp](../Greedy%20Algorithms/minimum_cost_ropes_connect.cpp) | `O(N log N) time` | `VERIFIED` |
| `ALG-0479` | **Minimum Refueling Stops** | [minimum_number_of_refueling_stops.cpp](../Greedy%20Algorithms/minimum_number_of_refueling_stops.cpp) | `O(N log N) time` | `VERIFIED` |
| `ALG-0480` | **Minimum Operations to Reduce X to Zero** | [minimum_operations_reduce_x_to_zero.cpp](../Greedy%20Algorithms/minimum_operations_reduce_x_to_zero.cpp) | `O(N) time` | `VERIFIED` |
| `ALG-0481` | **Minimum Railway Platforms Required** | [minimum_platforms_trains.cpp](../Greedy%20Algorithms/minimum_platforms_trains.cpp) | `O(N log N) time` | `VERIFIED` |
| `ALG-0482` | **Monotone Increasing Digits** | [monotone_increasing_digits.cpp](../Greedy%20Algorithms/monotone_increasing_digits.cpp) | `O(digits) time` | `VERIFIED` |
| `ALG-0483` | **Non-Overlapping Intervals (Minimum Removals)** | [non_overlapping_intervals_erase.cpp](../Greedy%20Algorithms/non_overlapping_intervals_erase.cpp) | `O(N log N) time` | `VERIFIED` |
| `ALG-0484` | **Optimal Merge Patterns** | [optimal_merge_patterns.cpp](../Greedy%20Algorithms/optimal_merge_patterns.cpp) | `O(N log N) time` | `VERIFIED` |
| `ALG-0485` | **Patching Array (Greedy Range Expansion)** | [patching_array.cpp](../Greedy%20Algorithms/patching_array.cpp) | `O(M + log N) time` | `VERIFIED` |
| `ALG-0486` | **Queue Reconstruction by Height** | [queue_reconstruction_by_height.cpp](../Greedy%20Algorithms/queue_reconstruction_by_height.cpp) | `O(N^2) time` | `VERIFIED` |
| `ALG-0487` | **Remove K Digits (Smallest Number Monotonic Stack)** | [remove_k_digits_smallest_number.cpp](../Greedy%20Algorithms/remove_k_digits_smallest_number.cpp) | `O(N) time` | `VERIFIED` |
| `ALG-0488` | **Reorganize String (No Adjacent Identical Characters)** | [reorganize_string_greedy.cpp](../Greedy%20Algorithms/reorganize_string_greedy.cpp) | `O(N log 26) time` | `VERIFIED` |
| `ALG-0489` | **Split Array into Consecutive Subsequences** | [split_array_consecutive_subsequences.cpp](../Greedy%20Algorithms/split_array_consecutive_subsequences.cpp) | `O(N) time` | `VERIFIED` |
| `ALG-0490` | **Task Scheduler with Cooldown** | [task_scheduler_cooldown.cpp](../Greedy%20Algorithms/task_scheduler_cooldown.cpp) | `O(Tasks) time` | `VERIFIED` |
| `ALG-0491` | **Two City Scheduling** | [two_city_scheduling.cpp](../Greedy%20Algorithms/two_city_scheduling.cpp) | `O(N log N) time` | `VERIFIED` |

### Number Theory (37 implementations)

| ID | Algorithm | File | Complexity | Status |
| :--- | :--- | :--- | :--- | :---: |
| `ALG-0492` | **Stein's Binary GCD Algorithm** | [binary_gcd_stein.cpp](../Number%20Theory/binary_gcd_stein.cpp) | `O(log(min(a, b))) time` | `VERIFIED` |
| `ALG-0493` | **Modular Catalan Numbers** | [catalan_numbers_modular.cpp](../Number%20Theory/catalan_numbers_modular.cpp) | `O(N) time` | `VERIFIED` |
| `ALG-0494` | **Chinese Remainder Theorem (CRT)** | [chinese_remainder_theorem.cpp](../Number%20Theory/chinese_remainder_theorem.cpp) | `O(k * log(lcm(m))) time, O(1) space` | `VERIFIED` |
| `ALG-0495` | **Continued Fraction Expansion** | [continued_fractions.cpp](../Number%20Theory/continued_fractions.cpp) | `O(log(Q)) time` | `VERIFIED` |
| `ALG-0496` | **Chinese Remainder Theorem (Non-Coprime Moduli)** | [crt_non_coprime.cpp](../Number%20Theory/crt_non_coprime.cpp) | `O(N log(lcm)) time` | `VERIFIED` |
| `ALG-0497` | **Baby-Step Giant-Step (Discrete Logarithm)** | [discrete_log_baby_step_giant_step.cpp](../Number%20Theory/discrete_log_baby_step_giant_step.cpp) | `O(sqrt(m) log m) time` | `VERIFIED` |
| `ALG-0498` | **Discrete Root Solver (x^k = a mod p)** | [discrete_root_solver.cpp](../Number%20Theory/discrete_root_solver.cpp) | `O(sqrt(p) log p) time` | `VERIFIED` |
| `ALG-0499` | **Sum of Divisor Function Sum(Tau) in O(sqrt(N))** | [divisor_sum_range_fast.cpp](../Number%20Theory/divisor_sum_range_fast.cpp) | `O(sqrt(N)) time` | `VERIFIED` |
| `ALG-0500` | **Euler's Totient Function (Phi)** | [euler_totient.cpp](../Number%20Theory/euler_totient.cpp) | `O(sqrt(n)) single value, O(N) for sieve range [1, N]` | `VERIFIED` |
| `ALG-0501` | **Range Euler's Totient Sieve** | [euler_totient_range_sieve.cpp](../Number%20Theory/euler_totient_range_sieve.cpp) | `O((R - L + 1) log log R + sqrt(R)) time` | `VERIFIED` |
| `ALG-0502` | **Euler's Totient Function (Single Integer)** | [euler_totient_single.cpp](../Number%20Theory/euler_totient_single.cpp) | `O(sqrt(N)) time` | `VERIFIED` |
| `ALG-0503` | **Extended GCD and Modular Inverse** | [extended_gcd_and_modular_inverse.cpp](../Number%20Theory/extended_gcd_and_modular_inverse.cpp) | `O(log(min(a, b))) time, O(1) space` | `VERIFIED` |
| `ALG-0504` | **Extended Euclidean Algorithm (Iterative)** | [extended_gcd_iterative.cpp](../Number%20Theory/extended_gcd_iterative.cpp) | `O(log(min(a, b))) time` | `VERIFIED` |
| `ALG-0505` | **Floor Sum of Arithmetic Progression** | [floor_sum_ap.cpp](../Number%20Theory/floor_sum_ap.cpp) | `O(log c) time` | `VERIFIED` |
| `ALG-0506` | **Array GCD and LCM** | [greatest_common_divisor_array.cpp](../Number%20Theory/greatest_common_divisor_array.cpp) | `O(N log(max_val)) time` | `VERIFIED` |
| `ALG-0507` | **Harmonic Lemma (Block Square Root Division)** | [harmonic_lemma_sqrt_decomposition.cpp](../Number%20Theory/harmonic_lemma_sqrt_decomposition.cpp) | `O(sqrt(N)) steps` | `VERIFIED` |
| `ALG-0508` | **Legendre's Formula (Prime Factor Multiplicity in N!)** | [legendre_formula_prime_exponent.cpp](../Number%20Theory/legendre_formula_prime_exponent.cpp) | `O(log_P N) time` | `VERIFIED` |
| `ALG-0509` | **Linear Diophantine Equation Solver** | [linear_diophantine_solver.cpp](../Number%20Theory/linear_diophantine_solver.cpp) | `O(log(min(a, b))) time` | `VERIFIED` |
| `ALG-0510` | **Euler's Linear Sieve (SPF)** | [linear_sieve.cpp](../Number%20Theory/linear_sieve.cpp) | `O(N) preprocessing, O(log x) factorization per number` | `VERIFIED` |
| `ALG-0511` | **Lucas-Lehmer Primality Test** | [lucas_lehmer_mersenne.cpp](../Number%20Theory/lucas_lehmer_mersenne.cpp) | `O(p * M(p)) time where M(p) is multiplication complexity` | `VERIFIED` |
| `ALG-0512` | **Lucas' Theorem for Binomial Coefficients** | [lucas_theorem_combinations.cpp](../Number%20Theory/lucas_theorem_combinations.cpp) | `O(P + log_P N) time` | `VERIFIED` |
| `ALG-0513` | **Deterministic Miller-Rabin Primality Test (64-bit)** | [miller_rabin_deterministic_64.cpp](../Number%20Theory/miller_rabin_deterministic_64.cpp) | `O(7 log N) time` | `VERIFIED` |
| `ALG-0514` | **Miller-Rabin Primality Test** | [miller_rabin_primality.cpp](../Number%20Theory/miller_rabin_primality.cpp) | `O(k log n) where k is 12 deterministic test bases, < 1 microsecond per query` | `VERIFIED` |
| `ALG-0515` | **Linear Range Modular Inverses** | [modular_inverse_range.cpp](../Number%20Theory/modular_inverse_range.cpp) | `O(N) time` | `VERIFIED` |
| `ALG-0516` | **Pollard's p-1 Factorization** | [pollard_p_minus_1.cpp](../Number%20Theory/pollard_p_minus_1.cpp) | `O(B log N) time` | `VERIFIED` |
| `ALG-0517` | **Pollard's Rho Algorithm (Brent's Cycle Detection)** | [pollards_rho.cpp](../Number%20Theory/pollards_rho.cpp) | `O(n^(1/4)) expected time per factor, O(1) memory` | `VERIFIED` |
| `ALG-0518` | **Primitive Root Finder** | [primitive_root_search.cpp](../Number%20Theory/primitive_root_search.cpp) | `O(Ans * log^2 P) where Ans is usually very small (< 10)` | `VERIFIED` |
| `ALG-0519` | **Pythagorean Triples Generator (Euclid's Formula)** | [pythagorean_triples_generator.cpp](../Number%20Theory/pythagorean_triples_generator.cpp) | `O(sqrt(limit) log(limit)) time` | `VERIFIED` |
| `ALG-0520` | **Segmented Sieve of Eratosthenes** | [segmented_sieve.cpp](../Number%20Theory/segmented_sieve.cpp) | `O((R - L + 1) log log R + sqrt(R) log log sqrt(R)) time` | `VERIFIED` |
| `ALG-0521` | **Linear Sieve for Divisor Count (Tau)** | [sieve_divisor_count_tau.cpp](../Number%20Theory/sieve_divisor_count_tau.cpp) | `O(N) time` | `VERIFIED` |
| `ALG-0522` | **Linear Sieve for Divisor Sum (Sigma)** | [sieve_divisor_sum_sigma.cpp](../Number%20Theory/sieve_divisor_sum_sigma.cpp) | `O(N) time` | `VERIFIED` |
| `ALG-0523` | **Linear Sieve for Mobius Function (Mu)** | [sieve_mobius_mu.cpp](../Number%20Theory/sieve_mobius_mu.cpp) | `O(N) time` | `VERIFIED` |
| `ALG-0524` | **Sieve of Eratosthenes** | [sieve_of_eratosthenes.cpp](../Number%20Theory/sieve_of_eratosthenes.cpp) | `O(N log log N) time, O(N) memory` | `VERIFIED` |
| `ALG-0525` | **Stern-Brocot Tree and Farey Sequence** | [stern_brocot_farey.cpp](../Number%20Theory/stern_brocot_farey.cpp) | `O(log(Q)) time` | `VERIFIED` |
| `ALG-0526` | **Fermat's Two Squares Representation** | [sum_of_squares_two_squares.cpp](../Number%20Theory/sum_of_squares_two_squares.cpp) | `O(sqrt(N)) time` | `VERIFIED` |
| `ALG-0527` | **Tonelli-Shanks Algorithm (Modular Square Root)** | [tonelli_shanks_sqrt.cpp](../Number%20Theory/tonelli_shanks_sqrt.cpp) | `O(log^2 p) expected time` | `VERIFIED` |
| `ALG-0528` | **Wilson's Theorem Primality Check** | [wilson_theorem_primality.cpp](../Number%20Theory/wilson_theorem_primality.cpp) | `O(N) time` | `VERIFIED` |

### Optimization and Advanced Techniques (1 implementations)

| ID | Algorithm | File | Complexity | Status |
| :--- | :--- | :--- | :--- | :---: |
| `ALG-0529` | **Simulated Annealing Metaheuristic** | [simulated_annealing.cpp](../Optimization%20and%20Advanced%20Techniques/simulated_annealing.cpp) | `Dependent on time limit and iteration budget` | `VERIFIED` |

### Recursion and Backtracking (25 implementations)

| ID | Algorithm | File | Complexity | Status |
| :--- | :--- | :--- | :--- | :---: |
| `ALG-0530` | **Combination Sum III (K Numbers from 1 to 9)** | [combination_sum_fixed_k.cpp](../Recursion%20and%20Backtracking/combination_sum_fixed_k.cpp) | `O(C(9, K)) time` | `VERIFIED` |
| `ALG-0531` | **Combination Sum II (Single Use with Duplicates)** | [combination_sum_unique.cpp](../Recursion%20and%20Backtracking/combination_sum_unique.cpp) | `O(2^N) time` | `VERIFIED` |
| `ALG-0532` | **Combination Sum (Unlimited Use)** | [combination_sum_unlimited.cpp](../Recursion%20and%20Backtracking/combination_sum_unlimited.cpp) | `O(2^Target) worst case` | `VERIFIED` |
| `ALG-0533` | **Expression Add Operators** | [expression_add_operators.cpp](../Recursion%20and%20Backtracking/expression_add_operators.cpp) | `O(4^N) time` | `VERIFIED` |
| `ALG-0534` | **Generate Parentheses** | [generate_parentheses.cpp](../Recursion%20and%20Backtracking/generate_parentheses.cpp) | `O(4^N / sqrt(N)) Catalan number bound` | `VERIFIED` |
| `ALG-0535` | **Graph M-Coloring (Backtracking)** | [graph_m_coloring.cpp](../Recursion%20and%20Backtracking/graph_m_coloring.cpp) | `O(M^V) worst case` | `VERIFIED` |
| `ALG-0536` | **Hamiltonian Cycle (Backtracking)** | [hamiltonian_cycle_backtracking.cpp](../Recursion%20and%20Backtracking/hamiltonian_cycle_backtracking.cpp) | `O(N!) worst case` | `VERIFIED` |
| `ALG-0537` | **Knight's Tour (Warnsdorff's Heuristic)** | [knights_tour_warnsdorff.cpp](../Recursion%20and%20Backtracking/knights_tour_warnsdorff.cpp) | `O(N^2) linear time with Warnsdorff's tie-breaking` | `VERIFIED` |
| `ALG-0538` | **Letter Combinations of a Phone Number** | [letter_combinations_phone_number.cpp](../Recursion%20and%20Backtracking/letter_combinations_phone_number.cpp) | `O(4^N * N) time` | `VERIFIED` |
| `ALG-0539` | **Matchsticks to Square** | [matchsticks_to_square.cpp](../Recursion%20and%20Backtracking/matchsticks_to_square.cpp) | `O(4^N) time with sorted pruning` | `VERIFIED` |
| `ALG-0540` | **N-Queens Solver (Bitmask Optimization)** | [n_queens_bitmask.cpp](../Recursion%20and%20Backtracking/n_queens_bitmask.cpp) | `O(N!) time with ultra-fast bitwise constant factors` | `VERIFIED` |
| `ALG-0541` | **N-Queens Solver (Standard Backtracking)** | [n_queens_standard.cpp](../Recursion%20and%20Backtracking/n_queens_standard.cpp) | `O(N!) time` | `VERIFIED` |
| `ALG-0542` | **Palindrome Partitioning** | [palindrome_partitioning.cpp](../Recursion%20and%20Backtracking/palindrome_partitioning.cpp) | `O(N * 2^N) time` | `VERIFIED` |
| `ALG-0543` | **Partition to K Equal Sum Subsets** | [partition_k_equal_sum_subsets.cpp](../Recursion%20and%20Backtracking/partition_k_equal_sum_subsets.cpp) | `O(K * 2^N) time with pruning` | `VERIFIED` |
| `ALG-0544` | **Permutations Generator** | [permutations_all.cpp](../Recursion%20and%20Backtracking/permutations_all.cpp) | `O(N * N!) time` | `VERIFIED` |
| `ALG-0545` | **Permutations II (Unique Permutations with Duplicates)** | [permutations_with_duplicates.cpp](../Recursion%20and%20Backtracking/permutations_with_duplicates.cpp) | `O(N * N!) time` | `VERIFIED` |
| `ALG-0546` | **Rat in a Maze (All Directional Paths)** | [rat_in_a_maze.cpp](../Recursion%20and%20Backtracking/rat_in_a_maze.cpp) | `O(4^(N^2)) worst case` | `VERIFIED` |
| `ALG-0547` | **Restore IP Addresses** | [restore_ip_addresses.cpp](../Recursion%20and%20Backtracking/restore_ip_addresses.cpp) | `O(3^4) = O(1) bounded time` | `VERIFIED` |
| `ALG-0548` | **Lexicographical Subsets Generation** | [subsets_lexicographic.cpp](../Recursion%20and%20Backtracking/subsets_lexicographic.cpp) | `O(N * 2^N) time` | `VERIFIED` |
| `ALG-0549` | **Subsets II (Subsets with Duplicates)** | [subsets_with_duplicates.cpp](../Recursion%20and%20Backtracking/subsets_with_duplicates.cpp) | `O(N * 2^N) time` | `VERIFIED` |
| `ALG-0550` | **Sudoku Solver (Exact Cover / Backtracking)** | [sudoku_solver.cpp](../Recursion%20and%20Backtracking/sudoku_solver.cpp) | `O(9^(empty cells)) worst case, sub-millisecond in practice` | `VERIFIED` |
| `ALG-0551` | **Target Sum (+ and - Assignments)** | [target_sum_ways.cpp](../Recursion%20and%20Backtracking/target_sum_ways.cpp) | `O(2^N) time recursion, O(N * Sum) with memoization` | `VERIFIED` |
| `ALG-0552` | **Tug of War (Equal-Size Partition with Minimum Difference)** | [tug_of_war_partition.cpp](../Recursion%20and%20Backtracking/tug_of_war_partition.cpp) | `O(2^N) with branch-and-bound pruning` | `VERIFIED` |
| `ALG-0553` | **Word Break II (Sentence Generation)** | [word_break_backtracking.cpp](../Recursion%20and%20Backtracking/word_break_backtracking.cpp) | `O(2^N) worst case` | `VERIFIED` |
| `ALG-0554` | **2D Grid Word Search** | [word_search_grid.cpp](../Recursion%20and%20Backtracking/word_search_grid.cpp) | `O(R * C * 3^L) time where L is word length` | `VERIFIED` |

### Sorting and Searching (53 implementations)

| ID | Algorithm | File | Complexity | Status |
| :--- | :--- | :--- | :--- | :---: |
| `ALG-0555` | **Binary Search on Answer (Maximize Minimum Distance)** | [binary_search_answer_max_min.cpp](../Sorting%20and%20Searching/binary_search_answer_max_min.cpp) | `O(N log(max_pos - min_pos)) time` | `VERIFIED` |
| `ALG-0556` | **Binary Search on Answer (Minimize Maximum)** | [binary_search_answer_min_max.cpp](../Sorting%20and%20Searching/binary_search_answer_min_max.cpp) | `O(N log(sum - max)) time` | `VERIFIED` |
| `ALG-0557` | **Bitonic Sort Network** | [bitonic_sort.cpp](../Sorting%20and%20Searching/bitonic_sort.cpp) | `O(N log^2 N) sequential time, O(log^2 N) parallel depth` | `VERIFIED` |
| `ALG-0558` | **Bucket Sort for Uniform Floating-Point Numbers** | [bucket_sort_floating.cpp](../Sorting%20and%20Searching/bucket_sort_floating.cpp) | `O(N) expected time, O(N^2) worst case` | `VERIFIED` |
| `ALG-0559` | **Cocktail Shaker Sort** | [cocktail_shaker_sort.cpp](../Sorting%20and%20Searching/cocktail_shaker_sort.cpp) | `O(N^2) worst case, O(N) best case` | `VERIFIED` |
| `ALG-0560` | **Comb Sort** | [comb_sort.cpp](../Sorting%20and%20Searching/comb_sort.cpp) | `O(N^2) worst case, O(N log N) typical competitive programming performance` | `VERIFIED` |
| `ALG-0561` | **Counting Sort for Signed Integers** | [counting_sort_signed.cpp](../Sorting%20and%20Searching/counting_sort_signed.cpp) | `O(N + K) where K = max_val - min_val + 1` | `VERIFIED` |
| `ALG-0562` | **Cycle Sort** | [cycle_sort.cpp](../Sorting%20and%20Searching/cycle_sort.cpp) | `O(N^2) time with at most N - 1 writes` | `VERIFIED` |
| `ALG-0563` | **Exponential (Galloping) Search** | [exponential_search.cpp](../Sorting%20and%20Searching/exponential_search.cpp) | `O(log i) where i is the target index position` | `VERIFIED` |
| `ALG-0564` | **First and Last Position in Sorted Array** | [find_first_and_last_position.cpp](../Sorting%20and%20Searching/find_first_and_last_position.cpp) | `O(log N) time` | `VERIFIED` |
| `ALG-0565` | **Count Frequency in Sorted Array** | [find_frequency_sorted_array.cpp](../Sorting%20and%20Searching/find_frequency_sorted_array.cpp) | `O(log N) time` | `VERIFIED` |
| `ALG-0566` | **Find Minimum in Rotated Sorted Array** | [find_minimum_rotated_sorted.cpp](../Sorting%20and%20Searching/find_minimum_rotated_sorted.cpp) | `O(log N) time` | `VERIFIED` |
| `ALG-0567` | **Single Element in a Sorted Array** | [find_single_non_duplicate.cpp](../Sorting%20and%20Searching/find_single_non_duplicate.cpp) | `O(log N) time` | `VERIFIED` |
| `ALG-0568` | **Circular Next Greater Character** | [find_smallest_letter_greater_than_target.cpp](../Sorting%20and%20Searching/find_smallest_letter_greater_than_target.cpp) | `O(log N) time` | `VERIFIED` |
| `ALG-0569` | **4-Sum via Pair Sums and Binary Search** | [four_sum_binary_search.cpp](../Sorting%20and%20Searching/four_sum_binary_search.cpp) | `O(N^2 log N) time` | `VERIFIED` |
| `ALG-0570` | **In-Place Heap Sort** | [heap_sort_in_place.cpp](../Sorting%20and%20Searching/heap_sort_in_place.cpp) | `O(N log N) guaranteed time` | `VERIFIED` |
| `ALG-0571` | **Magic Index (A[i] == i) Finder** | [index_equals_value_search.cpp](../Sorting%20and%20Searching/index_equals_value_search.cpp) | `O(log N) for distinct elements` | `VERIFIED` |
| `ALG-0572` | **Interpolation Search** | [interpolation_search.cpp](../Sorting%20and%20Searching/interpolation_search.cpp) | `O(log log N) average, O(N) worst case` | `VERIFIED` |
| `ALG-0573` | **Inversion Counting via Fenwick Tree** | [inversion_count_fenwick.cpp](../Sorting%20and%20Searching/inversion_count_fenwick.cpp) | `O(N log N) time` | `VERIFIED` |
| `ALG-0574` | **K-th Element of Two Sorted Arrays** | [kth_element_of_two_sorted_arrays.cpp](../Sorting%20and%20Searching/kth_element_of_two_sorted_arrays.cpp) | `O(log(min(M, N))) time` | `VERIFIED` |
| `ALG-0575` | **K-th Smallest Absolute Pair Distance** | [kth_smallest_difference_pairs.cpp](../Sorting%20and%20Searching/kth_smallest_difference_pairs.cpp) | `O(N log(max_dist)) time` | `VERIFIED` |
| `ALG-0576` | **Majority Element in Sorted Array** | [majority_element_binary_search.cpp](../Sorting%20and%20Searching/majority_element_binary_search.cpp) | `O(log N) time` | `VERIFIED` |
| `ALG-0577` | **Median of Two Sorted Arrays** | [median_of_two_sorted_arrays.cpp](../Sorting%20and%20Searching/median_of_two_sorted_arrays.cpp) | `O(log(min(M, N))) time` | `VERIFIED` |
| `ALG-0578` | **Median in a Row-Wise Sorted Matrix** | [median_sorted_matrix.cpp](../Sorting%20and%20Searching/median_sorted_matrix.cpp) | `O(32 * R * log C) time` | `VERIFIED` |
| `ALG-0579` | **Merge Sort with Inversion Counting** | [merge_sort_inversions.cpp](../Sorting%20and%20Searching/merge_sort_inversions.cpp) | `O(N log N) time` | `VERIFIED` |
| `ALG-0580` | **Minimize Maximum Distance to Gas Station** | [minimize_max_distance_to_gas_station.cpp](../Sorting%20and%20Searching/minimize_max_distance_to_gas_station.cpp) | `O(N * log(max_gap / eps)) time` | `VERIFIED` |
| `ALG-0581` | **Missing Number in Sorted Arithmetic Progression** | [missing_number_binary_search.cpp](../Sorting%20and%20Searching/missing_number_binary_search.cpp) | `O(log N) time` | `VERIFIED` |
| `ALG-0582` | **Integer N-th Root via Binary Search** | [nth_root_binary_search.cpp](../Sorting%20and%20Searching/nth_root_binary_search.cpp) | `O(N * log X) time` | `VERIFIED` |
| `ALG-0583` | **Pancake Sorting** | [pancake_sorting.cpp](../Sorting%20and%20Searching/pancake_sorting.cpp) | `O(N^2) time with at most 2*N flip operations` | `VERIFIED` |
| `ALG-0584` | **1D Peak Element Finder** | [peak_element_1d.cpp](../Sorting%20and%20Searching/peak_element_1d.cpp) | `O(log N) time` | `VERIFIED` |
| `ALG-0585` | **2D Matrix Peak Finder** | [peak_element_2d.cpp](../Sorting%20and%20Searching/peak_element_2d.cpp) | `O(N log M) time` | `VERIFIED` |
| `ALG-0586` | **Pigeonhole Sort** | [pigeonhole_sort.cpp](../Sorting%20and%20Searching/pigeonhole_sort.cpp) | `O(N + Range) time` | `VERIFIED` |
| `ALG-0587` | **3-Way Quick Sort (Fat Partition)** | [quicksort_3way_dutch_flag.cpp](../Sorting%20and%20Searching/quicksort_3way_dutch_flag.cpp) | `O(N log N) average, O(N) when duplicate elements dominate` | `VERIFIED` |
| `ALG-0588` | **Quick Sort (Hoare Partition)** | [quicksort_hoare.cpp](../Sorting%20and%20Searching/quicksort_hoare.cpp) | `O(N log N) average, O(N^2) worst case` | `VERIFIED` |
| `ALG-0589` | **Quick Sort (Lomuto Partition)** | [quicksort_lomuto.cpp](../Sorting%20and%20Searching/quicksort_lomuto.cpp) | `O(N log N) average, O(N^2) worst case` | `VERIFIED` |
| `ALG-0590` | **Base-256 Radix Sort (32-bit Unsigned)** | [radix_sort_base256.cpp](../Sorting%20and%20Searching/radix_sort_base256.cpp) | `O(4 * (N + 256)) = O(N) time` | `VERIFIED` |
| `ALG-0591` | **Signed 32-bit Radix Sort** | [radix_sort_signed.cpp](../Sorting%20and%20Searching/radix_sort_signed.cpp) | `O(N) time` | `VERIFIED` |
| `ALG-0592` | **Randomized Quickselect** | [randomized_quickselect.cpp](../Sorting%20and%20Searching/randomized_quickselect.cpp) | `O(N) expected time, O(N^2) worst case` | `VERIFIED` |
| `ALG-0593` | **Search 2D Row-Major Sorted Matrix** | [search_2d_matrix_row_major.cpp](../Sorting%20and%20Searching/search_2d_matrix_row_major.cpp) | `O(log(R * C)) time` | `VERIFIED` |
| `ALG-0594` | **Search in 2D Sorted Matrix (Staircase Search)** | [search_2d_matrix_sorted.cpp](../Sorting%20and%20Searching/search_2d_matrix_sorted.cpp) | `O(R + C) time` | `VERIFIED` |
| `ALG-0595` | **Search in K-Nearly Sorted Array** | [search_nearly_sorted_array.cpp](../Sorting%20and%20Searching/search_nearly_sorted_array.cpp) | `O(log N) time` | `VERIFIED` |
| `ALG-0596` | **Search in Rotated Sorted Array (Distinct Elements)** | [search_rotated_sorted_array.cpp](../Sorting%20and%20Searching/search_rotated_sorted_array.cpp) | `O(log N) time` | `VERIFIED` |
| `ALG-0597` | **Search in Rotated Sorted Array with Duplicates** | [search_rotated_sorted_array_duplicates.cpp](../Sorting%20and%20Searching/search_rotated_sorted_array_duplicates.cpp) | `O(log N) average, O(N) worst case` | `VERIFIED` |
| `ALG-0598` | **Shell Sort (Ciura Sequence)** | [shell_sort_ciura.cpp](../Sorting%20and%20Searching/shell_sort_ciura.cpp) | `O(N^(4/3)) empirical time` | `VERIFIED` |
| `ALG-0599` | **K-th Smallest Element in Row-and-Column Sorted Matrix** | [sorted_matrix_kth_smallest.cpp](../Sorting%20and%20Searching/sorted_matrix_kth_smallest.cpp) | `O(N log(max_val - min_val)) time` | `VERIFIED` |
| `ALG-0600` | **Integer and Real Square Root via Binary Search** | [square_root_binary_search.cpp](../Sorting%20and%20Searching/square_root_binary_search.cpp) | `O(log X) integer sqrt, O(iterations) floating-point sqrt` | `VERIFIED` |
| `ALG-0601` | **Stable Selection Sort** | [stable_selection_sort.cpp](../Sorting%20and%20Searching/stable_selection_sort.cpp) | `O(N^2) time` | `VERIFIED` |
| `ALG-0602` | **Stooge Sort** | [stooge_sort.cpp](../Sorting%20and%20Searching/stooge_sort.cpp) | `O(N^(log 3 / log 1.5)) = O(N^2.7095) time` | `VERIFIED` |
| `ALG-0603` | **Strand Sort** | [strand_sort.cpp](../Sorting%20and%20Searching/strand_sort.cpp) | `O(N log N) best case, O(N^2) worst case` | `VERIFIED` |
| `ALG-0604` | **Discrete Ternary Search on Unimodal Array** | [ternary_search_discrete.cpp](../Sorting%20and%20Searching/ternary_search_discrete.cpp) | `O(log N) evaluations` | `VERIFIED` |
| `ALG-0605` | **Ternary Search on Unimodal Real Function** | [ternary_search_unimodal.cpp](../Sorting%20and%20Searching/ternary_search_unimodal.cpp) | `O(log((R - L) / eps)) time (typically ~80 to 100 iterations)` | `VERIFIED` |
| `ALG-0606` | **3-Sum via Binary Search** | [three_sum_binary_search.cpp](../Sorting%20and%20Searching/three_sum_binary_search.cpp) | `O(N^2 log N) time` | `VERIFIED` |
| `ALG-0607` | **Wiggle Sort (Odd-Even Peak Rearrangement)** | [wiggle_sort.cpp](../Sorting%20and%20Searching/wiggle_sort.cpp) | `O(N) time with a single pass` | `VERIFIED` |

### Specialized Data Structures and Advanced Range Queries (36 implementations)

| ID | Algorithm | File | Complexity | Status |
| :--- | :--- | :--- | :--- | :---: |
| `ALG-0608` | **Sqrt Block Decomposition Range Add Range Sum** | [block_decomposition_range_add_range_sum.cpp](../Specialized%20Data%20Structures%20and%20Advanced%20Range%20Queries/block_decomposition_range_add_range_sum.cpp) | `O(sqrt N) update/query` | `VERIFIED` |
| `ALG-0609` | **Sqrt Decomposition Range Mode Query** | [block_decomposition_range_mode.cpp](../Specialized%20Data%20Structures%20and%20Advanced%20Range%20Queries/block_decomposition_range_mode.cpp) | `O(sqrt N) query, O(N sqrt N) build` | `VERIFIED` |
| `ALG-0610` | **Cartesian Tree Offline RMQ via LCA** | [cartesian_tree_rmq_offline.cpp](../Specialized%20Data%20Structures%20and%20Advanced%20Range%20Queries/cartesian_tree_rmq_offline.cpp) | `O(1) query, O(N) build` | `VERIFIED` |
| `ALG-0611` | **CDQ Divide and Conquer (3D Partial Order)** | [cdq_divide_and_conquer_3d_partial_order.cpp](../Specialized%20Data%20Structures%20and%20Advanced%20Range%20Queries/cdq_divide_and_conquer_3d_partial_order.cpp) | `O(N log^2 N)` | `VERIFIED` |
| `ALG-0612` | **CDQ Divide and Conquer Offline Dynamic Connectivity** | [cdq_offline_dynamic_connectivity.cpp](../Specialized%20Data%20Structures%20and%20Advanced%20Range%20Queries/cdq_offline_dynamic_connectivity.cpp) | `O((V + Q) log^2 Q)` | `VERIFIED` |
| `ALG-0613` | **Online Bipartite DSU with Rank and Parity** | [disjoint_set_union_bipartite_online.cpp](../Specialized%20Data%20Structures%20and%20Advanced%20Range%20Queries/disjoint_set_union_bipartite_online.cpp) | `O(alpha(N))` | `VERIFIED` |
| `ALG-0614` | **DSU on Tree (Sack / Small-to-Large)** | [dsu_on_tree_sack_heavy_light.cpp](../Specialized%20Data%20Structures%20and%20Advanced%20Range%20Queries/dsu_on_tree_sack_heavy_light.cpp) | `O(N log N)` | `VERIFIED` |
| `ALG-0615` | **Dynamic Segment Tree with Sparse Allocation** | [dynamic_segment_tree_sparse_alloc.cpp](../Specialized%20Data%20Structures%20and%20Advanced%20Range%20Queries/dynamic_segment_tree_sparse_alloc.cpp) | `O(log C) per query/update` | `VERIFIED` |
| `ALG-0616` | **Fenwick Tree Binary Lifting K-th Element** | [fenwick_tree_binary_lifting_kth.cpp](../Specialized%20Data%20Structures%20and%20Advanced%20Range%20Queries/fenwick_tree_binary_lifting_kth.cpp) | `O(log N)` | `VERIFIED` |
| `ALG-0617` | **Sparse Table Range GCD Query** | [fenwick_tree_range_gcd.cpp](../Specialized%20Data%20Structures%20and%20Advanced%20Range%20Queries/fenwick_tree_range_gcd.cpp) | `O(log(MaxVal)) query, O(N log N) build` | `VERIFIED` |
| `ALG-0618` | **2D Kd-Tree Orthogonal Range Reporting** | [kdtree_2d_orthogonal_range_query.cpp](../Specialized%20Data%20Structures%20and%20Advanced%20Range%20Queries/kdtree_2d_orthogonal_range_query.cpp) | `O(sqrt N + K)` | `VERIFIED` |
| `ALG-0619` | **Mo's Algorithm with Rollback DSU** | [mo_algorithm_rollback_disjoint_set.cpp](../Specialized%20Data%20Structures%20and%20Advanced%20Range%20Queries/mo_algorithm_rollback_disjoint_set.cpp) | `O(Q sqrt(N) log N)` | `VERIFIED` |
| `ALG-0620` | **Mo's Algorithm for Range Distinct Count** | [mo_algorithm_standard.cpp](../Specialized%20Data%20Structures%20and%20Advanced%20Range%20Queries/mo_algorithm_standard.cpp) | `O((N + Q) sqrt(N))` | `VERIFIED` |
| `ALG-0621` | **Mo's Algorithm on Tree Paths** | [mo_algorithm_tree_path.cpp](../Specialized%20Data%20Structures%20and%20Advanced%20Range%20Queries/mo_algorithm_tree_path.cpp) | `O((N + Q) sqrt(N))` | `VERIFIED` |
| `ALG-0622` | **Mo's Algorithm with Hilbert Curve Ordering** | [mo_algorithm_with_hilbert.cpp](../Specialized%20Data%20Structures%20and%20Advanced%20Range%20Queries/mo_algorithm_with_hilbert.cpp) | `O(N * sqrt(Q)) time, O(Q) memory` | `VERIFIED` |
| `ALG-0623` | **3D Mo's Algorithm with Point Updates** | [mo_algorithm_with_updates_3d.cpp](../Specialized%20Data%20Structures%20and%20Advanced%20Range%20Queries/mo_algorithm_with_updates_3d.cpp) | `O(N^(5/3))` | `VERIFIED` |
| `ALG-0624` | **Generic Monoid Segment Tree** | [monoid_segment_tree_framework.cpp](../Specialized%20Data%20Structures%20and%20Advanced%20Range%20Queries/monoid_segment_tree_framework.cpp) | `O(log N) query/update` | `VERIFIED` |
| `ALG-0625` | **Offline Point Add Rectangle Sum via CDQ** | [offline_point_add_rectangle_sum_cdq.cpp](../Specialized%20Data%20Structures%20and%20Advanced%20Range%20Queries/offline_point_add_rectangle_sum_cdq.cpp) | `O(Q log^2 Q)` | `VERIFIED` |
| `ALG-0626` | **Parallel Binary Search** | [parallel_binary_search.cpp](../Specialized%20Data%20Structures%20and%20Advanced%20Range%20Queries/parallel_binary_search.cpp) | `O((N + Q) log T)` | `VERIFIED` |
| `ALG-0627` | **Persistent Array via Fat Nodes** | [persistent_array_fat_node.cpp](../Specialized%20Data%20Structures%20and%20Advanced%20Range%20Queries/persistent_array_fat_node.cpp) | `O(log V) get, O(1) set` | `VERIFIED` |
| `ALG-0628` | **Persistent Array via Binary Tree Path Copying** | [persistent_array_tree_based.cpp](../Specialized%20Data%20Structures%20and%20Advanced%20Range%20Queries/persistent_array_tree_based.cpp) | `O(log N) get and set` | `VERIFIED` |
| `ALG-0629` | **Persistent Segment Tree Range K-th Smallest** | [persistent_segment_tree_kth_range.cpp](../Specialized%20Data%20Structures%20and%20Advanced%20Range%20Queries/persistent_segment_tree_kth_range.cpp) | `O(log N) per query, O(N log N) build` | `VERIFIED` |
| `ALG-0630` | **Persistent Binary Trie Range Max XOR** | [persistent_trie_maximum_xor_range.cpp](../Specialized%20Data%20Structures%20and%20Advanced%20Range%20Queries/persistent_trie_maximum_xor_range.cpp) | `O(30) per query` | `VERIFIED` |
| `ALG-0631` | **Range Affine Range Sum Segment Tree** | [range_affine_range_sum_segment_tree.cpp](../Specialized%20Data%20Structures%20and%20Advanced%20Range%20Queries/range_affine_range_sum_segment_tree.cpp) | `O(log N)` | `VERIFIED` |
| `ALG-0632` | **Range Frequency Query via Position Vectors** | [range_frequency_query_vector.cpp](../Specialized%20Data%20Structures%20and%20Advanced%20Range%20Queries/range_frequency_query_vector.cpp) | `O(log N) query, O(N) build` | `VERIFIED` |
| `ALG-0633` | **Range LIS Query Framework** | [range_lis_query_dp.cpp](../Specialized%20Data%20Structures%20and%20Advanced%20Range%20Queries/range_lis_query_dp.cpp) | `O(N log N)` | `VERIFIED` |
| `ALG-0634` | **Range MEX Query via Persistent Segment Tree** | [range_mex_query_persistent_seg.cpp](../Specialized%20Data%20Structures%20and%20Advanced%20Range%20Queries/range_mex_query_persistent_seg.cpp) | `O(log N)` | `VERIFIED` |
| `ALG-0635` | **Segment Tree Historic Maximum Query** | [segment_tree_beats_historic_max.cpp](../Specialized%20Data%20Structures%20and%20Advanced%20Range%20Queries/segment_tree_beats_historic_max.cpp) | `O(log N)` | `VERIFIED` |
| `ALG-0636` | **Fractional Cascading Range Search** | [segment_tree_fractional_cascading.cpp](../Specialized%20Data%20Structures%20and%20Advanced%20Range%20Queries/segment_tree_fractional_cascading.cpp) | `O(log N + K)` | `VERIFIED` |
| `ALG-0637` | **Sparse Table Range XOR Query** | [sparse_table_disjoint_xor.cpp](../Specialized%20Data%20Structures%20and%20Advanced%20Range%20Queries/sparse_table_disjoint_xor.cpp) | `O(1) query, O(N) build` | `VERIFIED` |
| `ALG-0638` | **Sqrt Decomposition Range Affine Update** | [sqrt_decomposition_range_affine.cpp](../Specialized%20Data%20Structures%20and%20Advanced%20Range%20Queries/sqrt_decomposition_range_affine.cpp) | `O(sqrt N)` | `VERIFIED` |
| `ALG-0639` | **Sqrt Tree for O(1) Range Queries** | [sqrt_tree_constant_query.cpp](../Specialized%20Data%20Structures%20and%20Advanced%20Range%20Queries/sqrt_tree_constant_query.cpp) | `O(1) query, O(N log log N) build` | `VERIFIED` |
| `ALG-0640` | **Persistent Immutable Treap** | [treap_persistent_immutable.cpp](../Specialized%20Data%20Structures%20and%20Advanced%20Range%20Queries/treap_persistent_immutable.cpp) | `O(log N)` | `VERIFIED` |
| `ALG-0641` | **Implicit Treap Range Affine Transformation** | [treap_range_affine_transformation.cpp](../Specialized%20Data%20Structures%20and%20Advanced%20Range%20Queries/treap_range_affine_transformation.cpp) | `O(log N)` | `VERIFIED` |
| `ALG-0642` | **2D Fenwick Tree Range Add and Rectangle Sum** | [two_dimensional_fenwick_range_add.cpp](../Specialized%20Data%20Structures%20and%20Advanced%20Range%20Queries/two_dimensional_fenwick_range_add.cpp) | `O(log R * log C) query/update` | `VERIFIED` |
| `ALG-0643` | **Wavelet Tree Range Quantile Query** | [wavelet_tree_range_quantile.cpp](../Specialized%20Data%20Structures%20and%20Advanced%20Range%20Queries/wavelet_tree_range_quantile.cpp) | `O(log(Alphabet))` | `VERIFIED` |

### Strings and Text Algorithms (30 implementations)

| ID | Algorithm | File | Complexity | Status |
| :--- | :--- | :--- | :--- | :---: |
| `ALG-0644` | **Aho-Corasick Automaton** | [aho_corasick.cpp](../Strings%20and%20Text%20Algorithms/aho_corasick.cpp) | `O(total_pattern_length) construction, O(|text| + matches) search, O(states * ALPHABET) memory` | `VERIFIED` |
| `ALG-0645` | **Aho-Corasick Extended Pattern Automaton** | [aho_corasick_extended_trie.cpp](../Strings%20and%20Text%20Algorithms/aho_corasick_extended_trie.cpp) | `O(Total Pattern Length) build, O(|Text| + Matches) query` | `VERIFIED` |
| `ALG-0646` | **Binary Trie (XOR Trie)** | [binary_trie.cpp](../Strings%20and%20Text%20Algorithms/binary_trie.cpp) | `O(BITS) per operation, O(N * BITS) memory` | `VERIFIED` |
| `ALG-0647` | **Booth's Algorithm (Minimal String Rotation)** | [booth_lexicographically_minimal_rotation.cpp](../Strings%20and%20Text%20Algorithms/booth_lexicographically_minimal_rotation.cpp) | `O(N) time` | `VERIFIED` |
| `ALG-0648` | **Burrows-Wheeler Transform (BWT)** | [burrows_wheeler_transform.cpp](../Strings%20and%20Text%20Algorithms/burrows_wheeler_transform.cpp) | `O(N log N) time` | `VERIFIED` |
| `ALG-0649` | **Duval's Algorithm (Lyndon Factorization)** | [duval_lyndon_factorization.cpp](../Strings%20and%20Text%20Algorithms/duval_lyndon_factorization.cpp) | `O(N) time` | `VERIFIED` |
| `ALG-0650` | **Kasai's LCP Array Construction** | [kasai_lcp_array.cpp](../Strings%20and%20Text%20Algorithms/kasai_lcp_array.cpp) | `O(N) time` | `VERIFIED` |
| `ALG-0651` | **Knuth-Morris-Pratt (All Occurrences)** | [kmp_all_occurrences.cpp](../Strings%20and%20Text%20Algorithms/kmp_all_occurrences.cpp) | `O(N + M) time` | `VERIFIED` |
| `ALG-0652` | **Knuth-Morris-Pratt (KMP) Prefix Function** | [kmp_prefix_function.cpp](../Strings%20and%20Text%20Algorithms/kmp_prefix_function.cpp) | `O(n) prefix table construction, O(n + m) pattern search, O(n) memory` | `VERIFIED` |
| `ALG-0653` | **Longest Common Substring of Two Strings** | [longest_common_substring_two_strings.cpp](../Strings%20and%20Text%20Algorithms/longest_common_substring_two_strings.cpp) | `O((N + M) log(N + M)) time` | `VERIFIED` |
| `ALG-0654` | **Longest Palindromic Subsequence (Reconstruction)** | [longest_palindromic_subsequence_str.cpp](../Strings%20and%20Text%20Algorithms/longest_palindromic_subsequence_str.cpp) | `O(N^2) time` | `VERIFIED` |
| `ALG-0655` | **Longest Repeated Substring** | [longest_repeated_substring.cpp](../Strings%20and%20Text%20Algorithms/longest_repeated_substring.cpp) | `O(N log N) time` | `VERIFIED` |
| `ALG-0656` | **Manacher's Algorithm** | [manacher_palindromes.cpp](../Strings%20and%20Text%20Algorithms/manacher_palindromes.cpp) | `O(n) time, O(n) memory` | `VERIFIED` |
| `ALG-0657` | **Minimal Window Subsequence** | [minimal_window_subsequence.cpp](../Strings%20and%20Text%20Algorithms/minimal_window_subsequence.cpp) | `O(|S| * |T|) time` | `VERIFIED` |
| `ALG-0658` | **Palindromic Tree (EERTREE)** | [palindromic_tree_eertree.cpp](../Strings%20and%20Text%20Algorithms/palindromic_tree_eertree.cpp) | `O(N) total time for string length N` | `VERIFIED` |
| `ALG-0659` | **Rabin-Karp Rolling Hash Pattern Search** | [rabin_karp_rolling_hash.cpp](../Strings%20and%20Text%20Algorithms/rabin_karp_rolling_hash.cpp) | `O(N + M) average time, O(N * M) worst case` | `VERIFIED` |
| `ALG-0660` | **Regular Expression Matching ('.' and '*')** | [regular_expression_matching_dp.cpp](../Strings%20and%20Text%20Algorithms/regular_expression_matching_dp.cpp) | `O(N * M) time` | `VERIFIED` |
| `ALG-0661` | **Run-Length Encoding and Decoding** | [run_length_encoding.cpp](../Strings%20and%20Text%20Algorithms/run_length_encoding.cpp) | `O(N) time` | `VERIFIED` |
| `ALG-0662` | **Double Rolling Polynomial String Hash** | [string_hashing.cpp](../Strings%20and%20Text%20Algorithms/string_hashing.cpp) | `O(n) preprocessing, O(1) per substring hash query, O(n) memory` | `VERIFIED` |
| `ALG-0663` | **Multi-Base String Hashing** | [string_hashing_multi_base.cpp](../Strings%20and%20Text%20Algorithms/string_hashing_multi_base.cpp) | `O(N) preprocessing, O(1) per range hash query` | `VERIFIED` |
| `ALG-0664` | **Suffix Array Construction (O(N log N))** | [suffix_array_n_logn.cpp](../Strings%20and%20Text%20Algorithms/suffix_array_n_logn.cpp) | `O(N log N) time` | `VERIFIED` |
| `ALG-0665` | **Suffix Array Pattern Search** | [suffix_array_pattern_search.cpp](../Strings%20and%20Text%20Algorithms/suffix_array_pattern_search.cpp) | `O(|P| log |S|) time` | `VERIFIED` |
| `ALG-0666` | **Suffix Automaton (SAM)** | [suffix_automaton.cpp](../Strings%20and%20Text%20Algorithms/suffix_automaton.cpp) | `O(n) construction time, O(n * ALPHABET) memory` | `VERIFIED` |
| `ALG-0667` | **Suffix Automaton (Basic State Construction)** | [suffix_automaton_basic.cpp](../Strings%20and%20Text%20Algorithms/suffix_automaton_basic.cpp) | `O(N) time` | `VERIFIED` |
| `ALG-0668` | **Trie (Prefix Tree)** | [trie.cpp](../Strings%20and%20Text%20Algorithms/trie.cpp) | `O(|S|) per insertion/search, O(total_chars * ALPHABET) memory` | `VERIFIED` |
| `ALG-0669` | **Trie with Wildcard Search ('?' and '*')** | [trie_wildcard_search.cpp](../Strings%20and%20Text%20Algorithms/trie_wildcard_search.cpp) | `O(Sigma^K) where K is number of wildcards` | `VERIFIED` |
| `ALG-0670` | **Trie with Dynamic Deletion** | [trie_with_deletion.cpp](../Strings%20and%20Text%20Algorithms/trie_with_deletion.cpp) | `O(|word|) per operation` | `VERIFIED` |
| `ALG-0671` | **Wildcard Matching (Dynamic Programming)** | [wildcard_pattern_matching_dp.cpp](../Strings%20and%20Text%20Algorithms/wildcard_pattern_matching_dp.cpp) | `O(N * M) time` | `VERIFIED` |
| `ALG-0672` | **Z-Algorithm** | [z_algorithm.cpp](../Strings%20and%20Text%20Algorithms/z_algorithm.cpp) | `O(n) linear time, O(n) memory` | `VERIFIED` |
| `ALG-0673` | **Z-Algorithm for Pattern Matching** | [z_algorithm_search.cpp](../Strings%20and%20Text%20Algorithms/z_algorithm_search.cpp) | `O(N + M) time` | `VERIFIED` |

### Templates (4 implementations)

| ID | Algorithm | File | Complexity | Status |
| :--- | :--- | :--- | :--- | :---: |
| `ALG-0674` | **Contest Template** | [contest_template.cpp](../Templates/contest_template.cpp) | `O(1) setup` | `VERIFIED` |
| `ALG-0675` | **Fast I/O with Buffer** | [fast_io.cpp](../Templates/fast_io.cpp) | `O(1) amortized per character/integer` | `VERIFIED` |
| `ALG-0676` | **Modular Integer (Mint)** | [modular_int.cpp](../Templates/modular_int.cpp) | `O(1) for +, -, *, O(log MOD) for division and power` | `VERIFIED` |
| `ALG-0677` | **Stress Testing Framework** | [stress_framework.cpp](../Templates/stress_framework.cpp) | `Dependent on testcase generation and oracle complexity` | `VERIFIED` |

### Trees and Tree Algorithms (55 implementations)

| ID | Algorithm | File | Complexity | Status |
| :--- | :--- | :--- | :--- | :---: |
| `ALG-0678` | **Binary Lifting Lowest Common Ancestor (LCA)** | [binary_lifting_lca.cpp](../Trees%20and%20Tree%20Algorithms/binary_lifting_lca.cpp) | `O(n log n) preprocessing, O(log n) per query, O(n log n) memory` | `VERIFIED` |
| `ALG-0679` | **Centroid Decomposition** | [centroid_decomposition.cpp](../Trees%20and%20Tree%20Algorithms/centroid_decomposition.cpp) | `O(n log n) construction time, O(n) memory, centroid tree height <= log2(n)` | `VERIFIED` |
| `ALG-0680` | **Euler Tour Tree Flattening** | [euler_tour_flattening.cpp](../Trees%20and%20Tree%20Algorithms/euler_tour_flattening.cpp) | `O(n) preprocessing, O(1) subtree query bounds, O(n) memory` | `VERIFIED` |
| `ALG-0681` | **Heavy-Light Decomposition (HLD)** | [heavy_light_decomposition.cpp](../Trees%20and%20Tree%20Algorithms/heavy_light_decomposition.cpp) | `O(n) preprocessing, O(log^2 n) per path operation, O(n) memory` | `VERIFIED` |
| `ALG-0682` | **Link-Cut Tree (Dynamic Tree Path Aggregates)** | [link_cut_tree_path_aggregate.cpp](../Trees%20and%20Tree%20Algorithms/link_cut_tree_path_aggregate.cpp) | `O(log N) amortized per operation` | `VERIFIED` |
| `ALG-0683` | **DSU on Tree (Sack / Small-to-Large Tree Merging)** | [sack_dsu_on_tree.cpp](../Trees%20and%20Tree%20Algorithms/sack_dsu_on_tree.cpp) | `O(n log n) total time, O(n) memory` | `VERIFIED` |
| `ALG-0684` | **All-Pairs Distances Sum via Tree Rerooting** | [tree_all_pairs_distances_sum.cpp](../Trees%20and%20Tree%20Algorithms/tree_all_pairs_distances_sum.cpp) | `O(N)` | `VERIFIED` |
| `ALG-0685` | **Tree Distance via Binary Lifting LCA** | [tree_binary_lifting_lca_distance.cpp](../Trees%20and%20Tree%20Algorithms/tree_binary_lifting_lca_distance.cpp) | `O(N log N) build, O(log N) query` | `VERIFIED` |
| `ALG-0686` | **Binary Tree Subtree Pruning** | [tree_binary_tree_pruning.cpp](../Trees%20and%20Tree%20Algorithms/tree_binary_tree_pruning.cpp) | `O(N)` | `VERIFIED` |
| `ALG-0687` | **Tree Center Identification (1 or 2 Centers)** | [tree_center_two_centers.cpp](../Trees%20and%20Tree%20Algorithms/tree_center_two_centers.cpp) | `O(N)` | `VERIFIED` |
| `ALG-0688` | **Centroid Decomposition Distance-K Pair Count** | [tree_centroid_decomposition_distance_k.cpp](../Trees%20and%20Tree%20Algorithms/tree_centroid_decomposition_distance_k.cpp) | `O(N log N)` | `VERIFIED` |
| `ALG-0689` | **Centroid Tree Decomposition Hierarchy** | [tree_centroid_tree_construction.cpp](../Trees%20and%20Tree%20Algorithms/tree_centroid_tree_construction.cpp) | `O(N log N)` | `VERIFIED` |
| `ALG-0690` | **Check Completeness of Binary Tree** | [tree_check_completeness.cpp](../Trees%20and%20Tree%20Algorithms/tree_check_completeness.cpp) | `O(N)` | `VERIFIED` |
| `ALG-0691` | **Construct Binary Tree from Postorder and Inorder Traversal** | [tree_construct_from_postorder_inorder.cpp](../Trees%20and%20Tree%20Algorithms/tree_construct_from_postorder_inorder.cpp) | `O(N)` | `VERIFIED` |
| `ALG-0692` | **Construct Binary Tree from Preorder and Inorder Traversal** | [tree_construct_from_preorder_inorder.cpp](../Trees%20and%20Tree%20Algorithms/tree_construct_from_preorder_inorder.cpp) | `O(N)` | `VERIFIED` |
| `ALG-0693` | **Count Good Nodes in Binary Tree** | [tree_count_good_nodes.cpp](../Trees%20and%20Tree%20Algorithms/tree_count_good_nodes.cpp) | `O(N)` | `VERIFIED` |
| `ALG-0694` | **Cousins in Binary Tree Verification** | [tree_cousins_in_binary_tree.cpp](../Trees%20and%20Tree%20Algorithms/tree_cousins_in_binary_tree.cpp) | `O(N)` | `VERIFIED` |
| `ALG-0695` | **Tree Diameter and Center** | [tree_diameter_and_center.cpp](../Trees%20and%20Tree%20Algorithms/tree_diameter_and_center.cpp) | `O(n) time, O(n) memory` | `VERIFIED` |
| `ALG-0696` | **Distribute Coins in Binary Tree** | [tree_distribute_coins.cpp](../Trees%20and%20Tree%20Algorithms/tree_distribute_coins.cpp) | `O(N)` | `VERIFIED` |
| `ALG-0697` | **Minimum Dominating Set Exact Extraction** | [tree_dominating_set_exact.cpp](../Trees%20and%20Tree%20Algorithms/tree_dominating_set_exact.cpp) | `O(N)` | `VERIFIED` |
| `ALG-0698` | **Euler Tour Flattening Range XOR** | [tree_euler_tour_range_xor.cpp](../Trees%20and%20Tree%20Algorithms/tree_euler_tour_range_xor.cpp) | `O(N) build, O(1) query` | `VERIFIED` |
| `ALG-0699` | **Flatten Binary Tree to Linked List In-Place** | [tree_flatten_binary_tree_to_linked_list.cpp](../Trees%20and%20Tree%20Algorithms/tree_flatten_binary_tree_to_linked_list.cpp) | `O(N)` | `VERIFIED` |
| `ALG-0700` | **Mo's Algorithm on Trees via Tour Flattening** | [tree_flattening_mo_algorithm.cpp](../Trees%20and%20Tree%20Algorithms/tree_flattening_mo_algorithm.cpp) | `O((N + Q) sqrt(N))` | `VERIFIED` |
| `ALG-0701` | **HLD Edge Weight Point Update and Path Query** | [tree_heavy_light_edge_updates.cpp](../Trees%20and%20Tree%20Algorithms/tree_heavy_light_edge_updates.cpp) | `O(log^2 N) query, O(log N) update` | `VERIFIED` |
| `ALG-0702` | **Heavy-Light Decomposition Subtree Updates** | [tree_heavy_light_subtree_update.cpp](../Trees%20and%20Tree%20Algorithms/tree_heavy_light_subtree_update.cpp) | `O(log N) per subtree update/query` | `VERIFIED` |
| `ALG-0703` | **AHU Rooted Tree Isomorphism Algorithm** | [tree_isomorphism_ahu.cpp](../Trees%20and%20Tree%20Algorithms/tree_isomorphism_ahu.cpp) | `O(N log N)` | `VERIFIED` |
| `ALG-0704` | **Randomized Tree Subtree Polynomial Hashing** | [tree_isomorphism_hashing.cpp](../Trees%20and%20Tree%20Algorithms/tree_isomorphism_hashing.cpp) | `O(N)` | `VERIFIED` |
| `ALG-0705` | **Tree Knapsack with Subtree Size Bounding** | [tree_knapsack_subtree_size_bound.cpp](../Trees%20and%20Tree%20Algorithms/tree_knapsack_subtree_size_bound.cpp) | `O(N * W)` | `VERIFIED` |
| `ALG-0706` | **K-th Ancestor via Binary Lifting** | [tree_kth_ancestor_binary_lifting.cpp](../Trees%20and%20Tree%20Algorithms/tree_kth_ancestor_binary_lifting.cpp) | `O(N log N) precomputation, O(log N) per query` | `VERIFIED` |
| `ALG-0707` | **Tree Jump Pointers Level Ancestor** | [tree_kth_ancestor_jump_pointers.cpp](../Trees%20and%20Tree%20Algorithms/tree_kth_ancestor_jump_pointers.cpp) | `O(N log N) precomputation, O(log N) query` | `VERIFIED` |
| `ALG-0708` | **Lowest Common Ancestor via Euler Tour and RMQ** | [tree_lca_euler_tour_rmq.cpp](../Trees%20and%20Tree%20Algorithms/tree_lca_euler_tour_rmq.cpp) | `O(N log N) precomputation, O(1) per query` | `VERIFIED` |
| `ALG-0709` | **Longest Path in Tree with Value Condition** | [tree_longest_path_with_condition.cpp](../Trees%20and%20Tree%20Algorithms/tree_longest_path_with_condition.cpp) | `O(N)` | `VERIFIED` |
| `ALG-0710` | **Tree LCA via Depth Binary Search** | [tree_lowest_common_ancestor_binary_search.cpp](../Trees%20and%20Tree%20Algorithms/tree_lowest_common_ancestor_binary_search.cpp) | `O(log^2 N)` | `VERIFIED` |
| `ALG-0711` | **Recursive LCA in Binary Tree** | [tree_lowest_common_ancestor_binary_tree.cpp](../Trees%20and%20Tree%20Algorithms/tree_lowest_common_ancestor_binary_tree.cpp) | `O(N)` | `VERIFIED` |
| `ALG-0712` | **Tarjan's Offline LCA Algorithm via DSU** | [tree_lowest_common_ancestor_tarjan_offline.cpp](../Trees%20and%20Tree%20Algorithms/tree_lowest_common_ancestor_tarjan_offline.cpp) | `O((N + Q) * alpha(N))` | `VERIFIED` |
| `ALG-0713` | **Deepest Leaves Sum and Deepest Path** | [tree_maximum_depth_leaf.cpp](../Trees%20and%20Tree%20Algorithms/tree_maximum_depth_leaf.cpp) | `O(N)` | `VERIFIED` |
| `ALG-0714` | **Maximum Independent Set on Tree with Reconstruction** | [tree_maximum_independent_set_reconstruct.cpp](../Trees%20and%20Tree%20Algorithms/tree_maximum_independent_set_reconstruct.cpp) | `O(N)` | `VERIFIED` |
| `ALG-0715` | **Maximum Weight Path Between Any Two Nodes** | [tree_maximum_weight_path_two_nodes.cpp](../Trees%20and%20Tree%20Algorithms/tree_maximum_weight_path_two_nodes.cpp) | `O(N)` | `VERIFIED` |
| `ALG-0716` | **Morris Inorder Traversal (O(1) Extra Space)** | [tree_morris_inorder_traversal.cpp](../Trees%20and%20Tree%20Algorithms/tree_morris_inorder_traversal.cpp) | `O(N)` | `VERIFIED` |
| `ALG-0717` | **Morris Preorder Traversal (O(1) Extra Space)** | [tree_morris_preorder_traversal.cpp](../Trees%20and%20Tree%20Algorithms/tree_morris_preorder_traversal.cpp) | `O(N)` | `VERIFIED` |
| `ALG-0718` | **Number of Tree Paths with Sum K** | [tree_number_of_paths_sum_k.cpp](../Trees%20and%20Tree%20Algorithms/tree_number_of_paths_sum_k.cpp) | `O(N)` | `VERIFIED` |
| `ALG-0719` | **Tree Path Aggregates via Binary Lifting** | [tree_path_aggregates_binary_lifting.cpp](../Trees%20and%20Tree%20Algorithms/tree_path_aggregates_binary_lifting.cpp) | `O(N log N) precomputation, O(log N) per query` | `VERIFIED` |
| `ALG-0720` | **Path Sum III (Downwards Paths Sum to Target)** | [tree_path_sum_iii_all_paths.cpp](../Trees%20and%20Tree%20Algorithms/tree_path_sum_iii_all_paths.cpp) | `O(N)` | `VERIFIED` |
| `ALG-0721` | **Tree Path XOR Query in O(1)** | [tree_path_xor_query.cpp](../Trees%20and%20Tree%20Algorithms/tree_path_xor_query.cpp) | `O(N) precomputation, O(1) query` | `VERIFIED` |
| `ALG-0722` | **Recover BST Two Swapped Nodes (Morris Traversal)** | [tree_recover_bst_two_swapped.cpp](../Trees%20and%20Tree%20Algorithms/tree_recover_bst_two_swapped.cpp) | `O(N)` | `VERIFIED` |
| `ALG-0723` | **Tree Rerooting DP (All Distances Sum)** | [tree_rerooting_dp.cpp](../Trees%20and%20Tree%20Algorithms/tree_rerooting_dp.cpp) | `O(n) total time, O(n) memory` | `VERIFIED` |
| `ALG-0724` | **Farthest Node Distance for All Vertices via Rerooting** | [tree_rerooting_farthest_node.cpp](../Trees%20and%20Tree%20Algorithms/tree_rerooting_farthest_node.cpp) | `O(N)` | `VERIFIED` |
| `ALG-0725` | **Preorder Binary Tree Serialization and Deserialization** | [tree_serialize_deserialize_preorder.cpp](../Trees%20and%20Tree%20Algorithms/tree_serialize_deserialize_preorder.cpp) | `O(N)` | `VERIFIED` |
| `ALG-0726` | **Distinct Values in Subtrees via Small-to-Large Merging** | [tree_subtree_frequencies_small_to_large.cpp](../Trees%20and%20Tree%20Algorithms/tree_subtree_frequencies_small_to_large.cpp) | `O(N log^2 N)` | `VERIFIED` |
| `ALG-0727` | **Subtree Queries and Point Updates via Fenwick Tree** | [tree_subtree_queries_fenwick.cpp](../Trees%20and%20Tree%20Algorithms/tree_subtree_queries_fenwick.cpp) | `O(log N) per query and update` | `VERIFIED` |
| `ALG-0728` | **Subtree Sizes, Depths, and Heights DFS** | [tree_subtree_size_and_depth.cpp](../Trees%20and%20Tree%20Algorithms/tree_subtree_size_and_depth.cpp) | `O(N)` | `VERIFIED` |
| `ALG-0729` | **Sum Root to Leaf Numbers in Binary Tree** | [tree_sum_root_to_leaf_numbers.cpp](../Trees%20and%20Tree%20Algorithms/tree_sum_root_to_leaf_numbers.cpp) | `O(N)` | `VERIFIED` |
| `ALG-0730` | **Minimum Weight Vertex Cover on Trees** | [tree_vertex_cover_min_weight.cpp](../Trees%20and%20Tree%20Algorithms/tree_vertex_cover_min_weight.cpp) | `O(N)` | `VERIFIED` |
| `ALG-0731` | **Vertical Order Traversal of Binary Tree** | [tree_vertical_order_traversal.cpp](../Trees%20and%20Tree%20Algorithms/tree_vertical_order_traversal.cpp) | `O(N log N)` | `VERIFIED` |
| `ALG-0732` | **Virtual (Auxiliary) Tree Construction** | [virtual_tree_auxiliary_tree.cpp](../Trees%20and%20Tree%20Algorithms/virtual_tree_auxiliary_tree.cpp) | `O(K log K)` | `VERIFIED` |

### Two Pointers and Sliding Window (25 implementations)

| ID | Algorithm | File | Complexity | Status |
| :--- | :--- | :--- | :--- | :---: |
| `ALG-0733` | **Backspace String Compare (Two Pointers Reverse)** | [backspace_string_compare.cpp](../Two%20Pointers%20and%20Sliding%20Window/backspace_string_compare.cpp) | `O(N + M) time` | `VERIFIED` |
| `ALG-0734` | **Boats to Save People (Two Pointers Greedy)** | [boats_to_save_people.cpp](../Two%20Pointers%20and%20Sliding%20Window/boats_to_save_people.cpp) | `O(N log N) time` | `VERIFIED` |
| `ALG-0735` | **Container with Most Water** | [container_with_most_water.cpp](../Two%20Pointers%20and%20Sliding%20Window/container_with_most_water.cpp) | `O(N) time` | `VERIFIED` |
| `ALG-0736` | **Find All Anagrams in a String** | [find_all_anagrams_in_string.cpp](../Two%20Pointers%20and%20Sliding%20Window/find_all_anagrams_in_string.cpp) | `O(|S|) time` | `VERIFIED` |
| `ALG-0737` | **4-Sum (Two Pointers)** | [four_sum_two_pointers.cpp](../Two%20Pointers%20and%20Sliding%20Window/four_sum_two_pointers.cpp) | `O(N^3) time` | `VERIFIED` |
| `ALG-0738` | **Fruit Into Baskets (Sliding Window At Most 2 Types)** | [fruit_into_baskets.cpp](../Two%20Pointers%20and%20Sliding%20Window/fruit_into_baskets.cpp) | `O(N) time` | `VERIFIED` |
| `ALG-0739` | **Interval List Intersections** | [interval_list_intersections.cpp](../Two%20Pointers%20and%20Sliding%20Window/interval_list_intersections.cpp) | `O(N + M) time` | `VERIFIED` |
| `ALG-0740` | **Longest Repeating Character Replacement** | [longest_repeating_character_replacement.cpp](../Two%20Pointers%20and%20Sliding%20Window/longest_repeating_character_replacement.cpp) | `O(N) time` | `VERIFIED` |
| `ALG-0741` | **Subarrays with Exactly K Distinct Characters** | [longest_substring_exact_k_distinct.cpp](../Two%20Pointers%20and%20Sliding%20Window/longest_substring_exact_k_distinct.cpp) | `O(N) time` | `VERIFIED` |
| `ALG-0742` | **Longest Substring with At Most K Distinct Characters** | [longest_substring_k_distinct.cpp](../Two%20Pointers%20and%20Sliding%20Window/longest_substring_k_distinct.cpp) | `O(N) time` | `VERIFIED` |
| `ALG-0743` | **Longest Substring Without Repeating Characters** | [longest_substring_without_repeating_characters.cpp](../Two%20Pointers%20and%20Sliding%20Window/longest_substring_without_repeating_characters.cpp) | `O(N) time` | `VERIFIED` |
| `ALG-0744` | **Max Consecutive Ones III (Two Pointers)** | [max_consecutive_ones_iii.cpp](../Two%20Pointers%20and%20Sliding%20Window/max_consecutive_ones_iii.cpp) | `O(N) time` | `VERIFIED` |
| `ALG-0745` | **Minimum Window Substring** | [min_window_substring.cpp](../Two%20Pointers%20and%20Sliding%20Window/min_window_substring.cpp) | `O(|S| + |T|) time` | `VERIFIED` |
| `ALG-0746` | **Minimum Size Subarray Sum** | [minimum_size_subarray_sum.cpp](../Two%20Pointers%20and%20Sliding%20Window/minimum_size_subarray_sum.cpp) | `O(N) time` | `VERIFIED` |
| `ALG-0747` | **Move Zeroes to End** | [move_zeroes.cpp](../Two%20Pointers%20and%20Sliding%20Window/move_zeroes.cpp) | `O(N) time with minimal writes` | `VERIFIED` |
| `ALG-0748` | **Partition Labels** | [partition_labels.cpp](../Two%20Pointers%20and%20Sliding%20Window/partition_labels.cpp) | `O(N) time` | `VERIFIED` |
| `ALG-0749` | **Permutation in String (Sliding Window Frequency Match)** | [permutation_in_string.cpp](../Two%20Pointers%20and%20Sliding%20Window/permutation_in_string.cpp) | `O(|s2|) time` | `VERIFIED` |
| `ALG-0750` | **Remove Duplicates from Sorted Array (In-Place)** | [remove_duplicates_sorted_array.cpp](../Two%20Pointers%20and%20Sliding%20Window/remove_duplicates_sorted_array.cpp) | `O(N) time` | `VERIFIED` |
| `ALG-0751` | **Remove Duplicates from Sorted Array II (At Most Twice)** | [remove_duplicates_sorted_array_ii.cpp](../Two%20Pointers%20and%20Sliding%20Window/remove_duplicates_sorted_array_ii.cpp) | `O(N) time` | `VERIFIED` |
| `ALG-0752` | **Sort Colors (0, 1, 2 In-Place)** | [sort_colors.cpp](../Two%20Pointers%20and%20Sliding%20Window/sort_colors.cpp) | `O(N) time with one pass` | `VERIFIED` |
| `ALG-0753` | **Subarray Product Less Than K** | [subarray_product_less_than_k.cpp](../Two%20Pointers%20and%20Sliding%20Window/subarray_product_less_than_k.cpp) | `O(N) time` | `VERIFIED` |
| `ALG-0754` | **3-Sum Closest** | [three_sum_closest.cpp](../Two%20Pointers%20and%20Sliding%20Window/three_sum_closest.cpp) | `O(N^2) time` | `VERIFIED` |
| `ALG-0755` | **3-Sum (Two Pointers)** | [three_sum_two_pointers.cpp](../Two%20Pointers%20and%20Sliding%20Window/three_sum_two_pointers.cpp) | `O(N^2) time` | `VERIFIED` |
| `ALG-0756` | **Trapping Rainwater (Two Pointers)** | [trapping_rainwater_two_pointers.cpp](../Two%20Pointers%20and%20Sliding%20Window/trapping_rainwater_two_pointers.cpp) | `O(N) time` | `VERIFIED` |
| `ALG-0757` | **Two Sum (Sorted Array Two Pointers)** | [two_sum_sorted.cpp](../Two%20Pointers%20and%20Sliding%20Window/two_sum_sorted.cpp) | `O(N) time` | `VERIFIED` |
