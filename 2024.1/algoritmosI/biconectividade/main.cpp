#include <vector>
#include <stdio.h>

using namespace std;

void read_graph(vector<int> graph[], int n_vertex) {    
    for (int i=0; i < n_vertex; ++i) {
        
        // grau do vértice i
        int degree; scanf(" %d", &degree);
        graph[i].resize(degree);


        // leitura dos vizinhos j do vértice i
        for (int j=0; j<degree; ++j) {
            int neigh; scanf(" %d", &graph[i][j]);
        }
    }
}


void print_graph(vector<int> graph[], int n_vertex) {
    
    for (int i = 0; i < n_vertex; ++i) {
        printf("%d: ", i);
        for (int j = 0; j < graph[i].size(); ++j) {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
}

void print_dfs_result(int n_vertex, vector<int>& born_times, vector<int>& end_times, vector<int>& parents, vector<int>& colors) {
    printf("Vertex\tColor\tParent\tTimes\n");
    for (int i = 0; i < n_vertex; ++i) {
        printf("%d\t%d\t%d\t%d / %d\n", i, colors[i], parents[i], born_times[i], end_times[i]);
    }
}



void DFS_visit(vector<int> graph[], int& u, int& time, vector<int>& born_times, 
vector<int>& end_times, vector<int>& parents, vector<int>& colors) {
    
    ++time;
    colors[u] = 1; // vértice u descoberto colorido de cinza
    born_times[u] = time; // tempo de descoberta de u

    // percorre-se todos os vértices adjacentes a u
    for (int v : graph[u]) {

        // vértice adjacente é branco
        if (colors[v] == 0) {

            // u é pai de v
            parents[v] = u;
            // chama-se DFS_visit para o novo vértice descoberto v
            DFS_visit(graph, v, time, born_times, end_times, parents, colors);

        }
    }
    
    // todas as arestas de u foram percorridas
    ++time;
    end_times[u] = time;
    colors[u] = 2; // colore-se u de preto

}



void DFS(vector<int> graph[], int n_vertex, int& time, vector<int>& born_times, 
vector<int>& end_times, vector<int>& parents, vector<int>& colors) {
    
    // para cada vértice u
    for (int u=0; u < n_vertex; ++u) {
            // se o vértice adjacente é branco
            if (colors[u] == 0) {
                DFS_visit(graph, u, time, born_times, end_times, parents, colors);
            }
        }
    }


int main(void) {
    
    // lendo o número de vértices do grafo
    int n_vertex; scanf(" %d", &n_vertex);
    // declarando grafo como lista de adjacências: array de vetores

    vector<int> graph[n_vertex];
    read_graph(graph, n_vertex);
    

    // arrays auxiliares DFS
    vector<int> born_times(n_vertex, 0); // tempos de início zerados
    vector<int> end_times(n_vertex, 0); // tempos de fim zerados
    vector<int> parents(n_vertex, -1); // -1 indica que o vértice é raiz da árvore de predecessores
    vector<int> colors(n_vertex, 0); // 0: branco, 1: cinza, 2: preto
    int time = 0;

    DFS(graph, n_vertex, time, born_times, end_times, parents, colors);

    // Print the DFS result
    print_dfs_result(n_vertex, born_times, end_times, parents, colors);


    return 0;
}