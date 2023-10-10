#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>

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