#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <iostream>
#include "utils.hpp"
#include "node.hpp"


class ExceptionEmptyQueue{};

template<typename T>
class Queue {
public:
    Queue() {
        _first = nullptr;
        _last = nullptr;
        _size = 0;
    };

    ~Queue() {
        clear();
    };

    void add(T data) {
        Node<T>* new_node = new Node<T>(data, nullptr);
        if (empty()) {
            _first = new_node;
            _last = new_node;
        } else {
            _last->link = new_node;
            _last = new_node;
        }
        ++_size;
    };

    T pop() {
        if (empty()) {
            throw(ExceptionEmptyQueue());
        }

        Node<T>* del_node = _first;
        T data = _first->data;
        _first = _first->link;
        delete del_node;
        --_size;

        if (_first == nullptr) {
            _last = nullptr;
        }

        return data;
    }

    T peek() const {
        if (empty()) {
            throw(ExceptionEmptyQueue());
        }
        return _first->data;
    }

    void clear() {
        while (_first != nullptr) {
            pop();
        }
    }

    bool empty() const {
        return _size == 0;
    };

    unsigned get_size() {
        return _size;
    }

private:
    Node<T>* _first;
    Node<T>* _last;
    unsigned _size;
};

#endif
