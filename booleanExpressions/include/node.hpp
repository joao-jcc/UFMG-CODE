#ifndef NODE_HPP
#define NODE_HPP

template<typename T>
struct Node {
    T data;
    Node<T>* link;

    Node(T data, Node<T>* link) : data(data), link(link) {

    }
};


#endif