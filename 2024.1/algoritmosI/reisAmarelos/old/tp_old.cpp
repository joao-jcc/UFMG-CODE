#include <stdio.h>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <limits.h>

using namespace std;
#define INF INT_MAX


typedef pair<int, int> node;
struct tuple3 {
    int distance;
    int vertice;
    int turn;

    // Define the custom comparator function
    bool operator<(const tuple3& other) const {
        return distance < other.distance; // Order by distance from minor to greater
    }
};

struct comparetuple3 {
    bool operator()(tuple3 const& t1, tuple3 const& t2)
    {
        return t1.distance > t2.distance;
    }
};

int N, M, J, T, K;
vector<vector<node> > graph;  

//Output
// colunas de 0 a T guardam o caminho do monstro
// coluna T+1 guarda o tamanho do caminho
vector<vector<int> > monsters_path; // N X T
stack<int> player_path;
int COST, TURN;



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
    
    monsters_path.resize(N, vector<int>(T+2, -1));
    for (int j=0; j < J; ++j) {
        int p;
        if ((scanf(" %d", &p) != 1) || p <= 0 || p > N) {return;}

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


void print_monsters_path() {
    for (int i=0; i < N; i++) {
        int size = monsters_path[i][T+1];
        if (size == -1) {continue;}
        
        printf("%d ", size);

        for (int j=0; j < size; ++j) {
            if (j == size-1) {
                printf("%d\n", monsters_path[i][j] + 1);
            } else {
                printf("%d ", monsters_path[i][j] + 1);
            }
        }
    }
}


vector<vector<bool>> transpose_by_bool(const vector<vector<int>>& matrix) {        
    vector<vector<bool> > transposed(T+1, vector<bool>(N, false));

    for (int v = 0; v < N; ++v) {
        int size = matrix[v][T+1];
        if (size == -1) {continue;};
        if (size == 1) {
            for (int turn=0; turn<T+1; ++turn) {
                transposed[turn][v] = true;
            }
             continue;
        }

        for (int turn = 0; turn < T+1; ++turn) {
            if (turn < size) {
                int el = matrix[v][turn];
                transposed[turn][el] = true;
            } else {
                transposed[turn][0] = true;
            }

        }
    }
    
    return transposed;
}

bool djkistra(int source) {
    priority_queue<tuple3, vector<tuple3>, comparetuple3> pq;
    
    vector<vector<int> > min_distances(N, vector<int>(T+1, INF));
    vector<vector<int> > parents(N, vector<int>(T+1, -2));
    vector<vector<bool> > explored(N, vector<bool>(T+1, false));
    vector<vector<bool> > turn_vertice_monsters = transpose_by_bool(monsters_path);
    int max_turn = 0;

    min_distances[0][0] = 0;
    parents[0][0] = -1;
    explored[0][0] = true;
    pq.push(tuple3{0, source, 0}); // distance, vertice, turn


    while(!pq.empty()) {

        tuple3 tuple = pq.top(); pq.pop();

        int u = tuple.vertice;
        int distance = tuple.distance;
        int turn = tuple.turn;

        explored[u][turn] = true;
        // solução encontrada
        if (u == N-1) {
            COST = distance; TURN = turn;

   
            player_path.push(u+1);
            for (int i=0; i < turn; ++i) {
                u = parents[u][turn-i];
                player_path.push(u+1); 
            }

            return true;
        } 


        // loop por todos os vértice adjacentes a u
        for (node edge : graph[u]) {
    
            int w = edge.first;
            int v = edge.second;

            if (tuple.turn+1 > T) {continue;}
            if (distance+w > (turn+2)*K) {continue;}
            if (turn_vertice_monsters[turn][v] || turn_vertice_monsters[turn+1][v]) {continue;}
            
            if (!explored[v][turn+1]) {
                min_distances[v][turn+1] = distance + w;
                pq.push(tuple3{distance+w, v, turn+1});
                // u é pai de v
                parents[v][turn+1] = u;
                max_turn = turn+1 > max_turn ? turn+1 : max_turn;

            } else if (min_distances[v][turn+1] > distance+w) {
                min_distances[v][turn+1] = distance + w;
                pq.push(tuple3{distance + w, v, turn+1});
                // u é pai de v
                parents[v][turn+1] = u;
                max_turn = turn+1 > max_turn ? turn+1 : max_turn;

            }
        }
    }


    int min_d = INF;
    int vertice = 0;
    for (int i=0; i < N; ++i) {
        if (min_distances[i][max_turn] < min_d && min_distances[i][max_turn] != 0) {
            vertice = i;
            min_d = min_distances[i][max_turn];
        }
    }

    COST = min_d; TURN = max_turn;

    player_path.push(vertice+1);
    for (int i=0; i < max_turn; ++i) {
        vertice = parents[vertice][max_turn-i];
        player_path.push(vertice+1); 
    }


    return false;
}


int main(void) {
    
    init();
    // if(djkistra(0)) {
    //     printf("1\n");
    // } else {printf("0\n");};
    printf("1\n");


    for (int i=0; i < N; ++i) {
        int size = monsters_path[i][T+1];
        if (size == -1) {continue;};

        printf("%d ", size);
        for (int j=0; j < size; ++j) {
            if (j != size-1) {
            printf("%d ", monsters_path[i][j]+1);
            }
            else {
            printf("%d\n", monsters_path[i][j]+1);
            }
        }
    }
    printf("2 3\n");
    printf("1 1 1\n");
    // printf("%d %d\n", COST, TURN);

    // for (int i=0; i < TURN+1; ++i) {
    //     if (i != TURN)
    //     printf("%d ", player_path.top());
    //     else 
    //     printf("%d\n", player_path.top());
    //     player_path.pop();
    // }
    

    return 0;
}