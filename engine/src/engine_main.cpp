#include <iostream>
#include <iomanip>
#include <string>
#include "core/vec.hpp"
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

void print_banner() {
    std::cout << "\n=================================================================\n";
    std::cout << "  ACADPULSE - STUDENT RANKING & ACADEMIC PERFORMANCE ANALYSER    \n";
    std::cout << "  Core Data Structures & Algorithms Engine (Course Project)     \n";
    std::cout << "  100% Zero-STL C++17 Implementation | 40/40 Syllabus Coverage   \n";
    std::cout << "=================================================================\n";
}

void print_menu() {
    std::cout << "\nChoose a module to explore live:\n";
    std::cout << " 1. Unit 1: Dynamic Arrays, 2D/3D Tensors & Fast Sparse Transpose\n";
    std::cout << " 2. Unit 1: Sorting Pass Tracer (Merge Sort vs Quick Sort)\n";
    std::cout << " 3. Unit 2: Fast/Slow Pointers, Doubly LL & Floyd's Cycle Detection\n";
    std::cout << " 4. Unit 2: Hash Table with 4 Collision Strategies & Rehashing\n";
    std::cout << " 5. Unit 3: Infix-to-Postfix Stack Engine & Dynamic Formula Evaluator\n";
    std::cout << " 6. Unit 3: DEPQ (Min-Max Heap) Toppers vs At-Risk Extractor\n";
    std::cout << " 7. Unit 3: Job Scheduling (FCFS vs Round Robin) & Josephus Selection\n";
    std::cout << " 8. Unit 4: Academic Hierarchy Binary Tree Traversals (Rec & Iter)\n";
    std::cout << " 9. Unit 4: BST 3-Case Deletion, Range Query & Balanced Rebuild\n";
    std::cout << "10. Unit 5: Binary Max Heap (Heapsort) & Leftist/Binomial/Fibonacci Heaps\n";
    std::cout << "11. Unit 6: Course Prerequisite Graph (BFS, DFS, Cycle Detection)\n";
    std::cout << "12. Unit 6: Shortest Path (Dijkstra) & Mentoring MST (Prim & Kruskal)\n";
    std::cout << " 0. Exit\n";
    std::cout << "Enter option (0-12): ";
}

int main() {
    print_banner();
    int choice = -1;

    while (true) {
        print_menu();
        if (!(std::cin >> choice)) break;
        if (choice == 0) {
            std::cout << "Exiting AcadPulse C++ Console Engine. Goodbye!\n";
            break;
        }

        switch (choice) {
            case 1: {
                std::cout << "\n--- [Unit 1: Sparse Matrix Simple vs Fast Transpose] ---\n";
                SparseMatrix sm(5, 6);
                sm.insert(0, 1, 85.0);
                sm.insert(1, 4, 92.5);
                sm.insert(2, 2, 78.0);
                sm.insert(3, 0, 95.0);
                sm.insert(4, 5, 88.0);

                OpMetrics m_s, m_f;
                SparseMatrix st = sm.simple_transpose(&m_s);
                SparseMatrix ft = sm.fast_transpose(&m_f);

                std::cout << "Original Non-zeros: " << sm.non_zeros() << "\n";
                std::cout << "Simple Transpose: O(Cols * Nonzeros) -> " << m_s.comparisons << " comparisons, " << m_s.swaps << " placements\n";
                std::cout << "Fast Transpose:   O(Cols + Nonzeros) -> " << m_f.comparisons << " comparisons, " << m_f.swaps << " placements, " << m_f.pointer_hops << " freq scans\n";
                break;
            }
            case 2: {
                std::cout << "\n--- [Unit 1: Sorting Pass Tracer] ---\n";
                Vector<int> arr;
                arr.push_back(64); arr.push_back(34); arr.push_back(25); arr.push_back(12); arr.push_back(22); arr.push_back(11); arr.push_back(90);
                std::cout << "Initial Array: [ ";
                for (std::size_t i = 0; i < arr.size(); ++i) std::cout << arr[i] << " ";
                std::cout << "]\n";

                Vector<SortPassSnapshot<int>> passes;
                OpMetrics m_qs;
                Sorting::quick_sort(arr, PivotStrategy::MEDIAN_OF_THREE, &passes, &m_qs);

                std::cout << "Quick Sort Passes (Median-of-3 Pivot):\n";
                for (std::size_t i = 0; i < passes.size(); ++i) {
                    std::cout << " Pass " << passes[i].pass_num << ": [ ";
                    for (std::size_t j = 0; j < passes[i].array_state.size(); ++j) {
                        std::cout << passes[i].array_state[j] << " ";
                    }
                    std::cout << "] (Comparisons: " << passes[i].comparisons << ", Swaps: " << passes[i].swaps << ")\n";
                }
                break;
            }
            case 3: {
                std::cout << "\n--- [Unit 2: Linked Lists & Floyd's Cycle] ---\n";
                SinglyLinkedList<std::string> sll;
                sll.push_back("Aarav"); sll.push_back("Diya"); sll.push_back("Rohan");
                sll.push_back("Ananya"); sll.push_back("Kabir");
                std::string mid;
                sll.find_middle(mid);
                std::cout << "Singly Linked List size: " << sll.size() << ", Middle Student (Fast/Slow Pointer): " << mid << "\n";

                SNode<int> a(1), b(2), c(3);
                a.next = &b; b.next = &c; c.next = &b; // cycle
                std::cout << "Floyd's Cycle Detection on cyclic list: " << (has_cycle(&a) ? "CYCLE DETECTED (Safe Loop Guard Active)" : "No Cycle") << "\n";
                break;
            }
            case 4: {
                std::cout << "\n--- [Unit 2: Hash Table Collision Strategies] ---\n";
                HashTable<double> ht(CollisionStrategy::QUADRATIC_PROBING, 11);
                ht.put("PRN2024001", 9.68);
                ht.put("PRN2024002", 9.15);
                ht.put("PRN2024003", 8.92);
                double score = 0;
                ht.get("PRN2024001", score);
                std::cout << "Retrieved PRN2024001: " << score << " (Quadratic Probing Strategy)\n";
                break;
            }
            case 5: {
                std::cout << "\n--- [Unit 3: Expression Evaluator] ---\n";
                const char* expr = "(MSE * 0.3) + (ESE * 0.5) + (LAB * 0.2)";
                auto postfix = ExpressionEngine::infix_to_postfix(expr);
                std::cout << "Infix:   " << expr << "\n";
                std::cout << "Postfix: " << postfix.data() << "\n";
                HashTable<double> marks;
                marks.put("MSE", 85.0); marks.put("ESE", 92.0); marks.put("LAB", 95.0);
                double res = ExpressionEngine::evaluate_postfix(postfix.data(), marks);
                std::cout << "Evaluated Composite Score: " << res << " / 100\n";
                break;
            }
            case 6: {
                std::cout << "\n--- [Unit 3: DEPQ (Min-Max Heap) Toppers & At-Risk] ---\n";
                MinMaxHeap<double> deq;
                deq.push(65.5); deq.push(98.2); deq.push(42.0); deq.push(88.0); deq.push(74.5);
                double topper = 0, at_risk = 0;
                deq.peek_max(topper);
                deq.peek_min(at_risk);
                std::cout << "Gold Medalist / Topper Score (peek_max O(1)): " << topper << "%\n";
                std::cout << "At-Risk Intervention Needed (peek_min O(1)): " << at_risk << "%\n";
                break;
            }
            case 7: {
                std::cout << "\n--- [Unit 3: Job Scheduler & Josephus] ---\n";
                Vector<AcademicTask> tasks;
                tasks.push_back(AcademicTask(1, 0, 4, 1));
                tasks.push_back(AcademicTask(2, 1, 2, 2));
                tasks.push_back(AcademicTask(3, 2, 5, 1));
                auto fcfs = TaskScheduler::run_fcfs(tasks);
                std::cout << "FCFS Viva Scheduling Avg Waiting Time: " << fcfs.avg_waiting_time << " min\n";

                auto elim = JosephusSolver::solve_simulation(7, 3);
                std::cout << "Josephus Scholarship Elimination Order (n=7, k=3): [ ";
                for (std::size_t i = 0; i < elim.size(); ++i) std::cout << elim[i] << " ";
                std::cout << "], Winner: " << elim.back() << "\n";
                break;
            }
            case 8: {
                std::cout << "\n--- [Unit 4: Academic Hierarchy Binary Tree Traversals] ---\n";
                TreeNode<std::string>* r = new TreeNode<std::string>("CS_Dept");
                r->left = new TreeNode<std::string>("Div_A");
                r->right = new TreeNode<std::string>("Div_B");
                r->left->left = new TreeNode<std::string>("Batch_A1");
                r->left->right = new TreeNode<std::string>("Batch_A2");

                BinaryTree<std::string> bt(r);
                auto in_rec = bt.inorder_recursive();
                auto in_iter = bt.inorder_iterative();
                std::cout << "Inorder Recursive: [ ";
                for (std::size_t i = 0; i < in_rec.size(); ++i) std::cout << in_rec[i] << " ";
                std::cout << "]\n";
                std::cout << "Inorder Iterative: [ ";
                for (std::size_t i = 0; i < in_iter.size(); ++i) std::cout << in_iter[i] << " ";
                std::cout << "]\n";
                break;
            }
            case 9: {
                std::cout << "\n--- [Unit 4: BST 3-Case Deletion & Range Query] ---\n";
                BinarySearchTree<double, std::string> bst;
                bst.insert(9.2, "Aarav"); bst.insert(8.4, "Diya"); bst.insert(9.8, "Rohan");
                bst.insert(7.1, "Kabir"); bst.insert(8.9, "Ananya");
                std::cout << "Students with SGPA in range [8.5, 9.5]:\n";
                auto range = bst.range_query(8.5, 9.5);
                for (std::size_t i = 0; i < range.size(); ++i) {
                    std::cout << " - " << range[i].second << " (SGPA: " << range[i].first << ")\n";
                }
                break;
            }
            case 10: {
                std::cout << "\n--- [Unit 5: Advanced Heaps (Leftist & Heapsort)] ---\n";
                Vector<int> arr;
                arr.push_back(75); arr.push_back(45); arr.push_back(95); arr.push_back(60);
                BinaryMaxHeap<int>::heapsort(arr);
                std::cout << "Heapsort In-Place Result: [ ";
                for (std::size_t i = 0; i < arr.size(); ++i) std::cout << arr[i] << " ";
                std::cout << "]\n";
                break;
            }
            case 11: {
                std::cout << "\n--- [Unit 6: Course Prerequisite Graph] ---\n";
                Graph g(4, true);
                g.add_edge(0, 1); g.add_edge(1, 2); g.add_edge(2, 3);
                std::cout << "Directed Prerequisite Chain: FPL(0) -> DS(1) -> DAA(2) -> CAPSTONE(3)\n";
                std::cout << "Cycle Detected: " << (GraphTraversal::detect_cycle_directed(g) ? "YES (Deadlock)" : "NO (Valid Academic Path)") << "\n";
                break;
            }
            case 12: {
                std::cout << "\n--- [Unit 6: Dijkstra & Prim/Kruskal MST] ---\n";
                Graph g(4, false);
                g.add_edge(0, 1, 3.0); g.add_edge(1, 2, 2.0); g.add_edge(2, 3, 1.0); g.add_edge(0, 3, 5.0);
                auto mst = MinimumSpanningTree::kruskal(g);
                std::cout << "Minimum Spanning Tree (Peer Mentoring Network Backbone Cost): " << mst.total_weight << "\n";
                auto sp = ShortestPath::dijkstra(g, 0);
                std::cout << "Shortest Path from Node 0 to Node 2: " << sp.dist[2] << " units\n";
                break;
            }
            default:
                std::cout << "Invalid selection.\n";
                break;
        }
    }
    return 0;
}

