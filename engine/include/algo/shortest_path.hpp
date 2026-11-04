#ifndef ACADPULSE_SHORTEST_PATH_HPP
#define ACADPULSE_SHORTEST_PATH_HPP

#include <cstddef>
#include "core/vec.hpp"
#include "core/pair.hpp"
#include "core/array2d.hpp"
#include "core/metrics.hpp"
#include "algo/graph.hpp"

namespace dsa {

struct ShortestPathResult {
    Vector<double> dist;
    Vector<int> parent;

    Vector<std::size_t> reconstruct_path(std::size_t target) const {
        Vector<std::size_t> path;
        int curr = static_cast<int>(target);
        while (curr != -1) {
            path.push_back(static_cast<std::size_t>(curr));
            curr = parent[curr];
        }
        // reverse
        std::size_t n = path.size();
        for (std::size_t i = 0; i < n / 2; ++i) {
            std::size_t tmp = path[i];
            path[i] = path[n - 1 - i];
            path[n - 1 - i] = tmp;
        }
        return path;
    }
};

/**
 * Shortest Path Algorithms.
 * Covers Syllabus: Unit 6 (Shortest Path Algorithms: Dijkstra, Floyd-Warshall)
 */
class ShortestPath {
public:
    /**
     * Dijkstra's Single Source Shortest Path Algorithm.
     * Time: O(V^2) / O((V+E) log V), Space: O(V)
     */
    static ShortestPathResult dijkstra(const Graph& g, std::size_t start, OpMetrics* metrics = nullptr) {
        std::size_t v = g.num_vertices();
        ShortestPathResult result;
        result.dist.resize(v, 1e18);
        result.parent.resize(v, -1);

        if (start >= v) return result;

        Vector<bool> visited(v, false);
        result.dist[start] = 0.0;

        for (std::size_t count = 0; count < v; ++count) {
            double min_d = 1e18;
            std::size_t u = v;

            for (std::size_t i = 0; i < v; ++i) {
                if (metrics) metrics->comparisons++;
                if (!visited[i] && result.dist[i] < min_d) {
                    min_d = result.dist[i];
                    u = i;
                }
            }

            if (u == v || min_d >= 1e17) break;

            visited[u] = true;
            const auto& adj = g.neighbors(u);

            for (std::size_t i = 0; i < adj.size(); ++i) {
                std::size_t nxt = adj[i].first;
                double w = adj[i].second;

                if (metrics) metrics->comparisons++;
                if (!visited[nxt] && result.dist[u] + w < result.dist[nxt]) {
                    result.dist[nxt] = result.dist[u] + w;
                    result.parent[nxt] = static_cast<int>(u);
                    if (metrics) metrics->swaps++;
                }
            }
        }

        return result;
    }

    /**
     * Floyd-Warshall All-Pairs Shortest Path Algorithm.
     * Time: O(V^3), Space: O(V^2)
     */
    static Array2D<double> floyd_warshall(const Graph& g, OpMetrics* metrics = nullptr) {
        std::size_t v = g.num_vertices();
        Array2D<double> dist(v, v, 1e18);

        for (std::size_t i = 0; i < v; ++i) {
            dist(i, i) = 0.0;
        }

        const auto& edges = g.edges();
        for (std::size_t i = 0; i < edges.size(); ++i) {
            dist(edges[i].u, edges[i].v) = edges[i].weight;
        }

        for (std::size_t k = 0; k < v; ++k) {
            for (std::size_t i = 0; i < v; ++i) {
                for (std::size_t j = 0; j < v; ++j) {
                    if (metrics) metrics->comparisons++;
                    if (dist(i, k) < 1e17 && dist(k, j) < 1e17) {
                        if (dist(i, k) + dist(k, j) < dist(i, j)) {
                            dist(i, j) = dist(i, k) + dist(k, j);
                            if (metrics) metrics->swaps++;
                        }
                    }
                }
            }
        }

        return dist;
    }
};

} // namespace dsa

#endif // ACADPULSE_SHORTEST_PATH_HPP

