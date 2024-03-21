// SegTree.hpp

#ifndef SEGTREE_HPP
#define SEGTREE_HPP

#include "matrix.hpp"

// Definição da classe SegTree
class SegTree {
public:
    // Construtor da árvore de segmentos com o tamanho especificado
    SegTree(int size);

    // Destrutor
    ~SegTree();

    // Obtém o tamanho da árvore de segmentos
    int get_size();

    // Constrói a árvore de segmentos recursivamente a partir do array de matrizes
    Matrix build(int p, int l, int r, Matrix* array);

    // Realiza uma consulta na árvore de segmentos para o intervalo [a, b]
    Matrix query(int a, int b, int p, int l, int r);

    // Atualiza a árvore de segmentos com uma nova matriz na posição i
    Matrix update(int i, const Matrix& x, int p, int l, int r);

    // Imprime os elementos de um nó específico da árvore de segmentos
    void print_node(int position);

private:
    // Tamanho da árvore de segmentos
    int _size;

    // Array que armazena os elementos da árvore de segmentos
    Matrix* seg_array;
};

#endif
