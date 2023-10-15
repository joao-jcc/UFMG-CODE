#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <iostream>
#include "utils.hpp"
#include "node.hpp"

/**
 * @brief Lança uma exceção quando a fila está vazia.
 */
class ExceptionEmptyQueue{};

/**
 * @brief Classe que representa uma fila (queue) de elementos genéricos.
 * @tparam T O tipo de dados dos elementos na fila.
 */
template<typename T>
class Queue {
public:
    /**
     * @brief Construtor que inicializa uma fila vazia.
     */
    Queue() {
        _first = nullptr;
        _last = nullptr;
        _size = 0;
    };

    /**
     * @brief Destrutor que limpa todos os elementos da fila.
     */
    ~Queue() {
        clear();
    };

    /**
     * @brief Adiciona um elemento à fila.
     * @param data O elemento a ser adicionado à fila.
     */
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

    /**
     * @brief Remove e retorna o elemento na parte frontal da fila.
     * @return O elemento removido da fila.
     * @throws ExceptionEmptyQueue se a fila estiver vazia.
     */
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

    /**
     * @brief Retorna o elemento na parte frontal da fila sem removê-lo.
     * @return O elemento na parte frontal da fila.
     * @throws ExceptionEmptyQueue se a fila estiver vazia.
     */
    T peek() const {
        if (empty()) {
            throw(ExceptionEmptyQueue());
        }
        return _first->data;
    }

    /**
     * @brief Remove todos os elementos da fila.
     */
    void clear() {
        while (_first != nullptr) {
            pop();
        }
    }

    /**
     * @brief Verifica se a fila está vazia.
     * @return true se a fila estiver vazia, false caso contrário.
     */
    bool empty() const {
        return _size == 0;
    };

    /**
     * @brief Retorna o tamanho atual da fila.
     * @return O tamanho da fila.
     */
    unsigned get_size() {
        return _size;
    }

private:
    Node<T>* _first;  // Ponteiro para o primeiro elemento da fila.
    Node<T>* _last;   // Ponteiro para o último elemento da fila.
    unsigned _size;  // Tamanho atual da fila.
};

#endif