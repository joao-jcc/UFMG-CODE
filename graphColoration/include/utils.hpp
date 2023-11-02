//
// Created by João Costa on 30/10/23.
//

#ifndef UTILS_HPP
#define UTILS_HPP

#include "linkedList.hpp"

int read_graph(LinkedList<int>**& graph) {
    int n_vertex; // Number of vertices in the graph
    std::cin >> n_vertex;
    graph = new LinkedList<int>*[n_vertex]; // array of pointers to LinkedLists;

    for (int i = 0; i < n_vertex; ++i) {
        graph[i] = new LinkedList<int>();

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

void print_graph(LinkedList<int>**& graph, int n_vertex) {
    std::cout << "Printing the graph:" << std::endl;
    for (int i = 0; i < n_vertex; ++i) {
        LinkedList<int>* list = graph[i];

        std::cout << "LL ID: " << list->get_id() << " Color: " << list->get_color() << " Elements: ";
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


void swap_vertex(LinkedList<int>*& vertex1, LinkedList<int>*& vertex2) {

    LinkedList<int>* temp = vertex1;
    vertex1 = vertex2;
    vertex2 = temp;

}


#endif //UTILS_HPP
