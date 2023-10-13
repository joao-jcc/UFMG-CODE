#ifndef STACK_HPP
#define STACK_HPP

#include <stdlib.h>
#include <iostream>
#include "node.hpp"

class ExceptionEmptyStack{};

template<typename T>
class Stack {
    public:
        Stack() {
            _header = nullptr;
            _size = 0;
        };
        ~Stack() {
            clear();
        };

        void add(T data) {
            Node<T>* new_node = new Node<T>(data, _header);
            new_node->link = _header;
            _header = new_node;
            ++_size;
        };

        T pop() {
            if (empty()) {
                throw(ExceptionEmptyStack());
            }

            Node<T>* del_node = _header;
            T data = _header->data;
            _header = _header->link;
            delete del_node;
            --_size;
            return data;
        }

        T peek() const {
            if (empty()) {
                throw(ExceptionEmptyStack());
            }
            return _header->data;
        }

        // deleta toda a pilha
        void clear() {
            while (_header != nullptr) {
                pop();
            }
        }

        bool empty() const{
            return _size == 0;
        };

        unsigned get_size() {
            return _size;
        }


    private:
        Node<T>* _header;
        unsigned _size;
};

#endif