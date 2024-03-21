//
// Criado por João Costa em 26/11/23.
//

#include <iostream>
#include "matrix.hpp"
#include "segTree.hpp"
//#include "simpleVector.hpp"

int main(void) {

    // Tamanho da sequência e número de consultas
    int n, q;
    std::cin >> n >> q;

    // Inicializa a árvore de segmentos com tamanho n
    SegTree seg_tree(n);

    // Variável para armazenar a operação ('u' para update, 'q' para query)
    char operation;

    // Loop através de todas as consultas
    while(q--) {
        std::cin >> operation;

        // Se a operação for uma atualização ('u')
        if (operation == 'u') {
            // Índice da atualização
            int i;
            std::cin >> i;

            // Matriz para armazenar a atualização
            Matrix matrix(2, 2, false);
            matrix.read();

            // Atualiza a árvore de segmentos
            seg_tree.update(i, matrix, 1, 0, n-1);

        }

            // Se a operação for uma consulta ('q')
        else if (operation == 'q') {
            // Tempo de nascimento e morte, e coordenadas do ponto
            int born_time, death_time;
            Vector2D point;
            std::cin >> born_time >> death_time >> point.x >> point.y;

            // Realiza uma consulta na árvore de segmentos
            Matrix matrix = seg_tree.query(born_time, death_time, 1, 0, n-1);

            // Aplica a matriz ao ponto e imprime o resultado
            Vector2D new_point = matrix * point;
            new_point.print();

        }
    }

    return 0;
}
