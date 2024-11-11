// graphW.cpp
#include "graphW.hpp"

// Função para ler o grafo direcionado de um arquivo de palavras
GGTWord readWordGraph(const string& inputFile) {
    ifstream input(inputFile);
    if (!input) {
        cerr << "Erro ao abrir o arquivo!" << endl;
        exit(1);
    }

    int N, M;
    input >> N >> M; // Lê o número de vértices e arestas

    unordered_map<string, int> nameToIndex;
    vector<vector<int>> graph(N);
    vector<vector<int>> graphT(N);
    vector<string> indexToName(N);
    int nodeCount = 0;
    string name1, name2;

    for (int i = 0; i < M; ++i) {
        input >> name1 >> name2;
        
        // Se o nome não está no mapa, adiciona com um novo índice
        if (nameToIndex.find(name1) == nameToIndex.end()) {
            nameToIndex[name1] = nodeCount;
            indexToName[nodeCount++] = name1;
        }
        if (nameToIndex.find(name2) == nameToIndex.end()) {
            nameToIndex[name2] = nodeCount;
            indexToName[nodeCount++] = name2;
        }

        int idx1 = nameToIndex[name1];
        int idx2 = nameToIndex[name2];
        
        // Adiciona a aresta direcionada idx1 -> idx2
        graph[idx1].push_back(idx2);
        graphT[idx2].push_back(idx1);
    }

    return GGTWord{graph, graphT, N, nameToIndex, indexToName};
}

// Função para imprimir o grafo direcionado usando os nomes originais
void printWordGraph(const GGTWord& ggt) {
    int N = ggt.g.size();
    for (int i = 0; i < N; ++i) {
        cout << ggt.indexToName[i] << ": ";
        for (int v : ggt.g[i]) {
            cout << ggt.indexToName[v] << " ";
        }
        cout << endl;
    }
}
