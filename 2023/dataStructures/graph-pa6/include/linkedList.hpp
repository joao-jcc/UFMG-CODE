#ifndef LINKED_LIST
#define LINKED_LIST

#include <iostream>

// Estrutura de dados para lista
typedef struct Node {
    int index;
    Node* next;

} Node;


class LinkedList {
    private:
        int _size;
        Node* _first;
        Node* _last;
    
    public:

        LinkedList();
        ~LinkedList();

        bool empty();

        void insert(int key);

        void remove_all();

        void print();

        int get_size() {
            return _size;
        }

};   


#endif