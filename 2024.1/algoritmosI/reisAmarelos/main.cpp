#include <stdio.h>
#include <vector>
#include <queue>
#include <limits.h>

using namespace std;
#define INF INT_MAX

/*
node: (peso da aresta, vértice de destino) ou (distancia pata origem, vértice)
N: número de vértices no grafo
M: número de conexões no grafo
J: número de monstros
T: número máximo de turnos a serem jogados
K: número de recursos adquiridos por turno
graph: mapa do jogo, grafo ponderado
graph_t: mapa do jogo sem pesos para BFS da etapa dos monstros
monsters: indica a posição inicial dos monstros no turno 0
monsters_turn_position: posição dos monstros ao longo dos turnos até o turno onde não há mais mudança
resources: quantidade de recursos do jogador no turno corrente
*/
typedef pair<int, int> node;
int N, M, J, T, K; 
vector<vector<node> > graph;  
vector<vector<int> > graph_t; 
vector<bool> monsters;
vector<vector<bool> > monsters_turn_position;
int max_monster_turn;


// função que incializa as variáveis globais 
void init() {

    scanf(" %d %d %d %d %d", &N, &M, &J, &T, &K);
    monsters_turn_position.resize(N, std::vector<bool>(N, false));
    monsters.resize(N, false);
    max_monster_turn = -1;

    for (int j=0; j < J; ++j) {
        int p;
        scanf("%d", &p);
        monsters[p-1] = true; // vértice diminuído de 1
    }

    // ler grafo/mapa com arestas ponderadas
    graph.resize(N);
    graph_t.resize(N);
    for (int i=0; i < M; ++i) {

        int x, y, w;         // aresta de x para y com peso w
        scanf(" %d %d %d", &x, &y, &w);
        --x; --y; // vértices diminúidos de 1

        graph[x].push_back(make_pair(w, y)); 
        graph_t[y].push_back(x);

    }

    // adicionando ciclos
    // for (int i=0; i < N; ++i) {
    //     graph[i].push_back(make_pair(1, i));
    // }

}


// calcula a posição dos monstros ao longo dos turnos
void build_monsters_route(vector<int> parents, vector<int> depths) {
    // loop por todas as posições iniciais dos monstros
    for (int i=0; i < N; ++i) {
        if (!monsters[i]) {continue;}
        // não há caminho do monstro para a caravana
        if (depths[i] == INF){
            for (int turn=0; turn < N; ++turn) {
                monsters_turn_position[turn][i] = true; // monstro parado
            }
            continue;
        }
            // há monstro na posição inicial i
        int vertice = i;
        int turns = depths[i] + 1;
        for (int turn=0; turn < turns; ++turn) {
            monsters_turn_position[turn][vertice] = true;
            vertice = parents[vertice];
        }

        max_monster_turn = turns > max_monster_turn ? turns : max_monster_turn;
        --max_monster_turn;
    }
}


// calcula os caminhos mínimos dos monstros à caravana
void bfs() {

    // estruturas da bfs
    vector<int> parents(N, -1);
    vector<bool> explored(N, false);
    vector<int> depths(N, INF);
    queue<int> frontier;
    // vértice de início/caravana
    depths[0] = 0;
    frontier.push(0);
    while(!frontier.empty()) {
        int u = frontier.front();
        frontier.pop();
        explored[u] = true;

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
        }
    }

    build_monsters_route(parents, depths);

}


bool djkistra(int source) {
    priority_queue<node, vector<node>, greater<node> > pq;
    vector<int> distances(N, 1000);
    vector<int> parents(N, -1);

    int resources = K; // quantidade de recursos igual a K no turno 0
    int turn = 0;

    pq.push(make_pair(0, source));
    distances[source] = 0;

    while(!pq.empty() && turn <= T) {
        //  vértice com distância mínima da fonte
        // rótulo do vértice em .second
        // distância do vértice à fonte em .first

        int u = pq.top().second;
        pq.pop();
        printf("==== turn: %d ====\n (u=%d)\n", turn, u);
        if (u == N-1) {
            while (u != -1) {
                printf("%d ", u);
                u = parents[u];
            }
            printf("\n");
            return true;
            } // solução encontrada

        // loop thorugh all adjacent vertices of u

        for (node edge : graph[u]) {
            int v = edge.second;
            int w = edge.first;
            
            // se a distância é menor e os recursos a suportam
            int hyp_distance = distances[u] + w;
            
            // consigo acessa v a partir de u
            if ((distances[v] > hyp_distance) && (resources >= hyp_distance)) {

                // se há monstro em v e no turno dado vá para o próximo vértice
                if (monsters_turn_position[turn+1][v]) {
                    continue;
                }
                distances[v] = hyp_distance;
                
                
                printf("new node: (%d, %d)\n", hyp_distance, v);
                // neste ponto já se sabe a distância real de v
                pq.push(make_pair(distances[v], v));
                // u é pai de v
                parents[v] = u;
            }
        }

        resources += K; ++turn;
    }

    return false; // não há solução
}


// função para printar o grafo ponderado
void print(bool graph_flag=false, bool monsters_turn_flag=false) {

    if (graph_flag) {
        printf("=== GRAFO ===\n");
        for (int u=0; u < N; ++u) {
            printf("%d: ", u);
            for (node edge : graph[u]) {
                printf(" (%d %d)", edge.first, edge.second);
            }
            printf("\n");
        }
    }
    
    if (monsters_turn_flag) {
        for (int i=0; i < N; ++i) {
            printf("turn %d: ", i);
            for (int monster : monsters_turn_position[i]) {
                printf("%d ", monster);
            }
            printf("\n");
        }
        printf("max monster turn: %d\n", max_monster_turn);
    }
}


int main(void) {
    
    init();
    bfs();
    print(true, true);
    if (djkistra(0)) {printf("ok!");}

    return 0;
}


/*
Próxima etapa:
    calcular os caminhos mínimos dos mosntros até a caravana.
    Juntar isso em uma estrutura matricial ou de adjacência com turnos x posicao de mosntros
*/