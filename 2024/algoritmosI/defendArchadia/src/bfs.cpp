#include "bfs.hpp"
#include <vector>
#include <queue>


BFS::BFS(const Graph& graph)
    : capital(UNDEFINED),
      capitalCost(UNDEFINED),
      allParents(std::vector<std::vector<size_t>>(graph.N, std::vector<size_t>(graph.N, UNDEFINED))),
      graph(graph) {
        _findCapital();
}


InfoBFS BFS::_bfs(size_t start) {
    // inicialização das estruras de dados da bfs(start)
    size_t N = graph.N;
    std::vector<bool> explored(N, false);
    std::vector<size_t> depths(N, 0);
    std::vector<size_t> parents(N, UNDEFINED);

    std::queue<size_t> s; s.push(start); explored[start] = true;
    size_t cost = 0; size_t nExplored = 1;
    while (!s.empty()) {
        // loop por cada vizinho não explorado de v
        size_t v = s.front(); s.pop();
        for (size_t u : graph.g[v]) {
            if (!explored[u]) {
                // atualize estado de u: parent, depth, explored
                s.push(u);
                depths[u] = depths[v]+1;
                parents[u] = v;

                explored[u] = true;
                cost += depths[u]; ++nExplored;
            }
        }
    }

    // armazena árvore dessa instância da bfs
    allParents[start] = parents;

    return InfoBFS{cost, nExplored, explored, depths};
}


void BFS::_findCapital() {
    size_t N = graph.N;
    std::vector<bool> candidates(N, true); // todos os vértices são candidatos em potencial
    capitalDepths = std::vector<size_t>(N, UNDEFINED);

    for (size_t v=0; v < N; ++v) {

        InfoBFS info = _bfs(v);
        
        // v não acessa todo o grafo: seus descendentes não podem ser capital
        if (info.nExplored != N) {
            for (size_t u=0; u < N; ++u) {candidates[u] =  ! info.explored[u];}
        }
        // v acessa todo o grafo e tem custo menor que a capital anterior
        else if (info.cost < capitalCost) {
            capital = v; capitalCost = info.cost; capitalDepths = info.depths;
        }
    }  
}


std::vector<size_t> BFS::findMinPath(size_t start, size_t end) {
    // caminho mínimo entre dois vértices quaisquer: incluindo start e end
    std::stack<size_t> pathInv; pathInv.push(end); size_t u = end;
    while(allParents[start][u] != UNDEFINED) {
        u = allParents[start][u];
        pathInv.push(u);
    }

    if (u != start) {printf("Não há caminho válido!\n"); exit(1);}

    std::vector<size_t> path; 
    while (!pathInv.empty()) {path.push_back(pathInv.top()); pathInv.pop();}

    return path;
}

void BFS::print() {
    std::cout << graph.indexToName[capital] << '\n';
}