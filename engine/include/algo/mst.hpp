#ifndef ACADPULSE_MST_HPP
#define ACADPULSE_MST_HPP

#include <cstddef>
#include "core/vec.hpp"
#include "core/metrics.hpp"
#include "ds/dsu.hpp"
#include "algo/graph.hpp"

namespace dsa {

struct MSTResult {
    double total_weight = 0.0;
    Vector<GraphEdge> mst_edges;
};

/**
 * Minimum Spanning Tree Algorithms.
 * Covers Syllabus: Unit 6 (Prim's and Kruskal's Algorithm)
 * Used in Student Analyser for:
 * - Minimum-cost peer mentoring network
 * - Optimal study group clustering backbone
 */
class MinimumSpanningTree {
public:
    /**
     * Kruskal's Algorithm using Disjoint Set Union (DSU).
     * Time: O(E log E), Space: O(V + E)
     */
    static MSTResult kruskal(const Graph& g, OpMetrics* metrics = nullptr) {
        MSTResult result;
        std::size_t v = g.num_vertices();
        if (v == 0) return result;

        Vector<GraphEdge> edges = g.edges();
        std::size_t e = edges.size();

        // Sort edges by weight (Simple Selection Sort / QuickSort)
        for (std::size_t i = 0; i < e; ++i) {
            for (std::size_t j = i + 1; j < e; ++j) {
                if (metrics) metrics->comparisons++;
                if (edges[j].weight < edges[i].weight) {
                    GraphEdge tmp = edges[i];
                    edges[i] = edges[j];
                    edges[j] = tmp;
                    if (metrics) metrics->swaps++;
                }
            }
        }

        DisjointSetUnion dsu(v);

        for (std::size_t i = 0; i < e; ++i) {
            std::size_t u = edges[i].u;
            std::size_t w = edges[i].v;

            if (dsu.unite(u, w)) {
                result.mst_edges.push_back(edges[i]);
                result.total_weight += edges[i].weight;
                if (result.mst_edges.size() == v - 1) {
                    break;
                }
            }
        }

        return result;
    }

    /**
     * Prim's Algorithm.
     * Time: O(V^2) or O(E log V), Space: O(V)
     */
    static MSTResult prim(const Graph& g, OpMetrics* metrics = nullptr) {
        MSTResult result;
        std::size_t v = g.num_vertices();
        if (v == 0) return result;

        Vector<bool> in_mst(v, false);
        Vector<double> key(v, 1e18);
        Vector<int> parent(v, -1);

        key[0] = 0.0;

        for (std::size_t count = 0; count < v; ++count) {
            double min_key = 1e18;
            std::size_t u = v;

            for (std::size_t i = 0; i < v; ++i) {
                if (metrics) metrics->comparisons++;
                if (!in_mst[i] && key[i] < min_key) {
                    min_key = key[i];
                    u = i;
                }
            }

            if (u == v || min_key >= 1e17) break; // Disconnected

            in_mst[u] = true;
            if (parent[u] != -1) {
                result.mst_edges.push_back(GraphEdge(parent[u], u, key[u]));
                result.total_weight += key[u];
            }

            const auto& adj = g.neighbors(u);
            for (std::size_t i = 0; i < adj.size(); ++i) {
                std::size_t nxt = adj[i].first;
                double w = adj[i].second;
                if (metrics) metrics->comparisons++;
                if (!in_mst[nxt] && w < key[nxt]) {
                    key[nxt] = w;
                    parent[nxt] = static_cast<int>(u);
                }
            }
        }

        return result;
    }
};

} // namespace dsa

#endif // ACADPULSE_MST_HPP

