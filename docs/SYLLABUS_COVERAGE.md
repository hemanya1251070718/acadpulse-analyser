# AcadPulse — Complete 40/40 DSA Syllabus Coverage Guide

### Course: Advanced Data Structures Curriculum
### Topic: Student Ranking and Academic Performance Analyser
### Implementation: High-Performance Native Algorithmic Core Engine + Flask Web Interface

---

## Complete Syllabus Topic Matrix

| # | Syllabus Unit & Topic | Core Implementation File | Time Complexity | Space Complexity | Practical Project Role |
|---|---|---|---|---|---|
| **01** | Unit 1: Asymptotic Notations & Big-O | `engine/include/core/metrics.hpp` | O(1) op | O(1) | Real-time comparison, swap, and recursion depth tracking |
| **02** | Unit 1: Dynamic Arrays & Geometric Doubling | `engine/include/core/vec.hpp` | Amortized O(1) push | O(N) | Dynamic student ledger buffer with factor-2 reallocation |
| **03** | Unit 1: 2D Arrays & Row-Major Mapping | `engine/include/core/array2d.hpp` | O(1) index | O(R &times; C) | `Index(r,c) = r*C + c` gradebook assessment matrix |
| **04** | Unit 1: 3D Arrays & Multi-Depth Tensors | `engine/include/core/array3d.hpp` | O(1) index | O(D &times; R &times; C) | `Index(d,r,c) = d*R*C + r*C + c` Semester &times; Course &times; Assessment |
| **05** | Unit 1: Sparse Matrix Simple Transpose | `engine/include/ds/sparse_matrix.hpp` | O(Cols &times; Nonzeros) | O(Nonzeros) | Student Elective Registration 3-tuple transpose |
| **06** | Unit 1: Sparse Matrix Fast Transpose | `engine/include/ds/sparse_matrix.hpp` | O(Cols + Nonzeros) | O(Cols) aux | Frequency array `total[]` & index placement in O(C + NZ) |
| **07** | Unit 1: Merge Sort & Divide-and-Conquer | `engine/include/algo/sorting.hpp` | O(N log N) | O(N) aux | Stable student merit ranking with step-by-step pass logs |
| **08** | Unit 1: Quick Sort (3 Pivot Strategies) | `engine/include/algo/sorting.hpp` | O(N log N) avg | O(log N) stack | High-speed ranking with Median-of-3 pivot selection |
| **09** | Unit 1: Insertion Sort | `engine/include/algo/sorting.hpp` | O(N&sup2;) worst, O(N) best | O(1) | Small batch student grade updates |
| **10** | Unit 2: Pointers & Dynamic Memory Alloc | `engine/include/ds/linked_lists.hpp` | O(1) op | O(N) | Raw pointer heap allocation (`new`/`delete`) with zero STL |
| **11** | Unit 2: Fast & Slow Pointer Technique | `engine/include/ds/linked_lists.hpp` | O(N) single-pass | O(1) | Median-scoring student identification via Tortoise & Hare |
| **12** | Unit 2: Singly Linked Lists | `engine/include/ds/linked_lists.hpp` | O(1) push, O(N) search | O(N) | Dynamic student enrollment linked list |
| **13** | Unit 2: Doubly Linked Lists & Fast Removal | `engine/include/ds/linked_lists.hpp` | O(1) delete with ptr | O(N) | Bidirectional rank ledger with O(1) node unlinking |
| **14** | Unit 2: Circular Linked Lists | `engine/include/ds/linked_lists.hpp` | O(1) advance | O(N) | Round-robin oral viva examiner scheduling |
| **15** | Unit 2: Floyd's Cycle Detection | `engine/include/ds/linked_lists.hpp` | O(N) time | O(1) space | Route validation to prevent student reference loops |
| **16** | Unit 2: Polynomial Arithmetic via Lists | `engine/include/ds/linked_lists.hpp` | O(N + M) add | O(N + M) | Multi-factor student performance decay curves |
| **17** | Unit 2: Hash Tables (djb2 Hash Function) | `engine/include/ds/hash_table.hpp` | O(1) avg lookup | O(Capacity) | O(1) instant student lookup by PRN registration key |
| **18** | Unit 2: Collision Strategy: Chaining | `engine/include/ds/hash_table.hpp` | O(1) avg | O(N) | Linked-list backed bucket collision resolution |
| **19** | Unit 2: Collision Strategy: Linear Probing | `engine/include/ds/hash_table.hpp` | O(1) avg, O(N) worst | O(Capacity) | Open addressing with linear offset `(h + i) % M` |
| **20** | Unit 2: Collision Strategy: Quadratic Probing | `engine/include/ds/hash_table.hpp` | O(1) avg | O(Capacity) | Eliminates primary clustering via `(h + i&sup2;) % M` |
| **21** | Unit 2: Collision Strategy: Double Hashing | `engine/include/ds/hash_table.hpp` | O(1) avg | O(Capacity) | Uniform distribution via secondary hash step `(h1 + i*h2) % M` |
| **22** | Unit 3: Stack ADT (Array & Linked List) | `engine/include/ds/stack.hpp` | O(1) push/pop | O(N) | Assessment marks Undo/Redo historical stack |
| **23** | Unit 3: Infix to Postfix Conversion | `engine/include/algo/expressions.hpp` | O(N) | O(N) stack | Shunting-Yard parser for custom grading criteria formulas |
| **24** | Unit 3: Postfix Expression Evaluation | `engine/include/algo/expressions.hpp` | O(N) | O(N) stack | Dynamic calculation of composite scores: `(MSE*0.3)+(ESE*0.5)` |
| **25** | Unit 3: Queue ADT (Circular Array & Linked) | `engine/include/ds/queue.hpp` | O(1) enq/deq | O(N) | FIFO grade verification and marks re-evaluation buffer |
| **26** | Unit 3: Priority Queue | `engine/include/ds/queue.hpp` | O(log N) push/pop | O(N) | Urgent grievance re-evaluation requests queue |
| **27** | Unit 3: DEPQ (Min-Max Heap) | `engine/include/ds/depq_minmax.hpp` | O(1) peek, O(log N) del | O(N) | Instant simultaneous lookup of Toppers and At-Risk students |
| **28** | Unit 3: CPU Job Scheduling (4 Algorithms) | `engine/include/algo/scheduler.hpp` | O(N log N) | O(N) | FCFS, SJF, Priority, and Round-Robin viva/exam batching |
| **29** | Unit 3: Josephus Problem (Simulation & Math)| `engine/include/algo/josephus.hpp` | O(N) math, O(NK) list | O(1) / O(N) | Scholarship elimination protocol & lottery candidate selection |
| **30** | Unit 4: Binary Tree Hierarchy | `engine/include/ds/binary_tree.hpp` | O(N) build | O(N) | Institutional academic hierarchy (Institute &rarr; Dept &rarr; Div &rarr; Batch) |
| **31** | Unit 4: Array Representation of Tree | `engine/include/ds/binary_tree.hpp` | O(1) child/parent | O(2^H) | Array-backed complete binary tree storage |
| **32** | Unit 4: Recursive & Iterative Traversals | `engine/include/ds/binary_tree.hpp` | O(N) | O(H) stack | Inorder, Preorder, Postorder & Level-Order traversals |
| **33** | Unit 4: BST Search, Insert & 3-Case Delete | `engine/include/ds/bst.hpp` | O(log N) avg | O(N) | Leaf, single-child, two-child (inorder successor) deletion |
| **34** | Unit 4: BST Range Query & Balancing | `engine/include/ds/bst.hpp` | O(log N + K) | O(N) | SGPA interval queries `[min_sgpa, max_sgpa]` & DSW rebalance |
| **35** | Unit 5: Binary Max Heap & Min Heap | `engine/include/ds/heaps_binary.hpp` | O(log N) push/pop | O(N) | Top-K merit extraction and remedial candidate monitoring |
| **36** | Unit 5: In-Place Heapsort | `engine/include/ds/heaps_binary.hpp` | O(N log N) | O(1) aux | In-place linear heapify + sift-down ranking |
| **37** | Unit 5: Leftist Heap | `engine/include/ds/heap_leftist.hpp` | O(log N) merge | O(N) | Multi-division merit queue merging via Null Path Length |
| **38** | Unit 5: Binomial Heap | `engine/include/ds/heap_binomial.hpp` | O(log N) union | O(N) | Cross-department merit collation via binomial trees |
| **39** | Unit 5: Fibonacci Heap | `engine/include/ds/heap_fibonacci.hpp` | Amortized O(1) dec-key | O(N) | Real-time grade decrement & Dijkstra's algorithm acceleration |
| **40** | Unit 6: Graphs (Matrix & List) & Traversals | `engine/include/algo/graph.hpp`, `graph_traversal.hpp` | O(V + E) | O(V) | Course Prerequisite DAG, BFS, DFS, and 3-color Cycle Detection |
| **41** | Unit 6: Minimum Spanning Tree (Prim & Kruskal)| `engine/include/algo/mst.hpp`, `dsu.hpp` | O(E log V) | O(V + E) | Peer mentoring minimum-overhead student support backbone |
| **42** | Unit 6: Shortest Path (Dijkstra & Floyd-Warshall)| `engine/include/algo/shortest_path.hpp` | O((V+E) log V) & O(V&sup3;) | O(V&sup2;) | Optimal remedial credit pathways & all-pairs distance matrix |

---

## Zero-STL Verification
Every single data structure is built completely from scratch without `<vector>`, `<list>`, `<map>`, `<set>`, `<queue>`, `<stack>`, or `<algorithm>`. Passes strict GCC 16.1 `-Wall -Wextra` validation.

