#include "unionFind.hpp"

UnionFind::UnionFind(int quantidade_subconjuntos) {
    subconjuntos = new Subconjunto[quantidade_subconjuntos];
    tamanho = quantidade_subconjuntos;

    for (int i = 0; i < quantidade_subconjuntos; i++) {
        subconjuntos[i].representante = i;
        subconjuntos[i].rank = 0;
    }
}


UnionFind::~UnionFind() {
    delete[] subconjuntos;
}

void UnionFind::Make(int x) {
    subconjuntos[x].representante = x;
    subconjuntos[x].rank = 0;
}

int UnionFind::Find(int x) {
    return subconjuntos[x].representante;
}

void UnionFind::Union(int x, int y) {
    int representante_x = Find(x);
    int representante_y = Find(y);

    if (representante_x == representante_y) {
        return;
    }

    if (subconjuntos[representante_x].rank < subconjuntos[representante_y].rank) {
        subconjuntos[representante_x].representante = representante_y;
        subconjuntos[representante_y].rank += subconjuntos[representante_x].rank;

        for (int i = 0; i < tamanho; ++i) {
            if (subconjuntos[i].representante == representante_x) {
                subconjuntos[i].representante = representante_y;
            }
        }
    } else {
        subconjuntos[representante_y].representante = representante_x;
        subconjuntos[representante_x].rank += subconjuntos[representante_y].rank;

        for (int i = 0; i < tamanho; ++i) {
            if (subconjuntos[i].representante == representante_y) {
                subconjuntos[i].representante = representante_x;
            }
        }
    }
}
