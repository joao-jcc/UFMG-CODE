#ifndef TREE_HPP
#define TREE_HPP

#include <string>

typedef struct NodeT {
    // NodeT interno
    std::string operation;

    // 1's e 0's que valoram variáveis booleanas
    std::string evaluation;

    // Ponteiros para node filhos 
    NodeT* right;
    NodeT* left;

    // NodeT vazio
    NodeT() {
        operation = "";
        evaluation = "";
        rigth = nullptr;
        left = nullptr;
    }

} NodeT;


// árvore binária
class Tree {
    public:
        Tree();
        void insert(std::string valuation, std::string operation);
        void delete_all();
        
    private:
        NodeT* _root;
        
}

#endif