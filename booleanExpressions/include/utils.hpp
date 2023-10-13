#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <stdlib.h>

// Operands
inline int precedence(char opt) {
    switch (opt) {
        case '|':
            return 0;
        case '&':
            return 1;
        case '~':
            return 2;
        case '(':
            return 3;
        default:
            return -1;
    }
}

inline bool is_operand(char c) {
    return (c == '|') || (c == '&') || (c == '~');
}

inline bool is_digit(char c) {
    return ('0' <= c) && (c <= '9');
}

// operands with char 1's ans 0's
inline char _neg(char c) {
    return c == '1' ? '0' : '1';
}

inline char _and(char c1, char c2) {
    return (c1 == '1' && c2 == '1') ? '1' : '0';
}

inline char _or(char c1, char c2) {
    return (c1 == '1' || c2 ==  '1') ? '1' : '0';
}


// STRINGS

// varrer a formula copiando símbolos para outra string
// mapeando valores numéricos para 0's e 1's pela string valuation
inline std::string set_values(std::string formula, std::string valuation) {
    std::string str_out;
    int len = formula.size();

    for (int i=0; i < len; ++i) {
        char c = formula[i];

        if (std::isspace(c)) {
            continue;
        }
        else if (is_digit(c)) {
            std::string digit_str;

            do {
                digit_str += c;
                c = formula[++i];
            } while (is_digit(c));
            
            int digit = std::atoi(digit_str.c_str());
            str_out += valuation[digit];
            --i;

        } else {
            str_out += c;
        }
    }

    return str_out;
}

inline std::string to_posfix(std::string infix_formula, std::string valuation) {
    std::string posfix_formula;
    Stack<char> stack;

    infix_formula = set_values(infix_formula, valuation);
    int len = infix_formula.size();
    for (int i = 0; i < len; ++i) {
        char c = infix_formula[i];

        if (c == '0' || c == '1') {
            posfix_formula += c;
        } else if (c == '(') {
            stack.add(c);
        } else if (c == ')') {
            while (!stack.empty() && stack.peek() != '(') {
                posfix_formula += stack.pop();
            }
            if (!stack.empty() && stack.peek() == '(') {
                stack.pop();
            }
        } else if (is_operand(c)) {
            while (!stack.empty() && (precedence(c) < precedence(stack.peek())) && stack.peek() != '(') {
                posfix_formula += stack.pop();
            }
            stack.add(c);
        }
    }

    while (!stack.empty()) {
        posfix_formula += stack.pop();
    }

    return posfix_formula;
}



inline bool evaluate_expression(std::string formula, std::string valuation) {
    // posfix expression with 0's and 1's
    formula = to_posfix(formula, valuation);

    Stack<char> stack;
    int len = formula.size();
    for (int i=0; i < len; ++i) {
        char c = formula[i];
        if ( is_digit(c) ) { 
            stack.add(c);
        }

        else if (c == '~') {
            stack.add( _neg( stack.pop() ) );
  

        } else {
            char operand1 = stack.pop();
            char operand2 = stack.pop();

            char result = c == '&' ? _and(operand1, operand2) : _or(operand1, operand2);          
            stack.add(result);
        }
    }

    return stack.pop() == '1' ? true : false;
}

inline int count_char(std::string str, char character) {
    int count = 0;
    for (char c : str) {
        if (c == character) {
            ++count;
        }
    }

    return count;
};


#endif