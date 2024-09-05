#include "system.hpp"

System::System() : equations_(std::vector<Equation>()) {

}


System::~System() {

}


void System::print(std::string separator, int max_coef_length, int max_operation_length) {
    // Imprimir cada equação, alinhando de acordo com o tamanho máximo
    for (Equation& equation : equations_) {
        // Define a largura máxima do campo para a operação
        std::string operation_str = equation.get_last_operation();
        std::stringstream formatted_operation;
        formatted_operation << std::left << std::setw(max_operation_length) << operation_str;

        // Imprime a equação com o texto da última operação alinhado
        printf("%s  %s\n", equation.to_string(max_coef_length).c_str(), formatted_operation.str().c_str());
    }

    // Imprime o separador
    printf("%s", separator.c_str());
}


static bool compare_equations(Equation& e1, Equation& e2) {
    return e1.get_pivot_pos() < e2.get_pivot_pos();
}

void System::sort() {
    std::sort(equations_.begin(), equations_.end(), compare_equations);
}


void System::add(Equation& equation) {
    equations_.push_back(equation);
    // ordeno as equações com base no pivot
    sort();
}

void System::pivot_to_one(int index) {
    if (index >= equations_.size() || index < 0) {
        printf("Index Inválido!\n");
        exit(1);
    }

    if (equations_[index].is_null()) {
        printf("Não há pivô em equação nula!\n");
        return;
    }

    Equation e1 = equations_[index];
    int pivot_pos = e1.get_pivot_pos();
    Fraction pivot = e1.get_coef(pivot_pos);

    if ( pivot.get('n') == 1 && pivot.get('d') == 1 && pivot.get('s') == 1 ) {return;}
    equations_[index] = e1 * pivot.invert();
}

void System::solve(bool print_flag) {
    // loop por todas as equações
    for (int i = 0; i < equations_.size(); ++i) {

        if (print_flag) {print("\n");}

        // se a equação for nula a solução se encerra
        if (equations_[i].is_null()) {return;}

        // Pivotar a equação corrente para que o pivot seja 1
        pivot_to_one(i);
        equations_[i].set_last_operation("pivot_to_one" + std::to_string(i + 1));

        if (print_flag) {
            print("\n");
        }

        int pivot_pos = equations_[i].get_pivot_pos();

        // Loop para eliminar as outras equações
        for (int j = 0; j < equations_.size(); ++j) {
            if (i == j) {continue;}  // Pule a equação pivot

            // Calcula o coeficiente para multiplicar a equação pivot
            Fraction coef = equations_[j].get_coef(pivot_pos) * -1;
            Equation temp = equations_[i] * coef;

            // Substitui a equação j para zerar o coeficiente da posição do pivot
            equations_[j] = equations_[j] + temp;
            equations_[j].set_last_operation("eq." + std::to_string(j + 1) + " = eq." + std::to_string(j + 1) + " + " + coef.to_string() + " * eq." + std::to_string(i + 1));
        }
    }

    if (print_flag) {
        print("");  // Imprime o estado final
    }
}
