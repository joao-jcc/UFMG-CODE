#include "system.hpp"

System::System() : equations_(std::vector<Equation>()), count_equations_(0) {

}


System::~System() {

}


void System::read() {
    std::cout << "Digite o número de equações: ";
    int n_equations; std::cin >> n_equations;

    std::cout << "Digite o número de variáveis: ";
    int n_variables; std::cin >> n_variables;

    for (int i=0; i < n_equations; ++i) {
        std::cout << "Digite a eq." << i + 1 << "no formato coef_1 coef_2 ... coef_n | bcoef" << std::endl;
        std::vector<Fraction> coefs;
        
        // lendo coeficientes
        for (int j=0; j < n_variables; ++j) {
            std::string coef_str; std::cin >> coef_str;
            Fraction f; f.parse(coef_str);
            coefs.push_back(f); // chamada polimórfica Fraction -> FractionParse
        }

        // lendo termo independente
        std::string bcoef_str; std::cin >> bcoef_str; std::cin >> bcoef_str;
        Fraction bcoef; bcoef.parse(bcoef_str);

        Equation eq; eq.config(coefs, bcoef);
        equations_.push_back(eq);
    }
}


void System::read(std::string path) {
    std::ifstream file;
    file.open(path, std::ios::in);

    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo!" << std::endl;
        exit(1);
    }

    std::string line;

    while(getline(file, line)) {
        Equation e; e.parse(line); add(e);
    }
}


void System::print(std::string separator, int max_coef_length) {
    // Imprime o separador
    printf("%s", separator.c_str());

    // Imprimir cada equação, alinhando de acordo com o tamanho máximo
    for (Equation& equation : equations_) {
        // Define a largura máxima do campo para a operação

        // Imprime a equação com o texto da última operação alinhado
        printf("%s  %s\n", equation.to_string(max_coef_length).c_str(), equation.get_description().c_str());
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
    // incrementa o contador de equações
    ++count_equations_;

    // a equação tem uma descrição apenas no contexto do sistema
    equation.set_description("e" + std::to_string(count_equations_));

    // adiciono a equação no sistema
    equations_.push_back(equation);
}


void System::solve() {
    print("BEGIN:\n");
    // Ordena as equações (se necessário)
    sort();
    print("SORT:\n");

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