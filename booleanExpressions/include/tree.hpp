#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>
#include <string>
#include "stack.hpp"
#include "queue.hpp"
#include  "utils.hpp"


enum Function {
    AND, OR, LEAF
};

typedef struct Tuple {
    Function function;
    std::string sub_string;
} Tuple;




typedef struct NodeT {
    std::string valuation;
    Function function;
    bool flag;

    NodeT* left;
    NodeT* right;
  

    NodeT(std::string valuation = "", Function function = LEAF, bool flag = false, NodeT* right = nullptr, NodeT* left = nullptr) :
        valuation(valuation), function(function), flag(flag), left(left), right(right) {
    }

} NodeT;


class Tree {
    public:
        Tree(std::string formula, std::string valuation);
        ~Tree();

        void solve();

        void print(NodeT* node, int depth, char prefix = 'o');

        NodeT* get_root() {
            return _root;
        }

        int get_depth() {
            return _depth;
        }

    private:
        NodeT* _root;
        int _depth;
        
        std::string _formula;
        std::string _valuation;

        void _build();
        bool _evaluate(NodeT* operand1, NodeT* operand2, Function function);
        std::string _merge(NodeT* operand1, NodeT* operand2);

        Stack<NodeT*> _traversal_stack();
        
        Tuple _find_operator(std::string valuation, int& index);
};

#endif