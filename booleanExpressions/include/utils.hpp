#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <map>
#include <stdlib.h>

#include "stack.hpp"

// Operands

const std::map<char, unsigned> opt_precedence = {{'|', 0}, {'&', 1}, {'~', 2}};

inline bool precedence(char opt1, char opt2) {
    return opt_precedence.at(opt1) > opt_precedence.at(opt2);
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


// infix_formula com zeros e uns e operadores apenas
inline std::string to_posfix(std::string infix_formula, std::string valuation) {
    std::string posfix_formula;
    Stack<char> stack;

    infix_formula = set_values(infix_formula, valuation);
    unsigned len = infix_formula.size();
    for (int i=0; i < len; ++i) {

        char c = infix_formula[i];
        // caractere é um operando
        if (c == '0' || c == '1') {
            posfix_formula += c;
        } 
        else if (stack.empty() || c == '(') {    
            stack.add(c);     
        }
        else if (c == ')') {
            while((c = stack.pop()) != '(') {
                posfix_formula += c;
            }
        }
        else if (is_operand(c)) {
            char stack_symb = stack.peek();

            if (stack_symb == '(') {
                stack.add(c);
                continue;
            }

            while (!precedence(c, stack_symb) && !stack.empty()) {
                stack_symb = stack.pop();
                posfix_formula += stack_symb;

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
    
    std::cout << formula << std::endl;

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


// TREE


enum Function {
    AND, OR, LEAF
};

enum Direction {
    RIGHT, LEFT
};

inline std::string func_to_str(Function function) {
    if (function == AND) {
        return "AND";
    }
    else if (function == OR) {
        return "OR";
    }
    else if (function == LEAF) {
        return "LEAF";
    }
    else {
        return "";
    }
} 

typedef struct Tuple {
    Function function;
    std::string sub_string;
    int index;

    void print() {
        std::cout << "---tuple---" << std::endl;
        std::cout << "f: " << func_to_str(function) << "\ns: " << sub_string << "\ni: " << index << std::endl;
    }

    bool is_leaf() {
        return function == LEAF;
    }
} Tuple;


inline std::string bool_to_str(bool value) {
    return value ? "true" : "false";
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


// encontra a posicao de um quantificador a partir de um determinado index
inline Tuple find_operator(std::string str, int index) {
    int start_index = index;
    for (; index < str.length(); ++index) {
        if (str[index] == 'a') {
            return Tuple{AND, str.substr(start_index, index - start_index), index};
        }
        else if (str[index] == 'e') {
            return Tuple{OR, str.substr(start_index, index - start_index), index};
        }
    }
    std::cout << "index: " << index << std::endl;
    return Tuple{LEAF, str.substr(start_index, index - start_index), index};
}


#endif