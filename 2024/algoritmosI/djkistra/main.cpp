#include <stdio.h>
#include <vector>
#include <queue>


using namespace std;
// par de interiros que representam arestas com pesos (.first: vertice y, .second: weight)
// ou vértice e sua distância da origem (.fisrt: distance, .second: vertice label)
typedef pair<int, int> node;


vector<vector<node> > graph;  // vetor de vetores
vector<int> distances;
vector<int> parents;
priority_queue<node, vector<node>, greater<node> > pq;

// função de leitura do grafo
void read(int m) {    
    for (int i=0; i < m; ++i) {
        // aresta de x para y com peso w
        int x, y, w; 
        scanf(" %d %d %d", &x, &y, &w);
        graph[x].push_back(make_pair(y, w));
    }
}

void print(int n) {
    for (int u=0; u < n; ++u) {
        printf("%d: ", u);
        for (node edge : graph[u]) {
            printf(" (%d %d)", edge.first, edge.second);
        }
        printf("\n");
    }
}

void init(bool print_flag=false) {
    // lendo o número de vértices do grafo e inicializando o grafo
    int n, m; 
    scanf(" %d %d", &n, &m);
    graph.resize(n);

    distances.assign(n, INT_MAX);
    parents.assign(n, -1);
    
    // declarando grafo como lista de adjacências: array de vetores
    read(m);
    if (print_flag) {print(n);};
}


void djkistra(int source) {
    pq.push(make_pair(0, source));
    distances[source] = 0;

    while(!pq.empty()) {
        //  vértice com distância mínima da fonte
        // rótulo do vértice em .second
        // distância do vértice à fonte em .first

        int u = pq.top().second;
        pq.pop();

        // loop thorugh all adjacent vertices of u
        for (node edge : graph[u]) {
            int v = edge.first;
            int w = edge.second;

            if (distances[v] > distances[u] + w) {
                distances[v] = distances[u] + w;
                pq.push(make_pair(distances[v], v));
                // u é pai de v
                parents[v] = u;
            }
        }
    }
}
 
void display_tree() {
    int i = 0;
    for (int parent: parents) {
        printf("%d %d\n", i, parent);
        ++i;
    }
}


int main(void) {
    
    init(true);
    djkistra(0);
    display_tree();
    return 0;
}