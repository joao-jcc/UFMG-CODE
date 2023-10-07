#ifndef STACK_HPP
#define STACK_HPP

#include <stdlib.h>
#include <iostream>

typedef struct Node {
    char data;
    Node* link;

    Node(char c, Node* ptr) {
        data = c;
        link = ptr;
    }

} Node;


class ExceptionEmptyStack {};

class Stack {
    public:
        Stack();
        ~Stack();

        void add(char c);

        char pop();
        char get() const;

        // deleta toda a pilha
        void delete_all();

        bool empty();

        void print();

    private:
        Node* _header;
        unsigned _size;
};


#endif