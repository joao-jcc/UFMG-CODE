#include "bfs.hpp"
#include <vector>
#include <queue>
#include <stack>


BFS::BFS(const Graph& graph)
    : capital(-1),
      capitalCost(INT_MAX),
      allParents(std::vector<std::vector<int>>(graph.N, std::vector<int>(graph.N, -1))),
      graph(graph) {
        _findCapital();
}


InfoBFS BFS::_bfs(int start) {
    // inicialização das estruras de dados da bfs(start)
    int N = graph.N;
    std::vector<bool> explored(N, false);
    std::vector<int> depths(N, 0);
    std::vector<int> parents(N, -1);

    std::queue<int> s; s.push(start); explored[start] = true;
    int cost = 0; int nExplored = 1;
    while (!s.empty()) {
        // loop por cada vizinho não explorado de v
        int v = s.front(); s.pop();
        for (int u : graph.g[v]) {
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
    int N = graph.N;
    std::vector<bool> candidates(N, true); // todos os vértices são candidatos em potencial
    capitalDepths = std::vector<int>(N, -1);

    for (int v=0; v < N; ++v) {

        InfoBFS info = _bfs(v);
        
        // v não acessa todo o grafo: seus descendentes não podem ser capital
        if (info.nExplored != N) {
            for (int u=0; u < N; ++u) {candidates[u] =  ! info.explored[u];}
        }
        // v acessa todo o grafo e tem custo menor que a capital anterior
        else if (info.cost < capitalCost) {
            capital = v; capitalCost = info.cost; capitalDepths = info.depths;
        }
    }  
}


std::vector<int> BFS::findMinPath(int start, int end) {
    // caminho mínimo entre dois vértices quaisquer: incluindo start e end
    std::stack<int> pathInv; pathInv.push(end); int u = end;
    while(allParents[start][u] != -1) {
        u = allParents[start][u];
        pathInv.push(u);
    }

    if (u != start) {printf("Não há caminho válido!\n"); exit(1);}

    std::vector<int> path; 
    while (!pathInv.empty()) {path.push_back(pathInv.top()); pathInv.pop();}

    return path;
}

void BFS::print() {printf("%s\n", graph.indexToName[capital].c_str());}