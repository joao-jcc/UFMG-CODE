#include <iostream>
#include "linkedList.hpp"
#include "utils.hpp"
#include "sort.hpp"

int main() {

    // Opção de ordenação
    char sort_option;
    std::cin >> sort_option;

    // Ler o grafo
    Vertex<int>** graph = nullptr;
    int n_vertex = read_graph(graph);

    // Validar o grafo
    bool validation = validate_graph(graph, n_vertex);

    if (!validation) {
        std::cout << "Grafo inválido." << std::endl;
        return 0;
    } else {
        // Ordenar o grafo
        sort(graph, n_vertex, sort_option);

        // Imprimir a validação
        std::cout << "Grafo válido." << std::endl;

        // Imprimir o grafo ordenado
        print_graph_id(graph, n_vertex);
    }

    // Liberar a memória alocada para o grafo
    free_graph(graph, n_vertex);

    return 0;
}
