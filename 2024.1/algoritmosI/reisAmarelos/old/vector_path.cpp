#include <stdio.h>
#include <vector>
#include <queue>
#include <stack>
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

struct tuple4 {
    int distance;
    int vertice;
    int turn;
    std::vector<int> path;

    // Default constructor
    tuple4() : distance(0), vertice(0), turn(0), path(std::vector<int>()) {}

    // Constructor with parameters
    tuple4(int d, int v, int t, const std::vector<int> p) : distance(d), vertice(v), turn(t), path(p) {}

    // Define the custom comparator function
    bool operator<(const tuple4& other) const {
        return distance < other.distance; // Order by distance from minor to greater
    }
};

struct comparetuple4 {
    bool operator()(tuple4 const& t1, tuple4 const& t2)
    {
        return t1.distance > t2.distance;
    }
};


int N, M, J, T, K; 
vector<vector<node> > graph;  
vector<vector<int> > graph_t; 
vector<bool> monsters;
vector<vector<bool> > monsters_turn_position;
int max_monster_turn;

// OUTPUT
int COST, TURN;
vector<int> PLAYER_PATH;

// função que incializa as variáveis globais 
void init() {

    scanf(" %d %d %d %d %d", &N, &M, &J, &T, &K);
    monsters_turn_position.resize(N, std::vector<bool>(N, false));
    monsters.resize(N, false);
    max_monster_turn = 0;

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
    // loops
    for (int i=0; i < N; ++i) {
        graph[i].push_back(make_pair(1, i));
    }
}

bool lack_rsc(int distance, int turn) {
    return distance > (turn+1) * K;
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
        // há monstro na posição inicial i e há caminho para caravana
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
        int u = frontier.front(); frontier.pop();
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


/*
[x] loops
[x] monstros
[x] turnos
[x] recursos
*/
bool djkistra(int source) {
    priority_queue<tuple4, vector<tuple4>, comparetuple4> pq;
    
    vector<vector<int> > min_distances(N, vector<int>(T, INF));
    vector<vector<bool> > explored(N, vector<bool>(T, false));
    int u, distance, turn;

    min_distances[0][0] = 0;
    explored[0][0] = true;
    vector<int> path; path.push_back(1);
    pq.push(tuple4(0, source, 0, path)); // distance, vertice, turn

    while(!pq.empty()) {

        tuple4 tuple = pq.top(); pq.pop();

        // excedeu número de turnos máximo
        if (tuple.turn > T) {continue;}

        u = tuple.vertice;
        distance = tuple.distance;
        turn = tuple.turn;
        path = tuple.path;

        explored[u][turn] = true;
        // solução encontrada
        if (u == N-1) {
            COST = distance; TURN = turn;
            PLAYER_PATH = path;
            return true;
        } 


        // loop por todos os vértice adjacentes a u
        for (node edge : graph[u]) {
    
            int w = edge.first;
            int v = edge.second;
            
            // monstros: olhando turno atual e futuro
            int indice = turn > max_monster_turn ? max_monster_turn : turn;
            if (monsters_turn_position[indice][v] || monsters_turn_position[indice+1][v]) {continue;}
            
            int hyp_distance = distance + w; // distância candidata
            if (!explored[v][turn+1]) { 
                // recursos insuficientes
                if (lack_rsc(hyp_distance, turn+1)) {continue;}

                min_distances[v][turn+1] = hyp_distance;
                vector<int> new_path = path;
                new_path.push_back(v+1);
                pq.push(tuple4(min_distances[v][turn+1], v, turn+1, new_path));
            

            } else if (min_distances[v][turn+1] > hyp_distance) {
                if (lack_rsc(hyp_distance, turn+1)) {continue;}
                min_distances[v][turn+1] = hyp_distance;
                vector<int> new_path = path;
                new_path.push_back(v+1);
                pq.push(tuple4(min_distances[v][turn+1], v, turn+1, new_path));

            }

            // loop
            vector<int> new_path = path;
            new_path.push_back(u+1);
            pq.push(tuple4(min_distances[u][turn+1], u, turn+1, new_path));
        }
    }

    COST = distance; TURN = turn;
    return false;
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

        printf("=== GRAFO T ===\n");
        for (int u=0; u < N; ++u) {
            printf("%d: ", u);
            for (int v : graph_t[u]) {
                printf(" %d", v);
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

    if(djkistra(0)) {
        printf("1\n");
    } else {printf("0\n");};
    printf("%d %d\n", COST, TURN);

    for (int i=0; i < TURN+1; i++) {
        printf("%d ", PLAYER_PATH[i]);
    }
    printf("\n");

    return 0;
}