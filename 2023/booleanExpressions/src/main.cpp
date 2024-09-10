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

    // Verificar a validade dos argumentos de linha de comando
    if ((!evaluation && !satisfiability) || (evaluation && satisfiability) || optind + 2 != argc) {
        std::cerr << "Uso: " << argv[0] << " [-a xor -s] fórmula valoração" << std::endl;
        return 1;
    }

    std::string formula = argv[optind];
    std::string valuation = argv[optind + 1];

    // Resolver o problema especificado
    if (evaluation) {
        // Avaliar a expressão lógica e imprimir o resultado
        bool result = evaluate_expression(formula, valuation);
        std::cout << result << std::endl;
    } else if (satisfiability) {
        // Realizar a satisfabilidade da fórmula e imprimir a árvore
        Tree tree(formula, valuation);
        tree.solve();
    }

    return 0;
}
