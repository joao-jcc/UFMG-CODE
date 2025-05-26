#include <iostream>
#include <vector>

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define INF 0x3f3f3f3f

int PS;
vector<int> costs, values;
vector<vector<int> > mem;

void solve() {
    // Leitura
    int N, C, R;
    cin >> N; costs.assign(N+1, 0); values.assign(N+1, 0);
    
    for (int i=0; i < N; ++i) cin >> values[i+1] >> costs[i+1];
    cin >> C >> R;
    // Itens:  0 ... N; Capacidade: 0 ... C.
    mem.assign(N+1, vector<int>(C+1, 0));

    // DP
    for (int item=1; item <= N; ++item) {
        int v = values[item], w = costs[item];
        for (int capacity=0, s1, s2; capacity <= C; ++capacity) {
            if (w > capacity) mem[item][capacity] = mem[item-1][capacity];
            else mem[item][capacity] = max(mem[item-1][capacity-w] + v, mem[item-1][capacity]);          
        }
    }

    if (mem[N][C] >= R) cout << "Missao completada com sucesso" << endl;
    else cout << "Falha na missao" << endl;
}


int main(void) {_
    cin >> PS; while(PS--) {solve();}
    
    exit(0);
}