#include "graph.hpp"
#include "flow.hpp"

// Função principal: executa a construção do grafo, cálculo do fluxo máximo,
// e exibe os resultados.
int main() {
    // Cria um grafo a partir da entrada padrão.
    Graph ggr;

    // Calcula o fluxo máximo e outras métricas relacionadas.
    Flow flow(ggr);
    flow.print(); // Exibe os resultados do fluxo.

    return 0;
}
