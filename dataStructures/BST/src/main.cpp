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
    tree.get_root()->left->right->print();

    return 0;
}