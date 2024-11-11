// graphW.hpp
#ifndef GRAPHW_HPP
#define GRAPHW_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

// Estrutura para grafos com nomes (strings)
struct GGTWord {
    vector<vector<int>> g;
    vector<vector<int>> gt;
    int N;
    unordered_map<string, int> nameToIndex;
    vector<string> indexToName;
};

// Função para ler o grafo direcionado de um arquivo de palavras
GGTWord readWordGraph(const string& inputFile);

// Função para imprimir o grafo direcionado usando os nomes originais
void printWordGraph(const GGTWord& ggt);

#endif // GRAPHW_HPP
