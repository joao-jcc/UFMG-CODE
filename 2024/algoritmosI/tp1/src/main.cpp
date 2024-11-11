#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>
#include "graphW.hpp"
#include "capital.hpp"
#include "batallion.hpp"

int main() {
    for (int i = 1; i <= 9; ++i) {
        // Construir o caminho do arquivo com zeros à esquerda (e.g., "input01.txt")
        std::ostringstream filename;
        filename << "data/teste/inputs/testCase0" << i << ".txt";
        
        // Carregar o grafo a partir de um arquivo de entrada
        GGTWord ggt = readWordGraph(filename.str());

        // Obter informações da capital a partir do grafo
        InfoCapital infoc = getCapital(ggt.g, ggt.N);

        // Executar o algoritmo de Kosaraju para componentes fortemente conectados
        InfoK infok = kosaraju(ggt.g, ggt.gt, ggt.N);

        // Obter os batalhões com base nas informações da capital e componentes
        std::vector<int> batallions = getBatallions(infoc, infok);

        // Exibir a capital
        std::cout << ggt.indexToName[infoc.capital] << std::endl;

        // Exibir os batalhões, excluindo a capital
        std::cout << batallions.size() - 1 << std::endl;
        for (int battalion : batallions) {
            if (battalion == -1 || battalion == infoc.capital) continue;
            std::cout << ggt.indexToName[battalion] << std::endl;
        }
        
        std::cout << std::endl; // Separador entre testes
    }
    
    return 0;
}
