#include "graph.hpp"

Graph::Graph() {
    _read();
}

// Método para leitura do grafo a partir da entrada padrão
void Graph::_read() {
    size_t M; 
    std::cin >> method;
    std::cin >> N >> M;

    matrix = std::vector<std::vector<size_t>>(N, std::vector<size_t>(N, UNDEFINED));
    name_to_index = std::map<std::string, size_t>(); 
    index_to_name = std::vector<std::string>(N);

    size_t index = 0;
    for (size_t edge = 0; edge < M; ++edge) {
        std::string city1, city2;
        size_t weight;
        std::cin >> city1 >> city2 >> weight; // Lê os dados da aresta
        
        // Se a cidade ainda não foi mapeada, atribui um novo índice
        if (name_to_index.find(city1) == name_to_index.end()) {
            name_to_index[city1] = index++;
        }
        if (name_to_index.find(city2) == name_to_index.end()) {
            name_to_index[city2] = index++;
        }

        // Obtém os índices das cidades
        size_t u = name_to_index[city1];
        size_t v = name_to_index[city2];
        index_to_name[u] = city1;
        index_to_name[v] = city2;

        // Atualiza a matriz de adjacência com o peso da aresta
        matrix[u][v] = weight;
        matrix[v][u] = weight;
    }
}
