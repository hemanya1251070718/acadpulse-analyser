#ifndef ACADPULSE_GRAPH_TRAVERSAL_HPP
#define ACADPULSE_GRAPH_TRAVERSAL_HPP

#include <cstddef>
#include "core/vec.hpp"
#include "ds/queue.hpp"
#include "ds/stack.hpp"
#include "algo/graph.hpp"

namespace dsa {

/**
 * Graph Traversals & Structural Analyzers.
 * Covers Syllabus: Unit 6 (Graph Traversals: BFS, DFS, Connected Graph, Detecting Cycle)
 */
class GraphTraversal {
public:
    /**
     * Breadth-First Search (BFS) using CircularQueue ADT.
     * Time: O(V + E), Space: O(V)
     */
    static Vector<std::size_t> bfs(const Graph& g, std::size_t start) {
        Vector<std::size_t> order;
        if (start >= g.num_vertices()) return order;

        Vector<bool> visited(g.num_vertices(), false);
        CircularQueue<std::size_t> q(g.num_vertices() + 4);

        visited[start] = true;
        q.enqueue(start);

        std::size_t curr = 0;
        while (q.dequeue(curr)) {
            order.push_back(curr);
            const auto& adj = g.neighbors(curr);
            for (std::size_t i = 0; i < adj.size(); ++i) {
                std::size_t nxt = adj[i].first;
                if (!visited[nxt]) {
                    visited[nxt] = true;
                    q.enqueue(nxt);
                }
            }
        }
        return order;
    }

    /**
     * Depth-First Search (DFS) - Recursive.
     * Time: O(V + E), Space: O(V) call stack
     */
    static Vector<std::size_t> dfs(const Graph& g, std::size_t start) {
        Vector<std::size_t> order;
        if (start >= g.num_vertices()) return order;

        Vector<bool> visited(g.num_vertices(), false);
        dfs_rec(g, start, visited, order);
        return order;
    }

private:
    static void dfs_rec(const Graph& g, std::size_t u, Vector<bool>& visited, Vector<std::size_t>& order) {
        visited[u] = true;
        order.push_back(u);
        const auto& adj = g.neighbors(u);
        for (std::size_t i = 0; i < adj.size(); ++i) {
            std::size_t v = adj[i].first;
            if (!visited[v]) {
                dfs_rec(g, v, visited, order);
            }
        }
    }

public:
    /**
     * Count Connected Components in an undirected graph.
     */
    static std::size_t count_connected_components(const Graph& g) {
        std::size_t v = g.num_vertices();
        Vector<bool> visited(v, false);
        std::size_t components = 0;

        for (std::size_t i = 0; i < v; ++i) {
            if (!visited[i]) {
                components++;
                // Run BFS
                CircularQueue<std::size_t> q(v + 4);
                visited[i] = true;
                q.enqueue(i);
                std::size_t curr = 0;
                while (q.dequeue(curr)) {
                    const auto& adj = g.neighbors(curr);
                    for (std::size_t j = 0; j < adj.size(); ++j) {
                        std::size_t nxt = adj[j].first;
                        if (!visited[nxt]) {
                            visited[nxt] = true;
                            q.enqueue(nxt);
                        }
                    }
                }
            }
        }
        return components;
    }

    /**
     * Detect Cycle in Directed Graph (e.g. Circular Prerequisite Detection).
     * Uses 3-color DFS: 0 = unvisited (white), 1 = visiting/in stack (gray), 2 = visited (black).
     * Covers Syllabus: Unit 6 (Detecting Cycle in graph)
     */
    static bool detect_cycle_directed(const Graph& g, Vector<std::size_t>* cycle_nodes = nullptr) {
        std::size_t v = g.num_vertices();
        Vector<int> color(v, 0); // 0=White, 1=Gray, 2=Black

        for (std::size_t i = 0; i < v; ++i) {
            if (color[i] == 0) {
                if (dfs_cycle_directed(g, i, color, cycle_nodes)) {
                    return true;
                }
            }
        }
        return false;
    }

private:
    static bool dfs_cycle_directed(const Graph& g, std::size_t u, Vector<int>& color, Vector<std::size_t>* cycle_nodes) {
        color[u] = 1; // Gray (currently in recursion call stack)
        const auto& adj = g.neighbors(u);

        for (std::size_t i = 0; i < adj.size(); ++i) {
            std::size_t v = adj[i].first;
            if (color[v] == 1) { // Back-edge found! Cycle!
                if (cycle_nodes) {
                    cycle_nodes->push_back(u);
                    cycle_nodes->push_back(v);
                }
                return true;
            }
            if (color[v] == 0) {
                if (dfs_cycle_directed(g, v, color, cycle_nodes)) {
                    if (cycle_nodes) cycle_nodes->push_back(u);
                    return true;
                }
            }
        }
        color[u] = 2; // Black
        return false;
    }
};

} // namespace dsa

#endif // ACADPULSE_GRAPH_TRAVERSAL_HPP

