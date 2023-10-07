#ifndef LISTA_ADJACENCIA
#define LISTA_ADJACENCIA

#include "linkedList.hpp"

typedef struct NodeAdj {
    LinkedList list;
    int key;
    NodeAdj* next;
} NodeAdj;

class ListaAdjacencia {
    public:
        ListaAdjacencia();

        ~ListaAdjacencia();

        bool empty();

        void insert();

        void insert(int key, int index);

        void remove_all();

        void print();

        int get_size() {
            return _size;
        }

        NodeAdj* get_first() {
            return _first;
        }


    private:
        int _size;
        NodeAdj* _first;
        NodeAdj* _last;

};

#endif