#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <map>
#include <stdlib.h>

#include "stack.hpp"


const std::map<char, unsigned> opt_precedence = {{'|', 0}, {'&', 1}, {'-', 2}};

bool precedence(char opt1, char opt2) {
    return opt_precedence.at(opt1) > opt_precedence.at(opt2);
}

bool is_operand(char c) {
    for (std::pair<char, unsigned> p : opt_precedence) {
        if (p.first == c) {
            return true;
        }
    }

    return false;
}


std::string remove_blanks(std::string string_in) {
    std::string string_out;
    for (char c : string_in) {

        if (!std::isspace(c)) {
            string_out += c;
        }

    }

    return string_out;
}

// infix_formula com zeros e uns e operadores apenas
std::string to_posfix(std::string infix_formula) {
    std::string posfix_formula;
    Stack stack;

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
            char s = stack.get();

            if (s == '(') {
                stack.add(c);
                continue;
            }

            while (!precedence(c, s)) {
                posfix_formula += stack.pop();

                if (stack.empty()) {
                    break;
                }
            }
            stack.add(c);
        }

    }

    while (!stack.empty()) {
        posfix_formula += stack.pop();
    }

    return posfix_formula;
}

bool is_digit(char c) {
    return !(is_operand(c) || c == '(' || c == ')');
}


// varrer a formula sem espaços em branco copiando símbolos para outra string
// mapeando valores numéricos para 0's e 1's pela string valuation
std::string set_values(std::string formula, std::string valuation) {
    std::string str_out;
    int len = formula.size();

    for (int i=0; i < len;) {
        char c = formula[i];

        if (is_digit(c)) {
            std::string digit_str;
            while (is_digit(c)) {
                digit_str += c;
                c = formula[++i];
            }
            
            int digit = std::atoi(digit_str.c_str());
            str_out += valuation[digit - 1];

        } else {
            str_out += c;
            ++i;
        }
    }

    return str_out;
}


bool evaluate_expression(std::string formula, std::string valuation) {
    formula = remove_blanks(formula);
    formula = set_values(formula, valuation);
    
    formula = to_posfix(formula);

    // pos-fixa
    std::cout << formula << std::endl;

    Stack stack;
    int len = formula.size();
    for (int i=0; i < len; ++i) {
        char c = formula[i];
        if ( is_digit(c) ) {
            std::cout << "add literal: " << c << std::endl; 
            stack.add(c);
        }

        else if (c == '-') {
            stack.print();
            std::cout << "opr: " << c << std::endl;
            stack.add('0' + !(stack.pop() - '0')); //removo elemento e adiciono a stack
            stack.print();

        } else {
            stack.print();
            std::cout << "opr: " << c << std::endl;
            int digit1 = stack.pop() - '0';
            int digit2 = stack.pop() - '0';
            // int a = digit1 & digit1;
            // int o = digit1 | digit2;

            // std::cout << "and: " << a << std::endl;
            // std::cout << "or: " << o << std::endl;

            char result = c == '&' ? '0' + (digit1 & digit2) : '0' + (digit1 | digit2);          
            stack.add(result);

            stack.print();
        }
    }

    return true;
}


#endif