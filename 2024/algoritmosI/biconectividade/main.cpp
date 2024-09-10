#include <vector>
#include <stack>
#include <set>
#include <algorithm>
#include <stdio.h>


using namespace std;

// estruturas auxiliares para problema da articulação e clusters
vector<vector<int>> graph;  // vetor de vetores
vector<int> born; // tempo de descobrimento do vértice
vector<int> low; // mínimo tempo de nascimento alcançavel
stack<int> s; // pilha auxiliar ao problema de clusters

// resultados
vector<bool> links; // links de borda
set<set<int>> clusters; // set de sets que representam componentes biconexas

int time_ = 0; // timestamp
int links_count = 0;
int clusters_count = 0;

void output(int n) {
    // etapa de link de borda
    printf("%d\n", links_count);
    for (int i=0; i < n; ++i) {
        if (links[i]) {printf("%d\n", i+1);}
    }

    // etapa de componentes biconexas
    printf("%d\n", clusters_count);
    int i = 0;
    for (set<int> cluster : clusters) {
        int cluster_size = cluster.size();
        printf("%d %d", n+i+1, cluster_size);
        for (int v : cluster) {
            printf(" %d", v + 1);
        }
        ++i;
    
    printf("\n");
    }

    // etapa da floresta
    int forest_edges_count = 0;
    int forest_vertexs = clusters_count+links_count;

    struct tuple {int link; int id;};
    vector<tuple> forest_edges;

    for (int i=0; i < n; ++i) {

        if (!links[i]) {continue;}
        int j = 0;
        for (set<int> cluster : clusters)  {
            if (count(cluster.begin(), cluster.end(), i) > 0) {
                forest_edges.push_back(tuple{i+1, n+j+1});
                ++forest_edges_count;         
            };
            j++;  
        }
    }

    printf("%d %d", forest_vertexs, forest_edges_count);
    if (forest_edges_count > 0) {printf("\n");};


    for(int i=0; i < forest_edges_count; ++i) {
        printf("%d %d", forest_edges[i].link, forest_edges[i].id);
        if (i < forest_edges_count-1) {printf("\n");}; 
    }
}

// função de leitura do grafo
void read_graph(int m) {    
    for (int i=0; i < m; ++i) {
        // grau do vértice i
        int x, y; 
        if (scanf(" %d %d", &x, &y) != 2 || x < 0 || y < 0) {return;};
        graph[x-1].push_back(y-1);
        graph[y-1].push_back(x-1);
    }
}


void DFS_aux(int u, int parent) {
    
    born[u] = low[u] = ++time_; // tempo de descoberta de u
    s.push(u);
    int children = 0; // numero de filhos de u na árvore de precedencia
    
    // percorre-se todos os vértices adjacentes a u
    for (int v : graph[u]) {
        // vértice adjacente ainda não foi descoberto
        if (born[v] == 0) {
            // chama-se DFS_aux para o novo vértice descoberto v, cujo pai é u
            DFS_aux(v, u);

            low[u] = min(low[u], low[v]);

            if (born[u] <= low[v]) {
                // u é de corte
                if (parent != -1) {links[u] = true; ++links_count;}

                // cluster
                set<int> cluster;
                int y;

                do {
                    y = s.top();
                    s.pop();
                    cluster.insert(y);

                } while (y != v);
                cluster.insert(u);
                clusters.insert(cluster); ++clusters_count;
            }

            ++children;

        } else {
            // há aresta de retorno
            low[u] = min(low[u], born[v]);
        }
    }

    if (parent == -1 && children >= 2) {links[u] = true; ++links_count;}
}


void DFS(int n) {
    // para cada vértice u
    for (int u=0; u < n; ++u) {
        // se o vértice u ainda não foi descoberto
        if ( born[u] == 0 ) {
            DFS_aux(u, -1);
        }
    }
}


int main(void) {
    
    // lendo o número de vértices do grafo e inicializando o grafo
    int n, m; 
    if (scanf(" %d %d", &n, &m) != 2 || n < 0 || m < 0) {return 1;};
    graph.resize(n);
    
    // declarando grafo como lista de adjacências: array de vetores
    read_graph(m);

    // arrays auxiliares DFS
    born.resize(n, 0); // tempos de início zerados (indicam que vértices não foram descobertos)
    low.resize(n, 0); // mínimo tempo de nascimento alcançável
    links.resize(n, false);
    
    DFS(n); output(n);

    return 0;
}