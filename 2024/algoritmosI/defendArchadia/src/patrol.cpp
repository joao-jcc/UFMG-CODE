#include <vector>
#include "patrol.hpp"

Patrol::Patrol(BFS& bfs_, DFS& dfs_, Graph& graph_)
    : bfs(bfs_), dfs(dfs_), graph(graph_), nPatrols(0), 
    patrolsPath(std::vector<std::vector<size_t>>()) {
        _patrolAll();
    }

void Patrol::_patrol(size_t battalion) {
        // patrulhamento para um batalhão específico
        std::vector<size_t> solution;
        // todas as arestas da SCC do batalhão
        std::vector<bool> edges = dfs.sccEdges[dfs.components[battalion]];
        size_t edgesSize = edges.size();  

        std::vector<bool> exploredEdges(edgesSize, false);

        size_t currentNode = battalion;
        size_t flag = true;
        while (flag) {
            flag=false;
            for (size_t i=0; i < edgesSize; ++i) {
                // aresta pertence a componente e não foi explorada
                if (edges[i] && !exploredEdges[i]) {
                    
                    // siga o caminho do vertice corrente até a aresta v --> u
                    size_t v = i / graph.N; size_t u = i % graph.N; 
                    
                    std::vector<size_t> path = bfs.findMinPath(currentNode, v); path.push_back(u);
                    // adiciona todas as arestas de currentNode -->  v -> u
                    _setEdgesTrue(path, exploredEdges, solution);

                    currentNode = u; flag=true;
                }
            }
        }
        if (currentNode != battalion) {
            solution.push_back(currentNode);
        }

        if (solution.size() == 0) {return;}

        size_t end = solution.back();
        if (!edges[end * graph.N + battalion]) {
            std::vector<size_t> pathBack = bfs.findMinPath(end, battalion); size_t pathSize = pathBack.size();
            // não inclui battalion/final; não inclui vertice final em solution prev
            for (size_t i=1; i < pathSize-1; ++i) {solution.push_back(pathBack[i]);}
        }

        patrolsPath.push_back(solution); ++nPatrols;

}


void Patrol::_setEdgesTrue(std::vector<size_t>& path, std::vector<bool>& exploredEdges, std::vector<size_t>& solution) {
     // adiciona todas as arestas em path e todos os vértices na solução
     size_t v, u; size_t pathSize = path.size();
    for (size_t i = 0; i < pathSize-1; ++i) {
        v = path[i]; u = path[i+1];
        exploredEdges[v * graph.N + u] = true;
        solution.push_back(v);
    }
}

void Patrol::_patrolAll() {
    _patrol(bfs.capital);
    for (size_t battalion : dfs.battalions) {_patrol(battalion);}
}

void Patrol::print() {
    std::cout << nPatrols << '\n';
    for (const auto& solution : patrolsPath) {
        size_t solutionSize = solution.size();
        for (size_t i = 0; i < solutionSize - 1; ++i) {
            std::cout << graph.indexToName[solution[i]] << ' ';
        }
        std::cout << graph.indexToName[solution.back()] << '\n';
    }
}