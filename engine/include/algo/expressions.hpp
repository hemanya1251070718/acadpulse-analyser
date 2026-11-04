#ifndef ACADPULSE_EXPRESSIONS_HPP
#define ACADPULSE_EXPRESSIONS_HPP

#include <cstddef>
#include <cmath>
#include <cctype>
#include "core/vec.hpp"
#include "core/string_builder.hpp"
#include "ds/stack.hpp"
#include "ds/hash_table.hpp"

namespace dsa {

/**
 * Expression Engine: Infix to Postfix Conversion and Evaluation via Stack ADT.
 * Covers Syllabus: Unit 3 (Expression conversions and evaluations)
 * 
 * Used in Student Ranking & Performance Analyser for custom grading formulas:
 * e.g., "MSE * 0.3 + ESE * 0.5 + LAB * 0.2"
 */
class ExpressionEngine {
private:
    static int precedence(char op) {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        if (op == '^') return 3;
        return 0;
    }

    static bool is_operator(char c) {
        return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
    }

public:
    /**
     * Converts Infix expression string to space-separated Postfix (RPN) string.
     * Uses explicit ArrayStack ADT.
     */
    static Vector<char> infix_to_postfix(const char* infix) {
        Vector<char> postfix;
        ArrayStack<char> op_stack;

        std::size_t i = 0;
        while (infix[i] != '\0') {
            char c = infix[i];

            if (std::isspace(c)) {
                ++i;
                continue;
            }

            // If alphanumeric (variable or number literal)
            if (std::isalnum(c) || c == '.') {
                while (infix[i] != '\0' && (std::isalnum(infix[i]) || infix[i] == '.' || infix[i] == '_')) {
                    postfix.push_back(infix[i]);
                    ++i;
                }
                postfix.push_back(' ');
                continue;
            }

            if (c == '(') {
                op_stack.push(c);
            } else if (c == ')') {
                char top_op;
                while (op_stack.pop(top_op) && top_op != '(') {
                    postfix.push_back(top_op);
                    postfix.push_back(' ');
                }
            } else if (is_operator(c)) {
                char top_op;
                while (op_stack.top(top_op) && top_op != '(' && 
                       (precedence(top_op) > precedence(c) || 
                       (precedence(top_op) == precedence(c) && c != '^'))) {
                    op_stack.pop(top_op);
                    postfix.push_back(top_op);
                    postfix.push_back(' ');
                }
                op_stack.push(c);
            }
            ++i;
        }

        char top_op;
        while (op_stack.pop(top_op)) {
            postfix.push_back(top_op);
            postfix.push_back(' ');
        }

        postfix.push_back('\0');
        return postfix;
    }

    /**
     * Evaluates Postfix expression using Stack ADT and variable symbol table.
     */
    static double evaluate_postfix(const char* postfix, const HashTable<double>& vars) {
        ArrayStack<double> val_stack;

        std::size_t i = 0;
        while (postfix[i] != '\0') {
            if (std::isspace(postfix[i])) {
                ++i;
                continue;
            }

            // Check if operator
            if (is_operator(postfix[i]) && (std::isspace(postfix[i + 1]) || postfix[i + 1] == '\0')) {
                char op = postfix[i];
                double b = 0.0, a = 0.0;
                val_stack.pop(b);
                val_stack.pop(a);

                double res = 0.0;
                if (op == '+') res = a + b;
                else if (op == '-') res = a - b;
                else if (op == '*') res = a * b;
                else if (op == '/') res = (b != 0.0 ? a / b : 0.0);
                else if (op == '^') res = std::pow(a, b);

                val_stack.push(res);
                ++i;
                continue;
            }

            // Parse token (number literal or variable)
            Vector<char> token;
            while (postfix[i] != '\0' && !std::isspace(postfix[i])) {
                token.push_back(postfix[i]);
                ++i;
            }
            token.push_back('\0');

            // Try parsing as number
            char* end_ptr = nullptr;
            double num = std::strtod(token.data(), &end_ptr);
            if (end_ptr != token.data() && *end_ptr == '\0') {
                val_stack.push(num);
            } else {
                // Lookup variable in Hash Table
                double val = 0.0;
                if (vars.get(token.data(), val)) {
                    val_stack.push(val);
                } else {
                    val_stack.push(0.0);
                }
            }
        }

        double final_res = 0.0;
        val_stack.pop(final_res);
        return final_res;
    }
};

} // namespace dsa

#endif // ACADPULSE_EXPRESSIONS_HPP

