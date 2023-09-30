#include <iostream>
#include <getopt.h>
#include <string>

#include "stack.hpp"
#include "utils.hpp"

int main(int argc, char* argv[]) {
    int option;
    std::string formula;
    std::string valuation;

    bool evaluate_problem = false;
    bool satisfiability_problem = false;

    // Processar os argumentos de linha de comando usando getopt
    while ((option = getopt(argc, argv, "as")) != -1) {
        switch (option) {
            case 'a':
                evaluate_problem = true;
                break;
            case 's':
                satisfiability_problem = true;
                break;
            default:
                std::cerr << "Uso: " << argv[0] << " [-a | -s] fórmula valoração" << std::endl;
                return 1;
        }
    }

    // Verificar se exatamente um problema foi especificado
    if ((evaluate_problem && satisfiability_problem) || (!evaluate_problem && !satisfiability_problem)) {
        std::cerr << "Especifique exatamente um problema (-a ou -s)." << std::endl;
        return 1;
    }

    // Obter a fórmula e a valoração dos argumentos restantes
    if (optind + 2 != argc) {
        std::cerr << "Uso: " << argv[0] << " [-a | -s] fórmula valoração" << std::endl;
        return 1;
    }

    formula = argv[optind];
    valuation = argv[optind + 1];
    // Resolver o problema especificado
    if (evaluate_problem) {        
        bool result = evaluate_expression(formula, valuation);
        std::cout << "Resultado da avaliação da expressão: " << result << std::endl;
    } 

    return 0;
}
