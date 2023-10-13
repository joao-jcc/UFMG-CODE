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

enum Direction {
    RIGHT, LEFT
};

typedef struct Tuple {
    Function function;
    std::string sub_string;
} Tuple;




typedef struct NodeT {
    std::string valuation;
    Function function;
    bool flag;

    NodeT* parent;
    NodeT* left;
    NodeT* right;
  

    NodeT(std::string valuation = "", Function function = LEAF, bool flag = false,
        NodeT* parent = nullptr, NodeT* right = nullptr, NodeT* left = nullptr) :
        valuation(valuation), function(function), flag(flag), parent(parent), left(left), right(right) {
    }

} NodeT;


class Tree {
    public:
        Tree(std::string formula, std::string valuation);
        ~Tree();

        void solve();

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
        void _update_nodes(NodeT* n1, NodeT* n2, NodeT* n3, bool value);
        std::string _merge(std::string str1, std::string str2);

        Stack<NodeT*> _traversal_stack();
        
        Tuple _find_operator(std::string valuation, int& index);

};

#endif