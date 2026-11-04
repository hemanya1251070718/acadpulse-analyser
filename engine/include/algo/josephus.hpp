#ifndef ACADPULSE_JOSEPHUS_HPP
#define ACADPULSE_JOSEPHUS_HPP

#include <cstddef>
#include "core/vec.hpp"
#include "ds/linked_lists.hpp"

namespace dsa {

/**
 * Josephus Problem Solver.
 * Covers Syllabus: Unit 3 (Applications of Queues / Circular Lists: Josephus problem)
 * Used in Student Analyser for student scholarship selection & candidate elimination rounds.
 */
class JosephusSolver {
public:
    /**
     * Circular Linked List simulation showing elimination order.
     * Time: O(N * K), Space: O(N)
     */
    static Vector<int> solve_simulation(int n, int k) {
        Vector<int> elimination_order;
        if (n <= 0 || k <= 0) return elimination_order;

        SNode<int>* head = new SNode<int>(1);
        SNode<int>* prev = head;
        for (int i = 2; i <= n; ++i) {
            SNode<int>* node = new SNode<int>(i);
            prev->next = node;
            prev = node;
        }
        prev->next = head; // Make circular

        SNode<int>* curr = head;
        SNode<int>* p = prev;

        while (elimination_order.size() < static_cast<std::size_t>(n)) {
            // Count k - 1 steps
            for (int count = 1; count < k; ++count) {
                p = curr;
                curr = curr->next;
            }
            // Eliminate curr
            elimination_order.push_back(curr->data);
            p->next = curr->next;
            delete curr;
            curr = p->next;
        }

        return elimination_order;
    }

    /**
     * Recursive solution: J(n, k) = (J(n-1, k) + k - 1) % n + 1
     * Time: O(N), Space: O(N) call stack
     */
    static int solve_recursive(int n, int k) {
        if (n == 1) return 1;
        return (solve_recursive(n - 1, k) + k - 1) % n + 1;
    }

    /**
     * Iterative solution: O(N) time, O(1) space.
     */
    static int solve_iterative(int n, int k) {
        int ans = 0;
        for (int i = 2; i <= n; ++i) {
            ans = (ans + k) % i;
        }
        return ans + 1;
    }
};

} // namespace dsa

#endif // ACADPULSE_JOSEPHUS_HPP

