#include <iostream>
#include "tree.hpp"

int main(void) {

    std::string test = "1a1ea";
    Tree tree(test);

    std::cout << "---MAIN---" << std::endl;
    std::cout << test << std::endl;
    std::cout << tree.get_depth() << std::endl;


    tree.get_root()->print();

    tree.get_root()->left->print();

    tree.get_root()->left->left->print();
    tree.get_root()->left->right->print(true);

    tree.get_root()->left->left->left->print();
    tree.get_root()->left->left->right->print();
    tree.get_root()->left->right->left->print();
    tree.get_root()->left->right->right->print();


    return 0;
}