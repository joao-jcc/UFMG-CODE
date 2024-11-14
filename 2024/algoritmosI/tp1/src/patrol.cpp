#include <vector>
#include "patrol.hpp"

Patrol::Patrol(BFS& bfs_, DFS& dfs_, Graph& graph_)
    : bfs(bfs_), dfs(dfs_), graph(graph_), nPatrols(0), 
    patrolsPath(std::vector<std::vector<int>>()) {
        _patrolAll();
    }

void Patrol::_patrol(int battalion) {
        // patrulhamento para um batalhão específico
        std::vector<int> solution;
        // todas as arestas da SCC do batalhão
        std::vector<bool> edges = dfs.sccEdges[dfs.components[battalion]];  

        std::vector<bool> exploredEdges(edges.size(), false);

        int currentNode = battalion;
        int flag = true;
        while (flag) {
            flag=false;
            for (int i=0; i < edges.size(); ++i) {
                // aresta pertence a componente e não foi explorada
                if (edges[i] && !exploredEdges[i]) {
                    
                    // siga o caminho do vertice corrente até a aresta v --> u
                    int v = i / graph.N; int u = i % graph.N; 
                    
                    std::vector<int> path = bfs.findMinPath(currentNode, v); path.push_back(u);
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

        int end = solution.back();
        if (!edges[end * graph.N + battalion]) {
            std::vector<int> pathBack = bfs.findMinPath(end, battalion);
            
            // não inclui battalion/final; não inclui vertice final em solution prev
            for (int i=1; i < pathBack.size()-1; ++i) {solution.push_back(pathBack[i]);}
        }

        patrolsPath.push_back(solution); ++nPatrols;

}


void Patrol::_setEdgesTrue(std::vector<int>& path, std::vector<bool>& exploredEdges, std::vector<int>& solution) {
     // adiciona todas as arestas em path e todos os vértices na solução
     int v, u;
    for (int i = 0; i < path.size()-1; ++i) {
        v = path[i]; u = path[i+1];
        exploredEdges[v * graph.N + u] = true;
        solution.push_back(v);
    }
}

void Patrol::_patrolAll() {
    _patrol(bfs.capital);
    for (int battalion : dfs.battalions) {_patrol(battalion);}
}

void Patrol::print() {
    printf("%d\n", nPatrols);
    for (auto solution : patrolsPath) {
    for (int i = 0; i < solution.size() - 1; ++i) {
        printf("%s ", graph.indexToName[solution[i]].c_str());
    }
    printf("%s\n", graph.indexToName[solution.back()].c_str());
    }
  
}