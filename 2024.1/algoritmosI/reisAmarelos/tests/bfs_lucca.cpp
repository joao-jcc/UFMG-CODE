#include <algorithm>
#include <queue>
#include <set>
#include <stack>
#include <stdio.h>
#include <vector>

#define INF 0x3f3f3f3f

using namespace std;

typedef pair<int, int> node;  //(Pesos, Vertices)

struct tuple3{
    int custo;
    int destino;
    int turno_visitado;

    bool operator<(const tuple3& outro) const{
        return custo < outro.custo; // Order by distance from minor to greater
    };
};

struct comparetuple3{
    bool operator()(tuple3 const& t1, tuple3 const& t2){
        if(t1.custo != t2.custo) {
            return t1.custo > t2.custo;
        } 
        else if(t1.turno_visitado != t2.turno_visitado){
            return t1.turno_visitado < t2.turno_visitado;
        } 
        else{
            return t1.destino > t2.destino;
        }
    };
};

class Graph{
    private:
        int _num_vertices;
        vector<vector<node>> _grafo;
        vector<int> _posicao_monstro;   // [0]->posição do 1° monstro dado na entrada , [1]->posição do 2° monstro dado na entrada, ...
        /*
        _posicao_monstro[0] = 6
        _posicao_monstro[1] = 7
        ordem dada pela entrada
        */
        vector<vector<int>> monsters_path;

        // Para fazer BFS:
        int _num_turnos;
        int _num_monstros;
        vector<vector<int>> _inverso; // grafo transposto
        vector<int> _distancia;        
        vector<int> _parente;
    
    public:
        Graph(int vertices, int turnos, int recursos, int inimigos){
            _num_vertices = vertices;
            _grafo.resize(vertices);
            _posicao_monstro.resize(inimigos, -1); // dimensão J
            monsters_path.resize(inimigos);

            // Para BFS
            _num_turnos = turnos;
            _num_monstros = inimigos;
            _inverso.resize(vertices);
            _distancia.resize(vertices, -1);
            _parente.resize(vertices, -1);
        };

        int lendo_entrada(int arestas, int num_monstros){
            for(int i=0; i < num_monstros; ++i){
                int temp;
                if((scanf(" %d", &temp) != 1) || temp <= 0 || temp > _num_vertices){
                    return 1; // Falha na leitura
                }
                _posicao_monstro[i] = temp; // no seu caso é p
            }

            for (int i=0; i < arestas; ++i){ // Adicionar arestas:
                int u, v, peso; 

                if(scanf(" %d %d %d", &u, &v, &peso) != 3 || u < 0 || v < 0){
                    return 1; // Falha na leitura
                }

                _grafo[u-1].push_back({v-1, peso}); // grafo direcionado
                // Pegar o grafo transposto Gt sem pesos para fazer BFS simples da parte dos monstros
                _inverso[v-1].push_back(u-1);
                // Resolver problema que monstros tem uma predileção por caminhos lexicograficamente pequenos:
                sort(_inverso[v-1].begin(), _inverso[v-1].end());
            }

            // loops
            for(int i=0; i < _num_vertices; ++i){
                _grafo[i].push_back(make_pair(1, i));
            }
            return 0;
        };

        void BFS(){
            int origem = 0; // pq vértice 1 está na posição 0
            // No construtor foi inicializado todas as distâncias e pais como -1

            queue<int> fila; //armazenar os vértices a serem visitados na BFS.
            fila.push(origem);
            _distancia[origem] = 0; //distância do vértice de origem para ele mesmo como 0

            vector<bool> visitado(_num_vertices, false);

            visitado[origem] = true;

            while(!fila.empty()){ // enquanto houver vértices a serem visitados
                //Retiramos o primeiro vértice da fila q e o armazenamos em u.
                int u = fila.front(); 
                fila.pop();

                for(int v : _inverso[u]){ // Iteramos sobre todos os vizinhos ao vértice u
                    if (!visitado[v]){ //verificamos se sua distância ainda não foi definida
                        visitado[v] = true; 
                        _distancia[v] = _distancia[u] + 1; // Se v ainda não foi visitado, atualizamos sua distância como a distância do vértice u mais 1
                        _parente[v] = u; // definimos o pai do vértice v como o vértice u
                        fila.push(v); // Adicionamos o vértice v à fila q, pois precisamos visitar seus vizinhos na próxima iteração do loop.
                    }
                    else if(_distancia[v] == _distancia[u] + 1 && _parente[v] > u){
                        _parente[v] = u;
                    }
                }
            }

            for (int i = 0; i < _num_monstros; i++) {
                int atual = _posicao_monstro[i] - 1; // Vértice 6 tem indice 5

                for (int v = atual; v != -1; v = _parente[v]){
                    monsters_path[i].push_back(v + 1);
                }
            }

            for (int i = 0; i < _num_monstros; i++){
                // Printar o comprimento do caminho do monstro i:
                int comp = monsters_path[i].size();
                printf("%d", comp);
                for(int t = 0; t < comp; t++){
                    // Printar o caminho do monstro i:
                    printf(" %d", monsters_path[i][t]);
                }
                printf("\n");
            }
        };
};

int main(){
    int vertices, arestas; // n° espaços no mapa, n° coneões no mapa
    int num_monstros, max_turno, RecursosPorTurno;

    if(scanf(" %d %d %d %d %d", &vertices, &arestas, &num_monstros, &max_turno, &RecursosPorTurno) != 5 || vertices < 0 || arestas < 0){
        return 1; // Falha na leitura, encerrando o programa
    }

    Graph g(vertices, max_turno, RecursosPorTurno, num_monstros);
       
    if(g.lendo_entrada(arestas, num_monstros) == 1){
        return 1;
    }

    g.BFS();
    printf("1\n");
    printf("1 ");
    for(int i=0; i < max_turno; i++){
        printf(" 1");
    }

    return 0;
}
