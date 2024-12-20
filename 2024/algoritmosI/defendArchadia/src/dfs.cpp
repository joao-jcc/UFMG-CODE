#include <iostream>
#include <vector>
#include <stack>
#include "dfs.hpp"
#include "bfs.hpp"

// Construtor: inicializa os componentes e executa o algoritmo de Kosaraju para encontrar SCCs
DFS::DFS(const Graph& graph) : nComponents(0), graph(graph)  {
    components = std::vector<size_t>(graph.N, UNDEFINED);
    _kosaraju(); // Encontra SCCs usando o algoritmo de Kosaraju
    _genEdgesSCC(); // Gera arestas entre os SCCs
}

// Realiza uma DFS padrão no grafo para determinar a ordem de término dos nós
void DFS::_dfs(size_t start, std::vector<bool>& explored) {
    explored[start] = true;
    for (size_t neighbor : graph.g[start]) {
        if (!explored[neighbor]) {
            _dfs(neighbor, explored);
        }
    }
    deathOrder.push(start); // Armazena o nó na pilha quando todos os vizinhos são explorados
}

// Realiza uma DFS no grafo transposto para identificar os SCCs
void DFS::_dfsSCC(size_t start, std::vector<bool>& explored) {
    explored[start] = true;
    components[start] = nComponents; // Marca o nó com o número do componente atual
    for (size_t neighbor : graph.gt[start]) {
        if (!explored[neighbor]) {
            _dfsSCC(neighbor, explored);
        }
    }
}

// Algoritmo de Kosaraju para identificar SCCs em duas passagens
void DFS::_kosaraju() {
    size_t N = graph.N;
    std::vector<bool> explored(N, false);

    // Primeira passagem: executa DFS no grafo original para determinar a ordem de término
    for (size_t v = 0; v < N; ++v) {
        if (!explored[v]) {
            _dfs(v, explored);
        }
    }

    // Segunda passagem: executa DFS no grafo transposto para identificar os SCCs
    explored.assign(N, false); // Reseta o vetor de explorados

    while (!deathOrder.empty()) {
        size_t v = deathOrder.top();
        deathOrder.pop();
        if (!explored[v]) {
            _dfsSCC(v, explored); // Identifica um SCC completo
            ++nComponents; // Incrementa o contador de SCCs
        }
    }
}

// Gera arestas entre os SCCs no grafo condensado
void DFS::_genEdgesSCC() {
    size_t N = graph.N;
    sccEdges.assign(nComponents, std::vector<bool>(N * N, false)); // Inicializa matriz para SCCs
    for (size_t v = 0; v < N; ++v) {
        // Itera pelos vizinhos de v
        for (size_t u : graph.g[v]) {
            if (components[u] == components[v]) {
                sccEdges[components[v]][v * N + u] = true; // Marca a aresta entre SCCs
            }
        }
    }
}

// Encontra os batalhões mais próximos para cada SCC com base nas profundidades
void DFS::findBattalions(const std::vector<size_t>& capitalDepths, size_t capital) {
    for (size_t component = 0; component < nComponents; ++component) {
        size_t battalion = UNDEFINED; 
        size_t minDepth = UNDEFINED;

        for (size_t v = 0; v < graph.N; ++v) {
            if (components[v] == component && capitalDepths[v] < minDepth) {
                battalion = v; 
                minDepth = capitalDepths[v]; // Atualiza o batalhão mais próximo
            }
        }

        if (battalion == capital) { continue; } // Ignora se for a capital
        battalions.push_back(battalion); // Adiciona o batalhão ao resultado
    }
}

// Imprime o número de batalhões e seus nomes
void DFS::print() {
    std::cout << battalions.size() << '\n';
    for (size_t battalion : battalions) {
        std::cout << graph.indexToName[battalion] << '\n'; // Converte índice para nome
    }
}
