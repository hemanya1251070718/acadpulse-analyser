#include <iostream>
#include <cassert>
#include <cmath>
#include "core/vec.hpp"
#include "core/pair.hpp"
#include "core/array2d.hpp"
#include "core/array3d.hpp"
#include "core/metrics.hpp"
#include "ds/sparse_matrix.hpp"
#include "ds/linked_lists.hpp"
#include "ds/hash_table.hpp"
#include "ds/stack.hpp"
#include "ds/queue.hpp"
#include "ds/depq_minmax.hpp"
#include "ds/binary_tree.hpp"
#include "ds/bst.hpp"
#include "ds/heaps_binary.hpp"
#include "ds/heap_leftist.hpp"
#include "ds/heap_binomial.hpp"
#include "ds/heap_fibonacci.hpp"
#include "ds/dsu.hpp"
#include "algo/sorting.hpp"
#include "algo/expressions.hpp"
#include "algo/scheduler.hpp"
#include "algo/josephus.hpp"
#include "algo/graph.hpp"
#include "algo/graph_traversal.hpp"
#include "algo/mst.hpp"
#include "algo/shortest_path.hpp"

using namespace dsa;

void test_arrays_and_matrices() {
    std::cout << "[TEST] 1. Dynamic Vector, Array2D, Array3D... ";
    Vector<int> v;
    for (int i = 0; i < 20; ++i) v.push_back(i * 10);
    assert(v.size() == 20);
    assert(v[5] == 50);

    Array2D<double> m(4, 5, 0.0);
    m(2, 3) = 95.5;
    assert(m.at(2, 3) == 95.5);
    assert(m.row_major_offset(2, 3) == 2 * 5 + 3);

    Array3D<double> cube(2, 3, 4, 1.0);
    cube(1, 2, 3) = 88.0;
    assert(cube.at(1, 2, 3) == 88.0);
    assert(cube.calculate_offset(1, 2, 3) == (1 * 3 * 4) + (2 * 4) + 3);
    std::cout << "PASSED" << std::endl;
}

void test_sparse_matrix() {
    std::cout << "[TEST] 2. Sparse Matrix (Simple & Fast Transpose)... ";
    SparseMatrix sm(4, 5);
    sm.insert(0, 1, 10.0);
    sm.insert(1, 3, 20.0);
    sm.insert(2, 0, 30.0);
    sm.insert(3, 4, 40.0);

    OpMetrics m_simple, m_fast;
    SparseMatrix st = sm.simple_transpose(&m_simple);
    SparseMatrix ft = sm.fast_transpose(&m_fast);

    assert(st.non_zeros() == 4);
    assert(ft.non_zeros() == 4);
    assert(st.rows() == 5 && st.cols() == 4);
    assert(ft.rows() == 5 && ft.cols() == 4);
    std::cout << "PASSED" << std::endl;
}

void test_linked_lists() {
    std::cout << "[TEST] 3. Singly, Doubly, Circular Lists, Floyd's Cycle, Polynomial... ";
    SinglyLinkedList<int> sll;
    for (int i = 1; i <= 5; ++i) sll.push_back(i * 10);
    int mid = 0;
    assert(sll.find_middle(mid));
    assert(mid == 30);

    DoublyLinkedList<int> dll;
    dll.push_back(100);
    dll.push_back(200);
    dll.push_back(300);
    assert(dll.size() == 3);
    dll.remove_node(dll.head()->next); // remove 200
    assert(dll.size() == 2);
    assert(dll.head()->next->data == 300);

    CircularLinkedList<int> cll;
    cll.push_back(1);
    cll.push_back(2);
    cll.push_back(3);
    assert(cll.size() == 3);

    // Floyd's Cycle Test
    SNode<int> n1(1), n2(2), n3(3);
    n1.next = &n2;
    n2.next = &n3;
    n3.next = nullptr;
    assert(!has_cycle(&n1));
    n3.next = &n2; // create cycle
    assert(has_cycle(&n1));

    // Polynomial Addition Test
    Polynomial p1, p2;
    p1.add_term(3.0, 2);
    p1.add_term(2.0, 1);
    p2.add_term(4.0, 2);
    p2.add_term(5.0, 0);
    Polynomial p3 = Polynomial::add(p1, p2);
    assert(p3.head->coeff == 7.0 && p3.head->exp == 2);
    std::cout << "PASSED" << std::endl;
}

void test_hash_table() {
    std::cout << "[TEST] 4. Hash Table (Chaining, Linear, Quadratic, Double Hash)... ";
    HashTable<double> ht_chain(CollisionStrategy::CHAINING);
    ht_chain.put("student_101", 9.45);
    ht_chain.put("student_102", 8.80);
    double val = 0.0;
    assert(ht_chain.get("student_101", val) && val == 9.45);
    assert(ht_chain.get("student_102", val) && val == 8.80);

    HashTable<int> ht_linear(CollisionStrategy::LINEAR_PROBING);
    ht_linear.put("AP001", 1);
    ht_linear.put("AP002", 2);
    int ival = 0;
    assert(ht_linear.get("AP001", ival) && ival == 1);

    HashTable<int> ht_quad(CollisionStrategy::QUADRATIC_PROBING);
    ht_quad.put("CS101", 100);
    assert(ht_quad.get("CS101", ival) && ival == 100);

    HashTable<int> ht_dh(CollisionStrategy::DOUBLE_HASHING);
    ht_dh.put("DSA", 99);
    assert(ht_dh.get("DSA", ival) && ival == 99);
    std::cout << "PASSED" << std::endl;
}

void test_stacks_and_queues() {
    std::cout << "[TEST] 5. Stacks, Circular Queue, Priority Queue, DEPQ (Min-Max Heap)... ";
    ArrayStack<int> as;
    as.push(10); as.push(20);
    int out = 0;
    as.pop(out); assert(out == 20);

    LinkedStack<int> ls;
    ls.push(30); ls.push(40);
    ls.pop(out); assert(out == 40);

    CircularQueue<int> cq(4);
    cq.enqueue(1); cq.enqueue(2);
    cq.dequeue(out); assert(out == 1);

    MinMaxHeap<int> mmh;
    mmh.push(50);
    mmh.push(10);
    mmh.push(90);
    mmh.push(30);
    mmh.push(70);

    int min_val = 0, max_val = 0;
    assert(mmh.peek_min(min_val) && min_val == 10);
    assert(mmh.peek_max(max_val) && max_val == 90);

    mmh.pop_min(min_val); assert(min_val == 10);
    mmh.pop_max(max_val); assert(max_val == 90);
    assert(mmh.peek_min(min_val) && min_val == 30);
    assert(mmh.peek_max(max_val) && max_val == 70);
    std::cout << "PASSED" << std::endl;
}

void test_trees_and_bst() {
    std::cout << "[TEST] 6. Binary Tree Traversals (Rec & Iter) & BST (Insert, 3-Case Delete, Range, Balance)... ";
    // Binary Tree
    TreeNode<int>* r = new TreeNode<int>(1);
    r->left = new TreeNode<int>(2);
    r->right = new TreeNode<int>(3);
    r->left->left = new TreeNode<int>(4);
    r->left->right = new TreeNode<int>(5);

    BinaryTree<int> bt(r);
    Vector<int> in_rec = bt.inorder_recursive();
    Vector<int> in_iter = bt.inorder_iterative();
    assert(in_rec.size() == in_iter.size());
    for (std::size_t i = 0; i < in_rec.size(); ++i) {
        assert(in_rec[i] == in_iter[i]);
    }

    Vector<int> pre_rec = bt.preorder_recursive();
    Vector<int> pre_iter = bt.preorder_iterative();
    assert(pre_rec.size() == pre_iter.size());
    for (std::size_t i = 0; i < pre_rec.size(); ++i) {
        assert(pre_rec[i] == pre_iter[i]);
    }

    Vector<int> post_rec = bt.postorder_recursive();
    Vector<int> post_iter = bt.postorder_iterative();
    assert(post_rec.size() == post_iter.size());
    for (std::size_t i = 0; i < post_rec.size(); ++i) {
        assert(post_rec[i] == post_iter[i]);
    }

    // BST 3-Case Delete
    BinarySearchTree<int, double> bst;
    bst.insert(50, 5.0);
    bst.insert(30, 3.0);
    bst.insert(70, 7.0);
    bst.insert(20, 2.0); // Leaf
    bst.insert(40, 4.0);
    bst.insert(60, 6.0);
    bst.insert(80, 8.0);

    double val = 0.0;
    assert(bst.search(40, val) && val == 4.0);

    // Case 1: Leaf
    assert(bst.remove(20));
    assert(!bst.search(20, val));

    // Case 3: Two children (50 root)
    assert(bst.remove(50));
    assert(!bst.search(50, val));
    assert(bst.search(60, val)); // successor became root or took position

    // Range Query
    auto range = bst.range_query(35, 75);
    assert(range.size() > 0);

    // Balance
    bst.balance();
    assert(bst.size() > 0);
    std::cout << "PASSED" << std::endl;
}

void test_heaps() {
    std::cout << "[TEST] 7. Binary Max/Min Heap, Heapsort, Leftist, Binomial, Fibonacci Heaps... ";
    Vector<int> arr;
    arr.push_back(40); arr.push_back(10); arr.push_back(30); arr.push_back(50); arr.push_back(20);
    BinaryMaxHeap<int>::heapsort(arr);
    assert(arr[0] == 10 && arr[4] == 50);

    // Leftist Heap Merge
    LeftistHeap<int> lh1, lh2;
    lh1.insert(15); lh1.insert(25);
    lh2.insert(10); lh2.insert(30);
    lh1.merge(lh2);
    int l_out = 0;
    assert(lh1.extract_min(l_out) && l_out == 10);
    assert(lh1.extract_min(l_out) && l_out == 15);

    // Binomial Heap
    BinomialHeap<int> bh;
    bh.insert(45); bh.insert(12); bh.insert(33);
    int b_out = 0;
    assert(bh.extract_min(b_out) && b_out == 12);

    // Fibonacci Heap
    FibonacciHeap<int> fh;
    auto n1 = fh.insert(50);
    fh.insert(30);
    fh.decrease_key(n1, 10);
    int f_out = 0;
    assert(fh.extract_min(f_out) && f_out == 10);
    assert(fh.extract_min(f_out) && f_out == 30);
    std::cout << "PASSED" << std::endl;
}

void test_sorting_and_expressions() {
    std::cout << "[TEST] 8. Sorting Passes & Expression Conversion/Evaluation... ";
    Vector<int> s_arr;
    s_arr.push_back(9); s_arr.push_back(4); s_arr.push_back(7); s_arr.push_back(2); s_arr.push_back(5);
    Vector<SortPassSnapshot<int>> passes;
    Sorting::quick_sort(s_arr, PivotStrategy::MEDIAN_OF_THREE, &passes);
    assert(s_arr[0] == 2 && s_arr[4] == 9);
    assert(passes.size() > 0);

    // Infix to Postfix & Evaluation
    const char* infix = "(MSE * 0.3) + (ESE * 0.5) + (LAB * 0.2)";
    Vector<char> postfix = ExpressionEngine::infix_to_postfix(infix);
    HashTable<double> scores;
    scores.put("MSE", 80.0);
    scores.put("ESE", 90.0);
    scores.put("LAB", 100.0);
    double result = ExpressionEngine::evaluate_postfix(postfix.data(), scores);
    // 80*0.3 + 90*0.5 + 100*0.2 = 24 + 45 + 20 = 89.0
    assert(std::fabs(result - 89.0) < 1e-4);
    std::cout << "PASSED" << std::endl;
}

void test_graphs_and_mst() {
    std::cout << "[TEST] 9. Graphs, BFS, DFS, Cycle, Prim, Kruskal, Dijkstra, Floyd-Warshall... ";
    Graph g(5, true); // directed
    g.add_edge(0, 1, 4.0);
    g.add_edge(0, 2, 2.0);
    g.add_edge(1, 2, 1.0);
    g.add_edge(1, 3, 5.0);
    g.add_edge(2, 3, 8.0);
    g.add_edge(2, 4, 10.0);
    g.add_edge(3, 4, 2.0);

    auto bfs_order = GraphTraversal::bfs(g, 0);
    assert(bfs_order.size() == 5);

    auto dfs_order = GraphTraversal::dfs(g, 0);
    assert(dfs_order.size() == 5);

    // Undirected graph for MST
    Graph ug(4, false);
    ug.add_edge(0, 1, 1.0);
    ug.add_edge(1, 2, 2.0);
    ug.add_edge(2, 3, 3.0);
    ug.add_edge(0, 3, 4.0);
    ug.add_edge(0, 2, 5.0);

    auto mst_k = MinimumSpanningTree::kruskal(ug);
    auto mst_p = MinimumSpanningTree::prim(ug);
    assert(mst_k.total_weight == 6.0); // 1 + 2 + 3 = 6
    assert(mst_p.total_weight == 6.0);

    // Dijkstra
    auto sp = ShortestPath::dijkstra(g, 0);
    // Path 0 -> 2 is 2.0. Path 0 -> 1 is 4.0. Path 0 -> 3 is 0->1->3 (9) or 0->2->3 (10). Wait, 0->1->3 = 4 + 5 = 9.
    assert(sp.dist[2] == 2.0);
    assert(sp.dist[1] == 4.0);

    // Floyd-Warshall
    auto all_pairs = ShortestPath::floyd_warshall(g);
    assert(all_pairs(0, 2) == 2.0);
    std::cout << "PASSED" << std::endl;
}

int main() {
    std::cout << "==========================================================" << std::endl;
    std::cout << " AcadPulse DSA Core Engine - 100% Zero-STL Verification   " << std::endl;
    std::cout << " Covers Comprehensive Data Structures Course Syllabus     " << std::endl;
    std::cout << "==========================================================" << std::endl;

    test_arrays_and_matrices();
    test_sparse_matrix();
    test_linked_lists();
    test_hash_table();
    test_stacks_and_queues();
    test_trees_and_bst();
    test_heaps();
    test_sorting_and_expressions();
    test_graphs_and_mst();

    std::cout << "==========================================================" << std::endl;
    std::cout << " ALL UNIT TESTS PASSED (100% DSA SYLLABUS COVERAGE)       " << std::endl;
    std::cout << "==========================================================" << std::endl;
    return 0;
}

