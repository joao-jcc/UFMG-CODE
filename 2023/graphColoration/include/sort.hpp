//
// Created by João Costa on 02/11/23.
//

#ifndef SORT_HPP
#define SORT_HPP

#include "linkedList.hpp"
#include "utils.hpp"
#include "heap.hpp"

inline void swap_vertex(Vertex<int>*& vertex1, Vertex<int>*& vertex2);

inline bool criterium(Vertex<int>*& vertex1, Vertex<int>*& vertex2);

// Função para ordenar um grafo representado por um array de ponteiros para vértices
// usando o algoritmo de ordenação Bubble Sort.
// Parâmetros:
// - graph: Array de ponteiros para vértices a ser ordenado.
// - n_vertex: Número de vértices no grafo.
inline void bubble_sort(Vertex<int>**& graph, int n_vertex) {
    // Loop externo para percorrer todo o array
    for (int i = 0; i < n_vertex; ++i) {
        // Loop interno para comparar e trocar os elementos
        for (int j = 0; j < n_vertex - i - 1; ++j) {
            // Verifica se o critério de ordenação é satisfeito
            if (criterium(graph[j], graph[j + 1])) {
                // Se sim, troca os vértices usando a função swap_vertex
                swap_vertex(graph[j], graph[j + 1]);
            }
        }
    }
}


// bubble sort com flag de otimização
//inline void bubble_sort_opt(Vertex<int>**& graph, int n_vertex) {
//    for (int i=0; i < n_vertex; ++i) {
//
//        bool swapped = false;
//        for (int j=0; j < n_vertex-i-1; ++j) {
//
//            if (criterium(graph[j], graph[j+1])) {
//                swap_vertex(graph[j], graph[j+1]);
//                swapped = true;
//            }
//
//        }
//
//        if (!swapped) {return;}
//
//    }
//}


// count sort com contagem de cores únicas
// inline void count_sort(Vertex<int>**& graph, int n_vertex) {
//     int unique = 0;
//     // check all different colors
//     for (int i=1; i < n_vertex+1; ++i) {
//         for (int j=0; j < n_vertex; ++j) {
//             if (graph[j]->get_color() == i) {
//                 ++unique;
//                 break;
//             }
//         }
//     }


//     int count_arr[unique];
//     for (int i=0; i<unique; ++i) {
//         count_arr[i] = 0;
//     }


//     // counting colors in graph
//     for (int i=0; i < n_vertex; ++i) {
//         ++count_arr[graph[i]->get_color()-1];
//     }

//     // cumulative counting
//     for (int i=1; i < unique; ++i) {
//         count_arr[i] += count_arr[i-1];
//     }

//     // output
//     Vertex<int>** output = new Vertex<int>*[n_vertex];
//     for (int i=0; i < n_vertex; ++i) {
//         output[i] = graph[i];
//     }

//     for (int i=n_vertex-1; i>=0; --i) {
//         output[count_arr[graph[i]->get_color()-1]-1] = graph[i];
//         --count_arr[graph[i]->get_color()-1];
//     }

//     for (int i=0; i < n_vertex; ++i) {
//         graph[i] = output[i];
//     }

//     delete[] output;
// }


// Função para ordenar um grafo representado por um array de ponteiros para vértices
// usando o algoritmo de ordenação Counting Sort.
// Parâmetros:
// - graph: Array de ponteiros para vértices a ser ordenado.
// - n_vertex: Número de vértices no grafo.
inline void count_sort(Vertex<int>**& graph, int n_vertex) {
    // Array para contar a ocorrência de cada cor
    int count_arr[n_vertex];
    for (int i = 0; i < n_vertex; ++i) {
        count_arr[i] = 0;
    }

    // Contagem das cores no grafo
    for (int i = 0; i < n_vertex; ++i) {
        ++count_arr[graph[i]->get_color() - 1];
    }

    // Contagem cumulativa
    for (int i = 1; i < n_vertex; ++i) {
        count_arr[i] += count_arr[i - 1];
    }

    // Criação de um array de saída
    Vertex<int>** output = new Vertex<int>*[n_vertex];
    for (int i = 0; i < n_vertex; ++i) {
        output[i] = graph[i];
    }

    // Preenchimento do array de saída usando a contagem cumulativa
    for (int i = n_vertex - 1; i >= 0; --i) {
        output[count_arr[graph[i]->get_color() - 1] - 1] = graph[i];
        --count_arr[graph[i]->get_color() - 1];
    }

    // Copia o array ordenado de volta para o array original
    for (int i = 0; i < n_vertex; ++i) {
        graph[i] = output[i];
    }

    // Libera a memória alocada para o array de saída
    delete[] output;
}




// Função para ordenar um grafo representado por um array de ponteiros para vértices
// usando o algoritmo de ordenação Selection Sort.
// Parâmetros:
// - graph: Array de ponteiros para vértices a ser ordenado.
// - n_vertex: Número de vértices no grafo.
inline void selection_sort(Vertex<int>**& graph, int n_vertex) {
    // Loop externo para percorrer o array
    for (int i = 0; i < n_vertex - 1; ++i) {
        // Assume que o elemento atual é o mínimo
        unsigned min = i;

        // Loop interno para encontrar o índice do mínimo
        for (int j = i + 1; j < n_vertex; ++j) {
            // Verifica se o critério de ordenação é satisfeito
            if (criterium(graph[min], graph[j])) {
                // Se sim, atualiza o índice do mínimo
                min = j;
            }
        }

        // Troca o elemento atual com o mínimo encontrado
        swap_vertex(graph[i], graph[min]);
    }
}



// Função para ordenar um grafo representado por um array de ponteiros para vértices
// usando o algoritmo de ordenação Insertion Sort.
// Parâmetros:
// - graph: Array de ponteiros para vértices a ser ordenado.
// - n_vertex: Número de vértices no grafo.
inline void insertion_sort(Vertex<int>**& graph, int n_vertex) {
    // Loop externo para percorrer o array
    for (int i = 1; i < n_vertex; ++i) {
        // Armazena o vértice atual que será movido para a posição correta
        Vertex<int>* current = graph[i];
        int j = i - 1;

        // Loop interno para mover os elementos maiores que o vértice atual para a direita
        while ((j >= 0) && (criterium(graph[j], current))) {
            graph[j + 1] = graph[j];
            --j;
        }

        // Insere o vértice atual na posição correta
        graph[j + 1] = current;
    }
}



// Função para realizar a partição em uma sub-sequência do array durante o Quick Sort.
// Parâmetros:
// - graph: Array de ponteiros para vértices a ser ordenado.
// - p: Índice do primeiro elemento da sub-sequência.
// - r: Índice do último elemento da sub-sequência.
// Retorna o índice onde a partição foi feita.
inline int partition(Vertex<int>**& graph, int p, int r) {
    Vertex<int>* x = graph[p];  // Elemento pivô
    int i = p - 1;
    int j = r + 1;

    // Loop para realizar a partição
    while (true) {
        // Encontra elemento menor que o pivô
        do { --j; } while (criterium(graph[j], x));
        // Encontra elemento maior que o pivô
        do { ++i; } while (criterium(x, graph[i]));

        // Troca os elementos se necessário
        if (i < j) {
            swap_vertex(graph[i], graph[j]);
        } else {
            return j;  // Retorna o índice onde a partição foi feita
        }
    }
}

// Função principal do Quick Sort para ordenar uma sub-sequência do array.
// Parâmetros:
// - graph: Array de ponteiros para vértices a ser ordenado.
// - p: Índice do primeiro elemento da sub-sequência.
// - r: Índice do último elemento da sub-sequência.
inline void quick_sort(Vertex<int>** graph, int p, int r) {
    if (p < r) {
        // Realiza a partição
        int q = partition(graph, p, r);
        // Chama o Quick Sort recursivamente para as sub-sequências
        quick_sort(graph, p, q);
        quick_sort(graph, q + 1, r);
    }
}

// Função de interface para o Quick Sort.
// Parâmetros:
// - graph: Array de ponteiros para vértices a ser ordenado.
// - n_vertex: Número de vértices no grafo.
inline void quick_sort(Vertex<int>**& graph, int n_vertex) {
    quick_sort(graph, 0, n_vertex - 1);
}


// Função para mesclar duas sub-sequências ordenadas em uma sequência ordenada.
// Parâmetros:
// - graph: Array de ponteiros para vértices a ser ordenado.
// - left: Índice do primeiro elemento da primeira sub-sequência.
// - mid: Índice do último elemento da primeira sub-sequência.
// - right: Índice do último elemento da segunda sub-sequência.
inline void merge(Vertex<int>** graph, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Criação de sub-arrays temporários para armazenar as sub-sequências
    Vertex<int>** left_arr = new Vertex<int>*[n1];
    Vertex<int>** right_arr = new Vertex<int>*[n2];

    // Copia os elementos para os sub-arrays temporários
    for (int i = 0; i < n1; i++) {
        left_arr[i] = graph[left + i];
    }
    for (int i = 0; i < n2; i++) {
        right_arr[i] = graph[mid + 1 + i];
    }

    int i = 0, j = 0, k = left;

    // Combina as sub-sequências ordenadas em uma sequência ordenada
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

    // Copia os elementos restantes, se houver, de ambas as sub-sequências
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

    // Libera a memória alocada para os sub-arrays temporários
    delete[] left_arr;
    delete[] right_arr;
}

// Função auxiliar para realizar o Merge Sort recursivamente.
// Parâmetros:
// - graph: Array de ponteiros para vértices a ser ordenado.
// - left: Índice do primeiro elemento da sub-sequência.
// - right: Índice do último elemento da sub-sequência.
inline void merge_sort_aux(Vertex<int>** graph, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        // Chama o Merge Sort recursivamente para as sub-sequências
        merge_sort_aux(graph, left, mid);
        merge_sort_aux(graph, mid + 1, right);
        // Combina as sub-sequências ordenadas
        merge(graph, left, mid, right);
    }
}

// Função de interface para o Merge Sort.
// Parâmetros:
// - graph: Array de ponteiros para vértices a ser ordenado.
// - n_vertex: Número de vértices no grafo.
inline void merge_sort(Vertex<int>** graph, int n_vertex) {
    // Chama a função auxiliar do Merge Sort para todo o array
    merge_sort_aux(graph, 0, n_vertex - 1);
}


// Função para realizar o Heap Sort em um array de vértices.
// Parâmetros:
// - graph: Array de ponteiros para vértices a ser ordenado.
// - n_vertex: Número de vértices no grafo.
inline void heap_sort(Vertex<int>**& graph, int n_vertex) {
    // Criação de um objeto Heap com capacidade igual ao número de vértices
    Heap heap(n_vertex);

    // Insere os vértices na heap
    for (int i = 0; i < n_vertex; ++i) {
        Tuple tuple = {graph[i]->get_color(), graph[i]->get_id()};
        heap.insert(tuple);
    }

    // Criação de um array temporário para armazenar os vértices ordenados
    Vertex<int>** sortedGraph = new Vertex<int>*[n_vertex];

    // Reorganiza o array sortedGraph com base na ordem de remoção da heap
    for (int i = 0; i < n_vertex; ++i) {
        int index = (int) heap.remove().id;
        sortedGraph[i] = graph[index];
    }

    // Copia os vértices ordenados de volta para o array original graph
    for (int i = 0; i < n_vertex; ++i) {
        graph[i] = sortedGraph[i];
    }

    // Libera a memória alocada para o array temporário sortedGraph
    delete[] sortedGraph;
}



// Função para ordenar um grafo representado por um array de ponteiros para vértices
// com base em um método de ordenação escolhido.
// Parâmetros:
// - graph: Array de ponteiros para vértices a ser ordenado.
// - n_vertex: Número de vértices no grafo.
// - sort_option: Opção de ordenação ('b' para Bubble Sort, 's' para Selection Sort,
//   'i' para Insertion Sort, 'q' para Quick Sort, 'p' para Heap Sort,
//   'm' para Merge Sort, 'y' para Count Sort, ou qualquer outra opção para Bubble Sort).
inline void sort(Vertex<int>**& graph, int n_vertex, char sort_option) {
    // Seleciona o algoritmo de ordenação com base na opção fornecida
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
            // Se a opção fornecida não for reconhecida, utiliza o Bubble Sort como padrão
            bubble_sort(graph, n_vertex);
            break;
    }
}



#endif //SORT_HPP
