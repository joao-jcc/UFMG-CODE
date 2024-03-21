#include <iostream>
#include "heap.hpp"
#include "unionFind.hpp"

int main(void) {    

    int n_vertices;
    int n_arestas;

    std::cin >> n_vertices;
    std::cin >> n_arestas;


    Heap heap(n_arestas);
    for (int i=0; i < n_arestas; ++i) {
        int u, v, custo;
        std::cin >> u;
        std::cin >> v;
        std::cin >> custo;
        heap.insert(Aresta{u, v, custo});
    }

    UnionFind union_find(n_vertices);
    int custo = 0, cont = 0;
    while(!heap.empty() && cont < n_vertices+1) {

        Aresta aresta = heap.remove();

        if (union_find.Find(aresta.u) != union_find.Find(aresta.v)) {
            union_find.Union(aresta.u, aresta.v);

            custo += aresta.custo;
            ++cont;

        }
    }

    std::cout << custo << std::endl;

    return 0;
}