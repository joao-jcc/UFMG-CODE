//
// Created by João Costa on 30/10/23.
//

#ifndef UTILS_HPP
#define UTILS_HPP

#include "linkedList.hpp"
#include "sort.hpp"

int read_graph(Vertex<int>**& graph) {
    int n_vertex; // Number of vertices in the graph
    std::cin >> n_vertex;
    graph = new Vertex<int>*[n_vertex]; // array of pointers to Vertex;

    for (int i = 0; i < n_vertex; ++i) {
        graph[i] = new Vertex<int>();

        int degree;
        std::cin >> degree;
        for (int j = 0; j < degree; ++j) {
            int neighbor;
            std::cin >> neighbor;
            graph[i]->append(neighbor);
        }
    }

    for (int i=0; i < n_vertex; ++i) {
        unsigned color;
        std::cin >> color;
        graph[i]->set_color(color);
    }

    return n_vertex;

}

void print_graph(Vertex<int>**& graph, int n_vertex) {
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

void print_graph_id(Vertex<int>**& graph, int n_vertex) {
    for (int i = 0; i < n_vertex; ++i) {
        std::cout << " " << graph[i]->get_id();
    }
    std::cout << std::endl;
}


bool validate_graph(Vertex<int>**& graph, int n_vertex) {
    for (int i=0; i < n_vertex; ++i) {
        bool status = graph[i]->validate(graph);
        if (!status) {
            return false;
        }
    }

    return true;
}

bool criterium(Vertex<int>*& vertex1, Vertex<int>*& vertex2) {
    // color criterium
    if (vertex1->get_color() > vertex2->get_color()) {
        return true;
    };

    // id criterium
    if ((vertex1->get_color() == vertex2->get_color()) && (vertex1->get_id() > vertex2->get_id())) {
        return true;
    }

    return false;
}


void swap_vertex(Vertex<int>*& vertex1, Vertex<int>*& vertex2) {

    Vertex<int>* temp = vertex1;
    vertex1 = vertex2;
    vertex2 = temp;

}


#endif //UTILS_HPP
