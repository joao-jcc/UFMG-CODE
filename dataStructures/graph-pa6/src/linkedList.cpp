#include "linkedList.hpp"

LinkedList::LinkedList() {
    _size = 0;
    _first = nullptr;
    _last = nullptr;
}

LinkedList::~LinkedList() {
    std::cout << "DELETING LINKED LIST" << std::endl;
    remove_all();
}

bool LinkedList::empty() {
    return _size == 0;
}

void LinkedList::insert(int index) {
    
    Node* new_node = new Node{index, nullptr};

    if (empty()) {
        _last = _first = new_node;
        ++_size;

        return;
    }

    _last->next = new_node;
    _last = new_node;
    ++_size;
}

void LinkedList::remove_all() {
    Node* aux = _first;
    while (_first) {
        _first = _first->next;
        delete aux;
        aux = _first;
    }

    _first = _last = nullptr;
    _size = 0;
}

void LinkedList::print() {
    Node* aux = _first;

    while (aux) {
        std::cout << aux->index << " ";
        aux = aux->next;
    }
    std::cout << "" << std::endl;
}