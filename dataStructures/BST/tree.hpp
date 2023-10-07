#ifndef TREE_HPP
#define TREE_HPP

#include <string>
#include <stdexcept>

typedef struct NodeT {
    std::string expression;
    std::string operation;

    NodeT* left;
    NodeT* right;

    NodeT(std::string expression="", std::string operation="", NodeT* left=nullptr, NodeT* right=nullptr) 
    : expression(expression), operation(operation), left(left), right(right) {
    }

} NodeT;


enum Direction {
    ROOT,
    RIGHT, 
    LEFT
};


class ExceptionEmptyTree : public std::exception {
public:
    const char* what() const noexcept override {
        return "Tree is empty!";
    }
};

class InvalidOperationException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Invalid operation!";
    }
};

class Tree {
    public:
        Tree();
        ~Tree();

        void insert(Direction direction, std::string sub_string, std::string operation);
        
        void print();

    private:
        NodeT* _root;

}


#endif