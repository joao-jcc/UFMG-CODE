#include "stack.hpp"

Stack::Stack() {
    _header = nullptr;
    _size = 0;
}

Stack::~Stack() {
    delete_all();
}

void Stack::add(char c) {
    _header = new Node(c, _header);
    ++_size;
}

char Stack::pop() {
    if (_header == nullptr) {
        std::cout << "ExceptionEmptyStack from Stack::pop!" << std::endl;
        throw(ExceptionEmptyStack());

    }

    char data = _header->data;
    
    Node* pop_node = _header;
    _header = _header->link;

    delete pop_node;
    --_size;

    return data;
}

char Stack::get() const {
    if (_header == nullptr) {
        std::cout << "ExceptionEmptyStack from Stack::get!" << std::endl;
        throw(ExceptionEmptyStack());
    }

    return _header->data;
}

void Stack::delete_all() {    
    while (_header != nullptr) {
        Node* del_node = _header;
        _header = _header->link;

        delete del_node;
    }
}


void Stack::print() {
    std::cout << "---STACK---" << std::endl;
    Node* temp = _header;
    while(temp != nullptr) {
        std::cout << temp->data << " " << temp->link << std::endl;
        temp = temp->link;
    }
}


bool Stack::empty() {
    return _size == 0;
}