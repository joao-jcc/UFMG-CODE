#include <iostream>
#include <getopt.h>
#include <string>

#include "stack.hpp"
#include "utils.hpp"
#include "tree.hpp"

int main(int argc, char* argv[]) {
    int option;
    bool evaluation = false;
    bool satisfiability = false;

    // Processar os argumentos de linha de comando usando getopt
    while ((option = getopt(argc, argv, "as")) != -1) {
        switch (option) {
            case 'a':
                evaluation = true;
                break;
            case 's':
                satisfiability = true;
                break;
            default:
                std::cerr << "Uso: " << argv[0] << " [-a xor -s] fórmula valoração" << std::endl;
                return 1;
        }
    }

    if ((!evaluation && !satisfiability) || (evaluation && satisfiability) || optind+2 != argc) {
        std::cerr << "Uso: " << argv[0] << " [-a xor -s] fórmula valoração" << std::endl;
        return 1;
    }

    std::string formula = argv[optind];
    std::string valuation = argv[optind + 1];
    // Resolver o problema especificado
    if (evaluation) {
        bool result = evaluate_expression(formula, valuation);
        std::cout << result  << std::endl;

    }

    else if(satisfiability) {
        Tree tree(formula, valuation);
        tree.print(tree.get_root(), tree.get_depth(), 'o');
        tree.solve();

    }

    return 0;
}
