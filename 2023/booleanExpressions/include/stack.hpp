#ifndef STACK_HPP
#define STACK_HPP

#include <stdlib.h>
#include <iostream>
#include "node.hpp"

/**
 * @brief Lança uma exceção quando a pilha está vazia.
 */
class ExceptionEmptyStack{};

/**
 * @brief Classe que representa uma pilha (stack) de elementos genéricos.
 * @tparam T O tipo de dados dos elementos na pilha.
 */
template<typename T>
class Stack {
public:
    /**
     * @brief Construtor que inicializa uma pilha vazia.
     */
    Stack() {
        _header = nullptr;
        _size = 0;
    };

    /**
     * @brief Destrutor que limpa todos os elementos da pilha.
     */
    ~Stack() {
        clear();
    };

    /**
     * @brief Adiciona um elemento ao topo da pilha.
     * @param data O elemento a ser adicionado à pilha.
     */
    void add(T data) {
        Node<T>* new_node = new Node<T>(data, _header);
        new_node->link = _header;
        _header = new_node;
        ++_size;
    };

    /**
     * @brief Remove e retorna o elemento no topo da pilha.
     * @return O elemento removido do topo da pilha.
     * @throws ExceptionEmptyStack se a pilha estiver vazia.
     */
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

    /**
     * @brief Retorna o elemento no topo da pilha sem removê-lo.
     * @return O elemento no topo da pilha.
     * @throws ExceptionEmptyStack se a pilha estiver vazia.
     */
    T peek() const {
        if (empty()) {
            throw(ExceptionEmptyStack());
        }
        return _header->data;
    }

    /**
     * @brief Remove todos os elementos da pilha.
     */
    void clear() {
        while (_header != nullptr) {
            pop();
        }
    }

    /**
     * @brief Verifica se a pilha está vazia.
     * @return true se a pilha estiver vazia, false caso contrário.
     */
    bool empty() const{
        return _size == 0;
    };

    /**
     * @brief Retorna o tamanho atual da pilha.
     * @return O tamanho da pilha.
     */
    unsigned get_size() {
        return _size;
    }

private:
    Node<T>* _header;  // Ponteiro para o topo da pilha.
    unsigned _size;   // Tamanho atual da pilha.
};


#endif