#include <vector>
#include <stack>
#include <set>
#include <stdio.h>
#include <algorithm>

using namespace std;

// estruturas auxiliares para problema da articulação e clusters
vector<vector<int>> graph;  // vetor de vetores
vector<int> born; // tempo de descobrimento do vértice
vector<int> low; // mínimo tempo de nascimento alcançavel
stack<int> s; // pilha auxiliar ao problema de clusters

// resultados
set<int> links; // links de borda
vector<vector<int>> components; // vetor de vetores que representam componentes biconexas

int time_ = 0; // timestamp
int links_count = 0;
int clusters_count = 0;

bool lexico_compare(const std::vector<int>& a, const std::vector<int>& b) {
    return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
}

void output(int n) {
    // etapa de link de borda
    printf("%d\n", links_count);
    for (int link : links) {
        printf("%d\n", link+1);
    }

    // etapa de componentes biconexas
    std::sort(components.begin(), components.end(), lexico_compare);
    printf("%d\n", clusters_count);
    for (int i=0; i < clusters_count; ++i) {
        int cluster_size = components[i].size();
        printf("%d %d", n+i+1, cluster_size);
        for (int j=0; j < cluster_size; ++j) {
            printf(" %d", components[i][j] + 1);
        }
    
    printf("\n");
    }

    // etapa da floresta
    int forest_edges_count = 0;
    int forest_vertexs = clusters_count+links_count;

    struct tuple {int link; int id;};
    vector<tuple> forest_edges;
    for (int link : links) {
        for (int i=0; i < clusters_count; ++i)  {
            if (count(components[i].begin(), components[i].end(), link) > 0) {
                forest_edges.push_back(tuple{link+1, n+i+1});
                ++forest_edges_count;           
            };
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
                if (parent != -1) {links.insert(u);}

                // cluster
                vector<int> component;
                int y;

                do {
                    y = s.top();
                    s.pop();
                    component.push_back(y);

                } while (y != v);
                component.push_back(u);
                sort(component.begin(), component.end());
                components.push_back(component);

            }

            ++children;

        } else {
            // há aresta de retorno
            low[u] = min(low[u], born[v]);
        }
    }

    if (parent == -1 && children >= 2) {links.insert(u);}
}


void DFS(int n) {
    // para cada vértice u
    for (int u=0; u < n; ++u) {
        // se o vértice u ainda não foi descoberto
        if ( born[u] == 0 ) {
            DFS_aux(u, -1);
        }
    }

    links_count = links.size();
    clusters_count = components.size();
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

    DFS(n); output(n);

    return 0;
}