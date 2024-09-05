#include "system.hpp"

System::System() : equations_(std::vector<Equation>()) {

}


System::~System() {

}


void System::print() {
    // Verificar o tamanho máximo de cada coeficiente em todo o sistema
    int max_coef_length = 0;
    for (Equation& equation : equations_) {
        for (Fraction& coef : equation.get_coefs()) {
            int length = coef.to_string().length();
            if (length > max_coef_length) {
                max_coef_length = length;
            }
        }
    }

    // Imprimir cada equação, alinhando de acordo com o tamanho máximo
    for (Equation& equation : equations_) {
        printf("%s  [pivot_index=%d]\n" , equation.to_string(max_coef_length).c_str(), equation.get_pivot());
    }
}

static bool compare_equations(Equation& e1, Equation& e2) {
    return e1.get_pivot() < e2.get_pivot();
}

void System::sort() {
    std::sort(equations_.begin(), equations_.end(), compare_equations);
}


void System::add(Equation& equation) {
    equations_.push_back(equation);
    // ordeno as equações com base no pivot
    sort();
}