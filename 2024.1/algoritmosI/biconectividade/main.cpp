#include <vector>
#include <stdio.h>

using namespace std;

void read_graph(vector<vector<int> >& graph) {
    // lendo o número de vértices do grafo
    int n_vertex; scanf(" %d", &n_vertex);

    graph.resize(n_vertex);
    
    for (int i=0; i < n_vertex; ++i) {
        
        // grau do vértice i
        int degree; scanf("%d ", &degree);
        graph[i].resize(degree);
        // leitura dos vizinhos j do vértice i
        for (int j=0; j<degree; ++j) {
            int neigh; scanf(" %d", &graph[i][j]);
        }
    }
}


void print_graph(vector<vector<int> >& graph) {
    
    for (int i = 0; i < graph.size(); ++i) {
        printf("%d: ", i);
        for (int j = 0; j < graph[i].size(); ++j) {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
}


void DFS(vector<vector<int> >& graph) {
    
}


int main(void) {

    // declarando grafo como lista de adjacências: array de vetores
    vector<vector<int> > graph;
    read_graph(graph);
    print_graph(graph);

    

    return 0;
}