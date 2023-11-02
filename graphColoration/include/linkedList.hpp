//
// Created by João Costa on 28/10/23.
//

#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include <cassert>

class ExceptionEmptyList: public std::exception {
    public:

        ExceptionEmptyList(const char* message) : _message(message){

        }

        const char* what() const throw() override {
            return _message;
        };

    private:
        const char* _message;
};


// Generic Node for LinkedList
template<typename T>
struct Node {
    T data;
    Node<T>* next;
};

// Generic LinkedList
template <typename T>
class LinkedList {
    static int _count;
    public:
        LinkedList() : _first(nullptr), _last(nullptr), _size(0), _id(_count), _color(0) {
            ++_count;
        };

        ~LinkedList() {
            std::cout << "Destroying List" << std::endl;
            Node<T>* temp = _first;
            while (temp != nullptr) {
                _first = _first->next;
                delete temp;
                temp = _first;
                --_size;
            }

            _first = _last = nullptr;
            assert(_size == 0);
        };

        bool empty() {
            return _size == 0;
        }

        // by the end
        void append(T data) {
            Node<T> * node = new Node<T>{data, nullptr};

            if (empty()) {
                _first = _last = node;
            } else {
                _last->next = node;
                _last = node;
            }

            ++_size;
        }

        // by the first
        T pop_front() {
            if(empty()) {
                throw(ExceptionEmptyList("LinkedList is empty!"));
            }

            T data = _first->data;

            Node<T>* del_node = _first;
            _first = _first->next;

            delete del_node;
            --_size;

            return data;
        }

        T get_item(int index) {
            Node<T>* temp = _first;

            for (int i=1; i < index; ++i) {
                temp = temp->next;
            }

            return temp->data;
        }

        unsigned get_size() const {
            return _size;
        }

        unsigned get_id() const {
            return _id;
        }

        unsigned get_color() const {
            return _color;
        }

        void set_color(unsigned  color) {
            _color = color;
        }

        Node<T>* get_first() const {
            return  _first;
        }

        static int get_count() {
            return _count;
        }

    private:
        Node<T>* _first;
        Node<T>* _last;

        unsigned _size;
        unsigned _id;
        unsigned _color;

};


template<typename T>
int LinkedList<T>::_count = 0;

#endif
