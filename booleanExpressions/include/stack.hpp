#ifndef STACK_HPP
#define STACK_HPP

#include <stdlib.h>
#include <iostream>
#include <memory>

class ExceptionEmptyStack{};

template<typename T>
typedef struct Node {
    T data;
    Node<T>* link;

    Node(T data, Node<T>* link) : data(data), link(link) {

    }

} Node;


template<typename T>
class Stack {
    public:
        Stack();
        ~Stack() {
            clear();
        };

        void add(T data) {
            Node<T>* new_node = new Node<T>(data, _header);
            ++_size;
        };

        void pop() {
            if (empty) {
                throw(ExceptionEmptyStack());
            }
            Node<T>* del_node = _header;
            _header = _header->link
            delete del_node;
            --_size;
        }

        T peek() const {
            if (empty) {
                throw(ExceptionEmptyStack());
            }
            return _header->data;
        }

        // deleta toda a pilha
        void clear() {
            Node<T>* del_node = _header;
            _header = _header->link;

            delete del_node;
        }

        bool empty() {
            _size == 0;
        };


    private:
        Node<T>* _header;
        unsigned _size;
};


#endif