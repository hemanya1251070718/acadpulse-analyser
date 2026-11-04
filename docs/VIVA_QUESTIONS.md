# AcadPulse — Data Structures Viva & External Evaluation Guide

### Subject: Data Structures Curriculum
### Project: Student Ranking & Academic Performance Analyser

---

### Q1: What was the primary motivation for using custom Zero-STL Data Structures in this project?
**Answer:** The standard template library (STL) hides low-level memory allocations, pointer mutations, and amortized growth mechanics. To demonstrate deep algorithmic mastery for university evaluation, all 40 syllabus topics are implemented with raw pointers, explicit destructor recursion, custom dynamic memory doubling, and custom templates without `#include <vector>`, `<list>`, `<stack>`, or `<queue>`.

---

### Q2: Why is Fast Transpose preferred over Simple Transpose for the Student Elective Matrix?
**Answer:** 
- **Simple Transpose** scans the entire triplet array of size $NZ$ for every column $c \in [0, \text{Cols}-1]$. Its time complexity is $O(\text{Cols} \times NZ)$, which degrades to $O(C^2 \times R)$ when dense.
- **Fast Transpose** uses two auxiliary arrays: `total[col]` to count frequencies in $O(NZ)$ and `index[col]` to compute prefix start positions in $O(\text{Cols})$. It then places each non-zero element directly into its transposed destination in one pass $O(NZ)$. Total time is $O(\text{Cols} + NZ)$ with $O(\text{Cols})$ space.

---

### Q3: Explain how the Double-Ended Priority Queue (DEPQ) works and why it is used here.
**Answer:** 
A Min-Max Heap is a complete binary tree where levels alternate between Min-levels (even depth) and Max-levels (odd depth).
- The root at level 0 holds the minimum value (lowest scoring / at-risk student).
- Level 1 holds the maximum value (topper / gold medalist).
- Both `peek_min()` and `peek_max()` are strictly **$O(1)$**, while `pop_min()` and `pop_max()` are **$O(\log N)$**. This allows our academic analyser to instantly identify both toppers and at-risk students simultaneously without full array sorting.

---

### Q4: How does the Shunting Yard Stack Engine evaluate custom grading criteria?
**Answer:** 
When an administrator inputs a formula like `(MSE * 0.3) + (ESE * 0.5) + (LAB * 0.2)`:
1. **Infix-to-Postfix (Shunting Yard)**: An operator stack processes tokens based on precedence (`*`, `/` > `+`, `-`). Parentheses force sub-expressions to be cleared. An output string contains Reverse Polish Notation (RPN).
2. **Postfix Evaluation**: A double operand stack pushes values. When an operator is encountered, the top two operands are popped, evaluated, and the result is pushed back. Variables (`MSE`, `ESE`, `LAB`) are looked up in $O(1)$ average time using our custom Hash Table.

---

### Q5: What is the 3-Case Deletion in Binary Search Trees (BST)?
**Answer:**
1. **Node is a Leaf (0 Children)**: Simply delete the node and set the parent pointer to `nullptr`.
2. **Node has 1 Child**: Replace the node with its non-null child and free the target node.
3. **Node has 2 Children**: Find the node's **In-Order Successor** (smallest element in its right subtree). Copy the successor's key and value into the target node, then recursively delete the successor from the right subtree (which is guaranteed to have at most 1 child).

---

### Q6: How does Floyd's Cycle Detection work in student prerequisite chains?
**Answer:**
It uses two pointers moving at different speeds: the **slow pointer (Tortoise)** advances 1 node per iteration, while the **fast pointer (Hare)** advances 2 nodes per iteration. If a cycle exists, the distance between them decreases by 1 in each step of the cycle, guaranteeing they will meet in $O(N)$ time with **$O(1)$ auxiliary space**, preventing infinite traversal loops.

---

### Q7: Why use Leftist and Binomial Heaps over simple Binary Heaps for multi-division grading?
**Answer:**
Merging two binary heaps takes $O(N)$ time. In contrast:
- A **Leftist Heap** maintains the leftist property ($npl(\text{left}) \ge npl(\text{right})$), allowing two heaps from Division A and Division B to be merged in **$O(\log N)$** time by merging down the right spine.
- A **Binomial Heap** represents data as a forest of binomial trees, allowing union operations in **$O(\log N)$** time similar to binary addition with carries.

---

### Q8: How does Kruskal's Algorithm use Disjoint Set Union (DSU) to build the Mentoring MST?
**Answer:**
Kruskal's algorithm sorts all graph edges by weight in $O(E \log E)$. It iterates through edges and uses **DSU**:
- `find(u)` uses **Path Compression** to flatten the tree in amortized $O(\alpha(V))$ time.
- `unite(u, v)` uses **Union by Rank** to attach the shorter tree under the taller tree.
- If `find(u) == find(v)`, the edge forms a cycle and is discarded; otherwise, it is added to the MST until $V-1$ edges are selected.

---

### Q9: How is the C++ engine connected to the Flask Web Application?
**Answer:**
The Flask application calls the compiled C++ executable (`engine_api.exe`) via high-speed CLI subprocess communication, passing command parameters and receiving deterministic JSON strings. It also includes an identical pure-DSA Python service fallback for cross-platform portability.

---

### Q10: How is this application containerized and served for production evaluation?
**Answer:**
1. Containerized with Docker via a multi-stage `Dockerfile` that compiles the C++17 engine using `g++` and installs Flask/Gunicorn.
2. Serves HTTP traffic through WSGI workers on port `8080` (or `5000` locally).
3. The zero-dependency container guarantees reproducible compilation and execution regardless of host OS.

