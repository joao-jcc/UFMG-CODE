#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>
#include <string>
#include  "utils.hpp"


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

    void print(bool option=false) {
        std::cout << "--nodeT--" << std::endl;
        std::cout << "valuation: " << valuation << std::endl;
        std::cout << "function: " << func_to_str(function) << std::endl;
        std::cout << "flag: " << bool_to_str(flag) << std::endl;
        if (option) {
            std::cout << "parent: " << parent << std::endl;
            std::cout << "right: " << right << std::endl;
            std::cout << "left: " << left << std::endl;
        }


    };

    bool is_leaf() {
        return function == LEAF;
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
        void _expand(Tuple tuple, Direction direction, int depth);
                Stack<NodeT*> _traversal_stack();
        NodeT* _walk_to(NodeT* temp, Direction direction);

        Tuple _find_operator(std::string valuation, int& index);

};

#endif