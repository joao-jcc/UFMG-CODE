#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>
#include <string>
#include  "utils.hpp"


typedef struct NodeT {
    std::string formula;
    Function function;
    

    NodeT* parent;
    NodeT* left;
    NodeT* right;
    bool flag;

    NodeT(std::string formula = "", Function function = LEAF, 
        NodeT* parent = nullptr, NodeT* right = nullptr, NodeT* left = nullptr, bool flag = false) :
        formula(formula), function(function), parent(parent), left(left), right(right), flag(flag) {
    }


    void print(bool option=false) {
        std::cout << "--nodeT--" << std::endl;
        std::cout << "formula: " << formula << std::endl;
        std::cout << "function: " << func_to_str(function) << std::endl;
        if (option) {
            std::cout << "flag: " << bool_to_str(flag) << std::endl;
            std::cout << "parent: " << parent << std::endl;
            std::cout << "right: " << right << std::endl;
            std::cout << "left: " << left << std::endl;
        }


    };

} NodeT;


class Tree {
    public:
        Tree(std::string base_formula);
        ~Tree();

        NodeT* get_root() {
            return _root;
        }

        int get_depth() {
            return _depth;
        }

        void solve();

    private:
        NodeT* _root;
        int _depth;
        std::string _base_formula;

        void _build();
        void _expand(Tuple tuple, Direction direction);
                Stack<NodeT*> _traversal_stack();
        NodeT* _walk_to(NodeT* temp, Direction direction);

};

#endif