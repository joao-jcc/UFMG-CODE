//
// Created by João Costa on 02/11/23.
//

#ifndef SORT_HPP
#define SORT_HPP

#include "linkedList.hpp"
#include "utils.hpp"

void bubble_sort(LinkedList<int>**& graph, int n_vertex) {
    for (int i=0; i < n_vertex; ++i) {

        for (int j=0; j < n_vertex-i; ++j) {

            if (graph[j]->get_color() > graph[j+1]->get_color()) {
                swap_vertex(graph[j], graph[j+1]);

            }

        }
    }
}


void bubble_sort_opt(LinkedList<int>**& graph, int n_vertex) {
    for (int i=0; i < n_vertex; ++i) {

        bool swapped = false;
        for (int j=0; j < n_vertex-i; ++j) {

            if (graph[j]->get_color() > graph[j+1]->get_color()) {
                swap_vertex(graph[j], graph[j+1]);
                swapped = true;
            }

        }

        if (!swapped) {return;}

    }
}


void selection_sort(LinkedList<int>**& graph, int n_vertex) {
    for (int i=0; i < n_vertex-1; ++i) {

        unsigned min = i;
        for (int j=i+1; j < n_vertex; ++j) {

            if (graph[j]->get_color() < graph[min]->get_color()) {
                min = j;
            }

        }

        swap_vertex(graph[i], graph[min]);

    }
}


void insertion_sort(LinkedList<int>**& graph, int n_vertex) {
    for (int i=1; i < n_vertex; ++i) {

        LinkedList<int>* current = graph[i];
        int j = i - 1;

        while((j>=0) && (current->get_color() < graph[j]->get_color())) {
            graph[j+1] = graph[j];
            --j;
        }

        graph[j+1] = current;

    }
}


void quick_sort(LinkedList<int>**& graph, int n_vertex) {

}


void merge_sort(LinkedList<int>**& graph, int n_vertex) {

}


void heap_sort(LinkedList<int>**& graph, int n_vertex) {

}

#endif //SORT_HPP
