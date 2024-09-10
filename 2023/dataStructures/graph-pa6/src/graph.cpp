#include "graph.hpp"

Grafo::Grafo() {

}

Grafo::~Grafo() {
    std::cout << "Deletando Grafo!" << std::endl;
    vertices.remove_all();
}


void Grafo::InsereVertice() {
    vertices.insert();
}


void Grafo::InsereAresta(int v, int w) {
    vertices.insert(v, w);
}

int Grafo::QuantidadeVertices() {
    return vertices.get_size();
}

int Grafo::QuantidadeArestas() {
    NodeAdj* temp = vertices.get_first();
    int degrees = 0;

    while(temp != nullptr) {
        degrees += temp->list.get_size();
        temp = temp->next;
    }

    return degrees/2;
}


int Grafo::GrauMinimo() {
    NodeAdj* temp = vertices.get_first();
    int grau = temp->list.get_size();

    while (temp != nullptr) {
        int size = temp->list.get_size();
        grau = size < grau ? size : grau;
        temp = temp->next;
    }

    return grau;
}

int Grafo::GrauMaximo() {
    NodeAdj* temp = vertices.get_first();
    int grau = temp->list.get_size();

    while (temp != nullptr) {
        int size = temp->list.get_size();
        grau = size > grau ? size : grau;
        temp = temp->next;
    }

    return grau;
}

void Grafo::ImprimeVizinhos(int v) {
    NodeAdj* temp = vertices.get_first();

    while(temp->key != v) {
        temp = temp->next;
    }

    temp->list.print();
} 

