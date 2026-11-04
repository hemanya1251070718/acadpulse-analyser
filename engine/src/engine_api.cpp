#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <cmath>

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

struct StudentItem {
    std::string prn;
    std::string name;
    std::string division;
    double mse = 0;
    double ese = 0;
    double lab = 0;
    double project = 0;
    double attendance = 0;
    double composite_score = 0;
    double sgpa = 0;
    int rank = 0;

    bool operator<(const StudentItem& o) const {
        return composite_score < o.composite_score;
    }
    bool operator<=(const StudentItem& o) const {
        return composite_score <= o.composite_score;
    }
};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "{\"status\":\"error\",\"message\":\"No command specified\"}" << std::endl;
        return 1;
    }

    std::string cmd = argv[1];

    if (cmd == "ping") {
        std::cout << "{\"status\":\"success\",\"message\":\"AcadPulse C++ DSA Engine v2.0 Online\",\"zero_stl\":true}" << std::endl;
        return 0;
    }

    if (cmd == "eval_formula") {
        // argv[2] = formula, argv[3] = MSE, argv[4] = ESE, argv[5] = LAB, argv[6] = PROJ
        if (argc < 7) {
            std::cout << "{\"status\":\"error\",\"message\":\"Insufficient formula parameters\"}" << std::endl;
            return 1;
        }
        std::string formula = argv[2];
        double mse = std::atof(argv[3]);
        double ese = std::atof(argv[4]);
        double lab = std::atof(argv[5]);
        double proj = std::atof(argv[6]);

        auto postfix = ExpressionEngine::infix_to_postfix(formula.c_str());
        HashTable<double> vars;
        vars.put("MSE", mse);
        vars.put("ESE", ese);
        vars.put("LAB", lab);
        vars.put("PROJ", proj);

        double evaluated = ExpressionEngine::evaluate_postfix(postfix.data(), vars);

        std::cout << "{\"status\":\"success\","
                  << "\"infix\":\"" << formula << "\","
                  << "\"postfix\":\"" << postfix.data() << "\","
                  << "\"score\":" << evaluated << "}" << std::endl;
        return 0;
    }

    if (cmd == "josephus") {
        int n = (argc > 2) ? std::atoi(argv[2]) : 7;
        int k = (argc > 3) ? std::atoi(argv[3]) : 3;

        auto elim = JosephusSolver::solve_simulation(n, k);
        int winner = JosephusSolver::solve_recursive(n, k);

        std::cout << "{\"status\":\"success\","
                  << "\"n\":" << n << ",\"k\":" << k << ","
                  << "\"winner\":" << winner << ",\"elimination_order\":[";
        for (std::size_t i = 0; i < elim.size(); ++i) {
            std::cout << elim[i] << (i + 1 < elim.size() ? "," : "");
        }
        std::cout << "]}" << std::endl;
        return 0;
    }

    if (cmd == "sparse_transpose") {
        SparseMatrix sm(5, 6);
        sm.insert(0, 1, 85.0);
        sm.insert(1, 4, 92.5);
        sm.insert(2, 2, 78.0);
        sm.insert(3, 0, 95.0);
        sm.insert(4, 5, 88.0);

        OpMetrics m_simple, m_fast;
        SparseMatrix st = sm.simple_transpose(&m_simple);
        SparseMatrix ft = sm.fast_transpose(&m_fast);

        std::cout << "{\"status\":\"success\","
                  << "\"non_zeros\":" << sm.non_zeros() << ","
                  << "\"simple\":{\"comparisons\":" << m_simple.comparisons << ",\"swaps\":" << m_simple.swaps << "},"
                  << "\"fast\":{\"comparisons\":" << m_fast.comparisons << ",\"swaps\":" << m_fast.swaps << ",\"pointer_hops\":" << m_fast.pointer_hops << "}}"
                  << std::endl;
        return 0;
    }

    if (cmd == "graph_analysis") {
        // Course Prerequisite Graph
        Graph g(6, true); // 6 courses: 0=FPL, 1=DS, 2=DAA, 3=OS, 4=DBMS, 5=CAPSTONE
        g.add_edge(0, 1, 4.0); // FPL -> DS
        g.add_edge(1, 2, 4.0); // DS -> DAA
        g.add_edge(1, 3, 3.0); // DS -> OS
        g.add_edge(1, 4, 3.0); // DS -> DBMS
        g.add_edge(2, 5, 5.0); // DAA -> CAPSTONE
        g.add_edge(4, 5, 4.0); // DBMS -> CAPSTONE

        auto bfs = GraphTraversal::bfs(g, 0);
        auto dfs = GraphTraversal::dfs(g, 0);
        bool has_cycle = GraphTraversal::detect_cycle_directed(g);
        auto sp = ShortestPath::dijkstra(g, 0);
        auto path_to_capstone = sp.reconstruct_path(5);

        // Undirected graph for Peer Mentoring MST
        Graph ug(6, false);
        ug.add_edge(0, 1, 2.0);
        ug.add_edge(1, 2, 3.0);
        ug.add_edge(1, 3, 1.5);
        ug.add_edge(2, 4, 2.5);
        ug.add_edge(3, 4, 4.0);
        ug.add_edge(4, 5, 1.0);
        ug.add_edge(0, 3, 3.5);

        auto mst_k = MinimumSpanningTree::kruskal(ug);
        auto mst_p = MinimumSpanningTree::prim(ug);

        std::cout << "{\"status\":\"success\","
                  << "\"has_circular_prerequisite\":" << (has_cycle ? "true" : "false") << ","
                  << "\"bfs_order\":[";
        for (std::size_t i = 0; i < bfs.size(); ++i) std::cout << bfs[i] << (i + 1 < bfs.size() ? "," : "");
        std::cout << "],\"dfs_order\":[";
        for (std::size_t i = 0; i < dfs.size(); ++i) std::cout << dfs[i] << (i + 1 < dfs.size() ? "," : "");
        std::cout << "],\"remediation_path_to_capstone\":[";
        for (std::size_t i = 0; i < path_to_capstone.size(); ++i) std::cout << path_to_capstone[i] << (i + 1 < path_to_capstone.size() ? "," : "");
        std::cout << "],\"mentoring_mst_cost\":" << mst_k.total_weight << "}" << std::endl;
        return 0;
    }

    if (cmd == "scheduler") {
        Vector<AcademicTask> tasks;
        tasks.push_back(AcademicTask(1, 0, 5, 2));
        tasks.push_back(AcademicTask(2, 1, 3, 1));
        tasks.push_back(AcademicTask(3, 2, 8, 3));
        tasks.push_back(AcademicTask(4, 3, 6, 2));

        auto fcfs = TaskScheduler::run_fcfs(tasks);
        auto rr = TaskScheduler::run_round_robin(tasks, 2);

        std::cout << "{\"status\":\"success\","
                  << "\"fcfs\":{\"avg_wait\":" << fcfs.avg_waiting_time << ",\"avg_tat\":" << fcfs.avg_turnaround_time << "},"
                  << "\"round_robin\":{\"avg_wait\":" << rr.avg_waiting_time << ",\"avg_tat\":" << rr.avg_turnaround_time << "}}"
                  << std::endl;
        return 0;
    }

    std::cout << "{\"status\":\"error\",\"message\":\"Unknown command: " << cmd << "\"}" << std::endl;
    return 0;
}

