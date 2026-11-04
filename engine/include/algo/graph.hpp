#ifndef ACADPULSE_GRAPH_HPP
#define ACADPULSE_GRAPH_HPP

#include <cstddef>
#include "core/vec.hpp"
#include "core/pair.hpp"
#include "core/array2d.hpp"

namespace dsa {

struct GraphEdge {
    std::size_t u;
    std::size_t v;
    double weight;

    GraphEdge() : u(0), v(0), weight(0.0) {}
    GraphEdge(std::size_t from, std::size_t to, double w = 1.0) : u(from), v(to), weight(w) {}

    bool operator<(const GraphEdge& other) const {
        return weight < other.weight;
    }
};

/**
 * Dual Representation Graph ADT (Adjacency Matrix + Adjacency List).
 * Covers Syllabus: Unit 6 (Graph terminology and representation using Adjacency Matrix and Adjacency Lists)
 * 
 * Used in Student Ranking & Performance Analyser for:
 * - Course prerequisite dependency network
 * - Student peer mentoring / study group network
 */
class Graph {
private:
    std::size_t num_vertices_;
    bool directed_;

    // Adjacency Matrix: O(V^2) space, O(1) edge lookup
    Array2D<double> adj_matrix_;

    // Adjacency List: O(V + E) space, O(deg(u)) iteration
    Vector<Vector<Pair<std::size_t, double>>> adj_list_;

    Vector<GraphEdge> all_edges_;

public:
    Graph(std::size_t v = 0, bool is_directed = false)
        : num_vertices_(v), directed_(is_directed),
          adj_matrix_(v, v, 0.0) {
        adj_list_.resize(v);
    }

    std::size_t num_vertices() const noexcept { return num_vertices_; }
    bool is_directed() const noexcept { return directed_; }

    void add_edge(std::size_t u, std::size_t v, double weight = 1.0) {
        if (u >= num_vertices_ || v >= num_vertices_) return;

        adj_matrix_(u, v) = weight;
        adj_list_[u].push_back(make_pair(v, weight));
        all_edges_.push_back(GraphEdge(u, v, weight));

        if (!directed_) {
            adj_matrix_(v, u) = weight;
            adj_list_[v].push_back(make_pair(u, weight));
            all_edges_.push_back(GraphEdge(v, u, weight));
        }
    }

    const Array2D<double>& adjacency_matrix() const noexcept {
        return adj_matrix_;
    }

    const Vector<Pair<std::size_t, double>>& neighbors(std::size_t u) const {
        return adj_list_[u];
    }

    const Vector<Vector<Pair<std::size_t, double>>>& adjacency_list() const noexcept {
        return adj_list_;
    }

    const Vector<GraphEdge>& edges() const noexcept {
        return all_edges_;
    }
};

} // namespace dsa

#endif // ACADPULSE_GRAPH_HPP

