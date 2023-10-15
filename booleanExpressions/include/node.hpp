#ifndef NODE_HPP
#define NODE_HPP

/**
 * @brief Estrutura que representa um nó em uma fila (queue) ou pilha (stack).
 * @tparam T O tipo de dados armazenado no nó.
 */
template<typename T>
struct Node {
    T data;      // Dados armazenados no nó.
    Node<T>* link;  // Ponteiro para o próximo nó na fila ou pilha.

    /**
     * @brief Construtor que inicializa um nó com os dados e um link para o próximo nó.
     * @param data Os dados a serem armazenados no nó.
     * @param link O ponteiro para o próximo nó na estrutura.
     */
    Node(T data, Node<T>* link) : data(data), link(link) {
    }
};


#endif