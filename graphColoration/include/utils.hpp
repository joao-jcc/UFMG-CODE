// Arquivo de cabeçalho "utils.hpp" - Contém funções utilitárias para manipulação de grafos

#ifndef UTILS_HPP
#define UTILS_HPP

#include "linkedList.hpp"  // Inclui o arquivo de cabeçalho que contém a implementação da lista encadeada
#include "sort.hpp"        // Inclui o arquivo de cabeçalho que contém as funções de ordenação

// Função para ler um grafo a partir da entrada padrão
inline int read_graph(Vertex<int>**& graph) {
    int n_vertex; // Número de vértices no grafo
    std::cin >> n_vertex;
    graph = new Vertex<int>*[n_vertex]; // Array de ponteiros para vértices

    for (int i = 0; i < n_vertex; ++i) {
        graph[i] = new Vertex<int>();  // Cria um novo vértice

        int degree;
        std::cin >> degree;
        for (int j = 0; j < degree; ++j) {
            int neighbor;
            std::cin >> neighbor;
            graph[i]->append(neighbor);  // Adiciona vizinhos à lista de adjacência do vértice
        }
    }

    for (int i = 0; i < n_vertex; ++i) {
        unsigned color;
        std::cin >> color;
        graph[i]->set_color(color);  // Define a cor de cada vértice
    }

    return n_vertex;
}

// Função para imprimir o grafo na saída padrão
inline void print_graph(Vertex<int>**& graph, int n_vertex) {
    std::cout << "Printing the graph:" << std::endl;
    for (int i = 0; i < n_vertex; ++i) {
        Vertex<int>* list = graph[i];

        std::cout << "(" << list->get_id() << "|" << list->get_color() << ") ";
        Node<int>* temp = list->get_first();

        while (temp != nullptr) {
            std::cout << temp->data;
            if (temp->next != nullptr) {
                std::cout << " -> ";
            }
            temp = temp->next;
        }
        std::cout << std::endl;
    }
}

// Função para imprimir os identificadores dos vértices do grafo
inline void print_graph_id(Vertex<int>**& graph, int n_vertex) {
    for (int i = 0; i < n_vertex; ++i) {
        std::cout << " " << graph[i]->get_id();
    }
    std::cout << std::endl;
}

// Função para validar o grafo verificando se os vértices atendem aos critérios especificados
inline bool validate_graph(Vertex<int>**& graph, int n_vertex) {
    for (int i = 0; i < n_vertex; ++i) {
        bool status = graph[i]->validate(graph);
        if (!status) {
            return false;
        }
    }
    return true;
}

// Função de critério para ordenação de vértices
inline bool criterium(Vertex<int>*& vertex1, Vertex<int>*& vertex2) {
    // Critério de cor
    if (vertex1->get_color() > vertex2->get_color()) {
        return true;
    }

    // Critério de ID se as cores forem iguais
    if ((vertex1->get_color() == vertex2->get_color()) && (vertex1->get_id() > vertex2->get_id())) {
        return true;
    }

    return false;
}

// Função para trocar os vértices
inline void swap_vertex(Vertex<int>*& vertex1, Vertex<int>*& vertex2) {
    Vertex<int>* temp = vertex1;
    vertex1 = vertex2;
    vertex2 = temp;
}

// Função para liberar a memória alocada para o grafo
inline void free_graph(Vertex<int>** graph, int n_vertex) {
    for (int i = 0; i < n_vertex; ++i) {
        delete graph[i];
    }
    delete[] graph;
}

#endif // UTILS_HPP
