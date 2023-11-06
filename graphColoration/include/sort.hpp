//
// Created by João Costa on 02/11/23.
//

#ifndef SORT_HPP
#define SORT_HPP

#include "linkedList.hpp"
#include "utils.hpp"
#include "heap.hpp"

void swap_vertex(Vertex<int>*& vertex1, Vertex<int>*& vertex2);

bool criterium(Vertex<int>*& vertex1, Vertex<int>*& vertex2);

void bubble_sort(Vertex<int>**& graph, int n_vertex) {
    for (int i=0; i < n_vertex; ++i) {

        for (int j=0; j < n_vertex-i-1; ++j) {

            if (criterium(graph[j], graph[j+1])) {
                swap_vertex(graph[j], graph[j+1]);

            }

        }
    }
}


void bubble_sort_opt(Vertex<int>**& graph, int n_vertex) {
    for (int i=0; i < n_vertex; ++i) {

        bool swapped = false;
        for (int j=0; j < n_vertex-i-1; ++j) {

            if (criterium(graph[j], graph[j+1])) {
                swap_vertex(graph[j], graph[j+1]);
                swapped = true;
            }

        }

        if (!swapped) {return;}

    }
}


void count_sort(Vertex<int>**& graph, int n_vertex) {
    int unique = 0;
    // check all different colors
    for (int i=1; i < n_vertex+1; ++i) {
        for (int j=0; j < n_vertex; ++j) {
            if (graph[j]->get_color() == i) {
                ++unique;
                break;
            }
        }
    }


    int count_arr[unique];
    for (int i=0; i<unique; ++i) {
        count_arr[i] = 0;
    }


    // counting colors in graph
    for (int i=0; i < n_vertex; ++i) {
        ++count_arr[graph[i]->get_color()-1];
    }

    // cumulative counting
    for (int i=1; i < unique; ++i) {
        count_arr[i] += count_arr[i-1];
    }

    // output
    Vertex<int>** output = new Vertex<int>*[n_vertex];
    for (int i=0; i < n_vertex; ++i) {
        output[i] = graph[i];
    }

    for (int i=n_vertex-1; i>=0; --i) {
        output[count_arr[graph[i]->get_color()-1]-1] = graph[i];
        --count_arr[graph[i]->get_color()-1];
    }

    for (int i=0; i < n_vertex; ++i) {
        graph[i] = output[i];
    }

    delete[] output;
}


void selection_sort(Vertex<int>**& graph, int n_vertex) {
    for (int i=0; i < n_vertex-1; ++i) {

        unsigned min = i;
        for (int j=i+1; j < n_vertex; ++j) {

            if (criterium(graph[min], graph[j])) {
                min = j;
            }

        }

        swap_vertex(graph[i], graph[min]);

    }
}


void insertion_sort(Vertex<int>**& graph, int n_vertex) {
    for (int i=1; i < n_vertex; ++i) {

        Vertex<int>* current = graph[i];
        int j = i - 1;


        while((j>=0) && (criterium(graph[j], current))) {
            graph[j+1] = graph[j];
            --j;
        }

        graph[j+1] = current;

    }
}


int partition(Vertex<int>**& graph, int p, int r) {
    Vertex<int> *x = graph[p];
    int i = p - 1;
    int j = r + 1;

    while (true) {
        do { --j; } while (criterium(graph[j], x));
        do { ++i; } while (criterium(x, graph[i]));

        if (i < j) {
            swap_vertex(graph[i], graph[j]);
        } else {
            return j;
        }
    }
}

void quick_sort(Vertex<int>** graph, int p, int r) {
    if (p < r) {
        int q = partition(graph, p, r);
        quick_sort(graph, p , q);
        quick_sort(graph, q+1, r);
    }
}

void quick_sort(Vertex<int>**& graph, int n_vertex) {
    quick_sort(graph, 0, n_vertex-1);
}


void merge(Vertex<int>** graph, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Vertex<int>** left_arr = new Vertex<int>*[n1];
    Vertex<int>** right_arr = new Vertex<int>*[n2];

    for (int i = 0; i < n1; i++) {
        left_arr[i] = graph[left + i];
    }
    for (int i = 0; i < n2; i++) {
        right_arr[i] = graph[mid + 1 + i];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (left_arr[i]->get_color() <= right_arr[j]->get_color()) {
            graph[k] = left_arr[i];
            i++;
        } else {
            graph[k] = right_arr[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        graph[k] = left_arr[i];
        i++;
        k++;
    }

    while (j < n2) {
        graph[k] = right_arr[j];
        j++;
        k++;
    }

    delete[] left_arr;
    delete[] right_arr;
}

void merge_sort_aux(Vertex<int>** graph, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort_aux(graph, left, mid);
        merge_sort_aux(graph, mid + 1, right);
        merge(graph, left, mid, right);
    }
}

void merge_sort(Vertex<int>** graph, int n_vertex) {
    merge_sort_aux(graph, 0, n_vertex - 1);
}

void heap_sort(Vertex<int>**& graph, int n_vertex) {
    Heap heap(n_vertex);

    // Insert the vertices into the heap
    for (int i = 0; i < n_vertex; ++i) {
        Tuple tuple = {graph[i]->get_color(), graph[i]->get_id()};
        heap.insert(tuple);
    }

    // Create a temporary array to store the sorted vertices
    Vertex<int>** sortedGraph = new Vertex<int>*[n_vertex];

    // Reorder the sortedGraph array based on the heap's removal order
    for (int i = 0; i < n_vertex; ++i) {
        int index = (int) heap.remove().id;
        sortedGraph[i] = graph[index];
    }

    // Copy the sorted vertices back to the original graph array
    for (int i = 0; i < n_vertex; ++i) {
        graph[i] = sortedGraph[i];
    }


    delete[] sortedGraph;
}


void sort(Vertex<int>**& graph, int n_vertex, char sort_option) {
    // sort
    switch (sort_option) {
        case 'b':
            bubble_sort(graph, n_vertex);
            break;

        case 's':
            selection_sort(graph, n_vertex);
            break;

        case 'i':
            insertion_sort(graph, n_vertex);
            break;

        case 'q':
            quick_sort(graph, n_vertex);
            break;

        case 'p':
            heap_sort(graph, n_vertex);
            break;

        case 'm':
            merge_sort(graph, n_vertex);
            break;

        case 'y':
            count_sort(graph, n_vertex);
            break;

        default:
            bubble_sort(graph, n_vertex);
            break;
    }
}


#endif //SORT_HPP
