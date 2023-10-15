#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <stdlib.h>

/**
 * @brief Retorna a precedência de um operador lógico.
 * @param opt O operador lógico a ser avaliado.
 * @return A precedência do operador, onde 0 indica a menor precedência.
 */
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

/**
 * @brief Verifica se um caractere é um operador lógico.
 * @param c O caractere a ser verificado.
 * @return true se o caractere for um operador lógico, false caso contrário.
 */
inline bool is_operand(char c) {
    return (c == '|') || (c == '&') || (c == '~');
}

/**
 * @brief Verifica se um caractere é um dígito (0 ou 1).
 * @param c O caractere a ser verificado.
 * @return true se o caractere for um dígito, false caso contrário.
 */
inline bool is_digit(char c) {
    return ('0' <= c) && (c <= '9');
}

/**
 * @brief Negação lógica de um caractere (0 para 1 e 1 para 0).
 * @param c O caractere a ser negado.
 * @return O resultado da negação.
 */
inline char _neg(char c) {
    return c == '1' ? '0' : '1';
}

/**
 * @brief Operação lógica "E" entre dois caracteres (0 e 1).
 * @param c1 O primeiro caractere.
 * @param c2 O segundo caractere.
 * @return O resultado da operação "E".
 */
inline char _and(char c1, char c2) {
    return (c1 == '1' && c2 == '1') ? '1' : '0';
}

/**
 * @brief Operação lógica "OU" entre dois caracteres (0 e 1).
 * @param c1 O primeiro caractere.
 * @param c2 O segundo caractere.
 * @return O resultado da operação "OU".
 */
inline char _or(char c1, char c2) {
    return (c1 == '1' || c2 ==  '1') ? '1' : '0';
}

/**
 * @brief Substitui os valores numéricos por 0's e 1's em uma fórmula lógica.
 * @param formula A fórmula lógica a ser modificada.
 * @param valuation A sequência de valores numéricos para substituição.
 * @return A fórmula lógica com os valores substituídos.
 */
inline std::string set_values(std::string formula, std::string valuation) {
    std::string str_out;
    int len = formula.size();

    for (int i = 0; i < len; ++i) {
        char c = formula[i];

        if (std::isspace(c)) {
            continue;
        } else if (is_digit(c)) {
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

/**
 * @brief Converte uma fórmula lógica infixa para pós-fixa.
 * @param infix_formula A fórmula lógica infixa.
 * @param valuation A sequência de valores numéricos para substituição.
 * @return A fórmula lógica pós-fixa.
 */
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

/**
 * @brief Avalia uma expressão lógica pós-fixa com valores 0's e 1's.
 * @param formula A fórmula lógica pós-fixa.
 * @param valuation A sequência de valores numéricos para substituição.
 * @return true se a expressão é verdadeira, false caso contrário.
 */
inline bool evaluate_expression(std::string formula, std::string valuation) {
    formula = to_posfix(formula, valuation);

    Stack<char> stack;
    int len = formula.size();
    for (int i = 0; i < len; ++i) {
        char c = formula[i];
        if (is_digit(c)) {
            stack.add(c);
        } else if (c == '~') {
            stack.add(_neg(stack.pop()));
        } else {
            char operand1 = stack.pop();
            char operand2 = stack.pop();
            char result = c == '&' ? _and(operand1, operand2) : _or(operand1, operand2);
            stack.add(result);
        }
    }

    return stack.pop() == '1' ? true : false;
}

/**
 * @brief Conta o número de ocorrências de um caractere em uma string.
 * @param str A string a ser verificada.
 * @param character O caractere a ser contado.
 * @return O número de ocorrências do caractere na string.
 */
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