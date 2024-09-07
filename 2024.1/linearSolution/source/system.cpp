#include "system.hpp"

System::System() : equations_(std::vector<Equation>()) {

}


System::~System() {

}


void System::print(std::string separator, int max_coef_length) {
    // Imprime o separador
    printf("%s", separator.c_str());

    // Imprimir cada equação, alinhando de acordo com o tamanho máximo
    for (Equation& equation : equations_) {
        // Define a largura máxima do campo para a operação

        // Imprime a equação com o texto da última operação alinhado
        printf("%s\n", equation.to_string(max_coef_length).c_str());
    }

    printf("\n");
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


void System::solve() {
    print("BEGIN:\n");

    // loop por todas as equações
    for (int i = 0; i < equations_.size(); ++i) {
        // se a equação for nula, a solução se encerra
        if (equations_[i].is_null()) {break;}

        // Pivotar a equação corrente para que o pivot seja 1
        equations_[i] = equations_[i].normalize();
        
        print("NORMALIZE\n"); // novo sistema equação normalizada

        int pivot_pos = equations_[i].get_pivot_pos();

        // Loop para eliminar as outras equações
        for (int j = 0; j < equations_.size(); ++j) {
            if (i == j || equations_[j].is_null()) {continue;} // pula a equação pivot ou equação que seja nula

            // Calcula o coeficiente para multiplicar a equação pivot
            Fraction coef = equations_[j].get_coef(pivot_pos) * -1;
            Equation temp = equations_[i] * coef;

            // Substitui a equação j para zerar o coeficiente da posição do pivot
            equations_[j] = equations_[j] + temp;
            print("LINEAR COMBINATION\n"); // pint após combinação linear
        }

        // Ordena as equações (se necessário)
        sort();
        print("SORT:\n");
    }

    print("END:\n");
}

