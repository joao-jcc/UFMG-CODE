#include "listaAdjacencia.hpp"


ListaAdjacencia::ListaAdjacencia() {
    _size = 0;
    _first = nullptr;
    _last = nullptr;
}

ListaAdjacencia::~ListaAdjacencia() {
    std::cout << "DELETANDO LISTA DE ADJACÊNCIA" << std::endl;
    remove_all();
}

bool ListaAdjacencia::empty() {
    return _size == 0;
}

void ListaAdjacencia::insert() {
    if (empty()) {
        _last = _first = new NodeAdj{LinkedList(), 0, nullptr};
        ++_size;

        return;
    }

    NodeAdj* new_node = new NodeAdj{LinkedList(), _last->key + 1, nullptr};

    _last->next = new_node;
    _last = new_node;
    ++_size;
}

void ListaAdjacencia::insert(int key, int index) {
    NodeAdj* aux = _first;
    while (aux->key != key) {
        aux = aux->next;
    }

    aux->list.insert(index);
}

void ListaAdjacencia::remove_all() {
    NodeAdj* aux = _first;
    while (_first) {
        _first = _first->next;

        aux->list.remove_all();
        delete aux;

        aux = _first;
    }

    _first = _last = nullptr;
    _size = 0;
}

void ListaAdjacencia::print() {
    NodeAdj* aux = _first;

    while (aux) {
        aux->list.print();
        std::cout << "" << std::endl;

        aux = aux->next;
    }

}