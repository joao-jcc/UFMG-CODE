#include "tree.hpp"

Tree::Tree() : _root(nullptr) {

}

Tree::~Tree() {

}


void Tree::insert(Direction direction, std::string sub_string, std::string operation) {
    if ((direction == ROOT && _root != nullptr) || (direction != ROOT && _root == nullptr)) {
        throw(InvalidOperationException());
    }

    if (direction == ROOT) {
        _root = new NodeT(sub_string, operation);
        return;
    }

    NodeT* temp = _root;

    while (temp->right == nullptr) {
        
    }
    NodeT* new_node = new NodeT(expression, operation);


    else {
        NodeT* current = _root;
        NodeT* parent = current;

        while()
    }
}