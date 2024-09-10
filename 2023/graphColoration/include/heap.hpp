//
// Created by João Costa on 03/11/23.
//

#ifndef HEAP_HPP
#define HEAP_HPP

#include <iostream>

// Define uma estrutura chamada Tuple com dois inteiros sem sinal: color e id
struct Tuple {
    unsigned color;
    unsigned id;
};


class Heap {

public:
    // Construtor: Aloca memória para o heap com um tamanho especificado
    Heap(int size);

    // Destrutor: Desaloca memória quando o objeto sai de escopo
    ~Heap();

    // Insere uma Tuple no heap
    void insert(Tuple tuple);

    // Remove e retorna a Tuple do topo do heap
    Tuple remove();

    // Verifica se o heap está vazio
    bool empty();

    // Imprime a estrutura do heap, parâmetros padrão para o nó raiz
    void print(int position=0, int level=0, int indentation=3);


private:
    // Função auxiliar: Obtém o índice do nó ancestral
    int _get_ancestral(int position);

    // Função auxiliar: Obtém o índice do nó sucessor à esquerda
    int _get_left_sucessor(int position);

    // Função auxiliar: Obtém o índice do nó sucessor à direita
    int _get_right_sucessor(int position);

    // Função auxiliar: Restaura a propriedade do heap movendo um nó para cima
    void _heapify_upper();

    // Função auxiliar: Restaura a propriedade do heap movendo um nó para baixo
    void _heapify_down();

    // Compara duas tuples com base em um critério específico
    bool criterium(Tuple tuple1, Tuple tuple2);

    // Troca os valores de duas tuples
    void swap(Tuple& tuple1, Tuple& tuple2);

    // Tamanho do heap
    int _size;

    // Array para armazenar os nós do heap
    Tuple* _node;

};

#endif //HEAP_HPP
