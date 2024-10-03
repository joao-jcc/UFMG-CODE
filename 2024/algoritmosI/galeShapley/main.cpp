#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <fstream>
#include <sstream>



void read_matrix(std::string filepath, std::vector<std::vector<int> > &matrix) {
    // input file stream
    std::ifstream file(filepath);

    if (!file.is_open()) {
        std::cerr << "Não foi possível abrir o arquivo: " << filepath << std::endl;
    }

    std::string line;
    while(std::getline(file, line)) {
        std::vector<int> row;
        // input string stream
        std::istringstream iss(line);
        int index;
        while(iss >> index) {
            row.push_back(index);
        };
        matrix.push_back(row);      
    }

}


void print_matrix(std::vector<std::vector<int> >& matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();

    for (int i=0; i < rows; ++i) {

        for (int j=0; j < cols; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}


void swap(std::vector<int>& vec, int i, int j) {
    int temp = vec[j];
    vec[j] = vec[i];
    vec[i] = temp;
}

// bubble_sort but a count_sort is better
std::vector<int> sort(std::vector<int> vec) {
    std::vector<int> vec_range; for (int i=0; i < vec.size(); ++i) {vec_range.push_back(i);}

    for (int i=0; i < vec.size(); ++i) {

        for (int j=0; j < vec.size()-i-1; ++j) {
            if (vec[j] > vec[j+1]) {
                swap(vec, j, j+1);
                swap(vec_range, j, j+1);
            }
        }
    }

    return vec_range;
}


// ordena as preferências dos alunos: o index do hospital indica sua pontuação-preferência
std::vector<std::vector<int> > genSIndex(std::vector<std::vector<int> > sPreferences) {

    std::vector<std::vector<int> > sIndexPreferences;
    for (int i=0; i < sPreferences.size(); ++i) {
        sIndexPreferences.push_back( sort(sPreferences[i]) );
    }

    return sIndexPreferences;
}


int main(void) {
    // hPreferences
    std::vector<std::vector<int> > hPreferences; read_matrix("data/h0.txt", hPreferences);
    int size = hPreferences.size();

    // sPreferences
    std::vector<std::vector<int> > sPreferences; read_matrix("data/s0.txt", sPreferences);

    // sIndexPreferences
    std::vector<std::vector<int> > sIndexPreferences = genSIndex(sPreferences);

    std::cout << "sIndexPreferences!" << std::endl;
    print_matrix(sIndexPreferences);

    // hUnmatched: inicializa todos os hospitais (0, .., size-1) como unmatched
    std::stack<int> hUnmatched; for (int i=0; i < size; ++i) {hUnmatched.push(i);}


    // hPointers: pointer para o estudante de maior preferência do hospital
    std::vector<int> hPointers(size, 0);

    // countOffers: conta número de ofertas de hospitais a estudantes, N**2 indica que todas as proposta foram feitas
    int countOffers = 0; int countHMatched = 0;
    
    // Matches: -1 indica que hospital ou aluno não foram alocados
    std::vector<int> hMatch, sMatch; for (int i=0; i < size; ++i) {hMatch.push_back(-1); sMatch.push_back(-1);}
    
    while (!hUnmatched.empty()) {
        // hospital unmatched a propor uma oferta
        int h = hUnmatched.top(); hUnmatched.pop();

        int s = hPreferences[h][hPointers[h]++];

        std::cout << "hPointers" << std::endl;
        for (int i=0; i < size; ++i) {
            std::cout << hPointers[i] << " ";
        }
        std::cout << std::endl;

        // estudante unmatched
        if (sMatch[s] == -1) {
            sMatch[s] = h; hMatch[h] = s;

        }
        else if (sIndexPreferences[s][h] < sIndexPreferences[s][sMatch[s]]) {

            hMatch[sMatch[s]] = -1; hUnmatched.push(sMatch[s]);// hospital volta a ser unmatched
            sMatch[s] = h; hMatch[h] = s;

        }
        else {

            hUnmatched.push(h);

        }

        countOffers++; 
    }

    std::cout << "hMatch:" << std::endl;
    for (int i=0; i < size; ++i) {
            std::cout << hMatch[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "sMatch:" << std::endl;
    for (int i=0; i < size; ++i) {
        std::cout << sMatch[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}