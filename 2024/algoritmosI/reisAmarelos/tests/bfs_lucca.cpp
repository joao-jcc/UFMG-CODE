#include <stdio.h>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <limits.h>

using namespace std;
#define INF INT_MAX


typedef pair<int, int> node;

int N, M, J, T, K;
vector<vector<node> > graph;  

//Output
// colunas de 0 a T guardam o caminho do monstro
// coluna T+1 guarda o tamanho do caminho
vector<vector<int> > monsters_path; // N X T
stack<int> player_path;
int COST, TURN, WIN;

vector<int> monsters_initial;
vector<vector<int> > monsters_path_2; // N X T



// calcula a posição dos monstros ao longo dos turnos
void build_monsters_path(vector<vector <int> >& graph_t) {

    // bfs no grafo transposto
    vector<int> parents(N, -1);
    vector<bool> explored(N, false);
    vector<int> depths(N, INF);
    queue<int> frontier;
    // vértice de início/caravana
    depths[0] = 0; 
    explored[0] = true;
    frontier.push(0);

    while(!frontier.empty()) {
        int u = frontier.front(); frontier.pop();
        // observa-se os vértices adjacentes a u
        for (int v: graph_t[u]) {
            // caso v não tenha sido explorado
            if (!explored[v]) {
                // u é pai de v
                parents[v] = u;
                depths[v] = depths[u] + 1;
                explored[v] = true;
                frontier.push(v);
            }
            else if (depths[v] == depths[u] + 1 && parents[v] > u) {
                parents[v] = u;
            }
        }
    }

    for (int i=0; i < J; ++i) {
        int current = monsters_initial[i] - 1;

        for (int v = current; v != -1; v = parents[v]) {
            monsters_path_2[i].push_back(v+1);
        }

    }

    // loop por todas as posições iniciais de monstros
    for (int i=0; i < N; ++i) {
        if (monsters_path[i][T+1] == -1) {continue;}
        // não há caminho do monstro para a caravana
        if (depths[i] == INF){continue;}
        // mosntro tem profundidade d entao o caminho tem comprimento d+1
        monsters_path[i][T+1] = depths[i]+1;
        // há monstro na posição inicial i e há caminho para caravana
        int vertice = parents[i];
        for (int turn=1; turn < depths[i]+1; ++turn) {
            monsters_path[i][turn] = vertice;
            vertice = parents[vertice];
        }
    }
}   


// função que incializa as variáveis globais 
void init() {
    if (scanf(" %d %d %d %d %d", &N, &M, &J, &T, &K) != 5 || N < 0 || M < 0 || J < 0 || T < 0 || K < 0) {return;}
    
    monsters_initial.resize(J, -1);
    monsters_path.resize(N, vector<int>(T+2, -1));
    monsters_path_2.resize(J, vector<int>());
    for (int j=0; j < J; ++j) {
        int p;
        if ((scanf(" %d", &p) != 1) || p <= 0 || p > N) {return;}
        
        monsters_initial[j] = p;

        monsters_path[p-1][T+1] = 1; // caminho do monstro tem comprimento minimo 1
        monsters_path[p-1][0] = p-1; // mosntro no turno 0
        // se na coluna t+1 não há monstro então temos vamor -1 
    }

    // ler grafo/mapa com arestas ponderadas
    vector<vector <int> > graph_t(N, vector<int>());
    graph.resize(N);
    for (int i=0; i < M; ++i) {

        int x, y, w;         // aresta de x para y com peso w

        if (scanf(" %d %d %d", &x, &y, &w) != 3 || x < 0 || y < 0 || w < 0) {return;}
        --x; --y; // vértices diminúidos de 1

        graph[x].push_back(make_pair(w, y)); 
        graph_t[y].push_back(x);
        // Resolver problema que monstros tem uma predileção por caminhos lexicograficamente pequenos:
        sort(graph_t[y].begin(), graph_t[y].end());

    }

    // loops
    for (int i=0; i < N; ++i) {
        graph[i].push_back(make_pair(1, i));
    }

    build_monsters_path(graph_t);
}

int main(void) {
    
    init();
    printf("LUCCA\n");
    for (int i = 0; i < J; i++){
        // Printar o comprimento do caminho do monstro i:
        int comp = monsters_path_2[i].size();
        printf("%d", comp);
        for(int t = 0; t < comp; t++){
            // Printar o caminho do monstro i:
            printf(" %d", monsters_path_2[i][t]);
        }
        printf("\n");
    }

    return 0;
}
