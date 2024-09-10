// SegTree.cpp

#include "segTree.hpp"

// Construtor da árvore de segmentos com o tamanho especificado
SegTree::SegTree(int size) : _size(size) {
    // Aloca o array de matrizes com o dobro do tamanho da árvore de segmentos
    seg_array = new Matrix[4 * size];

    // Inicializa cada elemento do array com a matriz identidade
    for (int i = 0; i < 4 * size; ++i) {
        seg_array[i] = Matrix(); // identity
    }
}

// Destrutor
SegTree::~SegTree() {
    // Desaloca o array de matrizes
    delete[] seg_array;
}

// Constrói a árvore de segmentos recursivamente a partir do array de matrizes
Matrix SegTree::build(int p, int l, int r, Matrix* array) {
    if (l == r) {
        return seg_array[p] = array[l];
    }

    int m = (l + r) / 2; // Ponto médio (arredondado para baixo)

    // Constrói os filhos e calcula o resultado
    Matrix left_child = build(2 * p, l, m, array);
    Matrix right_child = build(2 * p + 1, m + 1, r, array);
    Matrix result = left_child * right_child;

    // Atualiza o nó atual na árvore
    return seg_array[p] = result;
}

// Realiza uma consulta na árvore de segmentos para o intervalo [a, b]
Matrix SegTree::query(int a, int b, int p, int l, int r) {
    // Intervalo disjunto
    if (r < a || l > b) {
        return Matrix(); // identity
    }

    // Intervalo totalmente contido
    if (a <= l && r <= b) {
        return seg_array[p];
    }

    int m = (l + r) / 2;

    // Faz consultas nos filhos e calcula o resultado
    Matrix left_child = query(a, b, 2 * p, l, m);
    Matrix right_child = query(a, b, 2 * p + 1, m + 1, r);
    Matrix result = left_child * right_child;

    return result;
}

// Atualiza a árvore de segmentos com uma nova matriz na posição i
Matrix SegTree::update(int i, const Matrix& x, int p, int l, int r) {
    // Posição fora do intervalo
    if (i < l || r < i) {
        return seg_array[p];
    }

    // Folha da árvore, atualiza o valor
    if (l == r) {
        return seg_array[p] = x;
    }

    int m = (l + r) / 2;

    // Atualiza os filhos e recalcula o resultado
    Matrix left_child = update(i, x, 2 * p, l, m);
    Matrix right_child = update(i, x, 2 * p + 1, m + 1, r);

    return seg_array[p] = left_child * right_child;
}

// Obtém o tamanho da árvore de segmentos
int SegTree::get_size() {
    return _size;
}

// Imprime os elementos de um nó específico da árvore de segmentos
void SegTree::print_node(int position) {
    seg_array[position].print();
}
